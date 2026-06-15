#include "Message.h"
#include "../Users/User.h"

Message::Message(const std::weak_ptr<User>& sender, bool isRead, const std::string& contents, MessageType type)
	: sender(sender), isRead(isRead), contents(contents), type(type)
{
}

std::shared_ptr<User> Message::getSender() const { return sender.lock(); }

std::string Message::getSenderName() const
{
	auto s = sender.lock();
	return s ? s->getUsername() : "(deleted user)";
}

bool Message::getIsRead() const { return isRead; }
void Message::markRead() { isRead = true; }
const std::string& Message::getContents() const { return contents; }
MessageType Message::getType() const { return type; }
