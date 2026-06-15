#include "CommandException.h"

CommandException::CommandException(const std::string& reason)
{
	message = reason;
}
