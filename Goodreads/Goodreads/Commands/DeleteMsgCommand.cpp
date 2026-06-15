#include "DeleteMsgCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Exceptions/InvalidArgumentException.h"

DeleteMsgCommand::DeleteMsgCommand(Session& session, size_t index)
	: session(session), index(index) {}

void DeleteMsgCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);
	Message& msg = me->getMessage(index);   // throws on bad index
	if (!msg.getIsRead())
		throw InvalidArgumentException("read the message before deleting it.");
	me->removeMessage(index);
	std::cout << "Message deleted.\n";
}
void DeleteMsgCommand::undo() {}
bool DeleteMsgCommand::canUndo() const { return false; }
