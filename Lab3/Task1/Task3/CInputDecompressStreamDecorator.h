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

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	uint8_t ReadByte() override;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	IInputDataStreamPtr m_inputStream;
	CompressedByte m_currentByte;
};