#pragma once
#include "../Users/User.h"

class UserRegistry
{
private:
	std::vector<std::shared_ptr<User>> users;

	UserRegistry() = default;
public:
	static UserRegistry& getInstance();

	void add(const std::shared_ptr<User> user);

	void remove(const std::string& username);
};

