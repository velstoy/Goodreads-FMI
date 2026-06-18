#include "FileManager.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include <vector>
#include <string>
#include <memory>
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

void FileManager::saveDate(BinaryWriter& out, const Date& date)
{
	out.writeUInt(date.getDay());
	out.writeUInt(date.getMonth());
	out.writeUInt(date.getYear());
}

void FileManager::saveUserBasics(BinaryWriter& out, const std::shared_ptr<User>& user)
{
	out.writeString(StringUtils::toLower(user->getType()));   // reader/author/publisher
	out.writeString(user->getUsername());
	out.writeString(user->getPassword());
	saveDate(out, user->getRegistrationDate());

	auto reader = std::dynamic_pointer_cast<Reader>(user);
	bool hasBirthday = reader && reader->getBirthday().has_value();
	out.writeBool(hasBirthday);
	if (hasBirthday)
		saveDate(out, *reader->getBirthday());
}

void FileManager::saveBook(BinaryWriter& out, const Book& book)
{
	out.writeString(book.getName());
	out.writeString(book.getAuthorName());
	out.writeString(book.getPublisherName());
	out.writeString(book.getResume());

	std::vector<std::string> genres;
	for (Genre genre : book.getGenres())
		genres.push_back(genreToString(genre));
	out.writeStringList(genres);

	out.writeDouble(book.getAverageRating());
	out.writeUInt(book.getNumberOfRatings());
	saveDate(out, book.getPublishingDate());
	out.writeUInt(book.getNumberOfPages());
}

void FileManager::saveProfileBooks(BinaryWriter& out, const Reader& reader)
{
	const auto& entries = reader.getProfileBooks();
	out.writeUInt(entries.size());
	for (const auto& entry : entries)
	{
		out.writeString(entry.book.lock()->getName());
		out.writeString(readingStatusToString(entry.status));
		out.writeBool(entry.rating.has_value());
		if (entry.rating.has_value())
			out.writeDouble(*entry.rating);
	}
}

void FileManager::saveShelves(BinaryWriter& out, const Reader& reader)
{
	const auto& shelves = reader.getShelves();
	out.writeUInt(shelves.size());
	for (const auto& shelf : shelves)
	{
		out.writeString(shelf.getName());
		saveDate(out, shelf.getCreationDate());

		std::vector<std::string> titles;
		for (const auto& book : shelf.getBooks())
			titles.push_back(book->getName());
		out.writeStringList(titles);
	}
}

void FileManager::saveFavorites(BinaryWriter& out, const Reader& reader)
{
	std::vector<std::string> titles;
	for (const auto& book : reader.getFavorites())
		titles.push_back(book->getName());
	out.writeStringList(titles);
}

void FileManager::saveInbox(BinaryWriter& out, const User& user)
{
	const auto& inbox = user.getInbox();
	out.writeUInt(inbox.size());
	for (const auto& message : inbox)
	{
		auto sender = message->getSender();
		out.writeString(sender ? sender->getUsername() : "");
		out.writeUInt(static_cast<unsigned long long>(message->getType()));
		out.writeBool(message->getIsRead());
		out.writeString(message->getContents());
	}
}

void FileManager::saveUserRelations(BinaryWriter& out, const std::shared_ptr<User>& user)
{
	out.writeString(user->getUsername());

	std::vector<std::string> followers;
	for (const auto& weak : user->getFollowers())
		if (auto follower = weak.lock())
			followers.push_back(follower->getUsername());
	out.writeStringList(followers);

	if (auto reader = std::dynamic_pointer_cast<Reader>(user))
	{
		saveProfileBooks(out, *reader);
		saveShelves(out, *reader);
		saveFavorites(out, *reader);
	}

	saveInbox(out, *user);

	if (auto author = std::dynamic_pointer_cast<Author>(user))
	{
		std::vector<std::string> publishers;
		for (const auto& publisher : author->getPublishers())
			publishers.push_back(publisher->getUsername());
		out.writeStringList(publishers);
	}

	if (auto publisher = std::dynamic_pointer_cast<Publisher>(user))
	{
		std::vector<std::string> authors;
		for (const auto& author : publisher->getAuthors())
			authors.push_back(author->getUsername());
		out.writeStringList(authors);
	}
}

void FileManager::save(const std::string& path)
{
	BinaryWriter out(path);
	if (!out.isOpen())
		return;

	const auto& users = UserRegistry::getInstance().getAll();
	const auto& books = BookRegistry::getInstance().getAll();

	out.writeUInt(users.size());
	for (const auto& user : users)
		saveUserBasics(out, user);

	out.writeUInt(books.size());
	for (const auto& book : books)
		saveBook(out, *book);

	out.writeUInt(users.size());
	for (const auto& user : users)
		saveUserRelations(out, user);
}

