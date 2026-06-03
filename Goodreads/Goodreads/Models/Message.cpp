#include "Message.h"

Message::Message(const std::weak_ptr<User>& sender, bool isRead, const std::string& contents)
	: sender(sender), isRead(isRead), contents(contents)
{
}
