#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Date.h"

class Book;

class Shelf
{
private:
	std::string name;
	std::vector<std::weak_ptr<Book>> books;
	Date creationDate;
public:
	Shelf(const std::string& name, int cday, int cmonth, int cyear);

	size_t getBookCount() const;
};

