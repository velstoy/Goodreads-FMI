#pragma once
#include "GoodreadsException.h"

class EntityNotFoundException : public GoodreadsException
{
public:
	EntityNotFoundException(const std::string& entityKind, const std::string& name);
};
