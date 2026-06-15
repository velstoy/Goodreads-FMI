#include "AddBirthdayCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Models/Date.h"

AddBirthdayCommand::AddBirthdayCommand(Session& session, const std::optional<std::string>& dateText)
	: session(session), dateText(dateText) {}

void AddBirthdayCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	if (dateText.has_value())
	{
		reader->setBirthday(Date::parse(*dateText));   // throws on bad date
		std::cout << "Birthday set to " << *dateText << ".\n";
	}
	else
	{
		reader->setBirthday(std::nullopt);
		std::cout << "Birthday cleared.\n";
	}
}
void AddBirthdayCommand::undo() {}
bool AddBirthdayCommand::canUndo() const { return false; }
