#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class LogoutCommand : public ICommand
{
private:
	Session& session;
public:
	LogoutCommand(Session& session);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
