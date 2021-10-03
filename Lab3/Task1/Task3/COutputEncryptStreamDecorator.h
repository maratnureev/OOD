#pragma once
#include "Interfaces.h"
#include <vector>
#include <algorithm>
#include <random>

class COutputEncryptStreamDecorator : public IOutputDataStream
{
public:
	COutputEncryptStreamDecorator(IOutputDataStreamPtr&& outputStream, int encryptKey)
		: m_outputStream(move(outputStream))
	{
		for (uint8_t i = 0; i < 255; i++)
		{
			m_encryptMap.push_back(i);
		}
		std::shuffle(m_encryptMap.begin(), m_encryptMap.end(), std::default_random_engine(encryptKey));
	}

	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	void WriteByte(uint8_t data) override;

	// Записывает в поток блок данных размером size байт, 
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	IOutputDataStreamPtr m_outputStream;
	std::vector<uint8_t> m_encryptMap;
};

