#include "BinaryWriter.h"
#include <string>

BinaryWriter::BinaryWriter(const std::string& path)
	: out(path, std::ios::binary | std::ios::trunc)
{
}

bool BinaryWriter::isOpen() const
{
	return out.is_open();
}

void BinaryWriter::writeUInt(unsigned long long value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void BinaryWriter::writeBool(bool value)
{
	out.put(static_cast<char>(value));
}

void BinaryWriter::writeDouble(double value)
{
	writeString(std::to_string(value));
}

void BinaryWriter::writeString(const std::string& value)
{
	writeUInt(value.size());
	out.write(value.data(), static_cast<std::streamsize>(value.size()));
}

void BinaryWriter::writeStringList(const std::vector<std::string>& list)
{
	writeUInt(list.size());
	for (const auto& value : list)
		writeString(value);
}