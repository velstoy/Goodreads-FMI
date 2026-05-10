#pragma once
#include "../Users/Author.h"
#include "../Users/Publisher.h"

class PublishingRegistry
{
private:
	std::vector<std::shared_ptr<Author>> authors;
	std::vector<std::shared_ptr<Publisher>> publishers;
};

