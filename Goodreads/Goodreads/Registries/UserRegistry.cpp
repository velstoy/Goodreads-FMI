#include "UserRegistry.h"
#include <algorithm>
#include "../Exceptions/UserAlreadyExistsException.h"

UserRegistry& UserRegistry::getInstance()
{
	static UserRegistry instance;
	return instance;
}

void UserRegistry::add(const std::shared_ptr<User>& user)
{
	if (find(user->getUsername()) != nullptr)
		throw UserAlreadyExistsException(user->getUsername());
	users.push_back(user);
}

std::shared_ptr<User> UserRegistry::find(const std::string& username) const
{
	auto it = std::find_if(users.begin(), users.end(),
		[&](const std::shared_ptr<User>& u) { return u->getUsername() == username; });
	return it != users.end() ? *it : nullptr;
}

const std::vector<std::shared_ptr<User>>& UserRegistry::getAll() const { return users; }

void UserRegistry::clear() { users.clear(); }
