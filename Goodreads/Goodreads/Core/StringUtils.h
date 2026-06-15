#pragma once
#include <string>
#include <vector>

namespace StringUtils
{
	std::string toLower(const std::string& s);

	// Case-insensitive Levenshtein edit distance.
	size_t editDistance(const std::string& a, const std::string& b);

	// Whitespace tokeniser that keeps "double quoted" segments together,
	// so titles/usernames with spaces can be passed as one argument.
	std::vector<std::string> tokenize(const std::string& line);

	std::string join(const std::vector<std::string>& parts, size_t from, const std::string& sep = " ");
}
