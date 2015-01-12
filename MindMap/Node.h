#pragma once
#include "Composite.h"
#include <string>
#include <gtest/gtest_prod.h>

using namespace std;

class Node : public Composite
{
	friend class NodeTest;
	FRIEND_TEST(NodeTest, addParent);
	FRIEND_TEST(NodeTest, addSibling);
	FRIEND_TEST(NodeTest, setParent);
private:
	Component *_parent;
public:
	Node();
	Node(string description, int id);
	~Node();
	void addParent(Component *node);
	void addSibling(Component *node);
	void setParent(Component *node);
	Component* getParent();
	Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList);
	void accept(NodeVisitor* visitor);
};

