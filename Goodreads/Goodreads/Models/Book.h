#pragma once
#include <string>
#include <vector>
#include "../Users/Author.h"
#include "../Users/Publisher.h"
#include "Date.h"

enum class Genre {
    // Fiction
    Literary,
    Historical,
    Mystery,
    Thriller,
    Horror,
    Romance,
    ScienceFiction,
    Fantasy,
    Adventure,
    Crime,
    Dystopian,
    Supernatural,

    // Non-Fiction
    Biography,
    Autobiography,
    Memoir,
    SelfHelp,
    Psychology,
    Philosophy,
    History,
    Science,
    Travel,
    TrueCrime,
    Politics,
    Economics,

    // Other
    Children,
    YoungAdult,
    GraphicNovel,
    Poetry,
    Anthology,
    Reference,

    Unknown
};

class Book
{
private:
	std::string name;
	Author author;
	Publisher publisher;
	std::string resume;
	std::vector<Genre> genres;
    double averageRating;
    size_t numberOfRatings;
    Date publishingDate;
    size_t numberOfPages;

public:
    Book(const std::string& name, const Author& author, const Publisher& publisher, const std::string& resume, const std::vector<Genre>& genres, double averageRating, size_t numberOfRatings, int rday, int rmonth, int ryear, size_t numberOfPages);
};

