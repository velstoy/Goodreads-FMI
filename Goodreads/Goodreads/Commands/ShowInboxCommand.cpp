#include "ShowInboxCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Exceptions/InvalidArgumentException.h"

namespace
{
	const char* typeLabel(MessageType type)
	{
		switch (type)
		{
		case MessageType::FriendRequest: return "friend-request";
		case MessageType::JobOffer:      return "job-offer";
		case MessageType::Notification:  return "notification";
		default:                         return "message";
		}
	}
}

ShowInboxCommand::ShowInboxCommand(Session& session, const std::optional<std::string>& filter)
	: session(session), filter(filter) {}

void ShowInboxCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);

	std::optional<MessageType> wanted;
	if (filter.has_value())
	{
		if (*filter == "friends")     wanted = MessageType::FriendRequest;
		else if (*filter == "offers") wanted = MessageType::JobOffer;
		else throw InvalidArgumentException("unknown inbox filter (use 'friends' or 'offers').");
	}

	const auto& inbox = me->getInbox();
	bool any = false;
	std::cout << "Inbox:\n";
	for (size_t i = 0; i < inbox.size(); ++i)
	{
		const Message& msg = *inbox[i];
		if (wanted.has_value() && msg.getType() != *wanted)
			continue;
		any = true;
		std::cout << "  [" << i << "] " << (msg.getIsRead() ? "(read)   " : "(unread) ")
			<< "from " << msg.getSenderName()
			<< " [" << typeLabel(msg.getType()) << "]: " << msg.getContents() << "\n";
	}
	if (!any)
		std::cout << "  (no messages)\n";
}
void ShowInboxCommand::undo() {}
bool ShowInboxCommand::canUndo() const { return false; }
