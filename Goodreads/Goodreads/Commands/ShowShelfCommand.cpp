#include "ShowShelfCommand.h"
#include <iostream>
#include <format>
#include <memory>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Models/Book.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/AccessDeniedException.h"

ShowShelfCommand::ShowShelfCommand(Session& session, const std::optional<std::string>& readerName, const std::string& shelfName)
	: session(session), readerName(readerName), shelfName(shelfName) {}

void ShowShelfCommand::execute()
{
	auto me = CommandUtils::requireReader(session);

	std::shared_ptr<Reader> target = me;
	if (readerName.has_value() && *readerName != me->getUsername())
	{
		auto user = UserRegistry::getInstance().find(*readerName);
		if (!user)
			throw EntityNotFoundException("User", *readerName);
		target = std::dynamic_pointer_cast<Reader>(user);
		if (!target)
			throw AccessDeniedException("that user has no shelves.");
		if (!me->isFriendWith(*target))
			throw AccessDeniedException("you can only view a friend's shelves.");
	}

	Shelf& shelf = target->getShelf(shelfName);
	std::cout << "Shelf \"" << shelf.getName() << "\" (" << shelf.getBookCount() << " books):\n";
	auto books = shelf.getBooks();
	if (books.empty())
		std::cout << "  (empty)\n";
	for (const auto& book : books)
		std::cout << std::format("  {} ({:.2f})\n", book->getName(), book->getAverageRating());
}
