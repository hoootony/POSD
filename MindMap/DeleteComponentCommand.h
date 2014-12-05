#pragma once
#include "Command.h"
#include "Component.h"
#include "Model.h"

class DeleteComponentCommand : public Command
{
private:
	Model* _model;
	Component* _component; 
	list<Component *> _originalNodeList;
	Component* _originalParent;
public:
	DeleteComponentCommand(Model* model, Component* component);
	~DeleteComponentCommand();
	void execute();
	void unexecute();
};

