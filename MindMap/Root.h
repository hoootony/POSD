#pragma once
#include "Composite.h"
#include <string>

using namespace std;

class Root : public Composite
{
public:
	Root(string description, int id);
	~Root();
	void addParent(Component *node);
	void addSibling(Component *node);
	void setParent(Component *node);
	Component* getParent();
	Component* clone(ComponentFactory* factory, list<Component *>& clipBoardList);
};

