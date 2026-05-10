#include "GoodreadsException.h"

GoodreadsException::GoodreadsException(const std::string& message) : message(message)
{ }

const char* GoodreadsException::what()
{
	message = "Goodreads application error: " + message;

	return message.c_str();
}
