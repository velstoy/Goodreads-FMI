#include "HelpCommand.h"
#include "../Users/User.h"

HelpCommand::HelpCommand(const std::weak_ptr<User> user) : user(user)
{
}

void HelpCommand::execute()
{
	user.lock()->help();
}

void HelpCommand::undo()
{
}

bool HelpCommand::canUndo() const
{
	return false;
}
