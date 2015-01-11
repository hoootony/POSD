#include "GraphicsMindMap.h"
#include "GraphicsNode.h"

GraphicsMindMap::GraphicsMindMap()
{
}


GraphicsMindMap::~GraphicsMindMap()
{
}

void GraphicsMindMap::showGuiMap(QGraphicsScene* scene, list<Component *> mindMap, PresentationModel* pModel, QMainWindow *parent)
{
	list<GraphicsNode *> gNodeList;

	for (list<Component *>::iterator it = mindMap.begin(); it != mindMap.end(); ++it)
	{
		if ((*it)->getType() == "Root" || (*it)->getParent() != NULL)
		{
			qreal x = getLocateX(mindMap, (*it)->getX()) + Component::AFTER_SPACE * (*it)->getX();
			qreal y = (*it)->getY();
			(*it)->setXPixel(x);
			//qreal y = (*it)->getY() - (*it)->getHeigh() / 2;
			QGraphicsItem *qNode = new GraphicsNode(x, y, (*it), pModel, parent);
			scene->addItem(qNode);
			if ((*it)->getType() != "Root")
			{
				qreal parent_x = getLocateX(mindMap, (*it)->getParent()->getX()) + Component::AFTER_SPACE * (*it)->getParent()->getX() + (*it)->getParent()->getWidth();
				qreal parent_y = (*it)->getParent()->getY() + (*it)->getParent()->getHeigh() / 2;
				//qreal parent_y = (*it)->getParent()->getY();
				scene->addLine(x, y + (*it)->getHeigh() / 2, parent_x, parent_y);
			}
		}
	}
}

void GraphicsMindMap::showGuiMapDecorator(QGraphicsScene* scene, list<Component *> decorator, PresentationModel* pModel, QMainWindow *parent)
{
	for (list<Component *>::iterator it = decorator.begin(); it != decorator.end(); ++it)
	{
		if ((*it)->getType() == "Root" || (*it)->getParent() != NULL)
		{
			//qreal x = getLocateX(decorator, (*it)->getX()) + Component::AFTER_SPACE * (*it)->getX() - 5;
			qreal x = (*it)->getXPixel();
			qreal y = (*it)->getY();
			qreal w = (*it)->getWidth();
			qreal h = (*it)->getHeigh();

			QGraphicsItem *qNode;
			if ((*it)->getType() == "Rectangle")
			{
				//qNode = new QGraphicsRectItem(x, y, w, h);
				scene->addRect(x, y, w, h, QPen(Qt::blue));
			}
			else if ((*it)->getType() == "Circle")
			{
				//qNode = new QGraphicsEllipseItem(x, y, w, h);
				scene->addEllipse(x, y, w, h, QPen(Qt::red));
			}
			else if ((*it)->getType() == "Triangle")
			{
				QPolygonF triagnle;
				triagnle.append(QPointF(x, y + h));
				triagnle.append(QPointF(x + w, y + h));
				triagnle.append(QPointF(x + w / 2, y));
				triagnle.append(QPointF(x, y + h));
				//qNode = new QGraphicsPolygonItem(triagnle);
				scene->addPolygon(triagnle, QPen(Qt::green));
			}
			//scene->addItem(qNode);
		}
	}
}

qreal GraphicsMindMap::getMaxWidth(list<Component*> mindMap, Component* node)
{
	qreal width = node->getWidth();
	for (list<Component*>::iterator it = mindMap.begin(); it != mindMap.end(); ++it)
	{
		if ((*it)->getX() == node->getX())
		{
			if ((*it)->getWidth() > width)
			{
				width = (*it)->getWidth();
			}
		}
	}
	return width;
}

qreal GraphicsMindMap::getLocateX(list<Component*> mindMap, qreal xLevel)
{
	qreal x = 0;
	for (int i = 0; i < xLevel; i++)
	{
		for (list<Component*>::iterator it = mindMap.begin(); it != mindMap.end(); ++it)
		{
			if (i == (*it)->getX())
			{
				x += getMaxWidth(mindMap, *it);
				break;
			}
		}
	}
	return x;
}