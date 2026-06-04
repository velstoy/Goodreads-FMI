#include "Reader.h"

Reader::Reader(const std::string& username, const std::string& password, const Date& registrationDate, const std::optional<Date>& birthday)
	: User(username, password, registrationDate), birthday(birthday)
{
}

void Reader::help() const
{
	//TODO: Implement help
}
