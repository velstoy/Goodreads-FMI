#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Date.h"
#include "Genre.h"

class Author;
class Publisher;

class Book
{
private:
	std::string name;
	std::weak_ptr<Author> author;
	std::weak_ptr<Publisher> publisher;
	std::string authorName;              // kept by name so it survives if the user is removed
	std::string publisherName;
	std::string resume;                  // synopsis
	std::vector<Genre> genres;
	double averageRating;
	size_t numberOfRatings;
	Date publishingDate;
	size_t numberOfPages;

public:
	Book(const std::string& name,
		const std::shared_ptr<Author>& author,
		const std::shared_ptr<Publisher>& publisher,
		const std::string& resume,
		const std::vector<Genre>& genres,
		double averageRating, size_t numberOfRatings,
		int rday, int rmonth, int ryear, size_t numberOfPages);

	const std::string& getName() const;
	std::shared_ptr<Author> getAuthor() const;
	std::shared_ptr<Publisher> getPublisher() const;
	const std::string& getAuthorName() const;
	const std::string& getPublisherName() const;
	const std::string& getResume() const;
	const std::vector<Genre>& getGenres() const;
	double getAverageRating() const;
	size_t getNumberOfRatings() const;
	const Date& getPublishingDate() const;
	size_t getNumberOfPages() const;

	void setResume(const std::string& synopsis);
	void addRating(double rating);
};
