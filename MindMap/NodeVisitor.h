#pragma once
#include "Root.h"
#include "Node.h"

class NodeVisitor
{
public:
	NodeVisitor();
	~NodeVisitor();
	virtual void visitor(Root* root) = 0;
	virtual void visitor(Node* node) = 0;
};

