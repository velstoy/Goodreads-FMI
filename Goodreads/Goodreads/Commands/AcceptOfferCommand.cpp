#include "AcceptOfferCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Users/Publisher.h"
#include "../Exceptions/InvalidArgumentException.h"

AcceptOfferCommand::AcceptOfferCommand(Session& session, size_t index)
	: session(session), index(index) {}

void AcceptOfferCommand::execute()
{
	auto author = CommandUtils::requireAuthor(session);
	Message& msg = author->getMessage(index);   // throws on bad index
	if (msg.getType() != MessageType::JobOffer)
		throw InvalidArgumentException("that message is not a job offer.");

	auto sender = msg.getSender();
	auto publisher = std::dynamic_pointer_cast<Publisher>(sender);
	if (!publisher)
		throw InvalidArgumentException("the publisher who sent this offer no longer exists.");

	author->addPublisher(publisher);
	publisher->addAuthor(author);
	msg.markRead();

	std::cout << "You now work with publisher " << publisher->getUsername() << ".\n";
}
void AcceptOfferCommand::undo() {}
bool AcceptOfferCommand::canUndo() const { return false; }
