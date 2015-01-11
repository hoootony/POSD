#pragma once
#include "Decorator.h"
class Rectangle :
	public Decorator
{
public:
	Rectangle(Component* component);
	~Rectangle();
	void draw();
};

