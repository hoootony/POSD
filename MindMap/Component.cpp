#include "Component.h"
#include "ComponentFactory.h"
#include <QFontMetrics>

const qreal Component::MAX_WIDTH = 30;
const qreal Component::AFTER_SPACE = 20;

Component::Component()
{
}

Component::~Component()
{
}

int Component::getId()
{
	return _id;
}

string Component::getDescription()
{
	return _description;
}

string Component::getType()
{
	return _type;
}

void Component::setDescription(string description)
{
	_description = description;

	QFont myFont;
	QFontMetrics fm(myFont);
	if (description.size() > MAX_WIDTH)
	{
		_width = fm.width(string(MAX_WIDTH, '0').c_str()) + AFTER_SPACE;
		//_width = fm.width(description.substr(0, MAX_WIDTH).c_str()) + AFTER_SPACE;
		_heigh = fm.height() * ceil(description.size() / MAX_WIDTH) + AFTER_SPACE;
	}
	else
	{
		_width = fm.width(_description.c_str()) + AFTER_SPACE;
		_heigh = fm.height() + AFTER_SPACE;
	}
}

void Component::setSelected(bool select)
{
	_selected = select;
}

bool Component::isSelected()
{
	return _selected;
}

int Component::getX()
{
	return _x;
}

double Component::getY()
{
	return _y;
}

void Component::setX(int x)
{
	_x = x;
}

void Component::setY(double y)
{
	_y = y;
}

double Component::getHeigh()
{
	return _heigh;
}

double Component::getWidth()
{
	return _width;
}

void Component::setXPixel(double xPixel)
{
	_xPixel = xPixel;
}

double Component::getXPixel()
{
	return _xPixel;
}
