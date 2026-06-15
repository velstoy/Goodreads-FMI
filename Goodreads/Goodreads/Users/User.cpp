#include "User.h"
#include <iostream>
#include <algorithm>
#include "../Exceptions/InvalidArgumentException.h"

constexpr size_t MIN_USERNAME = 6;
constexpr size_t MAX_USERNAME = 24;
constexpr size_t MIN_PASSWORD = 12;
constexpr size_t MAX_PASSWORD = 36;

const std::string& User::validate_username(const std::string& username)
{
	size_t size = username.size();
	if (size < MIN_USERNAME || size > MAX_USERNAME)
		throw InvalidArgumentException("username", MIN_USERNAME, MAX_USERNAME);
	return username;
}

const std::string& User::validate_password(const std::string& password)
{
	size_t size = password.size();
	if (size < MIN_PASSWORD || size > MAX_PASSWORD)
		throw InvalidArgumentException("password", MIN_PASSWORD, MAX_PASSWORD);

	bool hasLower = false, hasUpper = false, hasNonLetter = false;
	for (unsigned char c : password)
	{
		if (std::islower(c)) hasLower = true;
		else if (std::isupper(c)) hasUpper = true;
		if (!std::isalpha(c)) hasNonLetter = true;
	}

	if (!hasLower || !hasUpper || !hasNonLetter)
		throw InvalidArgumentException(
			"password must contain at least one lowercase letter, one uppercase letter and one non-letter symbol!");

	return password;
}

User::User(const std::string& username, const std::string& password, const Date& registrationDate)
	: username(validate_username(username)), password(validate_password(password)), registrationDate(registrationDate)
{
}

const std::string& User::getUsername() const { return username; }
bool User::checkPassword(const std::string& candidate) const { return password == candidate; }
const std::string& User::getPassword() const { return password; }
const Date& User::getRegistrationDate() const { return registrationDate; }

const std::vector<std::weak_ptr<User>>& User::getFollowers() const { return followers; }

bool User::isFollowedBy(const std::string& name) const
{
	for (const auto& weak : followers)
	{
		auto follower = weak.lock();
		if (follower && follower->getUsername() == name)
			return true;
	}
	return false;
}

void User::addFollower(const std::shared_ptr<User>& user)
{
	if (!user || isFollowedBy(user->getUsername()))
		return;
	followers.push_back(user);
}

void User::removeFollower(const std::string& name)
{
	std::erase_if(followers, [&](const std::weak_ptr<User>& weak) {
		auto f = weak.lock();
		return !f || f->getUsername() == name;
	});
}

bool User::isFriendWith(const User& other) const
{
	return isFollowedBy(other.username) && other.isFollowedBy(username);
}

void User::receiveMessage(std::unique_ptr<Message> message)
{
	inbox.push_back(std::move(message));
}

const std::vector<std::unique_ptr<Message>>& User::getInbox() const { return inbox; }

Message& User::getMessage(size_t index)
{
	if (index >= inbox.size())
		throw InvalidArgumentException("Message index is out of range!");
	return *inbox[index];
}

void User::removeMessage(size_t index)
{
	if (index >= inbox.size())
		throw InvalidArgumentException("Message index is out of range!");
	inbox.erase(inbox.begin() + index);
}

void User::help() const
{
	std::cout << "Available commands:\n"
		<< "  help                     - show this list\n"
		<< "  logout                   - log out of the current account\n"
		<< "  exit                     - save everything and quit\n";
}
