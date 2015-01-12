#include "Decorator.h"

Decorator::Decorator()
{
}

Decorator::~Decorator()
{
}

stringstream Decorator::getMap(int depth)
{
	return _component->getMap(depth);
}

list<Component *> Decorator::getNodeList()
{
	return _component->getNodeList();
}

void Decorator::addChild(Component *node)
{
	_component->addChild(node);
}

void Decorator::removeChild(Component *node)
{
	_component->removeChild(node);
}

void Decorator::addParent(Component *node)
{
	_component->addParent(node);
}

void Decorator::addSibling(Component *node)
{
	_component->addSibling(node);
}

void Decorator::setParent(Component *node)
{
	_component->setParent(node);
}

Component* Decorator::getParent()
{
	return _component->getParent();
}

bool Decorator::isChild(Component *node)
{
	return _component->isChild(node);
}

bool Decorator::haveSibling()
{
	return _component->haveSibling();
}

void Decorator::showGuiMap(int depthX, double* depthY)
{
	_component->showGuiMap(depthX, depthY);
}

Component* Decorator::clone(ComponentFactory* factory, list<Component *>& clipBoardList)
{
	return _component->clone(factory, clipBoardList);
}

int Decorator::getNodeYLevel()
{
	return _component->getNodeYLevel();
}

void Decorator::cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList)
{
	return _component->cutNode(mindmap, clipBoardList);
}

void Decorator::draw()
{
	_component->draw();
}

Component* Decorator::getComposite()
{
	return _component->getComposite();
}

void Decorator::replaceChild(Component* oldNode, Component* newNode)
{
	return _component->replaceChild(oldNode, newNode);
}

void Decorator::accept(NodeVisitor* visitor)
{
	_component->accept(visitor);
}