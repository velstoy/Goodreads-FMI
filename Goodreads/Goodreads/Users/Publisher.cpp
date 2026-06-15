#include "Publisher.h"
#include <iostream>
#include <algorithm>
#include "Author.h"
#include "../Models/Book.h"

void Publisher::addPublishedBook(const std::shared_ptr<Book>& book)
{
	if (!book) return;
	for (const auto& w : publishedBooks)
	{
		auto b = w.lock();
		if (b && b->getName() == book->getName()) return;
	}
	publishedBooks.push_back(book);
}

std::vector<std::shared_ptr<Book>> Publisher::getPublishedBooks() const
{
	std::vector<std::shared_ptr<Book>> result;
	for (const auto& w : publishedBooks)
		if (auto b = w.lock()) result.push_back(b);
	return result;
}

bool Publisher::hasAuthor(const std::string& authorName) const
{
	for (const auto& w : authors)
	{
		auto a = w.lock();
		if (a && a->getUsername() == authorName) return true;
	}
	return false;
}

void Publisher::addAuthor(const std::shared_ptr<Author>& author)
{
	if (!author || hasAuthor(author->getUsername())) return;
	authors.push_back(author);
}

void Publisher::removeAuthor(const std::string& authorName)
{
	std::erase_if(authors, [&](const std::weak_ptr<Author>& w) {
		auto a = w.lock();
		return !a || a->getUsername() == authorName;
	});
}

std::vector<std::shared_ptr<Author>> Publisher::getAuthors() const
{
	std::vector<std::shared_ptr<Author>> result;
	for (const auto& w : authors)
		if (auto a = w.lock()) result.push_back(a);
	return result;
}

std::string Publisher::getType() const { return "Publisher"; }

void Publisher::help() const
{
	User::help();
	std::cout <<
		"  search <name>                          - find users and books (fuzzy, <=2 typos)\n"
		"  follow <username>                      - follow a user\n"
		"  publish <title> <author> <date> <pages> <genres...>  - publish a new book\n"
		"  add-synopsis <title> <synopsis>        - set a book's synopsis\n"
		"  offer <author>                         - send a job offer to an author\n";
}
