#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

class ShowInboxCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> filter;
public:
	ShowInboxCommand(Session& session, const std::optional<std::string>& filter);
	void execute() override;
};
