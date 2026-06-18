#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class FollowersCommand : public ICommand
{
private:
	Session& session;
public:
	explicit FollowersCommand(Session& session);
	void execute() override;
};
