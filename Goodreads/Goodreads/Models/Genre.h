#pragma once
#include <string>

// The Genre enum used to live inside Book.h. It is moved here so the
// string <-> enum conversions (needed when publishing / printing books)
// have a natural home and Book.h stays focused on the Book entity.
enum class Genre {
	// Fiction
	Literary, Historical, Mystery, Thriller, Horror, Romance,
	ScienceFiction, Fantasy, Adventure, Crime, Dystopian, Supernatural,
	// Non-Fiction
	Biography, Autobiography, Memoir, SelfHelp, Psychology, Philosophy,
	History, Science, Travel, TrueCrime, Politics, Economics,
	// Other
	Children, YoungAdult, GraphicNovel, Poetry, Anthology, Reference,
	Unknown
};

std::string genreToString(Genre genre);

// Case-insensitive parse. Returns Genre::Unknown for unrecognised input.
Genre genreFromString(const std::string& text);
