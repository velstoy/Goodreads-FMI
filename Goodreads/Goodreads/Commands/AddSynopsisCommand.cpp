#include "AddSynopsisCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/BookRegistry.h"
#include "../Models/Book.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/AccessDeniedException.h"

AddSynopsisCommand::AddSynopsisCommand(Session& session, const std::string& title, const std::string& synopsis)
	: session(session), title(title), synopsis(synopsis) {}

void AddSynopsisCommand::execute()
{
	auto publisher = CommandUtils::requirePublisher(session);
	auto book = BookRegistry::getInstance().find(title);
	if (!book)
		throw EntityNotFoundException("Book", title);
	if (book->getPublisherName() != publisher->getUsername())
		throw AccessDeniedException("only the book's publisher can set its synopsis.");

	book->setResume(synopsis);
	std::cout << "Synopsis updated for \"" << title << "\".\n";
}
