#pragma once
#include <memory>
#include "../Core/Session.h"
#include "../Users/Reader.h"
#include "../Users/Author.h"
#include "../Users/Publisher.h"
#include "../Exceptions/AccessDeniedException.h"

namespace CommandUtils
{
	inline std::shared_ptr<User> requireLogin(Session& session)
	{
		if (!session.isLoggedIn())
			throw AccessDeniedException("you must be logged in to do that.");
		return session.getCurrentUser();
	}

	inline std::shared_ptr<Reader> requireReader(Session& session)
	{
		auto reader = std::dynamic_pointer_cast<Reader>(requireLogin(session));
		if (!reader)
			throw AccessDeniedException("this command is available to readers and authors only.");
		return reader;
	}

	inline std::shared_ptr<Author> requireAuthor(Session& session)
	{
		auto author = std::dynamic_pointer_cast<Author>(requireLogin(session));
		if (!author)
			throw AccessDeniedException("this command is available to authors only.");
		return author;
	}

	inline std::shared_ptr<Publisher> requirePublisher(Session& session)
	{
		auto publisher = std::dynamic_pointer_cast<Publisher>(requireLogin(session));
		if (!publisher)
			throw AccessDeniedException("this command is available to publishers only.");
		return publisher;
	}
}
