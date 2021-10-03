#pragma once
#include <fstream>
#include "Interfaces.h"

class CFileInputStream: public IInputDataStream
{
public:
	CFileInputStream(std::string const& fileName)
	{
		m_file.open(fileName, ios::in | ios::binary);
		m_file.seekg(0, m_file.end);
		m_fileSize = m_file.tellg();
		m_file.seekg(0, m_file.beg);
	}
	~CFileInputStream()
	{
		m_file.close();
	}

	bool IsEOF() override;

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	uint8_t ReadByte() override;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::fstream m_file;
	std::streampos m_fileSize = 0;
};

