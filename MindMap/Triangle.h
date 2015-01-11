#pragma once
#include "Decorator.h"
class Triangle :
	public Decorator
{
public:
	Triangle(Component* component);
	~Triangle();
	void draw();
};

