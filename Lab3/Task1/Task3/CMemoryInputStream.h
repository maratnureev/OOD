#pragma once
#include "Interfaces.h"
#include <vector>
#include <iterator>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t> data)
		:m_data(data)
	{
	}
	// ���������� ������� ���������� ����� ������ ������
	// ����������� ���������� std::ios_base::failure � ������ ������
	bool IsEOF() const override;

	// ��������� ���� �� ������. 
	// ����������� ���������� std::ios_base::failure � ������ ������
	uint8_t ReadByte() override;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::vector<uint8_t> m_data;
	size_t m_currentIndex = 0;
};

