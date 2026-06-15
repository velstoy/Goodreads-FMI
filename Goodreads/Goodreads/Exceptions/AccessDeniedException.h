#pragma once
#include "GoodreadsException.h"

// Thrown when the current user is not allowed to perform an action.
class AccessDeniedException : public GoodreadsException
{
public:
	AccessDeniedException(const std::string& reason);
};
