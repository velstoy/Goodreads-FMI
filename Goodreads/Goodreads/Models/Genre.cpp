#include "Genre.h"
#include <algorithm>
#include <array>
#include <utility>

namespace {
	const std::array<std::pair<Genre, const char*>, 31> table = { {
		{Genre::Literary, "Literary"}, {Genre::Historical, "Historical"},
		{Genre::Mystery, "Mystery"}, {Genre::Thriller, "Thriller"},
		{Genre::Horror, "Horror"}, {Genre::Romance, "Romance"},
		{Genre::ScienceFiction, "ScienceFiction"}, {Genre::Fantasy, "Fantasy"},
		{Genre::Adventure, "Adventure"}, {Genre::Crime, "Crime"},
		{Genre::Dystopian, "Dystopian"}, {Genre::Supernatural, "Supernatural"},
		{Genre::Biography, "Biography"}, {Genre::Autobiography, "Autobiography"},
		{Genre::Memoir, "Memoir"}, {Genre::SelfHelp, "SelfHelp"},
		{Genre::Psychology, "Psychology"}, {Genre::Philosophy, "Philosophy"},
		{Genre::History, "History"}, {Genre::Science, "Science"},
		{Genre::Travel, "Travel"}, {Genre::TrueCrime, "TrueCrime"},
		{Genre::Politics, "Politics"}, {Genre::Economics, "Economics"},
		{Genre::Children, "Children"}, {Genre::YoungAdult, "YoungAdult"},
		{Genre::GraphicNovel, "GraphicNovel"}, {Genre::Poetry, "Poetry"},
		{Genre::Anthology, "Anthology"}, {Genre::Reference, "Reference"},
		{Genre::Unknown, "Unknown"}
	} };

	std::string toLower(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return (char)std::tolower(c); });
		return s;
	}
}

std::string genreToString(Genre genre)
{
	for (const auto& [g, name] : table)
		if (g == genre) return name;
	return "Unknown";
}

Genre genreFromString(const std::string& text)
{
	std::string lowered = toLower(text);
	for (const auto& [g, name] : table)
		if (toLower(name) == lowered) return g;
	return Genre::Unknown;
}
