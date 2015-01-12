#include "Node.h"
#include "ComponentFactory.h"
#include "NodeVisitor.h"

Node::Node()
{
	_nodeList.clear();
	_type = "Node";
}

Node::Node(string description, int id)
{
	_id = id;
	//_description = description;
	setDescription(description);
	_type = "Node";
	_parent = NULL;
}

Node::~Node()
{
}

void Node::addParent(Component *node) 
{
	//_parent->removeChild(this);	//原本父母親
	//_parent->addChild(node);
	_parent->replaceChild(this, node);

	node->setParent(_parent);	//插入的節點
	node->addChild(this);

	_parent = node;	//新節點為新的父母親
}

void Node::addSibling(Component *node)
{
	_parent->addChild(node);
}

void Node::setParent(Component *node)
{
	_parent = node;
}

Component* Node::getParent()
{
	return _parent;
}

Component* Node::clone(ComponentFactory* factory, list<Component *>& clipBoardList)
{
	return Composite::clone(factory, clipBoardList);
}

void Node::accept(NodeVisitor* visitor)
{
	visitor->visitor(this);
}
