#include "DeleteBookCommand.h"
#include <iostream>
#include "CommandUtils.h"

DeleteBookCommand::DeleteBookCommand(Session& session, const std::string& bookName)
	: session(session), bookName(bookName) {}

void DeleteBookCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	reader->removeBook(bookName);   // also removes from every shelf
	std::cout << "Removed \"" << bookName << "\" from your profile.\n";
}
void DeleteBookCommand::undo() {}
bool DeleteBookCommand::canUndo() const { return false; }
