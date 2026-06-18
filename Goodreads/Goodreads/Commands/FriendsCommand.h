#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

// friends [reader] : lists the friends (mutual followers) of yourself or
// another reader.
class FriendsCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> readerName;
public:
	FriendsCommand(Session& session, const std::optional<std::string>& readerName);
	void execute() override;
};
