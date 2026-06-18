#include "FriendsCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Exceptions/EntityNotFoundException.h"

FriendsCommand::FriendsCommand(Session& session, const std::optional<std::string>& readerName)
	: session(session), readerName(readerName) {}

void FriendsCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);

	std::shared_ptr<User> target = me;
	if (readerName.has_value() && *readerName != me->getUsername())
	{
		target = UserRegistry::getInstance().find(*readerName);
		if (!target)
			throw EntityNotFoundException("User", *readerName);
	}

	std::cout << target->getUsername() << "'s friends:\n";
	bool any = false;
	for (const auto& user : UserRegistry::getInstance().getAll())
	{
		if (user->getUsername() == target->getUsername())
			continue;
		if (target->isFriendWith(*user))
		{
			std::cout << "  " << user->getUsername() << " (" << user->getType() << ")\n";
			any = true;
		}
	}
	if (!any)
		std::cout << "  (none)\n";
}
