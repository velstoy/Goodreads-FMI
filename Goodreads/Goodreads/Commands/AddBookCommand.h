#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

class AddBookCommand : public ICommand
{
private:
	Session& session;
	std::string bookName;
	std::string statusText;
	std::optional<std::string> ratingText;
public:
	AddBookCommand(Session& session, const std::string& bookName,
		const std::string& statusText, const std::optional<std::string>& ratingText);
	void execute() override;
};
