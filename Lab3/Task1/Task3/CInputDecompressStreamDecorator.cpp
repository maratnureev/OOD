#include "CInputDecompressStreamDecorator.h"

bool CInputDecompressStreamDecorator::IsEOF() const
{
	return m_inputStream->IsEOF();
}

uint8_t CInputDecompressStreamDecorator::ReadByte()
{
	if (m_currentByte.count == 0)
	{
		m_currentByte.byte = m_inputStream->ReadByte();
		m_currentByte.count = m_inputStream->ReadByte();
	}
	m_currentByte.count--;

	return m_currentByte.byte;
}

std::streamsize CInputDecompressStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto data = static_cast<uint8_t*>(dstBuffer);
	for (std::streamsize i = 0; i < size; i++)
	{
		try 
		{
			data[i] = ReadByte();
		}
		catch (std::ios_base::failure)
		{
			return i++;
		}
	}

	return size;
}
