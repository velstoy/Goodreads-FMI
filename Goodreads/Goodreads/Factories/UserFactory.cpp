#include "UserFactory.h"
#include "../Users/Author.h"
#include "../Users/Reader.h"
#include "../Users/Publisher.h"
#include "../Exceptions/InvalidUserException.h"

std::shared_ptr<User> UserFactory::createUser(const std::string& type, const std::string& username, const std::string& password, const Date& registrationDate, const std::optional<Date>& birthday)
{
    if (type == "reader")
    {
        return std::make_shared<Reader>(username, password, registrationDate, birthday);
    }
    else if (type == "author")
    {
        return std::make_shared<Author>(username, password, registrationDate);
    }
    else if (type == "publisher")
    {
        return std::make_shared<Publisher>(username, password, registrationDate);
    }

    throw InvalidUserException(type);
}
