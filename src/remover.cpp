#include <remover.hpp>

#include <filesystem>
#include <iostream>

#include <QByteArray>
#include <QFile>

int Remover::run(int argc, char* argv[])
{
	if (argc != 3)
	{
		showUsage();
		return 1;
	}

	// Check platform
	QString platform = QString(argv[1]).toUpper();
	if (platform != "PS3" && platform != "X360" && platform != "PC"
		&& platform != "PS4" && platform != "NX")
	{
		std::cerr << "Invalid platform specified\n";
		showUsage();
		return 1;
	}

	if (platform == "PS3" || platform == "X360")
		isBigEndian = true;

	if (platform == "PS4" || platform == "NX")
		is64Bit = true;
	
	// Check that input exists and is a valid file
	if (!std::filesystem::exists(argv[2])
		|| !std::filesystem::is_regular_file(argv[2]))
	{
		std::cout << "Invalid input file";
		return 1;
	}

	// Read file into memory
	QFile input(argv[2]);
	input.open(QIODevice::ReadOnly);
	input.reset();
	QByteArray* inputByteArray = new QByteArray(input.readAll());
	QDataStream data(inputByteArray, QIODevice::ReadWrite);
	input.close();
	if (!isBigEndian)
		data.setByteOrder(QDataStream::LittleEndian);

	// Remove traffic from the asset
	removeTraffic(data);

	// Write data back to the file
	input.open(QIODevice::WriteOnly);
	input.reset();
	data.device()->reset();
	input.write(data.device()->readAll());
	input.close();

	delete inputByteArray;
	
	std::cout << "Traffic removed";

	return 0;
}

void Remover::removeTraffic(QDataStream& data)
{
	// Read the number of hull and the hull offsets
	uint16_t numHulls = read<uint16_t>(data, 2);
	uint64_t hullPtrsPtr = 0;
	if (!is64Bit)
		hullPtrsPtr = read<uint32_t>(data, 0xC);
	else
		hullPtrsPtr = read<uint64_t>(data, 0x10);
	data.device()->seek(hullPtrsPtr);
	QList<uint64_t> hullPtrs(numHulls);
	for (int i = 0; i < numHulls; ++i)
		hullPtrs[i] = readPtr(data);

	// For each hull, set the number of static traffic vehicles to 0
	for (int i = 0; i < numHulls; ++i)
		write<uint8_t>(data, hullPtrs[i] + 5, 0);

	// For each hull
	for (int i = 0; i < numHulls; ++i)
	{
		// Read the number of sections and the section flow offset
		uint8_t numSections = read<uint8_t>(data, hullPtrs[i]);
		uint64_t sectionFlowsPtr = 0;
		if (!is64Bit)
			sectionFlowsPtr = read<uint32_t>(data, hullPtrs[i] + 0x28);
		else
			sectionFlowsPtr = read<uint64_t>(data, hullPtrs[i] + 0x40);

		// Set the number of vehicles per minute in each flow to 0
		data.device()->seek(sectionFlowsPtr);
		for (int j = 0; j < numSections; ++j)
			write<uint16_t>(data, sectionFlowsPtr + j * 4 + 2, 0);
	}
}

void Remover::showUsage()
{
	std::cout << "Usage: Traffic_Remover <platform> <input>\n"
		<< "Valid platforms:\n  PS3\n  X360\n  PC\n  PS4\n  NX";
}

Remover::Remover()
{

}