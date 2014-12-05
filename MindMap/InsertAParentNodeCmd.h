#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class InsertAParentNodeCmd : public Command
{
private:
	Model* _model;
	Component* _selected;
	Component* _newNode;
public:
	InsertAParentNodeCmd(Model* model, Component* selected, Component* newNode);
	~InsertAParentNodeCmd();
	void execute();
	void unexecute();
};

