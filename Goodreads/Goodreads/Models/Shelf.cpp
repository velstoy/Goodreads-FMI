#include "Shelf.h"

Shelf::Shelf(const std::string& name, int cday, int cmonth, int cyear)
	: name(name), creationDate(cday, cmonth, cyear)
{
}

size_t Shelf::getBookCount() const
{
	return books.size();
}
