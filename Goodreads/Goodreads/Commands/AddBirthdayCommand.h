#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

// add-birthday [date] : sets (or clears) the reader's birthday. Date format
// is dd.mm.yyyy.
class AddBirthdayCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> dateText;
public:
	AddBirthdayCommand(Session& session, const std::optional<std::string>& dateText);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
