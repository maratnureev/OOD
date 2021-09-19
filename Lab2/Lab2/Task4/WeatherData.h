#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string name;
};

struct Statistic
{
	double maxValue = -std::numeric_limits<double>::infinity();
	double minValue = std::numeric_limits<double>::infinity();
	double accValue = 0;
	double countAcc = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Observed place: " << data.name << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	Statistic GetTemperature(std::string name)
	{
		return m_temperature[name];
	}

	Statistic GetPressure(std::string name)
	{
		return m_pressure[name];
	}

	Statistic GetHumidity(std::string name)
	{
		return m_humidity[name];
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature: " << std::endl;
		UpdateCurrentIndicator(m_temperature[data.name], data.temperature, data.name);
		std::cout << "Humidity: " << std::endl;
		UpdateCurrentIndicator(m_humidity[data.name], data.humidity, data.name);
		std::cout << "Pressure: " << std::endl;
		UpdateCurrentIndicator(m_pressure[data.name], data.pressure, data.name);
	}

	void UpdateCurrentIndicator(Statistic& prevData, double currentValue, std::string observerName)
	{
		if (prevData.minValue > currentValue)
		{
			prevData.minValue = currentValue;
		}
		if (prevData.maxValue < currentValue)
		{
			prevData.maxValue= currentValue;
		}
		prevData.accValue += currentValue;
		++prevData.countAcc;
		std::cout << "Place " << observerName << std::endl;
		std::cout << "Max " << prevData.maxValue << std::endl;
		std::cout << "Min " << prevData.minValue << std::endl;
		std::cout << "Average " << (prevData.accValue / prevData.countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::map<std::string, Statistic> m_temperature;
	std::map<std::string, Statistic> m_pressure;
	std::map<std::string, Statistic> m_humidity;

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string name)
		:m_name(name)
	{}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	std::string GetName() const
	{
		return m_name;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.name = GetName();
		return info;
	}
private:
	std::string m_name;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};