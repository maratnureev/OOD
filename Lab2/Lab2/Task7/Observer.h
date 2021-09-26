#pragma once

#include <set>
#include <map>
#include <functional>

/*
	��������� ��������� IObserver. ��� ������ ������������� �����,
	�������� �������� ����������� �� ���������������� IObservable
	���������� ������� �������� ��� ���������,
	������������� ����������� � ����� Update
*/

enum EventType {
	WIND_CHANGED,
	TEMPERATURE_CHANGED,
	PRESSURE_CHANGED,
	HUMIDITY_CHANGED,
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
	��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
	������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, EventType eventType) = 0;
	virtual void NotifyObservers(EventType eventType) = 0;
	virtual void RemoveObserver(IObserver<T>& observer, EventType eventType) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, EventType eventType) override
	{
		m_observers[eventType].insert(&observer);
	}

	void NotifyObservers(EventType eventType) override
	{
		T data = GetChangedData();
		for (auto& observer : m_observers[eventType])
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer, EventType eventType) override
	{
		m_observers[eventType].erase(&observer);
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	std::map<EventType, std::set<ObserverType*>> m_observers;
};