#pragma once
#include "GoodreadsException.h"

class CommandException : public GoodreadsException
{
public:
	CommandException(const std::string& reason);
};
