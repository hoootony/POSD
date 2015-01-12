#pragma once
#include "Component.h"
class Decorator :
	public Component
{
protected:
	Component* _component;
public:
	Decorator();
	~Decorator();
	virtual stringstream getMap(int depth);
	virtual list<Component *> getNodeList();
	virtual void addChild(Component *node);
	virtual void removeChild(Component *node);
	virtual void addParent(Component *node);
	virtual void addSibling(Component *node);
	virtual void setParent(Component *node);
	virtual Component* getParent();
	virtual bool isChild(Component *node);
	virtual bool haveSibling();
	virtual void showGuiMap(int depthX, double* depthY);
	virtual Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList);
	virtual int getNodeYLevel();
	virtual void cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList);
	virtual void draw();
	Component* getComposite();
	void cleanStyles();
	virtual void replaceChild(Component* oldNode, Component* newNode);
	virtual void accept(NodeVisitor* visitor);
};