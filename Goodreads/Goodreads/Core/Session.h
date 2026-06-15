#pragma once
#include <memory>
#include "../Users/User.h"

// Holds the currently logged-in user (if any).
class Session
{
private:
	std::shared_ptr<User> currentUser;
public:
	bool isLoggedIn() const;
	std::shared_ptr<User> getCurrentUser() const;
	void login(const std::shared_ptr<User>& user);
	void logout();
};
