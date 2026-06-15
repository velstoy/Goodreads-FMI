#include "ReadingStatus.h"
#include <algorithm>
#include "../Exceptions/InvalidArgumentException.h"

namespace {
	std::string toLower(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return (char)std::tolower(c); });
		return s;
	}
}

std::string readingStatusToString(ReadingStatus status)
{
	switch (status)
	{
	case ReadingStatus::PlanToRead: return "plan-to-read";
	case ReadingStatus::Reading:    return "reading";
	case ReadingStatus::Paused:     return "paused";
	case ReadingStatus::Dropped:    return "dropped";
	}
	return "plan-to-read";
}

ReadingStatus readingStatusFromString(const std::string& text)
{
	std::string s = toLower(text);
	if (s == "plan-to-read") return ReadingStatus::PlanToRead;
	if (s == "reading")      return ReadingStatus::Reading;
	if (s == "paused")       return ReadingStatus::Paused;
	if (s == "dropped")      return ReadingStatus::Dropped;
	throw InvalidArgumentException("status must be one of: plan-to-read, reading, paused, dropped!");
}
