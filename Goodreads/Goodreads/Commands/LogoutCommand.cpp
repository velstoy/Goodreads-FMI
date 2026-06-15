#include "LogoutCommand.h"
#include <iostream>
#include "CommandUtils.h"

LogoutCommand::LogoutCommand(Session& session) : session(session) {}

void LogoutCommand::execute()
{
	CommandUtils::requireLogin(session);
	std::cout << "Goodbye, " << session.getCurrentUser()->getUsername() << ".\n";
	session.logout();
}
void LogoutCommand::undo() {}
bool LogoutCommand::canUndo() const { return false; }
