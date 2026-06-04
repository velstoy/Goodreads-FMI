#include "RegisterCommand.h"
#include <ctime>
#include "../Factories/UserFactory.h"
#include "../Registries/UserRegistry.h"

RegisterCommand::RegisterCommand(const std::string& username, const std::string& password, const std::string& type) : username(username), password(password), type(type)
{
}

void RegisterCommand::execute()
{
	UserRegistry::getInstance().add(UserFactory::createUser(type, username, password, Date::today()));
}

void RegisterCommand::undo()
{
	UserRegistry::getInstance().remove(username);
}

bool RegisterCommand::canUndo() const
{
	return true;
}
