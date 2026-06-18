#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class ReadMsgCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	ReadMsgCommand(Session& session, size_t index);
	void execute() override;
};
