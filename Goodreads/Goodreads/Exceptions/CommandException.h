#pragma once
#include "GoodreadsException.h"

// Thrown for unknown commands or malformed command usage.
class CommandException : public GoodreadsException
{
public:
	CommandException(const std::string& reason);
};
