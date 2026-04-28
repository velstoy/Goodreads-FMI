#pragma once
#include <vector>
#include <memory>
#include "Book.h"

class BookRegistry
{
private:
	std::vector<std::shared_ptr<Book>> books;
};

