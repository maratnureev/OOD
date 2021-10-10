#include "CFileInputStream.h"

bool CFileInputStream::IsEOF() const
{
	return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	char symbol;
	if (!m_file.read(&symbol, 1))
		throw std::ios_base::failure("End of the file");
	return static_cast<uint8_t>(symbol);
}

std::streamsize CFileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (!m_file.read(static_cast<char*>(dstBuffer), size))
		throw std::ios_base::failure("End of the file");

	return m_file.gcount();
}
