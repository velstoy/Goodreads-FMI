#pragma once
#include <optional>
#include "User.h"
#include "../Models/Book.h"
#include "../Models/Shelf.h"
#include "../Models/Message.h"

class Reader : public User
{
private:
	std::vector<std::weak_ptr<Book>> booksInProfile;
	std::vector<Shelf> shelves;
	std::vector<std::weak_ptr<Book>> favoriteBooks;
	std::optional<Date> birthday;
	std::vector<std::unique_ptr<Message>> inbox;

public:
	Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear);

	Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear, int bday, int bmonth, int byear);
};

