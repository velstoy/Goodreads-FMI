#include "InvalidUserException.h"
#include <format>

InvalidUserException::InvalidUserException(const std::string& type)
{
	message = std::format("Invalid user of type {}!", type);
}
