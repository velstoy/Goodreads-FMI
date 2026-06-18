#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

// add-synopsis <title> <synopsis> : the publisher of a book sets its synopsis.
class AddSynopsisCommand : public ICommand
{
private:
	Session& session;
	std::string title;
	std::string synopsis;
public:
	AddSynopsisCommand(Session& session, const std::string& title, const std::string& synopsis);
	void execute() override;
};
