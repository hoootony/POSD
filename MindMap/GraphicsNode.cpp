#pragma once
#include <QGraphicsItem>
#include "GraphicsNode.h"
#include <QPainter>
#include <string>
#include <QInputDialog>
#include <QTimer>
#include "moc_GraphicsNode.cpp"		//for testing project, because it can't complie the .h file

const qreal GraphicsNode::WIDTH = 100;
const qreal GraphicsNode::HEIGH = 40;
const qreal GraphicsNode::AFTER_SPACE = 20;

GraphicsNode::GraphicsNode(qreal x, qreal y, Component *node, PresentationModel *pModel, QMainWindow *parent)
{
	_x = x;
	_y = y;
	_node = node;
	_pModel = pModel;
	_parent = parent;
}

GraphicsNode::~GraphicsNode()
{
}

QRectF GraphicsNode::boundingRect() const		//�~��Ĳ�ʽd��
{
	qreal penWidth = 1;
	qreal x = _x - penWidth / 2;
	qreal y = _y - penWidth / 2;
	return QRectF(x, y, WIDTH + penWidth, HEIGH + penWidth);
}

void GraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)	//ø�s�Ϯ�
{
	//�~��
	if (_node->isSelected())
		painter->setPen(Qt::red);
	else
		painter->setPen(Qt::black);
	painter->drawRect(QRectF(_x, _y, WIDTH, HEIGH));

	//��r
	painter->setPen(Qt::black);
	painter->drawText(QRectF(_x, _y, WIDTH, HEIGH), Qt::AlignVCenter | Qt::AlignHCenter, _node->getDescription().c_str());
}

void GraphicsNode::mousePressEvent(QGraphicsSceneMouseEvent *event)	//����
{
	QTimer::singleShot(10, this, SLOT(mouseClicked()));
	//QGraphicsItem::mousePressEvent(event);
}

void GraphicsNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)	//����
{
	bool isOK;
	QString input = QInputDialog::getText(_parent, "Input Dialog", "Please input your description:", QLineEdit::Normal, "your comment", &isOK);
	if (isOK)
		_pModel->editDescriptionCommand(_pModel->getSelectNodeId(), input.toStdString());
	QGraphicsItem::mousePressEvent(event);
}

void GraphicsNode::mouseClicked()	//���� timeout mouse click
{
	_pModel->clearSelect();
	_node->setSelected(true);
	_pModel->selectComponent(_node->getId());
	_pModel->notify();
}
