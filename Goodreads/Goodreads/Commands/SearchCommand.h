#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class SearchCommand : public ICommand
{
private:
	Session& session;
	std::string query;
public:
	SearchCommand(Session& session, const std::string& query);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
