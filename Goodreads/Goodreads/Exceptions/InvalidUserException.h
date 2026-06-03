#pragma once
#include "GoodreadsException.h"

class InvalidUserException : public GoodreadsException
{
public:
	InvalidUserException(const std::string& type);
};
