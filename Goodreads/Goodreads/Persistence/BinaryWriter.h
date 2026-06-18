#pragma once
#include <string>
#include <vector>
#include <fstream>

// Writes simple values to a binary file. Whole numbers are written one byte at
// a time and strings as their length followed by their characters, so values
// sit one after another with no separators between them.
class BinaryWriter
{
private:
	std::ofstream out;

public:
	explicit BinaryWriter(const std::string& path);

	bool isOpen() const;

	void writeUInt(unsigned long long value);
	void writeBool(bool value);
	void writeDouble(double value);
	void writeString(const std::string& value);
	void writeStringList(const std::vector<std::string>& list);
};
