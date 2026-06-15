#pragma once
#include <string>
#include "ICommand.h"

class RegisterCommand : public ICommand
{
private:
	std::string username;
	std::string password;
	std::string type;
public:
	RegisterCommand(const std::string& username, const std::string& password, const std::string& type);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
