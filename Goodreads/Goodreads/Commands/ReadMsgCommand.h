#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

// read-msg <index> : marks an inbox message as read and prints it.
class ReadMsgCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	ReadMsgCommand(Session& session, size_t index);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
