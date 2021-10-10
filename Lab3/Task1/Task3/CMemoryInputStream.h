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
	// Возвращает признак достижения конца данных потока
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	bool IsEOF() const override;

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	uint8_t ReadByte() override;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::vector<uint8_t> m_data;
	size_t m_currentIndex = 0;
};

