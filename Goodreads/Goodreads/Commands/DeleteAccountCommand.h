#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class DeleteAccountCommand : public ICommand
{
private:
	Session& session;
public:
	explicit DeleteAccountCommand(Session& session);
	void execute() override;
};