#include "LeaveCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Users/Publisher.h"
#include "../Exceptions/InvalidArgumentException.h"

LeaveCommand::LeaveCommand(Session& session, const std::string& publisherName)
	: session(session), publisherName(publisherName) {}

void LeaveCommand::execute()
{
	auto author = CommandUtils::requireAuthor(session);
	if (!author->worksWith(publisherName))
		throw InvalidArgumentException("you do not work with that publisher.");

	author->removePublisher(publisherName);

	// Keep the relationship symmetric if the publisher is still around.
	if (auto user = UserRegistry::getInstance().find(publisherName))
		if (auto publisher = std::dynamic_pointer_cast<Publisher>(user))
			publisher->removeAuthor(author->getUsername());

	std::cout << "You have left publisher " << publisherName << ".\n";
}
