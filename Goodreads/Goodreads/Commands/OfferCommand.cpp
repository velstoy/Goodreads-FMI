#include "OfferCommand.h"
#include <iostream>
#include <format>
#include "CommandUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Users/Author.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/InvalidArgumentException.h"

OfferCommand::OfferCommand(Session& session, const std::string& authorName)
	: session(session), authorName(authorName) {}

void OfferCommand::execute()
{
	auto publisher = CommandUtils::requirePublisher(session);

	auto user = UserRegistry::getInstance().find(authorName);
	if (!user)
		throw EntityNotFoundException("Author", authorName);
	auto author = std::dynamic_pointer_cast<Author>(user);
	if (!author)
		throw InvalidArgumentException("that user is not an author.");
	if (publisher->hasAuthor(authorName))
		throw InvalidArgumentException("this author already works with you.");

	author->receiveMessage(std::make_unique<Message>(publisher, false,
		std::format("Job offer from publisher {}.", publisher->getUsername()), MessageType::JobOffer));

	std::cout << "Offer sent to " << authorName << ".\n";
}
void OfferCommand::undo() {}
bool OfferCommand::canUndo() const { return false; }
