#pragma once
#include <string>

// Status of a book inside a reader's profile (add-book command).
enum class ReadingStatus { PlanToRead, Reading, Paused, Dropped };

std::string readingStatusToString(ReadingStatus status);

// Case-insensitive parse of plan-to-read / reading / paused / dropped.
// Throws InvalidArgumentException for anything else.
ReadingStatus readingStatusFromString(const std::string& text);
