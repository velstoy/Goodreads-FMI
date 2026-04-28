#pragma once
#include "Reader.h"

class Author : public Reader
{
private:
	std::vector<std::shared_ptr<Book>> publishedBooks;
};

