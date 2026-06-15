#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Models/Date.h"
#include "../Models/Message.h"

class User
{
private:
	std::string username;
	std::string password;
	Date registrationDate;
	std::vector<std::weak_ptr<User>> followers;     // users who follow me
	std::vector<std::unique_ptr<Message>> inbox;

	static const std::string& validate_username(const std::string& username);
	static const std::string& validate_password(const std::string& password);

public:
	User(const std::string& username, const std::string& password, const Date& registrationDate);

	const std::string& getUsername() const;
	bool checkPassword(const std::string& candidate) const;
	const std::string& getPassword() const;   // used by the persistence layer
	const Date& getRegistrationDate() const;

	// --- followers / friendship ---
	const std::vector<std::weak_ptr<User>>& getFollowers() const;
	bool isFollowedBy(const std::string& username) const;
	void addFollower(const std::shared_ptr<User>& user);
	void removeFollower(const std::string& username);
	// A friend is a user with whom you follow each other.
	bool isFriendWith(const User& other) const;

	// --- messaging ---
	void receiveMessage(std::unique_ptr<Message> message);
	const std::vector<std::unique_ptr<Message>>& getInbox() const;
	Message& getMessage(size_t index);   // throws on bad index
	void removeMessage(size_t index);

	virtual std::string getType() const = 0;   // "Reader" / "Author" / "Publisher"
	virtual void help() const;
	virtual ~User() = default;
};
