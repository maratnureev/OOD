#pragma once
#include "Interfaces.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(std::string const& fileName)
	{
		m_file.open(fileName, ios::out | ios::binary);
	}
	~CFileOutputStream()
	{
		m_file.close();
	}
	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	void WriteByte(uint8_t data) override;

	// Записывает в поток блок данных размером size байт, 
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;
private:
	fstream m_file;
};

