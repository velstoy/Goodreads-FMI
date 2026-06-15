#pragma once
#include "Reader.h"

class Publisher;
class Book;

// An author has every reader capability plus published books and the
// publishers they have worked with.
class Author : public Reader
{
private:
	std::vector<std::weak_ptr<Book>> publishedBooks;
	std::vector<std::weak_ptr<Publisher>> publishers;

public:
	using Reader::Reader;

	void addPublishedBook(const std::shared_ptr<Book>& book);
	std::vector<std::shared_ptr<Book>> getPublishedBooks() const;

	bool worksWith(const std::string& publisherName) const;
	void addPublisher(const std::shared_ptr<Publisher>& publisher);
	void removePublisher(const std::string& publisherName);
	std::vector<std::shared_ptr<Publisher>> getPublishers() const;

	std::string getType() const override;
	void help() const override;
};
