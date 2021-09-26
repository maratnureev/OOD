#pragma once

#include <set>
#include <map>
#include <functional>

/*
	Шаблонный интерфейс IObserver. Его должен реализовывать класс,
	желающий получать уведомления от соответствующего IObservable
	Параметром шаблона является тип аргумента,
	передаваемого Наблюдателю в метод Update
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
	Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
	инициировать рассылку уведомлений зарегистрированным наблюдателям.
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

// Реализация интерфейса IObservable
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
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<EventType, std::set<ObserverType*>> m_observers;
};