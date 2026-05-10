#include "Reader.h"

Reader::Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear) 
	: User(username, password, rday, rmonth, ryear), birthday(std::nullopt)
{
}

Reader::Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear, int bday, int bmonth, int byear)
	: User(username, password, rday, rmonth, ryear), birthday(bday, bmonth, byear)
{
}
