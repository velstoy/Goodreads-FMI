#pragma once
#include <string>
#include <vector>
#include <fstream>

class BinaryReader
{
private:
	std::ifstream in;

public:
	explicit BinaryReader(const std::string& path);

	bool isOpen() const;

	unsigned long long readUInt();
	bool readBool();
	double readDouble();
	std::string readString();
	std::vector<std::string> readStringList();
};