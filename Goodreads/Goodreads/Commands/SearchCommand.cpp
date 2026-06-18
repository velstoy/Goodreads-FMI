#include "SearchCommand.h"
#include <iostream>
#include <format>
#include "CommandUtils.h"
#include "../Core/StringUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Registries/BookRegistry.h"

constexpr size_t MAX_TYPOS = 2;

SearchCommand::SearchCommand(Session& session, const std::string& query)
	: session(session), query(query) {}

void SearchCommand::execute()
{
	CommandUtils::requireLogin(session);

	std::cout << "Users:\n";
	for (const auto& user : UserRegistry::getInstance().getAll())
		if (StringUtils::editDistance(user->getUsername(), query) <= MAX_TYPOS)
			std::cout << "  " << user->getUsername() << " (" << user->getType() << ")\n";

	std::cout << "Books:\n";
	for (const auto& book : BookRegistry::getInstance().getAll())
		if (StringUtils::editDistance(book->getName(), query) <= MAX_TYPOS)
			std::cout << std::format("  {} ({:.2f})\n", book->getName(), book->getAverageRating());
}
