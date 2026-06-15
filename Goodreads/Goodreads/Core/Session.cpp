#include "Session.h"

bool Session::isLoggedIn() const { return currentUser != nullptr; }
std::shared_ptr<User> Session::getCurrentUser() const { return currentUser; }
void Session::login(const std::shared_ptr<User>& user) { currentUser = user; }
void Session::logout() { currentUser = nullptr; }
