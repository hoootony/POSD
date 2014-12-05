#pragma once
#include <string>
#include <list>
#include <sstream>
#include <QGraphicsScene>
#include <gtest/gtest_prod.h>

using namespace std;
class ComponentFactory;
class Component
{
	friend class ComponentTest;
	FRIEND_TEST(ComponentTest, component);
protected:
	int _id;
	string _description;
	string _type;
	bool _selected = false;
public:
	Component();
	~Component();
	int getId();
	void setDescription(string description);
	string getDescription();
	string getType();
	virtual stringstream getMap(int depth) = 0;
	virtual list<Component *> getNodeList() = 0;
	virtual void addChild(Component *node) = 0;
	virtual void removeChild(Component *node) = 0;
	virtual void addParent(Component *node) = 0;
	virtual void addSibling(Component *node) = 0;
	virtual void setParent(Component *node) = 0;
	virtual Component* getParent() = 0;
	virtual bool isChild(Component *node) = 0;
	virtual bool haveSibling() = 0;
	virtual void showGuiMap(int depthX, vector<int>* heighDepthX) = 0;
	void setSelected(bool select);
	bool isSelected();
	virtual int getX() = 0;
	virtual double getY() = 0;
	virtual void setX(int x) = 0;
	virtual void setY(double y) = 0;
	virtual Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList) = 0;
	virtual int getNodeYLevel() = 0;
	virtual void cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList) = 0;
};

