#pragma once
#include "Component.h"
#include "PresentationModel.h"

class GraphicsMindMap
{
private:
	list<Component *> _mindMap;
	QGraphicsScene* _scene;

public:
	GraphicsMindMap();
	~GraphicsMindMap();
	void showGuiMap(QGraphicsScene* scene, list<Component *> mindMap, PresentationModel* pModel, QMainWindow *parent);
	void showGuiMapDecorator(QGraphicsScene* scene, list<Component *> decorator, PresentationModel* pModel, QMainWindow *parent);

private:
	qreal getMaxWidth(list<Component *> mindMap, Component* node);
	qreal getLocateX(list<Component*> mindMap, qreal xLevel);
};

