#include "Author.h"

Author::Author(const std::string& username, const std::string& password, int rday, int rmonth, int ryear) 
	: Reader(username, password, rday, rmonth, ryear)
{
}

Author::Author(const std::string& username, const std::string& password, int rday, int rmonth, int ryear, int bday, int bmonth, int byear)
	: Reader(username, password, rday, rmonth, ryear, bday, bmonth, byear)
{
}
