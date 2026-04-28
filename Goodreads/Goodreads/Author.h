#pragma once
#include "Reader.h"
#include "Publisher.h"

class Author : public Reader
{
private:
	std::vector<std::shared_ptr<Book>> publishedBooks;
	std::vector<std::weak_ptr<Publisher>> publishers;

public:
	Author(const std::string& username, const std::string& password, int rday, int rmonth, int ryear);

	Author(const std::string& username, const std::string& password, int rday, int rmonth, int ryear, int bday, int bmonth, int byear);
};

