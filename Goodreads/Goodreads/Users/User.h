#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Models/Date.h"

class User
{
private:
	std::string username;
	std::string password;
	Date registrationDate;
	std::vector<std::weak_ptr<User>> followers;

	const std::string& validate_username(const std::string& username) const;

	const std::string& validate_password(const std::string& password) const;

public:
	User(const std::string& username, const std::string& password, int rday, int rmonth, int ryear);
};

