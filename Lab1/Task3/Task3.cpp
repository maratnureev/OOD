#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

using DanceBehavior = function<void()>;

void DanceWaltz()
{
	cout << "I'm dancing waltz!" << endl;
}

void DanceMinuet()
{
	cout << "I'm dancing minuet!" << endl;
}

void NoDance(){}

using FlyBehavior = function<void()>;

void FlyWithWings()
{
	cout << "I'm flying with wings!!" << endl;
}

void FlyNoWay(){}

using QuackBehavior = function<void()>;

void Quacking()
{
	cout << "Quack Quack!!!" << endl;
}

void Squeak()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuack(){}

class Duck
{
public:
	Duck()
	{
	}
	void Quack()
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		if (m_flyBehavior)
		{
			m_flyBehavior();
		}
	}
	void Dance()
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}
	void SetFlyBehavior(const FlyBehavior& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetQuackBehavior(const QuackBehavior& quackBehavior)
	{
		m_quackBehavior = quackBehavior;
	}
	void SetDanceBehavior(const DanceBehavior& danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
	{
		SetQuackBehavior(Quacking);
		SetFlyBehavior(FlyWithWings);
		SetDanceBehavior(DanceWaltz);
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck()
	{
		SetQuackBehavior(Quacking);
		SetFlyBehavior(FlyWithWings);
		SetDanceBehavior(DanceWaltz);
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck()
	{
		SetQuackBehavior(MuteQuack);
		SetFlyBehavior(FlyNoWay);
		SetDanceBehavior(NoDance);
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck()
	{
		SetQuackBehavior(Squeak);
		SetFlyBehavior(FlyNoWay);
		SetDanceBehavior(NoDance);
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck()
	{
		SetQuackBehavior(Quacking);
		SetFlyBehavior(FlyNoWay);
		SetDanceBehavior(NoDance);
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}