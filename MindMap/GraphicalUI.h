#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include <QtWidgets/QMainWindow>
#include "ui_GraphicalUI.h"
#include "PresentationModel.h"
#include <string>
#include "IObserver.h"

class GraphicalUI : public QMainWindow, public IObserver
{
	Q_OBJECT

public:
	GraphicalUI(PresentationModel *pModel, QWidget *parent = 0);
	~GraphicalUI();

public slots:
	void actionExit();
	void actionCreateGraphicalUI();
	void actionLoadGraphicalUI();
	void actionSaveGraphicalUI();
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
	void actionUndo();
	void actionRedo();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	Ui::GraphicalUIClass ui;
	PresentationModel *_pModel;
	QGraphicsScene *_scene;
	string showInputDialog(string title);
};

#endif // GRAPHICALUI_H
