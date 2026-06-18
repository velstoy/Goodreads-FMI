#include "ProfileCommand.h"
#include <iostream>
#include <format>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Users/Reader.h"
#include "../Users/Author.h"
#include "../Users/Publisher.h"
#include "../Models/Book.h"
#include "../Exceptions/EntityNotFoundException.h"

ProfileCommand::ProfileCommand(Session& session, const std::optional<std::string>& userName)
	: session(session), userName(userName) {}

void ProfileCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);

	std::shared_ptr<User> target = me;
	if (userName.has_value() && *userName != me->getUsername())
	{
		target = UserRegistry::getInstance().find(*userName);
		if (!target)
			throw EntityNotFoundException("User", *userName);
	}

	std::cout << "==== " << target->getUsername() << " (" << target->getType() << ") ====\n";
	std::cout << "Registered: " << target->getRegistrationDate().toString() << "\n";
	std::cout << "Followers: " << target->getFollowers().size() << "\n";

	if (auto reader = std::dynamic_pointer_cast<Reader>(target))
	{
		if (reader->getBirthday().has_value())
			std::cout << "Birthday: " << reader->getBirthday()->toString() << "\n";

		const auto& books = reader->getProfileBooks();
		std::cout << "Books (" << books.size() << "):\n";
		for (const auto& entry : books)
		{
			auto book = entry.book.lock();
			if (!book)
				continue;
			std::cout << "  " << book->getName() << " [" << readingStatusToString(entry.status) << "]";
			if (entry.rating.has_value())
				std::cout << std::format(" - rated {:.2f}", *entry.rating);
			std::cout << "\n";
		}

		auto favorites = reader->getFavorites();
		std::cout << "Favourites (" << favorites.size() << "):\n";
		for (const auto& book : favorites)
			std::cout << std::format("  {} ({:.2f})\n", book->getName(), book->getAverageRating());

		const auto& shelves = reader->getShelves();
		std::cout << "Shelves (" << shelves.size() << "):\n";
		for (const auto& shelf : shelves)
			std::cout << "  " << shelf.getName() << " (" << shelf.getBookCount() << " books)\n";
	}

	if (auto author = std::dynamic_pointer_cast<Author>(target))
	{
		auto published = author->getPublishedBooks();
		std::cout << "Published books (" << published.size() << "):\n";
		for (const auto& book : published)
			std::cout << std::format("  {} ({:.2f})\n", book->getName(), book->getAverageRating());
	}

	if (auto publisher = std::dynamic_pointer_cast<Publisher>(target))
	{
		auto catalogue = publisher->getPublishedBooks();
		std::cout << "Catalogue (" << catalogue.size() << "):\n";
		for (const auto& book : catalogue)
			std::cout << std::format("  {} ({:.2f})\n", book->getName(), book->getAverageRating());
	}
}
