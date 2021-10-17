#pragma once
#include "ICommand.h"
#include <deque>
#include <memory>

class CHistory
{
public:
	bool CanUndo()const;
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command);
private:
	std::deque<std::unique_ptr<ICommand>> m_commands;
	size_t m_nextCommandIndex = 0;
};
