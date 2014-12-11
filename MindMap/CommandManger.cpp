#include "CommandManger.h"


CommandManger::CommandManger()
{
}

CommandManger::~CommandManger()
{
	while (!_undoCommands.empty())
	{
		Command* c = _undoCommands.top();
		_undoCommands.pop();
		delete c;
	}

	while (!_redoCommands.empty())
	{
		Command* c = _redoCommands.top();
		_redoCommands.pop();
		delete c;
	}
}

bool CommandManger::redo()
{
	if (_redoCommands.size() == 0)
		return false;

	Command* command = _redoCommands.top();
	_redoCommands.pop();
	command->execute();
	_undoCommands.push(command);
	return true;
}

bool CommandManger::undo()
{
	if (_undoCommands.size() == 0)
		return false;

	Command* command = _undoCommands.top();
	_undoCommands.pop();
	command->unexecute();
	_redoCommands.push(command);
	return true;
}

void CommandManger::execute(Command* command)
{
	command->execute();
	_undoCommands.push(command);

	while (!_redoCommands.empty())
	{
		Command* c = _redoCommands.top();
		_redoCommands.pop();
		delete c;
	}
}

bool CommandManger::canRedo()
{
	if (_redoCommands.size() == 0)
		return false;
	return true;
}

bool CommandManger::canUndo()
{
	if (_undoCommands.size() == 0)
		return false;
	return true;
}