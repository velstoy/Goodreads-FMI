#include "UserRegistry.h"
#include "../Exceptions/UserAlreadyExistsException.h"


UserRegistry& UserRegistry::getInstance()
{
	static UserRegistry userRegistry;

	return userRegistry;
}

void UserRegistry::add(const std::shared_ptr<User> user)
{
	auto found = std::find_if(users.begin(), users.end(), [&](const std::shared_ptr<User> local) {return user->getUsername() == local->getUsername();});

	if (*found)
	{
		throw UserAlreadyExistsException(user->getUsername());
	}

	users.push_back(user);
}

void UserRegistry::remove(const std::string& username)
{
	std::erase_if(users, [&](const std::shared_ptr<User> user) {return user->getUsername() == username;});
}
