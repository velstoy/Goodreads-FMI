#pragma once
#include <string>
#include "ICommand.h"

class ExitCommand : public ICommand
{
private:
	bool& running;
	std::string savePath;
public:
	ExitCommand(bool& running, const std::string& savePath);
	void execute() override;
};
