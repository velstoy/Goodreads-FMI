#include "Data.h"
#include <iostream>

bool Date::is_leap(int year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::is_valid(int day, int month, int year) const
{
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	int max_days[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (day > max_days[month])
		return false;

	if (is_leap(year) && day > 28)
		return false;

	return true;
}

Date::Date(int day, int month, int year)
{
	if (!is_valid(day, month, year))
		throw std::invalid_argument(std::format("Invalid date with parameters {}/{}/{}", day, month, year));
}
