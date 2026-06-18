#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

class ProfileCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> userName;
public:
	ProfileCommand(Session& session, const std::optional<std::string>& userName);
	void execute() override;
};
