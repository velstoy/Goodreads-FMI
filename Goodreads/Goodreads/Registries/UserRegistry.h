#pragma once
#include "../Users/User.h"

class UserRegistry
{
private:
	std::vector<std::shared_ptr<User>> users;
};

