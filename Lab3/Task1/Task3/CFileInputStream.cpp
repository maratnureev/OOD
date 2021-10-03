#include "CFileInputStream.h"

bool CFileInputStream::IsEOF()
{
	return m_fileSize == m_file.tellg();
}

uint8_t CFileInputStream::ReadByte()
{
	if (IsEOF())
		throw std::ios_base::failure("End of the file");
	char symbol;
	m_file.read(&symbol, 1);
	return static_cast<uint8_t>(symbol);
}

std::streamsize CFileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (!m_file.read(static_cast<char*>(dstBuffer), size))
		throw std::ios_base::failure("End of the file");

	return m_file.gcount();
}
