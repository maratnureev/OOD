#pragma once
#include "../Lab5/CAbstractCommand.h"

class CMockCommand : public CAbstractCommand
{
protected:

	void DoExecute() override
	{
	}

	void DoUnexecute() override
	{
	}

	void Destroy() override
	{
	}
};

