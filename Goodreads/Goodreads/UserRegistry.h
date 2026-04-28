#pragma once
#include "User.h"

class UserRegistry
{
private:
	std::vector<std::shared_ptr<User>> users;
};

