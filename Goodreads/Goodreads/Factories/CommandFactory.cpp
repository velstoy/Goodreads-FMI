#include "CommandFactory.h"
#include <stdexcept>
#include "../Core/StringUtils.h"
#include "../Exceptions/CommandException.h"

#include "../Commands/HelpCommand.h"
#include "../Commands/RegisterCommand.h"
#include "../Commands/LoginCommand.h"
#include "../Commands/LogoutCommand.h"
#include "../Commands/ExitCommand.h"
#include "../Commands/SearchCommand.h"
#include "../Commands/FollowCommand.h"
#include "../Commands/AddBookCommand.h"
#include "../Commands/CreateShelfCommand.h"
#include "../Commands/DeleteShelfCommand.h"
#include "../Commands/AddToShelfCommand.h"
#include "../Commands/RemoveFromShelfCommand.h"
#include "../Commands/DeleteBookCommand.h"
#include "../Commands/ShowShelfCommand.h"
#include "../Commands/ShowInboxCommand.h"
#include "../Commands/ReadMsgCommand.h"
#include "../Commands/DeleteMsgCommand.h"
#include "../Commands/FriendsCommand.h"
#include "../Commands/AddBirthdayCommand.h"
#include "../Commands/ProfileCommand.h"
#include "../Commands/PublishCommand.h"
#include "../Commands/AddSynopsisCommand.h"
#include "../Commands/OfferCommand.h"
#include "../Commands/AcceptOfferCommand.h"
#include "../Commands/LeaveCommand.h"
#include "../Commands/FollowersCommand.h"

namespace
{
	// argc = number of arguments after the command name.
	void requireArgs(const std::string& cmd, size_t argc, size_t min, size_t max)
	{
		if (argc < min || argc > max)
			throw CommandException("wrong number of arguments for '" + cmd + "'.");
	}

	size_t parseIndex(const std::string& cmd, const std::string& text)
	{
		try { return static_cast<size_t>(std::stoul(text)); }
		catch (...) { throw CommandException("'" + cmd + "' expects a numeric index."); }
	}
}

std::unique_ptr<ICommand> CommandFactory::create(const std::vector<std::string>& tokens,
	Session& session, bool& running, const std::string& savePath)
{
	const std::string& cmd = tokens[0];
	const size_t argc = tokens.size() - 1;

	if (cmd == "help")
	{
		requireArgs(cmd, argc, 0, 0);
		return std::make_unique<HelpCommand>(session);
	}
	if (cmd == "exit")
	{
		requireArgs(cmd, argc, 0, 0);
		return std::make_unique<ExitCommand>(running, savePath);
	}
	if (cmd == "register")
	{
		requireArgs(cmd, argc, 3, 3);
		return std::make_unique<RegisterCommand>(tokens[1], tokens[2], tokens[3]);
	}
	if (cmd == "login")
	{
		requireArgs(cmd, argc, 2, 2);
		return std::make_unique<LoginCommand>(session, tokens[1], tokens[2]);
	}
	if (cmd == "logout")
	{
		requireArgs(cmd, argc, 0, 0);
		return std::make_unique<LogoutCommand>(session);
	}

	if (cmd == "search")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<SearchCommand>(session, tokens[1]);
	}
	if (cmd == "follow")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<FollowCommand>(session, tokens[1]);
	}
	if (cmd == "add-book")
	{
		requireArgs(cmd, argc, 2, 3);
		std::optional<std::string> rating;
		if (argc == 3)
			rating = tokens[3];
		return std::make_unique<AddBookCommand>(session, tokens[1], tokens[2], rating);
	}
	if (cmd == "create-shelf")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<CreateShelfCommand>(session, tokens[1]);
	}
	if (cmd == "delete-shelf")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<DeleteShelfCommand>(session, tokens[1]);
	}
	if (cmd == "add-to-shelf")
	{
		requireArgs(cmd, argc, 2, 2);
		return std::make_unique<AddToShelfCommand>(session, tokens[1], tokens[2]);
	}
	if (cmd == "remove-from-shelf")
	{
		requireArgs(cmd, argc, 2, 2);
		return std::make_unique<RemoveFromShelfCommand>(session, tokens[1], tokens[2]);
	}
	if (cmd == "delete-book")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<DeleteBookCommand>(session, tokens[1]);
	}
	if (cmd == "show-shelf")
	{
		requireArgs(cmd, argc, 1, 2);
		if (argc == 1)
			return std::make_unique<ShowShelfCommand>(session, std::nullopt, tokens[1]);
		return std::make_unique<ShowShelfCommand>(session, tokens[1], tokens[2]);
	}
	if (cmd == "show-inbox")
	{
		requireArgs(cmd, argc, 0, 1);
		std::optional<std::string> filter;
		if (argc == 1)
			filter = tokens[1];
		return std::make_unique<ShowInboxCommand>(session, filter);
	}
	if (cmd == "read-msg")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<ReadMsgCommand>(session, parseIndex(cmd, tokens[1]));
	}
	if (cmd == "delete-msg")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<DeleteMsgCommand>(session, parseIndex(cmd, tokens[1]));
	}
	if (cmd == "friends")
	{
		requireArgs(cmd, argc, 0, 1);
		std::optional<std::string> reader;
		if (argc == 1)
			reader = tokens[1];
		return std::make_unique<FriendsCommand>(session, reader);
	}
	if (cmd == "add-birthday")
	{
		requireArgs(cmd, argc, 0, 1);
		std::optional<std::string> date;
		if (argc == 1)
			date = tokens[1];
		return std::make_unique<AddBirthdayCommand>(session, date);
	}
	if (cmd == "profile")
	{
		requireArgs(cmd, argc, 0, 1);
		std::optional<std::string> user;
		if (argc == 1)
			user = tokens[1];
		return std::make_unique<ProfileCommand>(session, user);
	}

	if (cmd == "publish")
	{
		// title author date pages [genres...]
		requireArgs(cmd, argc, 4, static_cast<size_t>(-1));
		std::vector<std::string> genres(tokens.begin() + 5, tokens.end());
		return std::make_unique<PublishCommand>(session, tokens[1], tokens[2], tokens[3], tokens[4], genres);
	}
	if (cmd == "add-synopsis")
	{
		requireArgs(cmd, argc, 2, static_cast<size_t>(-1));
		return std::make_unique<AddSynopsisCommand>(session, tokens[1], StringUtils::join(tokens, 2));
	}
	if (cmd == "offer")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<OfferCommand>(session, tokens[1]);
	}

	if (cmd == "accept-offer")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<AcceptOfferCommand>(session, parseIndex(cmd, tokens[1]));
	}
	if (cmd == "leave")
	{
		requireArgs(cmd, argc, 1, 1);
		return std::make_unique<LeaveCommand>(session, tokens[1]);
	}
	if (cmd == "followers")
	{
		requireArgs(cmd, argc, 0, 0);
		return std::make_unique<FollowersCommand>(session);
	}

	throw CommandException("unknown command '" + cmd + "'. Type 'help' for the list.");
}
