#pragma once
#include "NodeVisitor.h"
class SaveNodeVisitor :
	public NodeVisitor
{
public:
	SaveNodeVisitor();
	~SaveNodeVisitor();
	void visitor(Root* root);
	void visitor(Node* node);
};