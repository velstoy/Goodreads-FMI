#pragma once
#include "User.h"

class Author;
class Book;

class Publisher : public User
{
private:
	std::vector<std::weak_ptr<Book>> publishedBooks;
	std::vector<std::weak_ptr<Author>> authors;

public:
	using User::User;

	void addPublishedBook(const std::shared_ptr<Book>& book);
	std::vector<std::shared_ptr<Book>> getPublishedBooks() const;

	bool hasAuthor(const std::string& authorName) const;
	void addAuthor(const std::shared_ptr<Author>& author);
	void removeAuthor(const std::string& authorName);
	std::vector<std::shared_ptr<Author>> getAuthors() const;

	std::string getType() const override;
	void help() const override;
};
