#include "CInputDecryptStreamDecorator.h"

bool CInputDecryptStreamDecorator::IsEOF()
{
	return m_inputStream->IsEOF();
}

uint8_t CInputDecryptStreamDecorator::ReadByte()
{
	return m_encryptMap[m_inputStream->ReadByte()];
}

std::streamsize CInputDecryptStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto data = static_cast<uint8_t*>(dstBuffer);

	for (std::streamsize i = 0; i < size; i++)
	{
		try 
		{
			data[i] = m_encryptMap[m_inputStream->ReadByte()];
		}
		catch (std::ios_base::failure)
		{
			return i++;
		}
	}

	return size;
}
