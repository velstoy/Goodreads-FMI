#pragma once
#include <string>
#include <memory>

class User;

class Message
{
private:
	std::weak_ptr<User> sender;
	bool isRead = false;
	std::string contents;

public:
	Message(const std::weak_ptr<User>& sender, bool isRead, const std::string& contents);
};

