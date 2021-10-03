#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task3/CFileInputStream.h"
#include "../Task3/CFileOutputStream.h"
#include "../Task3/CMemoryInputStream.h"
#include "../Task3/CMemoryOutputStream.h"
#include "../Task3/COutputCompressStreamDecorator.h"
#include "../Task3/COutputEncryptStreamDecorator.h"
#include "../Task3/CInputDecryptStreamDecorator.h"
#include "../Task3/CInputDecompressStreamDecorator.h"

void WriteByteToFile(uint8_t symbol, std::string fileName)
{
	CFileOutputStream fileOutput(fileName);
	fileOutput.WriteByte(symbol);
}

void WriteBlockToFile(const char* symbols, std::streamsize size, std::string fileName)
{
	CFileOutputStream fileOutput(fileName);
	fileOutput.WriteBlock(symbols, size);
}

SCENARIO("Write 1 byte to memory")
{
	std::vector<uint8_t> data;
	CMemoryOutputStream memoryOutput(data);
	uint8_t symb = 1;
	memoryOutput.WriteByte(symb);
	REQUIRE(data[0] == symb);
}

SCENARIO("Write 10 bytes to memory at once ")
{
	std::vector<uint8_t> data;
	CMemoryOutputStream memoryOutput(data);
	const char* dataOutput = new char[10];
	dataOutput = "mememememe";
	memoryOutput.WriteBlock(dataOutput, 10);
	REQUIRE(data[0] == dataOutput[0]);
	REQUIRE(data[1] == dataOutput[1]);
	REQUIRE(data[2] == dataOutput[2]);
	REQUIRE(data[3] == dataOutput[3]);
	REQUIRE(data[4] == dataOutput[4]);
	REQUIRE(data[5] == dataOutput[5]);
	REQUIRE(data[9] == dataOutput[9]);
}

SCENARIO("Read 1 byte from memory")
{
	std::vector<uint8_t> data;
	uint8_t symbol = 1;
	data.push_back(symbol);
	CMemoryInputStream memoryInput(data);
	REQUIRE(memoryInput.ReadByte() == symbol);
}

SCENARIO("Read 10 bytes from memory")
{
	std::vector<uint8_t> data;
	const uint8_t symbol1 = 1;
	const uint8_t symbol2 = 2;
	for (int i = 0; i < 5; i++)
	{
		data.push_back(symbol1);
		data.push_back(symbol2);
	}
	CMemoryInputStream memoryInput(data);
	uint8_t* dataOutput = new uint8_t[10];
	memoryInput.ReadBlock(dataOutput, 10);
	REQUIRE(data[0] == dataOutput[0]);
	REQUIRE(data[1] == dataOutput[1]);
	REQUIRE(data[2] == dataOutput[2]);
	REQUIRE(data[3] == dataOutput[3]);
	REQUIRE(data[4] == dataOutput[4]);
	REQUIRE(data[9] == dataOutput[9]);
}

SCENARIO("Write 1 byte to file")
{
	uint8_t symb = 'm';
	std::string fileName = "output.txt";
	WriteByteToFile(symb, fileName);
	ifstream outputFile(fileName, ios::binary);
	std::vector<uint8_t> data;
	char readSymbol;
	outputFile.read(&readSymbol, 1);
	REQUIRE(readSymbol == symb);
}

SCENARIO("Write block of symbols to file")
{
	const char* testString = new char[10];
	testString = "mememememe";
	std::string fileName = "output.txt";
	WriteBlockToFile(testString, 10, fileName);
	ifstream inputFile(fileName, ios::binary);
	std::vector<uint8_t> data;
	char* resultString = new char[10];
	for (int i = 0; i < 10; i++)
		inputFile >> resultString[i];
	REQUIRE(std::strcmp(resultString, testString));
}

SCENARIO("Read 1 byte from file")
{
	std::string fileName = "input.txt";
	ofstream inputFile(fileName, ios::binary);
	uint8_t symbol = 'm';
	inputFile << symbol;
	inputFile.close();
	CFileInputStream memoryInput(fileName);
	REQUIRE(memoryInput.ReadByte() == symbol);
}

