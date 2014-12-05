#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand(Model* model, Component* myself, Component* newParent)
{
	_model = model;
	_myself = myself;
	_newParent = newParent;
	list<Component*> nodeList = _myself->getNodeList();
	for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		_childNodeList.push_back(*it);
	}
	_oldParent = _myself->getParent();
}

ChangeParentCommand::~ChangeParentCommand()
{
}

void ChangeParentCommand::execute()
{
	_model->changeParentByNode(_myself, _newParent);
}

void ChangeParentCommand::unexecute()
{
	_model->changeParentWithList(_myself, _oldParent, _childNodeList);
}