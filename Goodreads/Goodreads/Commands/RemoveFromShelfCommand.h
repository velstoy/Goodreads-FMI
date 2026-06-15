#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class RemoveFromShelfCommand : public ICommand
{
private:
	Session& session;
	std::string bookName;
	std::string shelfName;
public:
	RemoveFromShelfCommand(Session& session, const std::string& bookName, const std::string& shelfName);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
