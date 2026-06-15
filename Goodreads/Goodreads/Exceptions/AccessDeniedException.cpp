#include "AccessDeniedException.h"

AccessDeniedException::AccessDeniedException(const std::string& reason)
{
	message = "Access denied: " + reason;
}
