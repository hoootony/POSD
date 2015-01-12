#pragma once
#include <string>
#include <list>
#include <sstream>
#include <QGraphicsScene>
#include <gtest/gtest_prod.h>

using namespace std;
class NodeVisitor;
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
	double _width;
	double _heigh;
	int _x;	//x level by int
	double _xPixel;
	double _y;	//y pixel loaction
public:
	static const qreal MAX_WIDTH;
	static const qreal AFTER_SPACE;  
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
	virtual void showGuiMap(int depthX, double* depthY) = 0;
	void setSelected(bool select);
	bool isSelected();
	int getX();
	double getY();
	void setX(int x);
	void setY(double y);
	virtual Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList) = 0;
	virtual int getNodeYLevel() = 0;
	virtual void cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList) = 0;
	double getWidth();
	double getHeigh();
	virtual void draw() = 0;
	void setXPixel(double xPixel);
	double getXPixel();
	virtual Component* getComposite() = 0;
	virtual void replaceChild(Component* oldNode, Component* newNode) = 0;
	virtual void accept(NodeVisitor* visitor) = 0;
};

