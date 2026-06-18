#pragma once
#include <string>
#include <vector>
#include "ICommand.h"
#include "../Core/Session.h"

// publish <title> <author> <date> <pages> <genres...> : a publisher releases a
// new book by one of its authors and notifies the followers of both.
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
