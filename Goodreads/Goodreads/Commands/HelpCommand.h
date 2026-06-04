#pragma once
#include <memory>
#include "ICommand.h"

class User;

class HelpCommand : public ICommand
{
private:
	std::weak_ptr<User> user;
public:
	HelpCommand(const std::weak_ptr<User> user);

	void execute() override;
	void undo() override;
	bool canUndo() const override;
};