#include "LoginCommand.h"
#include <iostream>
#include "../Registries/UserRegistry.h"
#include "../Exceptions/AccessDeniedException.h"

LoginCommand::LoginCommand(Session& session, const std::string& username, const std::string& password)
	: session(session), username(username), password(password) {}

void LoginCommand::execute()
{
	if (session.isLoggedIn())
		throw AccessDeniedException("you are already logged in. Log out first.");

	auto user = UserRegistry::getInstance().find(username);
	if (!user || !user->checkPassword(password))
		throw AccessDeniedException("wrong username or password.");

	session.login(user);
	std::cout << "Welcome, " << username << "!\n";
}
