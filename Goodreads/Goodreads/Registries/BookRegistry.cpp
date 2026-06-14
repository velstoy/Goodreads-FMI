#include "BookRegistry.h"
#include <algorithm>
#include "../Exceptions/InvalidArgumentException.h"

BookRegistry& BookRegistry::getInstance()
{
	static BookRegistry instance;
	return instance;
}

void BookRegistry::add(const std::shared_ptr<Book>& book)
{
	if (find(book->getName()) != nullptr)
		throw InvalidArgumentException("A book with this title already exists!");
	books.push_back(book);
}

std::shared_ptr<Book> BookRegistry::find(const std::string& title) const
{
	auto it = std::find_if(books.begin(), books.end(),
		[&](const std::shared_ptr<Book>& b) { return b->getName() == title; });
	return it != books.end() ? *it : nullptr;
}

const std::vector<std::shared_ptr<Book>>& BookRegistry::getAll() const { return books; }

void BookRegistry::clear() { books.clear(); }
