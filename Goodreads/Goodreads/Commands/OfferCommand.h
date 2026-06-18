#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

class OfferCommand : public ICommand
{
private:
	Session& session;
	std::string authorName;
public:
	OfferCommand(Session& session, const std::string& authorName);
	void execute() override;
};
