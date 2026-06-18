#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class LeaveCommand : public ICommand
{
private:
	Session& session;
	std::string publisherName;
public:
	LeaveCommand(Session& session, const std::string& publisherName);
	void execute() override;
};
