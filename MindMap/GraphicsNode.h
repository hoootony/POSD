#pragma once
#include <QGraphicsItem>
#include "Component.h"
#include "PresentationModel.h"
#include <QMainWindow>
#include <QObject>

class GraphicsNode : public QGraphicsObject
{
	Q_OBJECT
public:
	static const qreal MAX_WIDTH;
	static const qreal MAX_HEIGH;
	static const qreal AFTER_SPACE;
	GraphicsNode(qreal x, qreal y, Component *node, PresentationModel *pModel, QMainWindow *parent = 0);
	~GraphicsNode();

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

public slots:
	void mouseClicked();

private:
	qreal _x;
	qreal _y;
	qreal _width;
	qreal _heigh;
	Component *_node;
	PresentationModel *_pModel;
	QMainWindow *_parent;
};

