#pragma once
#include "GoodreadsException.h"

class InvalidDateException : public GoodreadsException
{
private:
	int day = 0;
	int month = 0;
	int year = 0;
public:
	InvalidDateException(const std::string& message, int day, int month, int year);

	const char* what() override;
};