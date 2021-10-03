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
	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	void WriteByte(uint8_t data) override;

	// ���������� � ����� ���� ������ �������� size ����, 
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;
private:
	fstream m_file;
};

