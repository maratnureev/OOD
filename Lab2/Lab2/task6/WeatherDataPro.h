#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include "Observer.h"
#include "WeatherData.h"

const double HALF_CIRCLE = 180;
const double FULL_CIRCLE = 360;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
	std::string name;
};

struct Statistic
{
	double maxValue = -std::numeric_limits<double>::infinity();
	double minValue = std::numeric_limits<double>::infinity();
	double accValue = 0;
	int countAcc = 0;
};

struct WindVector
{
	double windVectorX = 0;
	double windVectorY = 0;
};

struct WindStatistic
{
	WindVector avgWindVector;
	double accSpeed = 0;
	WindVector maxWindVector;
	double maxSpeed = -std::numeric_limits<double>::infinity();
	WindVector minWindVector;
	double minSpeed = std::numeric_limits<double>::infinity();
	int countAcc = 0;
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
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	Statistic GetTemperature()
	{
		return m_temperature;
	}

	Statistic GetPressure()
	{
		return m_pressure;
	}

	Statistic GetHumidity()
	{
		return m_humidity;
	}
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Temperature: " << std::endl;
		UpdateCurrentIndicator(m_temperature, data.temperature);
		std::cout << "Humidity: " << std::endl;
		UpdateCurrentIndicator(m_humidity, data.humidity);
		std::cout << "Pressure: " << std::endl;
		UpdateCurrentIndicator(m_pressure, data.pressure);
		UpdateWindIndicator(data);
	}

	void UpdateCurrentIndicator(Statistic& prevData, double currentValue)
	{
		if (prevData.minValue > currentValue)
		{
			prevData.minValue = currentValue;
		}
		if (prevData.maxValue < currentValue)
		{
			prevData.maxValue = currentValue;
		}
		prevData.accValue += currentValue;
		++prevData.countAcc;

		std::cout << "Max " << prevData.maxValue << std::endl;
		std::cout << "Min " << prevData.minValue << std::endl;
		std::cout << "Average " << (prevData.accValue / prevData.countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void UpdateWindIndicator(SWeatherInfo const& data)
	{
		auto windVectorX = data.windSpeed * cos(data.windDirection * M_PI / HALF_CIRCLE);
		auto windVectorY = data.windSpeed * sin(data.windDirection * M_PI / HALF_CIRCLE);
		if (m_windDirections.minSpeed > data.windSpeed)
		{
			m_windDirections.minWindVector.windVectorX = windVectorX;
			m_windDirections.minWindVector.windVectorY = windVectorY;
			m_windDirections.minSpeed = data.windSpeed;
		}
		if (m_windDirections.maxSpeed < data.windSpeed)
		{
			m_windDirections.maxWindVector.windVectorX = windVectorX;
			m_windDirections.maxWindVector.windVectorY = windVectorY;
			m_windDirections.maxSpeed = data.windSpeed;
		}
		m_windDirections.accSpeed += data.windSpeed;
		++m_windDirections.countAcc;

		WindVector windMeasurments;
		m_windDirections.avgWindVector.windVectorX += windVectorX;
		m_windDirections.avgWindVector.windVectorY += windVectorY;
		double minDirection = atan2(m_windDirections.minWindVector.windVectorY, m_windDirections.minWindVector.windVectorX) * HALF_CIRCLE / M_PI;
		double maxDirection = atan2(m_windDirections.maxWindVector.windVectorY, m_windDirections.maxWindVector.windVectorX) * HALF_CIRCLE / M_PI;
		double avgDirection = atan2(m_windDirections.avgWindVector.windVectorY, m_windDirections.avgWindVector.windVectorX) * HALF_CIRCLE / M_PI;
		std::cout << "Wind: " << std::endl;
		std::cout << "Min speed " << m_windDirections.minSpeed << std::endl;
		std::cout << "Direction " << ((minDirection < 0) ? minDirection + FULL_CIRCLE : minDirection) << std::endl;
		std::cout << "Max speed " << m_windDirections.maxSpeed << std::endl;
		std::cout << "Direction " << ((maxDirection < 0) ? maxDirection + FULL_CIRCLE : maxDirection) << std::endl;
		std::cout << "Average speed " << m_windDirections.accSpeed / m_windDirections.countAcc << std::endl;
		std::cout << "Direction " << ((avgDirection < 0) ? avgDirection + FULL_CIRCLE : avgDirection) << std::endl;
	}

	Statistic m_temperature;
	Statistic m_pressure;
	Statistic m_humidity;
	WindStatistic m_windDirections;
};

class CWeatherDataPro : public CObservable<SWeatherInfo>
{
public:
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
	// Скорость ветра (м/c)
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}
	// Направление ветра (0-360 градусов)
	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windDirection = GetWindDirection();
		info.windSpeed = GetWindSpeed();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0.0;
	double m_windDirection = 0.0;
};