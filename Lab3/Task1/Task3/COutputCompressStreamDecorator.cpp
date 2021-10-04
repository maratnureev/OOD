#include "COutputCompressStreamDecorator.h"

void COutputCompressStreamDecorator::WriteByte(uint8_t data)
{
	if (m_currentByte.count > 254)
	{
		m_outputStream->WriteByte(m_currentByte.byte);
		m_outputStream->WriteByte(m_currentByte.count);
		m_currentByte.byte = data;
		m_currentByte.count = 1;
		return;
	}
	if (m_currentByte.count == 0)
	{
		m_currentByte.count = 1;
		m_currentByte.byte = data;
		return;
	}
	if (m_currentByte.byte == data)
	{
		m_currentByte.count++;
		return;
	}

	m_outputStream->WriteByte(m_currentByte.byte);
	m_outputStream->WriteByte(m_currentByte.count);
	m_currentByte.byte = data;
	m_currentByte.count = 1;
}

void COutputCompressStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(data[i]);
	}
}
