#include "Shelf.h"
#include "Book.h"

Shelf::Shelf(const std::string& name, int cday, int cmonth, int cyear)
	: name(name), creationDate(cday, cmonth, cyear)
{
}

const std::string& Shelf::getName() const { return name; }
const Date& Shelf::getCreationDate() const { return creationDate; }
size_t Shelf::getBookCount() const { return books.size(); }

bool Shelf::contains(const std::string& bookName) const
{
	for (const auto& weak : books)
	{
		auto book = weak.lock();
		if (book && book->getName() == bookName)
			return true;
	}
	return false;
}

void Shelf::addBook(const std::shared_ptr<Book>& book)
{
	if (!book || contains(book->getName()))
		return;
	books.push_back(book);
}

void Shelf::removeBook(const std::string& bookName)
{
	std::erase_if(books, [&](const std::weak_ptr<Book>& weak) {
		auto book = weak.lock();
		return !book || book->getName() == bookName;
	});
}

std::vector<std::shared_ptr<Book>> Shelf::getBooks() const
{
	std::vector<std::shared_ptr<Book>> result;
	for (const auto& weak : books)
		if (auto book = weak.lock())
			result.push_back(book);
	return result;
}
