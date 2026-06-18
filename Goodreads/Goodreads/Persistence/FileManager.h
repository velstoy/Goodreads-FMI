#pragma once
#include <string>

// Saves and loads the whole program state to a text file. save() writes every
// book and user; load() reads them back and reconnects each book to its author
// and publisher by name.
class FileManager
{
public:
	static void save(const std::string& path);
	static void load(const std::string& path);
};
