#include "DeleteAccountCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"

DeleteAccountCommand::DeleteAccountCommand(Session& session)
	: session(session) {
}

void DeleteAccountCommand::execute()
{
	auto user = CommandUtils::requireLogin(session);
	std::string username = user->getUsername();

	session.logout();
	UserRegistry::getInstance().remove(username);

	std::cout << "Account \"" << username << "\" successfully deleted.\n";
}