#include "UserRegistry.h"


UserRegistry& UserRegistry::getInstance()
{
	static UserRegistry userRegistry;

	return userRegistry;
}