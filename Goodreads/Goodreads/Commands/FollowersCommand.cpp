#include "FollowersCommand.h"
#include <iostream>
#include "CommandUtils.h"

FollowersCommand::FollowersCommand(Session& session)
	: session(session) {}

void FollowersCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);
	const auto& followers = me->getFollowers();
	std::cout << "Followers (" << followers.size() << "):\n";
	bool any = false;
	for (const auto& weak : followers)
	{
		if (auto follower = weak.lock())
		{
			std::cout << "  " << follower->getUsername() << " (" << follower->getType() << ")\n";
			any = true;
		}
	}
	if (!any)
		std::cout << "  (none)\n";
}
void FollowersCommand::undo() {}
bool FollowersCommand::canUndo() const { return false; }
