#include "EditComponentCommand.h"

EditComponentCommand::EditComponentCommand(Model* model, Component* component, string description)
{
	_model = model;
	_component = component;
	_newDescription = description;
	_prevDescription = _component->getDescription();
}

EditComponentCommand::~EditComponentCommand()
{

}

void EditComponentCommand::execute()
{
	//_component->setDescription(_newDescription);
	_model->editDescription(_component, _newDescription);
}

void EditComponentCommand::unexecute()
{
	//_component->setDescription(_prevDescription);
	_model->editDescription(_component, _prevDescription);
}