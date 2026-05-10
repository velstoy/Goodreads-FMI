#include "BookRegistry.h"

BookRegistry& BookRegistry::getInstance()
{
    static BookRegistry bookRegistry;

    return bookRegistry;
}
