#pragma once

#include <set>
#include <map>
#include <exception>
#include <functional>


/*
	��������� ��������� IObserver. ��� ������ ������������� �����,
	�������� �������� ����������� �� ���������������� IObservable
	���������� ������� �������� ��� ���������,
	������������� ����������� � ����� Update
*/
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
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
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
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType*> m_observers;
	std::multimap<int, ObserverType*> m_observersMap;
};