#pragma once
#include "GoodreadsException.h"

// Thrown when a looked-up user, book or shelf does not exist.
class EntityNotFoundException : public GoodreadsException
{
public:
	EntityNotFoundException(const std::string& entityKind, const std::string& name);
};
