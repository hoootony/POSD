#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class InsertASiblingNodeCmd : public Command
{
private:
	Model* _model;
	Component* _selected;
	Component* _newNode;
public:
	InsertASiblingNodeCmd(Model* model, Component* selected, Component* newNode);
	~InsertASiblingNodeCmd();
	void execute();
	void unexecute();
};
