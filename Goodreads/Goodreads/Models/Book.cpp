#include "Book.h"
#include "../Users/Author.h"
#include "../Users/Publisher.h"

Book::Book(const std::string& name,
	const std::shared_ptr<Author>& author,
	const std::shared_ptr<Publisher>& publisher,
	const std::string& resume,
	const std::vector<Genre>& genres,
	double averageRating, size_t numberOfRatings,
	int rday, int rmonth, int ryear, size_t numberOfPages)
	: name(name), author(author), publisher(publisher),
	authorName(author ? author->getUsername() : ""),
	publisherName(publisher ? publisher->getUsername() : ""),
	resume(resume), genres(genres),
	averageRating(averageRating), numberOfRatings(numberOfRatings),
	publishingDate(rday, rmonth, ryear), numberOfPages(numberOfPages)
{
}

const std::string& Book::getName() const { return name; }
std::shared_ptr<Author> Book::getAuthor() const { return author.lock(); }
std::shared_ptr<Publisher> Book::getPublisher() const { return publisher.lock(); }
const std::string& Book::getAuthorName() const { return authorName; }
const std::string& Book::getPublisherName() const { return publisherName; }
const std::string& Book::getResume() const { return resume; }
const std::vector<Genre>& Book::getGenres() const { return genres; }
double Book::getAverageRating() const { return averageRating; }
size_t Book::getNumberOfRatings() const { return numberOfRatings; }
const Date& Book::getPublishingDate() const { return publishingDate; }
size_t Book::getNumberOfPages() const { return numberOfPages; }

void Book::setResume(const std::string& synopsis) { resume = synopsis; }

void Book::addRating(double rating)
{
	averageRating = (averageRating * numberOfRatings + rating) / (numberOfRatings + 1);
	++numberOfRatings;
}
