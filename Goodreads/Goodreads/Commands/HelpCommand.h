#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class HelpCommand : public ICommand
{
private:
	Session& session;
public:
	HelpCommand(Session& session);
	void execute() override;
};
