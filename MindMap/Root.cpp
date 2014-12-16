#include "Root.h"

Root::Root(string description, int id)
{
	_id = id;
	//_description = description;
	setDescription(description);
	_type = "Root";
}

Root::~Root()
{
}

void Root::addParent(Component *node)
{

}
void Root::addSibling(Component *node)
{

}

void Root::setParent(Component *node)
{

}

Component* Root::getParent()
{
	return NULL;
}

Component* Root::clone(ComponentFactory* factory, list<Component *>& clipBoardList)
{
	return NULL;
}