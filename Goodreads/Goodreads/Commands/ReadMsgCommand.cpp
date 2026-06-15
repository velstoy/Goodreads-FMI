#include "ReadMsgCommand.h"
#include <iostream>
#include "CommandUtils.h"

ReadMsgCommand::ReadMsgCommand(Session& session, size_t index)
	: session(session), index(index) {}

void ReadMsgCommand::execute()
{
	auto me = CommandUtils::requireLogin(session);
	Message& msg = me->getMessage(index);   // throws on bad index
	msg.markRead();
	std::cout << "From " << msg.getSenderName() << ": " << msg.getContents() << "\n";
}
void ReadMsgCommand::undo() {}
bool ReadMsgCommand::canUndo() const { return false; }
