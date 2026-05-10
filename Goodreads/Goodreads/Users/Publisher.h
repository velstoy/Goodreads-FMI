#pragma once
#include "User.h"
#include "Author.h"
#include "../Models/Book.h"

class Publisher : public User
{
private:
	std::vector<std::weak_ptr<Book>> publishedBooks;
	std::vector<std::weak_ptr<Author>> authors;

public:
	Publisher(const std::string& username, const std::string& password, int rday, int rmonth, int ryear);
};

