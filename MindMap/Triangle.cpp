#include "Triangle.h"

Triangle::Triangle(Component* component)
{
	_type = "Triangle";
	_component = component;
	_width = _component->getWidth() + 10 + 10;
	_heigh = _component->getHeigh() + 10 + 20;
	_y = _component->getY() - 20;
	_xPixel = _component->getXPixel() - 10;
	Component *parent = _component->getParent();
	if (parent != NULL)
	{
		parent->replaceChild(_component, this);
	}
}

Triangle::~Triangle()
{
}

void Triangle::draw()
{
	Decorator::draw();
}
