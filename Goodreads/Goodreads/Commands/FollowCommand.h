#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class FollowCommand : public ICommand
{
private:
	Session& session;
	std::string target;
public:
	FollowCommand(Session& session, const std::string& target);
	void execute() override;
};
