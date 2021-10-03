#pragma once
#include "Interfaces.h"

class CInputDecompressStreamDecorator : public IInputDataStream
{
public:
	CInputDecompressStreamDecorator(IInputDataStreamPtr&& inputStream)
		: m_inputStream(move(inputStream))
	{
		m_currentByte.count = 0;
		m_currentByte.byte = 0;
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
	IInputDataStreamPtr m_inputStream;
	CompressedByte m_currentByte;
};