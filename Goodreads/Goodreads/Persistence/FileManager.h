#pragma once
#include <string>
#include <memory>

class User;
class Reader;
class Book;
class Date;
class BinaryWriter;
class BinaryReader;

// Saves and loads the whole program state. The byte-level work is left to
// BinaryWriter and BinaryReader; this class only decides what gets written and
// in what order. Everything is saved in three sections - the basic user data,
// then the books, then the relationships between them - so that while loading,
// every object already exists before anything points at it.
class FileManager
{
public:
	static void save(const std::string& path);
	static void load(const std::string& path);

private:
	static void saveDate(BinaryWriter& out, const Date& date);
	static void saveUserBasics(BinaryWriter& out, const std::shared_ptr<User>& user);
	static void saveBook(BinaryWriter& out, const Book& book);
	static void saveUserRelations(BinaryWriter& out, const std::shared_ptr<User>& user);
	static void saveProfileBooks(BinaryWriter& out, const Reader& reader);
	static void saveShelves(BinaryWriter& out, const Reader& reader);
	static void saveFavorites(BinaryWriter& out, const Reader& reader);
	static void saveInbox(BinaryWriter& out, const User& user);

	static Date loadDate(BinaryReader& in);
	static void loadUsers(BinaryReader& in);
	static void loadBooks(BinaryReader& in);
	static void loadRelations(BinaryReader& in);
	static void loadProfileBooks(BinaryReader& in, Reader& reader);
	static void loadShelves(BinaryReader& in, Reader& reader);
	static void loadFavorites(BinaryReader& in, Reader& reader);
	static void loadInbox(BinaryReader& in, User& user);
};
