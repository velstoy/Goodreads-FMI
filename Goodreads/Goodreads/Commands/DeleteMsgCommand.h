#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

// delete-msg <index> : removes a message from the inbox (must be read first).
class DeleteMsgCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	DeleteMsgCommand(Session& session, size_t index);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
