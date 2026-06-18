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

	InvalidArgumentException(const std::string& argumentName, size_t leftBoundary, size_t rightBoundary);
};
