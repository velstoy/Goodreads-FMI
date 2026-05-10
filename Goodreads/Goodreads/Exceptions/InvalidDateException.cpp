#include "InvalidDateException.h"
#include <format>

InvalidDateException::InvalidDateException(const std::string& message, int day, int month, int year) : GoodreadsException(message), day(day), month(month), year(year)
{ }

const char* InvalidDateException::what()
{
	if (!message.empty())
		message += " ";

	message += std::format("Date arguments:\nday - {},\nmonth - {},\nyear - {}", day, month, year);

	return message.c_str();
}
