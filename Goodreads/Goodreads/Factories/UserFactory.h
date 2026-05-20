#pragma once
#include <memory>
#include <string>
#include <optional>
#include "../Models/Date.h"
#include "../Users/User.h"
#include "../Users/Author.h"
#include "../Users/Reader.h"
#include "../Users/Publisher.h"

enum class UserType
{
	Reader,
	Author,
	Publisher
};

class UserFactory
{
private:
	UserFactory() = default;

public:
	static UserFactory& getInstance();

	std::shared_ptr<User> createUser(UserType type, const std::string& username, const std::string& password, int rday, int rmonth, int ryear, std::optional<Date> birthday = std::nullopt);
};