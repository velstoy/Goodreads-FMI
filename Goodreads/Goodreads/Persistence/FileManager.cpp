#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <optional>

#include "../Core/StringUtils.h"
#include "../Registries/UserRegistry.h"
#include "../Registries/BookRegistry.h"
#include "../Factories/UserFactory.h"
#include "../Users/Reader.h"
#include "../Users/Author.h"
#include "../Users/Publisher.h"
#include "../Models/Book.h"
#include "../Models/Shelf.h"
#include "../Models/Genre.h"
#include "../Models/ReadingStatus.h"
#include "../Models/Message.h"
#include "../Models/Date.h"

namespace
{
	// Separators placed between saved fields. These characters never appear in
	// normal text, so a title or synopsis with spaces won't clash with them.
	const char US = '\x1F';   // field within a record line
	const char RS = '\x1E';   // element within a list
	const char GS = '\x1D';   // field within a list element
	const char FS = '\x1C';   // deepest list (book titles inside a shelf)

	std::string joinList(const std::vector<std::string>& parts, char delim)
	{
		std::string out;
		for (size_t i = 0; i < parts.size(); ++i)
		{
			if (i) out += delim;
			out += parts[i];
		}
		return out;
	}

	// Splits into fields, keeping empty ones so a record always has the same count.
	std::vector<std::string> splitFields(const std::string& s, char delim)
	{
		std::vector<std::string> out;
		std::string cur;
		for (char c : s)
		{
			if (c == delim) { out.push_back(cur); cur.clear(); }
			else cur += c;
		}
		out.push_back(cur);
		return out;
	}

	// Splits a list; an empty string yields an empty list.
	std::vector<std::string> splitList(const std::string& s, char delim)
	{
		if (s.empty()) return {};
		return splitFields(s, delim);
	}

	std::string field(const std::vector<std::string>& f, size_t i)
	{
		return i < f.size() ? f[i] : std::string();
	}
}

void FileManager::save(const std::string& path)
{
	std::ofstream out(path, std::ios::trunc);
	if (!out) return;

	// ---- books ----
	const auto& books = BookRegistry::getInstance().getAll();
	out << "BOOKS " << books.size() << "\n";
	for (const auto& book : books)
	{
		std::vector<std::string> genres;
		for (Genre g : book->getGenres())
			genres.push_back(genreToString(g));

		std::ostringstream line;
		line << book->getName() << US
			<< book->getAuthorName() << US
			<< book->getPublisherName() << US
			<< book->getResume() << US
			<< joinList(genres, RS) << US
			<< book->getAverageRating() << US
			<< book->getNumberOfRatings() << US
			<< book->getPublishingDate().toString() << US
			<< book->getNumberOfPages();
		out << line.str() << "\n";
	}

	// ---- users ----
	const auto& users = UserRegistry::getInstance().getAll();
	out << "USERS " << users.size() << "\n";
	for (const auto& user : users)
	{
		// store the type in lower case (reader/author/publisher) for loading back
		std::string type = StringUtils::toLower(user->getType());

		std::vector<std::string> followers;
		for (const auto& w : user->getFollowers())
			if (auto f = w.lock())
				followers.push_back(f->getUsername());

		// inbox (every user has one)
		std::vector<std::string> inbox;
		for (const auto& msg : user->getInbox())
		{
			auto sender = msg->getSender();
			std::string senderName = sender ? sender->getUsername() : "";
			std::ostringstream m;
			m << senderName << GS
				<< static_cast<int>(msg->getType()) << GS
				<< (msg->getIsRead() ? 1 : 0) << GS
				<< msg->getContents();
			inbox.push_back(m.str());
		}

		std::string birthday, profileBooks, shelves, favorites;
		std::string authorPublishers, publisherAuthors;

		if (auto reader = std::dynamic_pointer_cast<Reader>(user))
		{
			if (reader->getBirthday().has_value())
				birthday = reader->getBirthday()->toString();

			std::vector<std::string> pb;
			for (const auto& entry : reader->getProfileBooks())
			{
				auto book = entry.book.lock();
				if (!book) continue;
				std::ostringstream e;
				e << book->getName() << GS
					<< readingStatusToString(entry.status) << GS
					<< (entry.rating.has_value() ? std::to_string(*entry.rating) : "");
				pb.push_back(e.str());
			}
			profileBooks = joinList(pb, RS);

			std::vector<std::string> sh;
			for (const auto& shelf : reader->getShelves())
			{
				std::vector<std::string> titles;
				for (const auto& b : shelf.getBooks())
					titles.push_back(b->getName());
				std::ostringstream e;
				e << shelf.getName() << GS
					<< shelf.getCreationDate().toString() << GS
					<< joinList(titles, FS);
				sh.push_back(e.str());
			}
			shelves = joinList(sh, RS);

			std::vector<std::string> fav;
			for (const auto& b : reader->getFavorites())
				fav.push_back(b->getName());
			favorites = joinList(fav, RS);
		}

		if (auto author = std::dynamic_pointer_cast<Author>(user))
		{
			std::vector<std::string> pubs;
			for (const auto& p : author->getPublishers())
				pubs.push_back(p->getUsername());
			authorPublishers = joinList(pubs, RS);
		}

		if (auto publisher = std::dynamic_pointer_cast<Publisher>(user))
		{
			std::vector<std::string> auths;
			for (const auto& a : publisher->getAuthors())
				auths.push_back(a->getUsername());
			publisherAuthors = joinList(auths, RS);
		}

		std::ostringstream line;
		line << type << US
			<< user->getUsername() << US
			<< user->getPassword() << US
			<< user->getRegistrationDate().toString() << US
			<< birthday << US
			<< joinList(followers, RS) << US
			<< profileBooks << US
			<< shelves << US
			<< favorites << US
			<< joinList(inbox, RS) << US
			<< authorPublishers << US
			<< publisherAuthors;
		out << line.str() << "\n";
	}
}

