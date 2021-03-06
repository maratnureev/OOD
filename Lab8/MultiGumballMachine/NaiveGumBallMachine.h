#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace naive
{
	const int MAX_QUARTERS = 5;
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,			// ?????? ???????????
			NoQuarter,			// ??? ???????
			HasQuarter,			// ???? ???????
			Sold,				// ?????? ??????
		};

		CGumballMachine(unsigned count, std::ostream& out)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
			, m_out(out)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				m_out << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				m_state = State::HasQuarter;
				m_out << "You inserted a quarter\n";
				m_quartersAmount++;
				break;
			case State::HasQuarter:
				if (m_quartersAmount == MAX_QUARTERS)
				{
					m_out << "You can't insert another quarter\n";
					break;
				}
				m_out << "You inserted a quarter\n";
				m_quartersAmount++;
				break;
			case State::Sold:
				m_out << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				m_out << "Quarter returned\n";
				m_quartersAmount = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				m_out << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				m_out << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				if (m_quartersAmount != 0)
				{
					m_out << "Returning quarter";
					m_quartersAmount--;
				}
				else
					m_out << "You can't eject, you haven't inserted a quarter yet\n";
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				m_out << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				m_out << "You turned but there's no quarter\n";
				break;
			case State::HasQuarter:
				m_out << "You turned...\n";
				m_quartersAmount--;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				m_out << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		void Refill(unsigned numBalls)
		{
			m_count += numBalls;
			if (m_count > 0 && m_quartersAmount == 0)
				m_state = State::NoQuarter;
			else if (m_count > 0 && m_quartersAmount > 0 && m_quartersAmount <= MAX_QUARTERS)
				m_state = State::HasQuarter;
			else
				m_state = State::SoldOut;
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank" 
				: "delivering a gumball";
			return "Mighty Gumball, Inc.\n"
				"C++-enabled Standing Gumball Model #2016\n"
				"Inventory: " + std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "\n"
				"Bank: " + std::to_string(m_quartersAmount) + " quarter" + (m_quartersAmount != 1 ? "s" : "") + "\n"
				"Machine is " + state + "\n";
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				m_out << "A gumball comes rolling out the slot...\n";
				--m_count;
				if (m_count == 0)
				{
					m_out << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else if (m_quartersAmount == 0)
					m_state = State::NoQuarter;
				else
					m_state = State::HasQuarter;
				break;
			case State::NoQuarter:
				m_out << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				m_out << "No gumball dispensed\n";
				break;
			}
		}

		unsigned m_count;	// ?????????? ???????
		State m_state = State::SoldOut;
		unsigned m_quartersAmount = 0;
		std::ostream& m_out;
	};
}