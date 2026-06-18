#pragma once
#include <string>
#include <memory>

class User;

enum class MessageType { General, FriendRequest, JobOffer, Notification };

class Message
{
private:
	std::weak_ptr<User> sender;
	bool isRead = false;
	std::string contents;
	MessageType type = MessageType::General;

public:
	Message(const std::weak_ptr<User>& sender, bool isRead, const std::string& contents, MessageType type = MessageType::General);

	std::shared_ptr<User> getSender() const;
	std::string getSenderName() const;   // "(deleted user)" if the sender is gone
	bool getIsRead() const;
	void markRead();
	const std::string& getContents() const;
	MessageType getType() const;
};
