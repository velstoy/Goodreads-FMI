#pragma once
#include <string>

class Date
{
private:
	int day = 0;
	int month = 0;
	int year = 0;

	static bool is_leap(int year);
	static bool is_valid(int day, int month, int year);

public:
	Date(int day, int month, int year);

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	// Serialises as dd.mm.yyyy
	std::string toString() const;

	bool operator==(const Date& other) const;

	static Date today();

	// Parses a "dd.mm.yyyy" string. Throws InvalidDateException on bad input.
	static Date parse(const std::string& text);
};
