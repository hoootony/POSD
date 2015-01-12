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
	//_parent->removeChild(this);	//�쥻������
	//_parent->addChild(node);
	_parent->replaceChild(this, node);

	node->setParent(_parent);	//���J���`�I
	node->addChild(this);

	_parent = node;	//�s�`�I���s��������
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
