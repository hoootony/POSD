#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class InsertAChildNodeCmd : public Command
{
private:
	Model* _model;
	Component* _selected;
	Component* _newNode;
public:
	InsertAChildNodeCmd(Model* model, Component* selected, Component* newNode);
	~InsertAChildNodeCmd();
	void execute();
	void unexecute();
};

