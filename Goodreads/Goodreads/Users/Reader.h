#pragma once
#include <optional>
#include "User.h"
#include "../Models/Shelf.h"
#include "../Models/Message.h"

class Book;

class Reader : public User
{
private:
	std::vector<std::weak_ptr<Book>> booksInProfile;
	std::vector<Shelf> shelves;
	std::vector<std::weak_ptr<Book>> favoriteBooks;
	std::optional<Date> birthday;
	std::vector<std::unique_ptr<Message>> inbox;

public:
	Reader(const std::string& username, const std::string& password, const Date& registrationDate, const std::optional<Date>& birthday = std::nullopt);

	// Inherited via User
	void help() const override;
};

