#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class DeleteMsgCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	DeleteMsgCommand(Session& session, size_t index);
	void execute() override;
};
