#pragma once
#include <string>
#include <exception>

class GoodreadsException : public std::exception
{
protected:
	std::string message;
public:
	GoodreadsException() = default;

	GoodreadsException(const std::string& message, int dummy = 0);

	const char* what() const noexcept;
};