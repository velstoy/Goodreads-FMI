#pragma once
#include <string>
#include "ICommand.h"
#include "../Core/Session.h"

// offer <author> : a publisher sends a job offer to an author's inbox.
class OfferCommand : public ICommand
{
private:
	Session& session;
	std::string authorName;
public:
	OfferCommand(Session& session, const std::string& authorName);
	void execute() override;
	void undo() override;
	bool canUndo() const override;
};
