#pragma once
class Date
{
private:
	int day, month, year;

	bool is_leap(int year) const;

	bool is_valid(int day, int month, int year) const;

public:
	Date(int day, int month, int year);

	int getDay() const;
	int getMonth() const;
	int getYear() const;
};

