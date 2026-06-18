#pragma once
#include <string>
#include <vector>
#include "ICommand.h"
#include "../Core/Session.h"

class PublishCommand : public ICommand
{
private:
	Session& session;
	std::string title;
	std::string authorName;
	std::string dateText;
	std::string pagesText;
	std::vector<std::string> genreTexts;
public:
	PublishCommand(Session& session, const std::string& title, const std::string& authorName,
		const std::string& dateText, const std::string& pagesText,
		const std::vector<std::string>& genreTexts);
	void execute() override;
};
