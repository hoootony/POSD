#include "Triangle.h"

Triangle::Triangle(Component* component)
{
	_type = "Triangle";
	_component = component;
	_width = _component->getWidth() + 10 * 2;
	_heigh = _component->getHeigh() + 10 * 2;
	_y = _component->getY() - 10;
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
