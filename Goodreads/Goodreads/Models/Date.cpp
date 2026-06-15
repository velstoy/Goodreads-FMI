#include "Date.h"
#include <chrono>
#include <format>
#include <sstream>
#include "../Exceptions/InvalidDateException.h"

bool Date::is_leap(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::is_valid(int day, int month, int year)
{
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return false;

	int max_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysInMonth = max_days[month - 1];

	if (month == 2 && is_leap(year))
		daysInMonth = 29;

	return day <= daysInMonth;
}

Date::Date(int day, int month, int year)
{
	if (!is_valid(day, month, year))
		throw InvalidDateException("Invalid date entry!", day, month, year);

	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

std::string Date::toString() const
{
	return std::format("{:02}.{:02}.{:04}", day, month, year);
}

bool Date::operator==(const Date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

Date Date::today()
{
	using namespace std::chrono;
	auto ymd = year_month_day(floor<days>(system_clock::now()));
	return Date((unsigned)ymd.day(), (unsigned)ymd.month(), (int)ymd.year());
}

Date Date::parse(const std::string& text)
{
	int d = 0, m = 0, y = 0;
	char dot1 = 0, dot2 = 0;
	std::istringstream in(text);
	in >> d >> dot1 >> m >> dot2 >> y;

	if (in.fail() || dot1 != '.' || dot2 != '.')
		throw InvalidDateException("Date must be in the format dd.mm.yyyy!", d, m, y);

	return Date(d, m, y);
}
