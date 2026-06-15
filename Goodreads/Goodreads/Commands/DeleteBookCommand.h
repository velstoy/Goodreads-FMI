#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class DeleteBookCommand : public ICommand
{
private:
	Session& session;
	std::string bookName;
public:
	DeleteBookCommand(Session& session, const std::string& bookName);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
