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
template <typename T, typename E>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, E eventType) = 0;
	virtual void NotifyObservers(E eventType) = 0;
	virtual void RemoveObserver(IObserver<T>& observer, E eventType) = 0;
};

// Реализация интерфейса IObservable
template <class T, typename E>
class CObservable : public IObservable<T, E>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, E eventType) override
	{
		m_observers[eventType].insert(&observer);
	}

	void NotifyObservers(E eventType) override
	{
		T data = GetChangedData();
		for (auto& observer : m_observers[eventType])
		{
			observer->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer, E eventType) override
	{
		m_observers[eventType].erase(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<E, std::set<ObserverType*>> m_observers;
};