#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include <QtWidgets/QMainWindow>
#include "ui_GraphicalUI.h"
#include "PresentationModel.h"
#include <string>
#include "IObserver.h"

class MindMap : public QMainWindow, public IObserver
{
	Q_OBJECT

public:
	MindMap(PresentationModel *pModel, QWidget *parent = 0);
	~MindMap();

public slots:
	void actionExit();
	void actionCreateMindMap();
	void actionLoadMindMap();
	void actionSaveMindMap();
	void actionEditNode();
	void actionDeleteNode();
	void actionInsertAChild();
	void actionInsertASibling();
	void actionInsertAParent();
	void about();
	void actionCut();
	void actionCopy();
	void actionPaste();
	void refreshUI();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	Ui::MindMapClass ui;
	PresentationModel *_pModel;
	QGraphicsScene *_scene;
	string showInputDialog(string title);
};

#endif // GRAPHICALUI_H
