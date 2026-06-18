#pragma once
#include <string>
#include <optional>
#include "ICommand.h"
#include "../Core/Session.h"

// profile [reader] : prints a user's public profile. For readers/authors this
// includes their shelves, favourites and books; for publishers the basics plus
// their catalogue.
class ProfileCommand : public ICommand
{
private:
	Session& session;
	std::optional<std::string> userName;
public:
	ProfileCommand(Session& session, const std::optional<std::string>& userName);
	void execute() override;
};
