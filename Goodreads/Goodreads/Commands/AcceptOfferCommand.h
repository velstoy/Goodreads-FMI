#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

class AcceptOfferCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	AcceptOfferCommand(Session& session, size_t index);
	void execute() override;
};
