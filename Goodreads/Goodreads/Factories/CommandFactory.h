#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../Commands/ICommand.h"
#include "../Core/Session.h"

// Factory pattern: builds the right command object from the words of a command
// line. Unknown commands and wrong argument counts are caught here, so each
// command can assume its input is already valid.
class CommandFactory
{
public:
	static std::unique_ptr<ICommand> create(const std::vector<std::string>& tokens,
		Session& session, bool& running, const std::string& savePath);
};
