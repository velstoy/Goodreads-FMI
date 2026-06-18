#include "CreateShelfCommand.h"
#include <iostream>
#include "CommandUtils.h"

CreateShelfCommand::CreateShelfCommand(Session& session, const std::string& name)
	: session(session), name(name) {}

void CreateShelfCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	reader->createShelf(name);
	std::cout << "Created shelf \"" << name << "\".\n";
}
