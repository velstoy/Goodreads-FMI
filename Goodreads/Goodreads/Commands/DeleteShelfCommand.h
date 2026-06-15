#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class DeleteShelfCommand : public ICommand
{
private:
	Session& session;
	std::string name;
public:
	DeleteShelfCommand(Session& session, const std::string& name);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
