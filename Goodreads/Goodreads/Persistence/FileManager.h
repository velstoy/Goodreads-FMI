#pragma once
#include <string>

// Flat-file persistence for the whole application state. The registries are
// the single source of truth: save() writes every book and user to disk, and
// load() rebuilds them (resolving the circular book<->user references by name).
class FileManager
{
public:
	static void save(const std::string& path);
	static void load(const std::string& path);
};
