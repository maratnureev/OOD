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

	// ��������� ���� �� ������. 
	// ����������� ���������� std::ios_base::failure � ������ ������
	uint8_t ReadByte() override;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::fstream m_file;
	std::streampos m_fileSize = 0;
};

