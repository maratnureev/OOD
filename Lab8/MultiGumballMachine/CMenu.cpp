#include "CMenu.h"
#include <algorithm>
#include <iostream>

using namespace std;

void CMenu::AddItem(const string& shortcut, const string& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void CMenu::Run()
{
	ShowInstructions();

	string command;
	while ((cout << ">")
		&& getline(m_in, command)
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions() const
{
	m_out << "Commands list:\n";
	for (auto& item : m_items)
	{
		m_out << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const string& command)
{
	istringstream iss(command);
	string name;
	iss >> name;

	m_exit = false;
	auto it = find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == name;
		});
	if (it != m_items.end())
	{
		try
		{
			it->command(iss);
		}
		catch (exception e)
		{
			m_out << e.what() << endl;
		}
	}
	else
	{
		cout << "Unknown command\n";
	}
	return !m_exit;
}