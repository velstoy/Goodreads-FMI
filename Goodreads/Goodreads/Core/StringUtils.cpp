#include "StringUtils.h"
#include <algorithm>
#include <cctype>

namespace StringUtils
{
	std::string toLower(const std::string& s)
	{
		std::string out = s;
		std::transform(out.begin(), out.end(), out.begin(),
			[](unsigned char c) { return (char)std::tolower(c); });
		return out;
	}

	size_t editDistance(const std::string& a0, const std::string& b0)
	{
		std::string a = toLower(a0), b = toLower(b0);
		size_t n = a.size(), m = b.size();
		std::vector<size_t> prev(m + 1), cur(m + 1);
		for (size_t j = 0; j <= m; ++j) prev[j] = j;
		for (size_t i = 1; i <= n; ++i)
		{
			cur[0] = i;
			for (size_t j = 1; j <= m; ++j)
			{
				size_t cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
				cur[j] = std::min({ prev[j] + 1, cur[j - 1] + 1, prev[j - 1] + cost });
			}
			std::swap(prev, cur);
		}
		return prev[m];
	}

	std::vector<std::string> tokenize(const std::string& line)
	{
		std::vector<std::string> tokens;
		std::string current;
		bool inQuotes = false, hasToken = false;
		for (char c : line)
		{
			if (c == '"') { inQuotes = !inQuotes; hasToken = true; }
			else if (std::isspace((unsigned char)c) && !inQuotes)
			{
				if (hasToken) { tokens.push_back(current); current.clear(); hasToken = false; }
			}
			else { current += c; hasToken = true; }
		}
		if (hasToken) tokens.push_back(current);
		return tokens;
	}

	std::string join(const std::vector<std::string>& parts, size_t from, const std::string& sep)
	{
		std::string out;
		for (size_t i = from; i < parts.size(); ++i)
		{
			if (i > from) out += sep;
			out += parts[i];
		}
		return out;
	}
}
