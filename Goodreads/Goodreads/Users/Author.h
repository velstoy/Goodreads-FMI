#pragma once
#include "Reader.h"

class Publisher;
class Book;

class Author : public Reader
{
private:
	std::vector<std::weak_ptr<Book>> publishedBooks;
	std::vector<std::weak_ptr<Publisher>> publishers;

public:
	using Reader::Reader;
};

