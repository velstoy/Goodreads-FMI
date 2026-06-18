#pragma once
#include <vector>
#include <memory>
#include "../Models/Book.h"

class BookRegistry
{
private:
	std::vector<std::shared_ptr<Book>> books;
	BookRegistry() = default;
public:
	BookRegistry(const BookRegistry&) = delete;
	BookRegistry& operator=(const BookRegistry&) = delete;

	static BookRegistry& getInstance();

	void add(const std::shared_ptr<Book>& book);   // throws if the title is taken
	std::shared_ptr<Book> find(const std::string& title) const;   // nullptr if absent
	const std::vector<std::shared_ptr<Book>>& getAll() const;
	void clear();
};
