#pragma once
#include "NodeVisitor.h"
class SaveNodeVisitor :
	public NodeVisitor
{
public:
	SaveNodeVisitor();
	~SaveNodeVisitor();
	virtual void visitor(Root* root);
	virtual void visitor(Node* node);
};