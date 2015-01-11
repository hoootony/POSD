#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(Component* component)
{
	_type = "Rectangle";
	_component = component;
	_width = _component->getWidth() + 5 * 2;
	_heigh = _component->getHeigh() + 5 * 2;
	_y = _component->getY() - 5;
	_xPixel = _component->getXPixel() - 5;
	Component *parent = _component->getParent();
	if (parent != NULL)
	{
		parent->replaceChild(_component, this);
	}
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw()
{
	cout << "Decorator: Rectangle(" << _x << ", " << _y << ", " << _width << ", " << _heigh << ")" << endl;
	Decorator::draw();
}