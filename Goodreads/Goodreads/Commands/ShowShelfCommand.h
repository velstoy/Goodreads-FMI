#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

// show-shelf [reader] <shelf> : prints the books on one of your shelves,
// or on a friend's shelf when a reader name is supplied.
class ShowShelfCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> readerName;
	std::string shelfName;
public:
	ShowShelfCommand(Session& session, const std::optional<std::string>& readerName, const std::string& shelfName);
	void execute() override;
};
