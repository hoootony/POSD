#pragma once
#include "Component.h"

using namespace std;

class Component;
class ComponentFactory
{
private:
	int _count;
public:
	ComponentFactory();
	~ComponentFactory();
	Component* create(string type, string description);
	Component* create(int id, string type, string description);
};

