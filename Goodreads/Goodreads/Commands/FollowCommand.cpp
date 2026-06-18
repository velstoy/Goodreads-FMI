#include "FollowCommand.h"
#include <iostream>
#include <format>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/InvalidArgumentException.h"

FollowCommand::FollowCommand(Session& session, const std::string& target)
	: session(session), target(target) {}

void FollowCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);
	if (target == me->getUsername())
		throw InvalidArgumentException("You cannot follow yourself!");

	auto user = UserRegistry::getInstance().find(target);
	if (!user)
		throw EntityNotFoundException("User", target);
	if (user->isFollowedBy(me->getUsername()))
		throw InvalidArgumentException("You already follow this user!");

	user->addFollower(me);
	user->receiveMessage(std::make_unique<Message>(
		me, false, std::format("{} started following you.", me->getUsername()), MessageType::FriendRequest));

	std::cout << "You are now following " << target << ".\n";
}
