#pragma once
#include "Command.h"
#include <stack>
#include <gtest/gtest_prod.h>

using namespace std;

class CommandManger
{
	friend class CommandMangerTest;
	friend class Model;
	FRIEND_TEST(CommandMangerTest, execute);
	FRIEND_TEST(CommandMangerTest, redo);
	FRIEND_TEST(CommandMangerTest, undo);
private:
	stack<Command *> _redoCommands;
	stack<Command *> _undoCommands;
public:
	CommandManger();
	~CommandManger();
	virtual void execute(Command * command);
	bool redo();
	bool undo();
};

