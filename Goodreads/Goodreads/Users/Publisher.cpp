#include "Publisher.h"

Publisher::Publisher(const std::string& username, const std::string& password, int rday, int rmonth, int ryear)
	: User(username, password, rday, rmonth, ryear)
{
}
