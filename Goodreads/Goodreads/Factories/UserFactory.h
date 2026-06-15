#pragma once
#include <memory>
#include <string>
#include <optional>
#include "../Models/Date.h"
#include "../Users/User.h"

class UserFactory
{
public:
	static std::shared_ptr<User> createUser(const std::string& type, const std::string& username,
		const std::string& password, const Date& registrationDate,
		const std::optional<Date>& birthday = std::nullopt);
};
