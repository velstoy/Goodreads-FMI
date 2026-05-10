#include "PublishingRegistry.h"

PublishingRegistry& PublishingRegistry::getInstance()
{
    static PublishingRegistry publishingRegistry;

    return publishingRegistry;
}
