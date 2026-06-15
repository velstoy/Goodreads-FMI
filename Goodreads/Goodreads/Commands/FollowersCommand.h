#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

// followers : lists the users who follow the current user.
class FollowersCommand : public ICommand
{
private:
	Session& session;
public:
	explicit FollowersCommand(Session& session);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
