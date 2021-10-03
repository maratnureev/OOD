#include "COutputEncryptStreamDecorator.h"

void COutputEncryptStreamDecorator::WriteByte(uint8_t data)
{
	m_outputStream->WriteByte(m_encryptMap[data]);
}

void COutputEncryptStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(data[i]);
	}
}
