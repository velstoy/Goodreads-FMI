#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class LoginCommand : public ICommand
{
private:
	Session& session;
	std::string username;
	std::string password;
public:
	LoginCommand(Session& session, const std::string& username, const std::string& password);
	void execute() override;
};
