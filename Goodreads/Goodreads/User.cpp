#include "User.h"
#include <iostream>

const std::string& User::validate_username(const std::string& username) const
{
    size_t usernameSize = username.size();

    if (usernameSize < 6 || usernameSize > 24)
        throw std::invalid_argument(std::format("The username must be between 6 and 25 characters, inclusive. {} was {} characters long!", username, usernameSize));

    return username;
}

const std::string& User::validate_password(const std::string& password) const
{
    size_t passwordSize = password.size();

    if (passwordSize < 12 || passwordSize > 36)
        throw std::invalid_argument(std::format("The password must be between 12 and 36 characters long, inclusive. You input a password that is {} characters long, instead!", passwordSize));

    return password;
}

User::User(const std::string& username, const std::string& password, int rday, int rmonth, int ryear)
    : username(validate_username(username)), password(validate_password(password)), registrationDate(rday, rmonth, ryear)
{
}
