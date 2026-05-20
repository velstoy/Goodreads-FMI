#include "UserFactory.h"

UserFactory& UserFactory::getInstance()
{
    static UserFactory instance;

    return instance;
}

std::shared_ptr<User> UserFactory::createUser(UserType type, const std::string& username, const std::string& password, int rday, int rmonth, int ryear, std::optional<Date> birthday)
{
    if (birthday.has_value())
    {
        switch (type)
        {
        case UserType::Reader:
            return std::make_shared<Reader>(username, password, rday, rmonth, ryear, birthday->getDay(), birthday->getMonth(), birthday->getYear());
            break;
        case UserType::Author:
            return std::make_shared<Author>(username, password, rday, rmonth, ryear, birthday->getDay(), birthday->getMonth(), birthday->getYear());
            break;
        case UserType::Publisher:

            break;
        default:
            break;
        }
    }

    return std::shared_ptr<User>();
}
