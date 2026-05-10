#pragma once
class Date
{
private:
	int day = 0;
	int month = 0;
	int year = 0;

	bool is_leap(int year) const;

	bool is_valid(int day, int month, int year) const;

public:
	Date(int day, int month, int year);

	int getDay() const;
	int getMonth() const;
	int getYear() const;
};

