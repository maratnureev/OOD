#pragma once

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
	virtual void Destroy() = 0;
	virtual ~ICommand() = default;
};