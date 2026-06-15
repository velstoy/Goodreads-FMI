#pragma once

// Command pattern: every user action is reified as a command object so the
// engine can validate, execute and (where meaningful) undo it uniformly.
class ICommand
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual bool canUndo() const = 0;
	virtual ~ICommand() = default;
};
