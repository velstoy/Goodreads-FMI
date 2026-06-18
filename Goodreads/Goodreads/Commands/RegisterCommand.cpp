#include "RegisterCommand.h"
#include <iostream>
#include "../Factories/UserFactory.h"
#include "../Registries/UserRegistry.h"

RegisterCommand::RegisterCommand(const std::string& username, const std::string& password, const std::string& type)
	: username(username), password(password), type(type) {}

void RegisterCommand::execute()
{
	UserRegistry::getInstance().add(UserFactory::createUser(type, username, password, Date::today()));
	std::cout << "Registered " << type << " \"" << username << "\" successfully.\n";
}
