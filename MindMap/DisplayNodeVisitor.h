#pragma once
#include "NodeVisitor.h"
class DisplayNodeVisitor :
	public NodeVisitor
{
public:
	DisplayNodeVisitor();
	~DisplayNodeVisitor();
	void visitor(Root* root);
	void visitor(Node* node);
};