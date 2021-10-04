#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

enum class CoffeeType{
	STANDARD,
	DOUBLE,
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeType type)
		:m_type(type)
	{
		std::string description = m_type == CoffeeType::STANDARD ? "Cappuccino" : "Double cappuccino";
		CCoffee(description);
	}

	double GetCost() const override
	{
		return m_type == CoffeeType::STANDARD ? 80 : 120;
	}
private:
	CoffeeType m_type;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeType type)
		:m_type(type)
	{
		std::string description = m_type == CoffeeType::STANDARD ? "Latte" : "Double latte";
		CCoffee(description);
	}

	double GetCost() const override
	{
		return m_type == CoffeeType::STANDARD ? 90 : 130;
	}
private:
	CoffeeType m_type;
};


enum class TeaType {
	HIBISCUS_TEA,
	BLACK_TEA,
	GREEN_TEA,
	PUER_TEA,
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType type)
		: CBeverage(GetTeaDescription(type))
	{}

	double GetCost() const override
	{
		return 30;
	}

	std::string GetTeaDescription(TeaType type) const
	{
		std::string description;
		switch (type)
		{
		case TeaType::BLACK_TEA:
			description = "Black tea";
		case TeaType::GREEN_TEA:
			description = "Green tea";
		case TeaType::HIBISCUS_TEA:
			description = "Hibiscus";
		case TeaType::PUER_TEA:
			description = "Puer";
		}
	}
};

enum class MilkshakePortionType{
	SMALL,
	STANDARD,
	BIG,
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionType type)
		:CBeverage(GetMilkshakeDescription(type))
		, m_type(type)
	{}

	double GetCost() const override
	{
		switch (m_type)
		{
		case MilkshakePortionType::SMALL:
			return 50;
		case MilkshakePortionType::STANDARD:
			return 60;
		case MilkshakePortionType::BIG:
			return 80;
		}
	}

	std::string GetMilkshakeDescription(MilkshakePortionType type) const 
	{
		std::string description;
		switch (type)
		{
		case MilkshakePortionType::SMALL:
			description = "Small milkshake";
		case MilkshakePortionType::STANDARD:
			description = "Medium milkshake";
		case MilkshakePortionType::BIG:
			description = "Big milkshake";
		}
	}
private:
	MilkshakePortionType m_type;
};