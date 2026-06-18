#include "DeleteBookCommand.h"
#include <iostream>
#include "CommandUtils.h"

DeleteBookCommand::DeleteBookCommand(Session& session, const std::string& bookName)
	: session(session), bookName(bookName) {}

void DeleteBookCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	reader->removeBook(bookName);
	std::cout << "Removed \"" << bookName << "\" from your profile.\n";
}
