#include "HelpCommand.h"
#include <iostream>

HelpCommand::HelpCommand(Session& session) : session(session) {}

void HelpCommand::execute()
{
	if (session.isLoggedIn())
		session.getCurrentUser()->help();
	else
		std::cout << "Available commands:\n"
			<< "  register <username> <password> <reader|author|publisher>\n"
			<< "  login <username> <password>\n"
			<< "  help\n"
			<< "  exit\n";
}
