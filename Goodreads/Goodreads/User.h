#pragma once
#include <string>
#include <vector>
#include "Data.h"

class User
{
protected:
	std::string name;
	std::string password;
	std::vector<User> followers;
	Date& registrationDate;


};

