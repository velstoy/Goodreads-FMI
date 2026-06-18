#include "DeleteShelfCommand.h"
#include <iostream>
#include "CommandUtils.h"

DeleteShelfCommand::DeleteShelfCommand(Session& session, const std::string& name)
	: session(session), name(name) {}

void DeleteShelfCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	reader->deleteShelf(name);
	std::cout << "Deleted shelf \"" << name << "\".\n";
}
