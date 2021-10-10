#pragma once
#include <fstream>
#include "Interfaces.h"

class CFileInputStream: public IInputDataStream
{
public:
	CFileInputStream(std::string const& fileName)
	{
		m_file.open(fileName, ios::in | ios::binary);
	}
	~CFileInputStream()
	{
		m_file.close();
	}

	bool IsEOF() const override;

	// ��������� ���� �� ������. 
	// ����������� ���������� std::ios_base::failure � ������ ������
	uint8_t ReadByte() override;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::fstream m_file;
};

