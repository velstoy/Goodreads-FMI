#pragma once
#include <vector>
#include <memory>
#include "../Models/Book.h"

class BookRegistry
{
private:
	std::vector<std::shared_ptr<Book>> books;

	BookRegistry() = default;
public:
	BookRegistry& getInstance();
};

