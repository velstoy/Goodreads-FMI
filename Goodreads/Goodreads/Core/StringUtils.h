#pragma once
#include <string>
#include <vector>

namespace StringUtils
{
	std::string toLower(const std::string& s);

	// Number of single-character changes needed to turn one word into another,
	// ignoring case. Search uses it to allow a couple of typos.
	size_t editDistance(const std::string& a, const std::string& b);

	// Splits a line into words. Text inside "double quotes" stays together as one
	// word, so titles or names with spaces can be passed as a single argument.
	std::vector<std::string> tokenize(const std::string& line);

	std::string join(const std::vector<std::string>& parts, size_t from, const std::string& sep = " ");
}
