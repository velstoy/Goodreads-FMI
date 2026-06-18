#pragma once
#include <string>
#include "Session.h"

// Runs the main loop: loads saved data on start, reads and executes commands
// one at a time, and saves everything again on exit.
class Engine
{
private:
	Session session;
	bool running = true;
	std::string savePath;
public:
	explicit Engine(const std::string& savePath = "goodreads_data.txt");
	void run();
};
