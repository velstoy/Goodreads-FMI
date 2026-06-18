#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../Commands/ICommand.h"
#include "../Core/Session.h"

class CommandFactory
{
public:
	static std::unique_ptr<ICommand> create(const std::vector<std::string>& tokens,
		Session& session, bool& running, const std::string& savePath);
};