SCENARIO("Read 10 bytes from file")
{
	std::string fileName = "input.txt";
	ofstream inputFile(fileName, ios::binary);
	const char* data = new char[10];
	data = "mememememe";
	for (int i = 0; i < 10; i++)
	{
		inputFile << data[i];
	}
	inputFile.close();
	CFileInputStream memoryInput(fileName);
	uint8_t* dataOutput = new uint8_t[10];
	memoryInput.ReadBlock(dataOutput, 10);
	REQUIRE(data[0] == dataOutput[0]);
	REQUIRE(data[1] == dataOutput[1]);
	REQUIRE(data[2] == dataOutput[2]);
	REQUIRE(data[3] == dataOutput[3]);
	REQUIRE(data[4] == dataOutput[4]);
	REQUIRE(data[9] == dataOutput[9]);
}

SCENARIO("Read 12 bytes from file")
{
	std::string fileName = "input.txt";
	ofstream inputFile(fileName, ios::binary);
	const char* data = new char[10];
	data = "mememememe";
	for (int i = 0; i < 10; i++)
	{
		inputFile << data[i];
	}
	inputFile.close();
	CFileInputStream memoryInput(fileName);
	uint8_t* dataOutput = new uint8_t[10];
	REQUIRE_THROWS(memoryInput.ReadBlock(dataOutput, 12));
}

void CompressMemory(IInputDataStreamPtr input, vector<uint8_t>& v)
{
	IOutputDataStreamPtr outputStream = make_unique<CMemoryOutputStream>(v);
	COutputCompressStreamDecorator compressed(move(outputStream));

	while (!input->IsEOF())
	{
		auto byte = input->ReadByte();
		compressed.WriteByte(byte);
	}
}

void DecompressMemory(IOutputDataStreamPtr finalStream, vector<uint8_t>& v)
{
	IInputDataStreamPtr inputStream = make_unique<CMemoryInputStream>(v);
	CInputDecompressStreamDecorator decompressed(move(inputStream));

	while (!decompressed.IsEOF())
	{
		auto byte = decompressed.ReadByte();
		finalStream->WriteByte(byte);
	}
}

SCENARIO("Compress and decompress data")
{
	string startValue = "5555446667878";
	vector<uint8_t> data(startValue.begin(), startValue.end());
	IInputDataStreamPtr input = make_unique<CMemoryInputStream>(data);

	vector<uint8_t> compressed;
	CompressMemory(move(input), compressed);

	vector<uint8_t> decompressed;
	IOutputDataStreamPtr finalstream = make_unique<CMemoryOutputStream>(decompressed);
	DecompressMemory(move(finalstream), compressed);

	REQUIRE(decompressed == data);
}

void EncryptMemory(IInputDataStreamPtr input, vector<uint8_t>& v)
{
	IOutputDataStreamPtr outputStream = make_unique<CMemoryOutputStream>(v);
	COutputEncryptStreamDecorator compressed(move(outputStream), 100);

	while (!input->IsEOF())
	{
		auto byte = input->ReadByte();
		compressed.WriteByte(byte);
	}
}

void DecryptMemory(IOutputDataStreamPtr finalStream, vector<uint8_t>& v)
{
	IInputDataStreamPtr inputStream = make_unique<CMemoryInputStream>(v);
	CInputDecryptStreamDecorator decompressed(move(inputStream), 100);

	while (!decompressed.IsEOF())
	{
		auto byte = decompressed.ReadByte();
		finalStream->WriteByte(byte);
	}
}

SCENARIO("Encrypt and decrypt data")
{
	string startValue = "5555446667878";
	vector<uint8_t> data(startValue.begin(), startValue.end());
	vector<uint8_t> decompressed;
	vector<uint8_t> compressed;
	IOutputDataStreamPtr finalstream = make_unique<CMemoryOutputStream>(decompressed);
	IInputDataStreamPtr input = make_unique<CMemoryInputStream>(data);

	EncryptMemory(move(input), compressed);
	DecryptMemory(move(finalstream), compressed);

	REQUIRE(decompressed == data);
}