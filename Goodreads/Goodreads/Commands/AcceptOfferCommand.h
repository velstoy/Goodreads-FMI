#pragma once
#include "ICommand.h"
#include "../Core/Session.h"

// accept-offer <index> : an author accepts a job offer in their inbox, joining
// the publisher that sent it.
class AcceptOfferCommand : public ICommand
{
private:
	Session& session;
	size_t index;
public:
	AcceptOfferCommand(Session& session, size_t index);
	void execute() override;
};
