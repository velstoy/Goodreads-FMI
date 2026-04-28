#pragma once
#include <string>
#include <vector>
#include "Data.h"

class User
{
private:
	std::string username;
	std::string password;
	std::vector<User> followers;
	Date registrationDate;

	const std::string& validate_username(const std::string& username) const;

	const std::string& validate_password(const std::string& password) const;

public:
	User(const std::string& username, const std::string& password, int day, int month, int year);
};

