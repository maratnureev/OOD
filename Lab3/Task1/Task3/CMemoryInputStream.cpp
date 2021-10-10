#include "CMemoryInputStream.h"

bool CMemoryInputStream::IsEOF() const
{
	return m_currentIndex >= m_data.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
	if (IsEOF())
		throw std::ios_base::failure("End of the file");
	return m_data[m_currentIndex++];
}

std::streamsize CMemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto dataPtr = static_cast<uint8_t*>(dstBuffer);
	std::streamsize readSymbols = 0;
	while (!IsEOF())
	{
		*dataPtr = ReadByte();
		dataPtr++;
		readSymbols++;
	}
	return readSymbols;
}
