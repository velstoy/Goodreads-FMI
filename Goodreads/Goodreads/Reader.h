#pragma once
#include <optional>
#include "User.h"
#include "Book.h"
#include "Shelf.h"
#include "Message.h"

class Reader : public User
{
private:
	std::vector<std::shared_ptr<Book>> booksInProfile;
	std::vector<Shelf> shelves;
	std::vector<std::shared_ptr<Book>> favoriteBooks;
	std::optional<Date> birthday;
	std::vector<std::unique_ptr<Message>> inbox;

public:
	Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear);

	Reader(const std::string& username, const std::string& password, int rday, int rmonth, int ryear, int bday, int bmonth, int byear);
};

