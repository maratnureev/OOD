#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace with_state
{
	const int MAX_QUARTERS = 5;
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
		virtual unsigned GetQuartersAmount()const = 0;
		virtual void IncreaseQuartersAmount() = 0;
		virtual void DecreaseQuartersAmount() = 0;
		virtual void EmptyBank() = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;
		virtual void SetFullState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine, std::ostream& out)
			:m_gumballMachine(gumballMachine)
			, m_out(out)
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
			else if (m_gumballMachine.GetQuartersAmount() != 0)
				m_gumballMachine.SetHasQuarterState();
			else
				m_gumballMachine.SetNoQuarterState();
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
			if (m_gumballMachine.GetQuartersAmount() != 0)
			{
				m_out << "Returning quarter";
				m_gumballMachine.DecreaseQuartersAmount();
			}
			else
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
			m_out << "You inserted a quarter\n";
			m_gumballMachine.IncreaseQuartersAmount();
			if (m_gumballMachine.GetQuartersAmount() == 5)
				m_gumballMachine.SetFullState();
		}
		void EjectQuarter() override
		{
			m_out << "Quarter returned\n";
			if (m_gumballMachine.GetQuartersAmount() == 0)
				m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			m_out << "You turned...\n";
			m_gumballMachine.DecreaseQuartersAmount();
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			m_out << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank or for quarter";
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
			m_gumballMachine.IncreaseQuartersAmount();
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

	class CFullOfQuartersState : public IState
	{
	public:
		CFullOfQuartersState(IGumballMachine& gumballMachine, std::ostream& out)
			: m_gumballMachine(gumballMachine)
			, m_out(out)
		{}

		void InsertQuarter() override
		{
			m_out << "You can't insert another quarter\n";
		}
		void EjectQuarter() override
		{
			m_out << "Quarters returned\n";
			m_gumballMachine.EmptyBank();
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			m_out << "You turned...\n";
			m_gumballMachine.DecreaseQuartersAmount();
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

	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls, std::ostream& out)
			: m_soldState(*this, out)
			, m_soldOutState(*this, out)
			, m_noQuarterState(*this, out)
			, m_hasQuarterState(*this, out)
			, m_fullState(*this, out)
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
				"Bank: " + std::to_string(m_quartersAmount) + " quarter" + (m_quartersAmount != 1 ? "s" : "") + "\n"
				"Machine is " + m_state->ToString() + "\n";
		}
		void Refill(unsigned numBalls)
		{
			m_count = numBalls;
			if (numBalls > 0 && m_quartersAmount == 0)
				SetNoQuarterState();
			else if (numBalls > 0 && m_quartersAmount > 0 && m_quartersAmount < MAX_QUARTERS)
				SetHasQuarterState();
			else if (numBalls > 0 && m_quartersAmount == MAX_QUARTERS)
				SetFullState();
			else
				SetSoldOutState();
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_count;
		}

		unsigned GetQuartersAmount()const override
		{
			return m_quartersAmount;
		}

		void IncreaseQuartersAmount() override
		{
			m_quartersAmount++;
		}

		void DecreaseQuartersAmount() override
		{
			m_quartersAmount--;
		}

		void EmptyBank() override
		{
			m_quartersAmount = 0;
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
		void SetFullState() override
		{
			m_state = &m_fullState;
		}
	private:
		unsigned m_count = 0;
		unsigned m_quartersAmount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		CFullOfQuartersState m_fullState;
		IState* m_state;
		std::ostream& m_out;
	};
}