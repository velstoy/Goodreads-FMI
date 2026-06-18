#pragma once
#include <string>

enum class Genre {
	Literary, Historical, Mystery, Thriller, Horror, Romance,
	ScienceFiction, Fantasy, Adventure, Crime, Dystopian, Supernatural,
	Biography, Autobiography, Memoir, SelfHelp, Psychology, Philosophy,
	History, Science, Travel, TrueCrime, Politics, Economics,
	Children, YoungAdult, GraphicNovel, Poetry, Anthology, Reference,
	Unknown
};

std::string genreToString(Genre genre);

// Case-insensitive parse. Returns Genre::Unknown for unrecognised input.
Genre genreFromString(const std::string& text);
