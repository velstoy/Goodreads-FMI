#include "Engine.h"
#include <iostream>
#include <string>
#include "StringUtils.h"
#include "../Factories/CommandFactory.h"
#include "../Persistence/FileManager.h"

Engine::Engine(const std::string& savePath)
	: savePath(savePath) {}

void Engine::run()
{
	try { FileManager::load(savePath); }
	catch (const std::exception& e)
	{
		std::cerr << "Warning: could not load saved data (" << e.what() << ").\n";
	}

	std::cout << "Welcome to Goodreads. Type 'help' for the list of commands.\n";

	std::string line;
	while (running && std::getline(std::cin, line))
	{
		auto tokens = StringUtils::tokenize(line);
		if (tokens.empty())
			continue;

		try
		{
			auto command = CommandFactory::create(tokens, session, running, savePath);
			command->execute();
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
	}

	// If input ended without an explicit 'exit', still persist the state.
	if (running)
	{
		try { FileManager::save(savePath); }
		catch (...) {}
	}
}
