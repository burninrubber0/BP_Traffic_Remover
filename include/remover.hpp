#pragma once

#include <cstdint>

#include <QDataStream>

class Remover
{
public:
	Remover();

	int run(int argc, char* argv[]);

private:
	bool isBigEndian = false;
	bool is64Bit = false;

	void showUsage();

	// Removes traffic from a TrafficData resource
	void removeTraffic(QDataStream& data);

	// Reads data of a specified type from the current position in a QDataStream
	// and returns the value
	template <typename T>
	T read(QDataStream& data)
	{
		T val = 0;
		data >> val;
		return val;
	}

	// Reads data of a specified type from the specified position in a
	// QDataStream and returns the value
	template <typename T>
	T read(QDataStream& data, int64_t offset)
	{
		T val = 0;
		data.device()->seek(offset);
		data >> val;
		return val;
	}

	// Reads a pointer from the current position in a QDataStream and returns
	// the value
	uint64_t readPtr(QDataStream& data)
	{
		uint64_t ptr = 0;
		if (!is64Bit)
			data >> (quint32&)ptr;
		else
			data >> ptr;
		return ptr;
	}

	// Writes data of a specified type to the specified position in a
	// QDataStream
	template <typename T>
	void write(QDataStream& data, int64_t offset, T value)
	{
		data.device()->seek(offset);
		data << value;
	}
};