#pragma once
#include "NodeVisitor.h"
class DisplayNodeVisitor :
	public NodeVisitor
{
public:
	DisplayNodeVisitor();
	~DisplayNodeVisitor();
	virtual void visitor(Root* root);
	virtual void visitor(Node* node);
};