#pragma once
#include "Interfaces.h"

class COutputCompressStreamDecorator : public IOutputDataStream
{
public:
	COutputCompressStreamDecorator(IOutputDataStreamPtr&& outputStream)
		: m_outputStream(move(outputStream))
	{
		m_currentByte.byte = 0;
		m_currentByte.count = 0;
	}
	~COutputCompressStreamDecorator()
	{
		WriteByte(m_currentByte.byte);
		WriteByte(m_currentByte.count);
	}

	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	void WriteByte(uint8_t data) override;

	// ���������� � ����� ���� ������ �������� size ����, 
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	IOutputDataStreamPtr m_outputStream;
	CompressedByte m_currentByte;
};
