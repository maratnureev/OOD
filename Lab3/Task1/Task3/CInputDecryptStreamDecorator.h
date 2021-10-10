#pragma once
#include "Interfaces.h"
#include <map>
#include <algorithm>
#include <random>

class CInputDecryptStreamDecorator : public IInputDataStream
{
public:
	CInputDecryptStreamDecorator(IInputDataStreamPtr inputStream, int encryptKey)
		: m_inputStream(move(inputStream))
	{
		std::vector<uint8_t> encryptMap;
		int i = 0;
		while (i < 256)
		{
			encryptMap.push_back(i++);
		}
		std::shuffle(encryptMap.begin(), encryptMap.end(), std::default_random_engine(encryptKey));
		int index = 0;
		for (auto value : encryptMap)
		{
			m_encryptMap[value] = index++;
		}
	}

	bool IsEOF() const override;

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	uint8_t ReadByte() override;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	IInputDataStreamPtr m_inputStream;
	std::map<uint8_t, uint8_t> m_encryptMap;
};

