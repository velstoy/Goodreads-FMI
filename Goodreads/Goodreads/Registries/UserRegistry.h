#pragma once
#include <vector>
#include <memory>
#include "../Users/User.h"

// Singleton store of every registered user.
class UserRegistry
{
private:
	std::vector<std::shared_ptr<User>> users;
	UserRegistry() = default;
public:
	UserRegistry(const UserRegistry&) = delete;
	UserRegistry& operator=(const UserRegistry&) = delete;

	static UserRegistry& getInstance();

	void add(const std::shared_ptr<User>& user);   // throws if the username is taken
	std::shared_ptr<User> find(const std::string& username) const;   // nullptr if absent
	const std::vector<std::shared_ptr<User>>& getAll() const;
	void clear();
};
