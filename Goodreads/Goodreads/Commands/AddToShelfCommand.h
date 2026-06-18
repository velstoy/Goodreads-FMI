#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class AddToShelfCommand : public ICommand
{
private:
	Session& session;
	std::string bookName;
	std::string shelfName;
public:
	AddToShelfCommand(Session& session, const std::string& bookName, const std::string& shelfName);
	void execute() override;
};
