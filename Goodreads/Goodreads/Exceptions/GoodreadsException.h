#pragma once
#include <string>
#include <exception>

class GoodreadsException : public std::exception
{
protected:
	std::string message;
public:
	GoodreadsException() = default;

	GoodreadsException(const std::string& message);

	const char* what() const noexcept override;
};