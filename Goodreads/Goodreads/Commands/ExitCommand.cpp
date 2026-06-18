#include "ExitCommand.h"
#include <iostream>
#include "../Persistence/FileManager.h"

ExitCommand::ExitCommand(bool& running, const std::string& savePath)
	: running(running), savePath(savePath) {}

void ExitCommand::execute()
{
	FileManager::save(savePath);
	std::cout << "Data saved. Goodbye!\n";
	running = false;
}
