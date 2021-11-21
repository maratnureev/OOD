#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace with_state
{
	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount()const = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine, std::ostream& out)
			:m_gumballMachine(gumballMachine)
			,m_out(out)
		{}
		void InsertQuarter() override
		{
			m_out << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			m_out << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			m_out << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				m_out << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out)
			:m_gumballMachine(gumballMachine)
			, m_out(out)
		{}

		void InsertQuarter() override
		{
			m_out << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			m_out << "You can't eject, you haven't inserted a quarter yet\n";
		}
		void TurnCrank() override
		{
			m_out << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			m_out << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
			:m_gumballMachine(gumballMachine)
			, m_out(out)
		{}

		void InsertQuarter() override
		{
			m_out << "You can't insert another quarter\n";
		}
		void EjectQuarter() override
		{
			m_out << "Quarter returned\n";
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			m_out << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			m_out << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
			: m_gumballMachine(gumballMachine)
			, m_out(out)
		{}

		void InsertQuarter() override
		{
			m_out << "You inserted a quarter\n";
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			m_out << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			m_out << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			m_out << "You need to pay first\n";
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};

	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls, std::ostream& out)
			: m_soldState(*this, out)
			, m_soldOutState(*this, out)
			, m_noQuarterState(*this, out)
			, m_hasQuarterState(*this, out)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
			, m_out(out)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		std::string ToString()const
		{
			return "Mighty Gumball, Inc.\n"
				"C++-enabled Standing Gumball Model #2016 (with state)\n"
				"Inventory: " + std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "\n"
				"Machine is " + m_state->ToString() + "\n";
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_count;
		}
		void ReleaseBall() override
		{
			if (m_count != 0)
			{
				m_out << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
	private:
		unsigned m_count = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
		std::ostream& m_out;
	};
}