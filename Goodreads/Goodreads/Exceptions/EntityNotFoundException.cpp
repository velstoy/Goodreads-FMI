#include "EntityNotFoundException.h"
#include <format>

EntityNotFoundException::EntityNotFoundException(const std::string& entityKind, const std::string& name)
{
	message = std::format("{} \"{}\" was not found!", entityKind, name);
}
