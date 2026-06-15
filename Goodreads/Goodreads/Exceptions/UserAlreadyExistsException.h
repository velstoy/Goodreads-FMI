#pragma once
#include <string>
#include "GoodreadsException.h"

class UserAlreadyExistsException : public GoodreadsException
{
public:
	UserAlreadyExistsException(const std::string& username);
};
