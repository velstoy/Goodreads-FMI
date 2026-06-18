#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class CreateShelfCommand : public ICommand
{
private:
	Session& session;
	std::string name;
public:
	CreateShelfCommand(Session& session, const std::string& name);
	void execute() override;
};
