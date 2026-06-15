#pragma once
#include <string>
#include "Session.h"

// Owns the application's run loop: loads saved data, reads commands from the
// user, dispatches them through the CommandFactory and persists on exit.
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
