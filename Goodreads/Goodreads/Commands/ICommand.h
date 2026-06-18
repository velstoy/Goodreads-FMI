#pragma once

// Command pattern: each user action is its own command object, so the engine
// can run them all the same way and undo the ones that support it.
class ICommand
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual bool canUndo() const = 0;
	virtual ~ICommand() = default;
};
