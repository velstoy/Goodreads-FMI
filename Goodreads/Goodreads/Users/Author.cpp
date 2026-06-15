#include "Author.h"
#include <iostream>
#include <algorithm>
#include "Publisher.h"
#include "../Models/Book.h"

void Author::addPublishedBook(const std::shared_ptr<Book>& book)
{
	if (!book) return;
	for (const auto& w : publishedBooks)
	{
		auto b = w.lock();
		if (b && b->getName() == book->getName()) return;
	}
	publishedBooks.push_back(book);
}

std::vector<std::shared_ptr<Book>> Author::getPublishedBooks() const
{
	std::vector<std::shared_ptr<Book>> result;
	for (const auto& w : publishedBooks)
		if (auto b = w.lock()) result.push_back(b);
	return result;
}

bool Author::worksWith(const std::string& publisherName) const
{
	for (const auto& w : publishers)
	{
		auto p = w.lock();
		if (p && p->getUsername() == publisherName) return true;
	}
	return false;
}

void Author::addPublisher(const std::shared_ptr<Publisher>& publisher)
{
	if (!publisher || worksWith(publisher->getUsername())) return;
	publishers.push_back(publisher);
}

void Author::removePublisher(const std::string& publisherName)
{
	std::erase_if(publishers, [&](const std::weak_ptr<Publisher>& w) {
		auto p = w.lock();
		return !p || p->getUsername() == publisherName;
	});
}

std::vector<std::shared_ptr<Publisher>> Author::getPublishers() const
{
	std::vector<std::shared_ptr<Publisher>> result;
	for (const auto& w : publishers)
		if (auto p = w.lock()) result.push_back(p);
	return result;
}

std::string Author::getType() const { return "Author"; }

void Author::help() const
{
	Reader::help();
	std::cout <<
		"  -- author --\n"
		"  show-inbox [offers]                    - list messages (optionally only offers)\n"
		"  accept-offer <index>                   - accept a job offer\n"
		"  leave <publisher>                      - stop working with a publisher\n"
		"  followers                              - list your followers\n";
}
