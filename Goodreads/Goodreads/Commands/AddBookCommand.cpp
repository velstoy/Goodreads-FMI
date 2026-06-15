#include "AddBookCommand.h"
#include <iostream>
#include "CommandUtils.h"
#include "../Registries/BookRegistry.h"
#include "../Models/ReadingStatus.h"
#include "../Exceptions/EntityNotFoundException.h"
#include "../Exceptions/InvalidArgumentException.h"

AddBookCommand::AddBookCommand(Session& session, const std::string& bookName,
	const std::string& statusText, const std::optional<std::string>& ratingText)
	: session(session), bookName(bookName), statusText(statusText), ratingText(ratingText) {}

void AddBookCommand::execute()
{
	auto reader = CommandUtils::requireReader(session);
	auto book = BookRegistry::getInstance().find(bookName);
	if (!book)
		throw EntityNotFoundException("Book", bookName);

	ReadingStatus status = readingStatusFromString(statusText);

	std::optional<double> rating;
	if (ratingText.has_value())
	{
		double value;
		try { value = std::stod(*ratingText); }
		catch (...) { throw InvalidArgumentException("rating must be a number between 0 and 10!"); }
		if (value < 0.0 || value > 10.0)
			throw InvalidArgumentException("rating must be between 0 and 10!");
		rating = value;
	}

	reader->addBook(book, status, rating);
	std::cout << "Added \"" << bookName << "\" to your profile.\n";
}
void AddBookCommand::undo() {}
bool AddBookCommand::canUndo() const { return false; }
