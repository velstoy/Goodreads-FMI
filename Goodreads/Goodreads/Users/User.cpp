#include "User.h"
#include "../Exceptions/InvalidArgumentException.h"

constexpr size_t MIN_USERNAME = 6;
constexpr size_t MAX_USERNAME = 24;
constexpr size_t MIN_PASSWORD = 12;
constexpr size_t MAX_PASSWORD = 36;

const std::string& User::validate_username(const std::string& username) const
{
    size_t usernameSize = username.size();

    if (usernameSize < MIN_USERNAME || usernameSize > MAX_USERNAME)
        throw InvalidArgumentException("username", MIN_USERNAME, MAX_USERNAME);

    return username;
}

const std::string& User::validate_password(const std::string& password) const
{
    size_t passwordSize = password.size();

    if (passwordSize < MIN_PASSWORD || passwordSize > MAX_PASSWORD)
        throw InvalidArgumentException("password", MIN_PASSWORD, MAX_PASSWORD);

    return password;
}

User::User(const std::string& username, const std::string& password, int rday, int rmonth, int ryear)
    : username(validate_username(username)), password(validate_password(password)), registrationDate(rday, rmonth, ryear)
{
}
