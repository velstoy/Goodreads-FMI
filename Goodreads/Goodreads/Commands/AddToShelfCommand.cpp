#include "AddToShelfCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/BookRegistry.h"
#include "../Exceptions/EntityNotFoundException.h"

AddToShelfCommand::AddToShelfCommand(Session& session, const std::string& bookName, const std::string& shelfName)
	: session(session), bookName(bookName), shelfName(shelfName) {}

void AddToShelfCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	auto book = BookRegistry::getInstance().find(bookName);
	if (!book)
		throw EntityNotFoundException("Book", bookName);

	Shelf& shelf = reader->getShelf(shelfName);
	shelf.addBook(book);
	std::cout << "Added \"" << bookName << "\" to shelf \"" << shelfName << "\".\n";
}