Date FileManager::loadDate(BinaryReader& in)
{
	int day = static_cast<int>(in.readUInt());
	int month = static_cast<int>(in.readUInt());
	int year = static_cast<int>(in.readUInt());
	return Date(day, month, year);
}

void FileManager::loadUsers(BinaryReader& in)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		std::string type = in.readString();
		std::string username = in.readString();
		std::string password = in.readString();
		Date registrationDate = loadDate(in);

		std::optional<Date> birthday;
		if (in.readBool())
			birthday = loadDate(in);

		UserRegistry::getInstance().add(
			UserFactory::createUser(type, username, password, registrationDate, birthday));
	}
}

void FileManager::loadBooks(BinaryReader& in)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		std::string name = in.readString();
		std::string authorName = in.readString();
		std::string publisherName = in.readString();
		std::string resume = in.readString();

		std::vector<Genre> genres;
		for (const auto& genre : in.readStringList())
			genres.push_back(genreFromString(genre));

		double averageRating = in.readDouble();
		size_t numberOfRatings = static_cast<size_t>(in.readUInt());
		Date publishingDate = loadDate(in);
		size_t numberOfPages = static_cast<size_t>(in.readUInt());

		auto author = std::dynamic_pointer_cast<Author>(UserRegistry::getInstance().find(authorName));
		auto publisher = std::dynamic_pointer_cast<Publisher>(UserRegistry::getInstance().find(publisherName));

		auto book = std::make_shared<Book>(name, author, publisher, resume, genres,
			averageRating, numberOfRatings,
			publishingDate.getDay(), publishingDate.getMonth(), publishingDate.getYear(),
			numberOfPages);

		BookRegistry::getInstance().add(book);
		if (author) author->addPublishedBook(book);
		if (publisher) publisher->addPublishedBook(book);
	}
}

void FileManager::loadProfileBooks(BinaryReader& in, Reader& reader)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		std::string title = in.readString();
		ReadingStatus status = readingStatusFromString(in.readString());

		std::optional<double> rating;
		if (in.readBool())
			rating = in.readDouble();

		if (auto book = BookRegistry::getInstance().find(title))
			reader.restoreBook(book, status, rating);
	}
}

void FileManager::loadShelves(BinaryReader& in, Reader& reader)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		std::string name = in.readString();
		Date created = loadDate(in);

		Shelf shelf(name, created.getDay(), created.getMonth(), created.getYear());
		for (const auto& title : in.readStringList())
			if (auto book = BookRegistry::getInstance().find(title))
				shelf.addBook(book);

		reader.restoreShelf(shelf);
	}
}

void FileManager::loadFavorites(BinaryReader& in, Reader& reader)
{
	for (const auto& title : in.readStringList())
		if (auto book = BookRegistry::getInstance().find(title))
			reader.addFavorite(book);
}

void FileManager::loadInbox(BinaryReader& in, User& user)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		std::string senderName = in.readString();
		auto type = static_cast<MessageType>(in.readUInt());
		bool isRead = in.readBool();
		std::string contents = in.readString();

		auto sender = UserRegistry::getInstance().find(senderName);   // may be null
		user.receiveMessage(std::make_unique<Message>(sender, isRead, contents, type));
	}
}

void FileManager::loadRelations(BinaryReader& in)
{
	unsigned long long count = in.readUInt();
	for (unsigned long long i = 0; i < count; ++i)
	{
		auto user = UserRegistry::getInstance().find(in.readString());

		for (const auto& name : in.readStringList())
			if (auto follower = UserRegistry::getInstance().find(name))
				user->addFollower(follower);

		if (auto reader = std::dynamic_pointer_cast<Reader>(user))
		{
			loadProfileBooks(in, *reader);
			loadShelves(in, *reader);
			loadFavorites(in, *reader);
		}

		loadInbox(in, *user);

		if (auto author = std::dynamic_pointer_cast<Author>(user))
			for (const auto& name : in.readStringList())
				if (auto publisher = std::dynamic_pointer_cast<Publisher>(UserRegistry::getInstance().find(name)))
					author->addPublisher(publisher);

		if (auto publisher = std::dynamic_pointer_cast<Publisher>(user))
			for (const auto& name : in.readStringList())
				if (auto author = std::dynamic_pointer_cast<Author>(UserRegistry::getInstance().find(name)))
					publisher->addAuthor(author);
	}
}

void FileManager::load(const std::string& path)
{
	BinaryReader in(path);
	if (!in.isOpen())
		return;   // first run: nothing to load

	UserRegistry::getInstance().clear();
	BookRegistry::getInstance().clear();

	loadUsers(in);
	loadBooks(in);
	loadRelations(in);
}
