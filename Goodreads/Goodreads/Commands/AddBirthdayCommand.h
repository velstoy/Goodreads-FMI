#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

class AddBirthdayCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> dateText;
public:
	AddBirthdayCommand(Session& session, const std::optional<std::string>& dateText);
	void execute() override;
};
