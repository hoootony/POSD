#pragma once
#include "Root.h"
#include "Node.h"

class NodeVisitor
{
public:
	NodeVisitor();
	~NodeVisitor();
	virtual void visitor(Root* root);
	virtual void visitor(Node* node);
};

