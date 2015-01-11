#include "Circle.h"


Circle::Circle(Component* component)
{
	_type = "Circle";
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

Circle::~Circle()
{
}

void Circle::draw()
{
	Decorator::draw();
}