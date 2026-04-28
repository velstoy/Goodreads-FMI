#include "Book.h"

Book::Book(const std::string& name, const Author& author, const Publisher& publisher, const std::string& resume, const std::vector<Genre>& genres, double averageRating, size_t numberOfRatings, int rday, int rmonth, int ryear, size_t numberOfPages)
	: name(name), author(author), publisher(publisher), resume(resume), genres(genres), averageRating(averageRating), numberOfRatings(numberOfRatings), publishingDate(rday, rmonth, ryear), numberOfPages(numberOfPages)
{
}
