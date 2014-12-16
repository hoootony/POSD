#pragma once
#include <QGraphicsItem>
#include "GraphicsNode.h"
#include <QPainter>
#include <string>
#include <QInputDialog>
#include <QTimer>
#include "moc_GraphicsNode.cpp"		//for testing project, because it can't complie the .h file

const qreal GraphicsNode::MAX_WIDTH = 100;
const qreal GraphicsNode::MAX_HEIGH = 40;
const qreal GraphicsNode::AFTER_SPACE = 20;

GraphicsNode::GraphicsNode(qreal x, qreal y, Component *node, PresentationModel *pModel, QMainWindow *parent)
{
	_x = x;
	_y = y;
	_node = node;
	_pModel = pModel;
	_parent = parent;

	//QFont myFont;
	//QFontMetrics fm(myFont);
	//_width = fm.width(_node->getDescription().c_str()) + AFTER_SPACE;
	//_heigh = MAX_HEIGH;
	_heigh = _node->getHeigh();
	_width = _node->getWidth();
}

GraphicsNode::~GraphicsNode()
{
}

QRectF GraphicsNode::boundingRect() const		//外框觸動範圍
{
	qreal penWidth = 1;
	qreal x = _x - penWidth / 2;
	qreal y = _y - penWidth / 2;
	return QRectF(x, y, _width + penWidth, _heigh + penWidth);
}

void GraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)	//繪製圖案
{
	//外框
	if (_node->isSelected())
		painter->setPen(Qt::red);
	else
		painter->setPen(Qt::black);
	painter->drawRect(QRectF(_x, _y, _width, _heigh));

	//文字
	QFont myFont;
	QFontMetrics fm(myFont);
	painter->setPen(Qt::black);
	if (_heigh > fm.height() + Component::AFTER_SPACE)
	{//自動換行
		for (int i = 0; i < ((_heigh - Component::AFTER_SPACE) / fm.height()); i++)
		{
			double textHigh = fm.height() * i;
			painter->drawText(_x, _y + Component::AFTER_SPACE / 2  + textHigh, _width, fm.height(), Qt::AlignVCenter | Qt::AlignHCenter, _node->getDescription().substr(0 + Component::MAX_WIDTH*i, Component::MAX_WIDTH).c_str());
		}
	}
	else
	{//不換行
		painter->drawText(_x, _y, _width, _heigh, Qt::AlignVCenter | Qt::AlignHCenter, _node->getDescription().c_str());
	}
}

void GraphicsNode::mousePressEvent(QGraphicsSceneMouseEvent *event)	//單擊
{
	QTimer::singleShot(10, this, SLOT(mouseClicked()));
	//QGraphicsItem::mousePressEvent(event);
}

void GraphicsNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)	//雙擊
{
	bool isOK;
	QString input = QInputDialog::getText(_parent, "Input Dialog", "Please input your description:", QLineEdit::Normal, "your comment", &isOK);
	if (isOK)
		_pModel->editDescriptionCommand(_pModel->getSelectNodeId(), input.toStdString());
	QGraphicsItem::mousePressEvent(event);
}

void GraphicsNode::mouseClicked()	//單擊 timeout mouse click
{
	_pModel->clearSelect();
	_node->setSelected(true);
	_pModel->selectComponent(_node->getId());
	_pModel->notify();
}
