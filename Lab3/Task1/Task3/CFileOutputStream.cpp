#include "CFileOutputStream.h"

void CFileOutputStream::WriteByte(uint8_t data)
{
	char charData = static_cast<char>(data);
	m_file.write(&charData, 1);
}

void CFileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	m_file.write(static_cast<const char*>(srcData), size);
}
