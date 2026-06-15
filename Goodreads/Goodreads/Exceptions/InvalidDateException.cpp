#include "InvalidDateException.h"
#include <format>

InvalidDateException::InvalidDateException(const std::string& message, int day, int month, int year)
	: GoodreadsException(message), day(day), month(month), year(year)
{
	this->message += std::format(" Date arguments: day - {}, month - {}, year - {}.", day, month, year);
}
