#pragma once
#include "Decorator.h"
class Circle :
	public Decorator
{
public:
	Circle(Component* component);
	~Circle();
	void draw();
};

