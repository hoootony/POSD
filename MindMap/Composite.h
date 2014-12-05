#pragma once
#include "Component.h"
#include <list>
#include <string>
#include <sstream>
#include <gtest/gtest_prod.h>
#include <QGraphicsScene>

using namespace std;

class Composite : public Component
{
	friend class CompositeTest;
	FRIEND_TEST(CompositeTest, addChild);
	FRIEND_TEST(CompositeTest, removeChild);
	FRIEND_TEST(CompositeTest, isChild);
	FRIEND_TEST(CompositeTest, haveSibling);
protected:
	list<Component *> _nodeList;
	int _x;
	double _y;
public:
	Composite();
	~Composite();
	stringstream getMap(int depth);
	void addChild(Component *node); 
	void removeChild(Component *node);
	virtual void addParent(Component *node) = 0;
	virtual void addSibling(Component *node) = 0;
	list<Component *> getNodeList();
	virtual void setParent(Component *node) = 0;
	virtual Component* getParent() = 0;
	bool isChild(Component *node);
	bool haveSibling();
	void showGuiMap(int depthX, vector<int>* heighDepthX);
	int getX();
	double getY();
	void setX(int x);
	void setY(double y);
	int getNodeYLevel();
	virtual Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList);
	void cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList);
};

