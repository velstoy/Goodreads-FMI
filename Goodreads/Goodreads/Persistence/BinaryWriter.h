#pragma once
#include <string>
#include <vector>
#include <fstream>

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