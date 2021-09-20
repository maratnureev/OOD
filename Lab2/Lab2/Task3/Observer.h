#pragma once

#include <set>
#include <map>
#include <exception>
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
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		if (m_observers.find(&observer) == m_observers.end())
		{
			m_observers.insert(&observer);
			m_observersMap.insert(std::make_pair(priority, &observer));
			return;
		}
		
		throw std::logic_error("Observer already registered");
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_observersMap.rbegin(); it != m_observersMap.rend(); ++it)
		{
			it->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
		for (auto it = m_observersMap.rbegin(); it != m_observersMap.rend(); ++it)
			if (it->second == &observer)
			{
				m_observersMap.erase(it->first);
				return;
			}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
	std::multimap<int, ObserverType*> m_observersMap;
};