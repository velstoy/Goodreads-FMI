#include "Message.h"

Message::Message(const User& sender, bool isRead, const std::string& contents)
	: sender(sender), isRead(isRead), contents(contents)
{
}
