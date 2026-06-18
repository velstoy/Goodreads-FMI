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

	const std::string& getName() const;
	const Date& getCreationDate() const;
	size_t getBookCount() const;

	bool contains(const std::string& bookName) const;
	void addBook(const std::shared_ptr<Book>& book);   // ignores duplicates
	void removeBook(const std::string& bookName);

	std::vector<std::shared_ptr<Book>> getBooks() const;
};
