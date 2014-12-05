#include "Component.h"
#include "ComponentFactory.h"

Component::Component()
{
}

Component::~Component()
{
}

int Component::getId()
{
	return _id;
}

string Component::getDescription()
{
	return _description;
}

string Component::getType()
{
	return _type;
}

void Component::setDescription(string description)
{
	_description = description;
}

void Component::setSelected(bool select)
{
	_selected = select;
}

bool Component::isSelected()
{
	return _selected;
}