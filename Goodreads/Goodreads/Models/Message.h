#pragma once
#include "../Users/User.h"

class Message
{
private:
	User sender;
	bool isRead = false;
	std::string contents;

public:
	Message(const User& sender, bool isRead, const std::string& contents);
};

