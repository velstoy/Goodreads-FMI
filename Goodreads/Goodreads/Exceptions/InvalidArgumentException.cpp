#include "InvalidArgumentException.h"
#include <format>

InvalidArgumentException::InvalidArgumentException(const std::string& message) : GoodreadsException(message)
{ }

InvalidArgumentException::InvalidArgumentException(const std::string & argumentName, size_t leftBoundary, size_t rightBoundary) : argumentName(argumentName), leftBoundary(leftBoundary), rightBoundary(rightBoundary)
{
	size_t argumentLength = argumentName.length();

	if (leftBoundary != 0 && rightBoundary != 0)
		message = std::format("The argument {} must be between {} and {} characters long!", argumentName, leftBoundary, rightBoundary);
	else if (leftBoundary != 0)
		message = std::format("The argument {} must be at least {} characters long!", argumentName, leftBoundary);
	else if (rightBoundary != 0)
		message = std::format("The argument {} must be no more than {} characters long!", argumentName, rightBoundary);
	else
		message = std::format("The argument {} is invalid!", argumentName);

	message += std::format(" Argument {} was {} characters long!", argumentName, argumentLength);
}

const char* InvalidArgumentException::what() const noexcept
{
	if (argumentName.empty())
		return message.c_str();
	else
		return GoodreadsException::what();
}
