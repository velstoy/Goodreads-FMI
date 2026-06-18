#pragma once
#include <string>
#include "Session.h"

class Engine
{
private:
	Session session;
	bool running = true;
	std::string savePath;
public:
	explicit Engine(const std::string& savePath = "goodreads_data.bin");
	void run();
};
