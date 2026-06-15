#pragma once
#include <optional>
#include "User.h"
#include "../Models/Shelf.h"
#include "../Models/ReadingStatus.h"

class Book;

// One entry in a reader's profile: the book, how the reader is reading it,
// and an optional personal rating.
struct ReadingEntry
{
	std::weak_ptr<Book> book;
	ReadingStatus status = ReadingStatus::PlanToRead;
	std::optional<double> rating;
};

class Reader : public User
{
private:
	std::vector<ReadingEntry> profileBooks;
	std::vector<Shelf> shelves;
	std::vector<std::weak_ptr<Book>> favoriteBooks;
	std::optional<Date> birthday;

public:
	Reader(const std::string& username, const std::string& password, const Date& registrationDate,
		const std::optional<Date>& birthday = std::nullopt);

	// --- profile books ---
	bool hasBook(const std::string& bookName) const;
	void addBook(const std::shared_ptr<Book>& book, ReadingStatus status, std::optional<double> rating);
	void removeBook(const std::string& bookName);   // also strips it from every shelf
	const std::vector<ReadingEntry>& getProfileBooks() const;

	// --- shelves ---
	bool hasShelf(const std::string& name) const;
	void createShelf(const std::string& name);
	void deleteShelf(const std::string& name);
	Shelf& getShelf(const std::string& name);             // throws if missing
	const std::vector<Shelf>& getShelves() const;

	// --- favourites & birthday ---
	void addFavorite(const std::shared_ptr<Book>& book);
	std::vector<std::shared_ptr<Book>> getFavorites() const;
	void setBirthday(const std::optional<Date>& date);
	const std::optional<Date>& getBirthday() const;

	std::string getType() const override;
	void help() const override;

	// --- persistence helpers ---
	// Re-attach a book to the profile exactly as it was saved, without
	// re-applying its rating to the book's running average.
	void restoreBook(const std::shared_ptr<Book>& book, ReadingStatus status, std::optional<double> rating);
	// Re-add a fully-built shelf (preserving its original creation date).
	void restoreShelf(const Shelf& shelf);
};
