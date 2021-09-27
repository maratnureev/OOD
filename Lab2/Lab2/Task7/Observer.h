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
template <typename T, typename E>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, E eventType) = 0;
	virtual void NotifyObservers(E eventType) = 0;
	virtual void RemoveObserver(IObserver<T>& observer, E eventType) = 0;
};

// ���������� ���������� IObservable
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
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	std::map<E, std::set<ObserverType*>> m_observers;
};