#pragma once
#include <memory>
#include <string>
#include <vector>
#include "../Commands/ICommand.h"
#include "../Core/Session.h"

// Factory pattern: turns a tokenised command line into the matching command
// object. Unknown commands and malformed argument lists are rejected here so
// the individual commands can assume well-formed input.
class CommandFactory
{
public:
	static std::unique_ptr<ICommand> create(const std::vector<std::string>& tokens,
		Session& session, bool& running, const std::string& savePath);
};
