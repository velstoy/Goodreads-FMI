#include "Reader.h"
#include <iostream>
#include <algorithm>
#include "../Models/Book.h"
#include "../Exceptions/InvalidArgumentException.h"
#include "../Exceptions/EntityNotFoundException.h"

constexpr double FAVORITE_THRESHOLD = 9.0;   // a book rated this high on add-book becomes a favourite

Reader::Reader(const std::string& username, const std::string& password, const Date& registrationDate,
	const std::optional<Date>& birthday)
	: User(username, password, registrationDate), birthday(birthday)
{
}

bool Reader::hasBook(const std::string& bookName) const
{
	for (const auto& entry : profileBooks)
	{
		auto book = entry.book.lock();
		if (book && book->getName() == bookName)
			return true;
	}
	return false;
}

void Reader::addBook(const std::shared_ptr<Book>& book, ReadingStatus status, std::optional<double> rating)
{
	if (!book)
		throw InvalidArgumentException("Cannot add a non-existent book!");
	if (hasBook(book->getName()))
		throw InvalidArgumentException("This book is already in your profile!");

	profileBooks.push_back(ReadingEntry{ book, status, rating });

	if (rating.has_value())
	{
		book->addRating(*rating);
		if (*rating >= FAVORITE_THRESHOLD)
			addFavorite(book);
	}
}

void Reader::removeBook(const std::string& bookName)
{
	if (!hasBook(bookName))
		throw EntityNotFoundException("Book in profile", bookName);

	std::erase_if(profileBooks, [&](const ReadingEntry& e) {
		auto b = e.book.lock();
		return !b || b->getName() == bookName;
	});
	std::erase_if(favoriteBooks, [&](const std::weak_ptr<Book>& w) {
		auto b = w.lock();
		return !b || b->getName() == bookName;
	});
	for (Shelf& shelf : shelves)
		shelf.removeBook(bookName);
}

const std::vector<ReadingEntry>& Reader::getProfileBooks() const { return profileBooks; }

bool Reader::hasShelf(const std::string& name) const
{
	return std::any_of(shelves.begin(), shelves.end(),
		[&](const Shelf& s) { return s.getName() == name; });
}

void Reader::createShelf(const std::string& name)
{
	if (hasShelf(name))
		throw InvalidArgumentException("A shelf with this name already exists!");
	Date now = Date::today();
	shelves.emplace_back(name, now.getDay(), now.getMonth(), now.getYear());
}

void Reader::deleteShelf(const std::string& name)
{
	if (!hasShelf(name))
		throw EntityNotFoundException("Shelf", name);
	std::erase_if(shelves, [&](const Shelf& s) { return s.getName() == name; });
}

Shelf& Reader::getShelf(const std::string& name)
{
	for (Shelf& s : shelves)
		if (s.getName() == name)
			return s;
	throw EntityNotFoundException("Shelf", name);
}

const std::vector<Shelf>& Reader::getShelves() const { return shelves; }

void Reader::addFavorite(const std::shared_ptr<Book>& book)
{
	if (!book) return;
	for (const auto& w : favoriteBooks)
	{
		auto b = w.lock();
		if (b && b->getName() == book->getName())
			return;
	}
	favoriteBooks.push_back(book);
}

std::vector<std::shared_ptr<Book>> Reader::getFavorites() const
{
	std::vector<std::shared_ptr<Book>> result;
	for (const auto& w : favoriteBooks)
		if (auto b = w.lock())
			result.push_back(b);
	return result;
}

void Reader::setBirthday(const std::optional<Date>& date) { birthday = date; }
const std::optional<Date>& Reader::getBirthday() const { return birthday; }

void Reader::restoreBook(const std::shared_ptr<Book>& book, ReadingStatus status, std::optional<double> rating)
{
	if (!book) return;
	profileBooks.push_back(ReadingEntry{ book, status, rating });
}

void Reader::restoreShelf(const Shelf& shelf)
{
	shelves.push_back(shelf);
}

std::string Reader::getType() const { return "Reader"; }

void Reader::help() const
{
	User::help();
	std::cout <<
		"  search <name>                          - find users and books (fuzzy, <=2 typos)\n"
		"  follow <username>                      - follow a user\n"
		"  add-book <book> <status> [rating]      - add a book to your profile\n"
		"  create-shelf <name>                    - create a shelf\n"
		"  delete-shelf <name>                    - delete a shelf\n"
		"  add-to-shelf <book> <shelf>            - put a book on a shelf\n"
		"  remove-from-shelf <book> <shelf>       - take a book off a shelf\n"
		"  delete-book <book>                     - remove a book from your profile\n"
		"  show-shelf [reader] <shelf>            - list a shelf's books\n"
		"  show-inbox [friends]                   - list your messages\n"
		"  read-msg <index>                       - mark a message as read\n"
		"  delete-msg <index>                     - delete a read message\n"
		"  friends [reader]                       - list mutual followers\n"
		"  add-birthday [dd.mm.yyyy]              - set or clear your birthday\n"
		"  profile [reader]                       - show a profile\n";
}
