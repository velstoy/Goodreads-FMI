#pragma once
#include <string>

// Book genres, kept here alongside the text <-> enum conversions used when
// publishing and printing books.
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
