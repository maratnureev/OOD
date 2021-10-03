#include "CMemoryOutputStream.h"

void CMemoryOutputStream::WriteByte(uint8_t data)
{
	m_data->push_back(data);
}

void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const char*>(srcData);
	for (long long i = 0; i < size; i++)
		m_data->push_back(data[i]);
}