void FileManager::load(const std::string& path)
{
	std::ifstream in(path);
	if (!in) return;   // first run: nothing to load

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line))
	{
		if (!line.empty() && line.back() == '\r') line.pop_back();   // tolerate CRLF
		lines.push_back(line);
	}
	if (lines.empty()) return;

	UserRegistry::getInstance().clear();
	BookRegistry::getInstance().clear();

	size_t pos = 0;

	auto readCount = [&](const std::string& tag) -> size_t {
		if (pos >= lines.size()) return 0;
		std::istringstream header(lines[pos++]);
		std::string word; size_t count = 0;
		header >> word >> count;
		(void)tag;
		return count;
	};

	// ---- books (raw) ----
	size_t bookCount = readCount("BOOKS");
	std::vector<std::vector<std::string>> bookRecords;
	for (size_t i = 0; i < bookCount && pos < lines.size(); ++i)
		bookRecords.push_back(splitFields(lines[pos++], US));

	// ---- users (raw) ----
	size_t userCount = readCount("USERS");
	std::vector<std::vector<std::string>> userRecords;
	for (size_t i = 0; i < userCount && pos < lines.size(); ++i)
		userRecords.push_back(splitFields(lines[pos++], US));

	// PASS 1: create users (no relationships yet).
	for (const auto& r : userRecords)
	{
		std::string type = field(r, 0);
		std::string username = field(r, 1);
		std::string password = field(r, 2);
		Date regDate = Date::parse(field(r, 3));
		std::optional<Date> birthday;
		if (!field(r, 4).empty())
			birthday = Date::parse(field(r, 4));

		UserRegistry::getInstance().add(
			UserFactory::createUser(type, username, password, regDate, birthday));
	}

	// PASS 2: create books and re-link them to their author/publisher.
	for (const auto& r : bookRecords)
	{
		std::string name = field(r, 0);
		std::string authorName = field(r, 1);
		std::string publisherName = field(r, 2);
		std::string resume = field(r, 3);

		std::vector<Genre> genres;
		for (const auto& g : splitList(field(r, 4), RS))
			genres.push_back(genreFromString(g));

		double avg = field(r, 5).empty() ? 0.0 : std::stod(field(r, 5));
		size_t numRatings = field(r, 6).empty() ? 0 : static_cast<size_t>(std::stoul(field(r, 6)));
		Date pub = Date::parse(field(r, 7));
		size_t pages = field(r, 8).empty() ? 0 : static_cast<size_t>(std::stoul(field(r, 8)));

		auto author = std::dynamic_pointer_cast<Author>(UserRegistry::getInstance().find(authorName));
		auto publisher = std::dynamic_pointer_cast<Publisher>(UserRegistry::getInstance().find(publisherName));

		auto book = std::make_shared<Book>(name, author, publisher, resume, genres,
			avg, numRatings, pub.getDay(), pub.getMonth(), pub.getYear(), pages);

		BookRegistry::getInstance().add(book);
		if (author) author->addPublishedBook(book);
		if (publisher) publisher->addPublishedBook(book);
	}

	// PASS 3: wire up the user relationships now that everything exists.
	for (const auto& r : userRecords)
	{
		auto user = UserRegistry::getInstance().find(field(r, 1));
		if (!user) continue;

		for (const auto& name : splitList(field(r, 5), RS))
			if (auto follower = UserRegistry::getInstance().find(name))
				user->addFollower(follower);

		// reader-specific state
		if (auto reader = std::dynamic_pointer_cast<Reader>(user))
		{
			for (const auto& e : splitList(field(r, 6), RS))
			{
				auto parts = splitFields(e, GS);
				auto book = BookRegistry::getInstance().find(field(parts, 0));
				if (!book) continue;
				ReadingStatus status = readingStatusFromString(field(parts, 1));
				std::optional<double> rating;
				if (!field(parts, 2).empty())
					rating = std::stod(field(parts, 2));
				reader->restoreBook(book, status, rating);
			}

			for (const auto& e : splitList(field(r, 7), RS))
			{
				auto parts = splitFields(e, GS);
				Date created = Date::parse(field(parts, 1));
				Shelf shelf(field(parts, 0), created.getDay(), created.getMonth(), created.getYear());
				for (const auto& title : splitList(field(parts, 2), FS))
					if (auto book = BookRegistry::getInstance().find(title))
						shelf.addBook(book);
				reader->restoreShelf(shelf);
			}

			for (const auto& title : splitList(field(r, 8), RS))
				if (auto book = BookRegistry::getInstance().find(title))
					reader->addFavorite(book);
		}

		// inbox (all users)
		for (const auto& e : splitList(field(r, 9), RS))
		{
			auto parts = splitFields(e, GS);
			auto sender = UserRegistry::getInstance().find(field(parts, 0));   // may be null
			auto type = static_cast<MessageType>(std::stoi(field(parts, 1)));
			bool isRead = field(parts, 2) == "1";
			std::string contents = field(parts, 3);
			user->receiveMessage(std::make_unique<Message>(sender, isRead, contents, type));
		}

		if (auto author = std::dynamic_pointer_cast<Author>(user))
			for (const auto& name : splitList(field(r, 10), RS))
				if (auto publisher = std::dynamic_pointer_cast<Publisher>(UserRegistry::getInstance().find(name)))
					author->addPublisher(publisher);

		if (auto publisher = std::dynamic_pointer_cast<Publisher>(user))
			for (const auto& name : splitList(field(r, 11), RS))
				if (auto a = std::dynamic_pointer_cast<Author>(UserRegistry::getInstance().find(name)))
					publisher->addAuthor(a);
	}
}
