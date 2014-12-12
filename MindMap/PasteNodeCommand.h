#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class PasteNodeCommand : public Command
{
private:
	Model* _model;
	Component* _selectedNode;
	list<Component*> _clipBoardNodeList;

public:
	PasteNodeCommand(Model* model, Component* selectedNode, list<Component*> clipBoardNodeList);
	~PasteNodeCommand();
	void execute();
	void unexecute();
};

