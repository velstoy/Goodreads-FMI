#include "BinaryReader.h"
#include <string>

BinaryReader::BinaryReader(const std::string& path)
	: in(path, std::ios::binary)
{
}

bool BinaryReader::isOpen() const
{
	return in.is_open();
}

unsigned long long BinaryReader::readUInt()
{
	// Rebuild the number from its eight bytes, lowest first.
	unsigned long long value = 0;
	for (int i = 0; i < 8; ++i)
	{
		unsigned char byte = static_cast<unsigned char>(in.get());
		value |= static_cast<unsigned long long>(byte) << (8 * i);
	}
	return value;
}

bool BinaryReader::readBool()
{
	return in.get() != 0;
}

double BinaryReader::readDouble()
{
	return std::stod(readString());
}

std::string BinaryReader::readString()
{
	unsigned long long length = readUInt();
	std::string value(static_cast<size_t>(length), '\0');
	if (length > 0)
		in.read(&value[0], static_cast<std::streamsize>(length));
	return value;
}

std::vector<std::string> BinaryReader::readStringList()
{
	unsigned long long count = readUInt();
	std::vector<std::string> list;
	list.reserve(static_cast<size_t>(count));
	for (unsigned long long i = 0; i < count; ++i)
		list.push_back(readString());
	return list;
}
