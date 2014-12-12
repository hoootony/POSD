#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class CutNodeCommand : public Command
{
private:
	Model* _model;
	Component* _selectedNode;
	Component* _parent;
	list<Component*> _clipBoardNodeList;

public:
	CutNodeCommand(Model* model, Component* selectedNode);
	~CutNodeCommand();
	void execute();
	void unexecute();
};

