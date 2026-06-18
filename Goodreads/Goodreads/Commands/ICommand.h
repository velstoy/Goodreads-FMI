#pragma once

// Command pattern: each user action is its own command object, so the engine
// can validate and run them all the same way.
class ICommand
{
public:
	virtual void execute() = 0;
	virtual ~ICommand() = default;
};
