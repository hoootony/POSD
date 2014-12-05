#pragma once
#include "Command.h"
#include "Model.h"

class ChangeParentCommand : public Command
{
private:
	Model* _model;
	Component* _myself;
	Component* _newParent;
	Component* _oldParent;
	list<Component*> _childNodeList;
public:
	ChangeParentCommand(Model* model, Component* myselfId, Component* newParentId);
	~ChangeParentCommand();
	void execute();
	void unexecute();
};

