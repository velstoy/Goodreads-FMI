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

	// Inherited via User
	void help() const override;
};

