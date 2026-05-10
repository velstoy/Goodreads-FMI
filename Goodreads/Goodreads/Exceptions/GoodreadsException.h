#pragma once
#include <string>
#include <exception>

class GoodreadsException : public std::exception
{
protected:
	std::string message;
public:
	GoodreadsException(const std::string& message);

	virtual const char* what();
};