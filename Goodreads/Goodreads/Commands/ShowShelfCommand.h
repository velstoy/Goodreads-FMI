#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

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
