#include "History.h"
#include "ICommand.h"
#include <assert.h>

const int MAX_HISTORY_SIZE = 10;

bool CHistory::CanUndo() const
{
	return m_nextCommandIndex != 0;
}

bool CHistory::CanRedo() const
{
	return m_nextCommandIndex != m_commands.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[m_nextCommandIndex - 1]->Unexecute(); // может выбросить исключение
		--m_nextCommandIndex;
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute(); // может выбросить исключение
		++m_nextCommandIndex;
	}
}

void CHistory::AddAndExecuteCommand(std::unique_ptr<ICommand>&& command)
{
	if (m_nextCommandIndex < m_commands.size()) // Ќе происходит расширени€ истории команд
	{
		command->Execute();	// может бросить исключение
		++m_nextCommandIndex;				
		m_commands.resize(m_nextCommandIndex);	// исключение выброшено не будет, т.к. размер <= текущему
		m_commands.back() = move(command);
	}
	else // будет происходить расширение истории команд
	{
		assert(m_nextCommandIndex == m_commands.size());
		// резервируем место по добавл€емую команду 
		m_commands.emplace_back(nullptr); // может выбросить исключение, но мы еще ничего не трогали

		try
		{
			command->Execute(); // может выбросить исключение
			// замен€ем команду-заглушку
			m_commands.back() = move(command); // не бросает исключений
			++m_nextCommandIndex; // теперь можно обновить индекс следующей команды
			if (m_nextCommandIndex > MAX_HISTORY_SIZE)
			{
				m_commands.erase(m_commands.begin());
				m_nextCommandIndex = MAX_HISTORY_SIZE;
			}
		}
		catch (...)
		{
			m_commands.pop_back();
			throw;
		}
	}
}