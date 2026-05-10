#pragma once
#include "GoodreadsException.h"

class InvalidArgumentException : public GoodreadsException
{
private:
	std::string argumentName;
	size_t leftBoundary = 0;
	size_t rightBoundary = 0;
public:
	InvalidArgumentException(const std::string& message);

	//Use this constructor only if you wish to use one of the 4 default messages for InvalidArgumentException.
	//Otherwise pass a custom message via the above constructor.
	InvalidArgumentException(const std::string& argumentName, size_t leftBoundary, size_t rightBoundary);

	const char* what() const noexcept override;
};