#include "PublishCommand.h"
#include <iostream>
#include <format>
#include "CommandUtils.h"
#include "../Registries/BookRegistry.h"
#include "../Registries/UserRegistry.h"
#include "../Users/Author.h"
#include "../Models/Book.h"
#include "../Models/Genre.h"
#include "../Models/Date.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/InvalidArgumentException.h"
#include "../Exceptions/AccessDeniedException.h"

PublishCommand::PublishCommand(Session& session, const std::string& title, const std::string& authorName,
	const std::string& dateText, const std::string& pagesText, const std::vector<std::string>& genreTexts)
	: session(session), title(title), authorName(authorName), dateText(dateText),
	  pagesText(pagesText), genreTexts(genreTexts) {}

void PublishCommand::execute()
{
	auto publisher = CommandUtils::requirePublisher(session);

	if (BookRegistry::getInstance().find(title))
		throw InvalidArgumentException("a book with this title already exists.");

	auto user = UserRegistry::getInstance().find(authorName);
	if (!user)
		throw EntityNotFoundException("Author", authorName);
	auto author = std::dynamic_pointer_cast<Author>(user);
	if (!author)
		throw InvalidArgumentException("that user is not an author.");
	if (!publisher->hasAuthor(author->getUsername()))
		throw AccessDeniedException("you must sign this author (via an accepted offer) before publishing their books.");

	Date publishingDate = Date::parse(dateText);

	size_t pages = 0;
	try { pages = std::stoul(pagesText); }
	catch (...) { throw InvalidArgumentException("page count must be a non-negative number."); }

	std::vector<Genre> genres;
	for (const auto& g : genreTexts)
		genres.push_back(genreFromString(g));

	auto book = std::make_shared<Book>(title, author, publisher, "", genres,
		0.0, 0, publishingDate.getDay(), publishingDate.getMonth(), publishingDate.getYear(), pages);

	BookRegistry::getInstance().add(book);
	author->addPublishedBook(book);
	publisher->addPublishedBook(book);

	std::string notice = std::format("New book \"{}\" by {} (published by {}).",
		title, author->getUsername(), publisher->getUsername());
	size_t notified = 0;
	for (const auto& u : UserRegistry::getInstance().getAll())
	{
		const std::string& name = u->getUsername();
		if (name == author->getUsername() || name == publisher->getUsername())
			continue;
		if (author->isFollowedBy(name) || publisher->isFollowedBy(name))
		{
			u->receiveMessage(std::make_unique<Message>(publisher, false, notice, MessageType::Notification));
			++notified;
		}
	}

	std::cout << std::format("Published \"{}\" by {}. Notified {} follower(s).\n",
		title, author->getUsername(), notified);
}
