#include "GoodreadsException.h"

GoodreadsException::GoodreadsException(const std::string& message) : message(message)
{ 
	this->message = "Goodreads application error: " + message;
}

const char* GoodreadsException::what() const noexcept
{
	return message.c_str();
}
