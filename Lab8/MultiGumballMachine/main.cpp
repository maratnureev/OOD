#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <optional>
#include <functional>
#include "NaiveGumBallMachine.h"
#include "GumBallMachineWithState.h"
#include "CMenu.h"

using namespace std;
using namespace std::placeholders;

namespace
{
	class GumballMachineController
	{
	public:
		GumballMachineController(istream& in, ostream& out)
			: m_gumballMachine(make_unique<with_state::CGumballMachine>(0, out))
			, m_menu(in, out)
		{
			m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
			m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
			AddMenuItem("insertQuarter", "insert 1 quarter", &GumballMachineController::InsertQuarter);
			AddMenuItem("ejectQuarter", "ejects 1 quarter", &GumballMachineController::EjectQuarter);
			AddMenuItem("turnCrank", "turn crank and give you gumball", &GumballMachineController::TurnCrank);
			AddMenuItem("refill", "refill gumball machine", &GumballMachineController::Refill);
			AddMenuItem("info", "gives you gumball machine state", &GumballMachineController::Info);
		}
		void Start()
		{
			m_menu.Run();
		}

	private:
		// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
		typedef void (GumballMachineController::* MenuHandler)(istream& in);

		void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
		{
			m_menu.AddItem(shortcut, description, bind(handler, this, _1));
		}

		void InsertQuarter(istream&)
		{
			m_gumballMachine->InsertQuarter();
		}

		void EjectQuarter(istream&)
		{
			m_gumballMachine->EjectQuarter();
		}

		void TurnCrank(istream&)
		{
			m_gumballMachine->TurnCrank();
		}
		void Refill(istream& in)
		{
			unsigned ballNum = 0;
			in >> ballNum;
			m_gumballMachine->Refill(ballNum);
		}
		void Info(istream&)
		{
			cout << m_gumballMachine->ToString();
		}

		CMenu m_menu;
		unique_ptr<with_state::CGumballMachine> m_gumballMachine;
	};

}

int main()
{
	GumballMachineController controller(cin, cout);
	controller.Start();
	return 0;
}