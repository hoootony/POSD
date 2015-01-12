#include "DisplayNodeVisitor.h"
#include <iostream>

DisplayNodeVisitor::DisplayNodeVisitor()
{
}

DisplayNodeVisitor::~DisplayNodeVisitor()
{
}

void DisplayNodeVisitor::visitor(Node* node)
{
	stringstream ss;
	int depth = 1;
	string blank(depth * 2, ' ');  //�p��`�ת��ťռƶq
	int indexDepth = 0;
	ss << "�ϡ�" << node->getDescription() << "(" << node->getType() << "," << "ID:" << node->getId() << ")" << endl;  //�L�X�`�I���e
	list<Component*> nodeList(node->getNodeList());
	for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		for (indexDepth = 0; indexDepth < depth; indexDepth++)	//print �e�m�ť�
		{
			Component* parent = (*it);
			for (int i = 0; i < depth - indexDepth; i++)
			{
				parent = parent->getParent();
			}
			if (indexDepth >= 1 && parent->haveSibling()) // not root && have sibling
				ss << "�U�@";
			else
				ss << "�@�@";  //two sapce
		}
		ss << (**it).getMap(depth + 1).str();
	}
	cout << ss.str();
}

void DisplayNodeVisitor::visitor(Root* root)
{
	stringstream ss;
	int depth = 1;
	string blank(depth * 2, ' ');  //�p��`�ת��ťռƶq
	int indexDepth = 0;
	ss << "�ϡ�" << root->getDescription() << "(" << root->getType() << "," << "ID:" << root->getId() << ")" << endl;  //�L�X�`�I���e
	list<Component*> nodeList(root->getNodeList());
	for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		for (indexDepth = 0; indexDepth < depth; indexDepth++)	//print �e�m�ť�
		{
			Component* parent = (*it);
			for (int i = 0; i < depth - indexDepth; i++)
			{
				parent = parent->getParent();
			}
			if (indexDepth >= 1 && parent->haveSibling()) // not root && have sibling
				ss << "�U�@";
			else
				ss << "�@�@";  //two sapce
		}
		ss << (**it).getMap(depth + 1).str();
	}
	cout << ss.str();
}