#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(Model* model, Component* component)
{
	_model = model;
	_component = component;
	_originalNodeList = _component->getNodeList();
	_originalParent = _component->getParent();
}

DeleteComponentCommand::~DeleteComponentCommand()
{
}

void DeleteComponentCommand::execute()
{
	_model->deleteComponent(_component);
}

void DeleteComponentCommand::unexecute()
{
	_model->addComponentWithList(_component, _originalParent, _originalNodeList);
}