#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

// show-inbox [filter] : lists the messages in the current user's inbox.
// filter "friends" keeps only friend requests, "offers" only job offers.
class ShowInboxCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> filter;
public:
	ShowInboxCommand(Session& session, const std::optional<std::string>& filter);
	void execute() override;
};
