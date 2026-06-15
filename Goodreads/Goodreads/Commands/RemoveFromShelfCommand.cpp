#include "RemoveFromShelfCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Exceptions/EntityNotFoundException.h"

RemoveFromShelfCommand::RemoveFromShelfCommand(Session& session, const std::string& bookName, const std::string& shelfName)
	: session(session), bookName(bookName), shelfName(shelfName) {}

void RemoveFromShelfCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	Shelf& shelf = reader->getShelf(shelfName);
	if (!shelf.contains(bookName))
		throw EntityNotFoundException("Book on shelf", bookName);
	shelf.removeBook(bookName);
	std::cout << "Removed \"" << bookName << "\" from shelf \"" << shelfName << "\".\n";
}
void RemoveFromShelfCommand::undo() {}
bool RemoveFromShelfCommand::canUndo() const { return false; }
