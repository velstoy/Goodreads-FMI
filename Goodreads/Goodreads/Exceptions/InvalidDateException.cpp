#include "InvalidDateException.h"
#include <format>

InvalidDateException::InvalidDateException(const std::string& message, int day, int month, int year) : GoodreadsException(message), day(day), month(month), year(year)
{ 
	if (this->message.empty())
		this->message += " ";
	this->message += std::format("Date arguments:\nday - {},\nmonth - {},\nyear - {}", day, month, year);
}

const char* InvalidDateException::what() const noexcept
{
	return message.c_str();
}
