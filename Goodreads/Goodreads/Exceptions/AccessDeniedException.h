#pragma once
#include "GoodreadsException.h"

class AccessDeniedException : public GoodreadsException
{
public:
	AccessDeniedException(const std::string& reason);
};
