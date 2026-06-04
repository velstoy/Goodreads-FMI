#include "UserAlreadyExistsException.h"
#include <format>

UserAlreadyExistsException::UserAlreadyExistsException(const std::string& username)
{
	message = std::format("A user with name {} already exists!", username);
}
