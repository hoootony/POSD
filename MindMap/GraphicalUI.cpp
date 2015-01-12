#include "GraphicalUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "GraphicsNode.h"
#include <QTimer>
#include "IObserver.h"

GraphicalUI::GraphicalUI(PresentationModel *pModel, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.graphicsView->setMouseTracking(true);

	_pModel = pModel;
	_pModel->attach(this);
	_scene = new QGraphicsScene(this);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(actionExit()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(actionCreateGraphicalUI()));
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(actionLoadGraphicalUI()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(actionSaveGraphicalUI()));
	connect(ui.actionEdit, SIGNAL(triggered()), this, SLOT(actionEditNode()));
	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(actionDeleteNode()));
	connect(ui.actionInsert_a_Child, SIGNAL(triggered()), this, SLOT(actionInsertAChild()));
	connect(ui.actionInsert_a_Sibling, SIGNAL(triggered()), this, SLOT(actionInsertASibling()));
	connect(ui.actionInsert_a_Parent, SIGNAL(triggered()), this, SLOT(actionInsertAParent()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.actionCut, SIGNAL(triggered()), this, SLOT(actionCut()));
	connect(ui.actionCopy, SIGNAL(triggered()), this, SLOT(actionCopy()));
	connect(ui.actionPaste, SIGNAL(triggered()), this, SLOT(actionPaste()));
	connect(ui.actionUndo, SIGNAL(triggered()), this, SLOT(actionUndo()));
	connect(ui.actionRedo, SIGNAL(triggered()), this, SLOT(actionRedo()));
	connect(ui.actionAdd_Rectangle, SIGNAL(triggered()), this, SLOT(actionAddRectangle()));
	connect(ui.actionAdd_Circle, SIGNAL(triggered()), this, SLOT(actionAddCircle()));
	connect(ui.actionAdd_Triangle, SIGNAL(triggered()), this, SLOT(actionAddTriangle()));
	connect(ui.actionClean_styles, SIGNAL(triggered()), this, SLOT(actionCleanStyles()));
	connect(ui.actionMove_Up, SIGNAL(triggered()), this, SLOT(actionMoveUp()));
	connect(ui.actionMove_Down, SIGNAL(triggered()), this, SLOT(actionMoveDown()));
	connect(ui.actionCollapse, SIGNAL(triggered()), this, SLOT(actionCollapse()));
	connect(ui.actionExpand, SIGNAL(triggered()), this, SLOT(actionExpand()));

	refreshUI();
}

GraphicalUI::~GraphicalUI()
{
	delete _scene;
}

void GraphicalUI::actionExit()
{
	exit(0);
}

void GraphicalUI::actionCreateGraphicalUI()
{
	string description = showInputDialog("Please input your description:");
	_pModel->createMindMap(description);
	refreshUI();
}

void GraphicalUI::actionLoadGraphicalUI()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open GraphicalUI File"), QDir::currentPath(), tr("MindMap (*.mm);;All files (*.*)"));
	_pModel->readMindMapFile(fileName.toStdString());
	refreshUI();
}

void GraphicalUI::actionSaveGraphicalUI()
{
	string fileName = QFileDialog::getSaveFileName(this, tr("Save GraphicalUI File"), QDir::currentPath(), tr("MindMap (*.mm);;All files (*.*)")).toStdString();
	_pModel->saveMindMapFile(fileName);
	_pModel->selectComponent(1);
	refreshUI();
}

void GraphicalUI::actionEditNode()
{
	int id = _pModel->getSelectNodeId();
	_pModel->editDescriptionCommand(id, showInputDialog("Please input your description:"));
	refreshUI();
}

void GraphicalUI::actionDeleteNode()
{
	int id = _pModel->getSelectNodeId();
	_pModel->deleteComponentCommand(id);
	refreshUI();
}

void GraphicalUI::actionInsertAChild()
{
	_pModel->setInsertMode("Child");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void GraphicalUI::actionInsertASibling()
{
	_pModel->setInsertMode("Sibling");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void GraphicalUI::actionInsertAParent()
{
	_pModel->setInsertMode("Parent");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void GraphicalUI::about()
{
	QMessageBox::about(this, tr("About GraphicalUI dialog"),
		tr("Student ID: 103598041\n"
		   "Student Name: Chang,Cheng-Yu\n"
		   "Courese Name: POSD"));
}

void GraphicalUI::actionCut()
{
	_pModel->cutNode();
	refreshUI();
}

void GraphicalUI::actionCopy()
{
	_pModel->copyNode();
	refreshUI();
}

void GraphicalUI::actionPaste()
{
	_pModel->pasteNode();
	refreshUI();
}

string GraphicalUI::showInputDialog(string title)
{
	//title = "Please input your description:";
	bool isOK;
	QString input = QInputDialog::getText(this, "Input Dialog", title.c_str(), QLineEdit::Normal, "your comment", &isOK);
	if (isOK)
		return input.toStdString();
	return "";
}

void GraphicalUI::refreshUI()
{
	//QGraphicsView Refresh
	_scene->clear();
	_pModel->showGuiMap(_scene, this);
	ui.graphicsView->setScene(_scene);

	//GUI action enabled
	ui.actionNew->setEnabled(_pModel->isActionEnabled(ui.actionNew->objectName().toStdString()));
	ui.actionLoad->setEnabled(_pModel->isActionEnabled(ui.actionLoad->objectName().toStdString()));
	ui.actionSave->setEnabled(_pModel->isActionEnabled(ui.actionSave->objectName().toStdString()));
	ui.actionEdit->setEnabled(_pModel->isActionEnabled(ui.actionEdit->objectName().toStdString()));
	ui.actionDelete->setEnabled(_pModel->isActionEnabled(ui.actionDelete->objectName().toStdString()));
	ui.actionInsert_a_Child->setEnabled(_pModel->isActionEnabled(ui.actionInsert_a_Child->objectName().toStdString()));
	ui.actionInsert_a_Parent->setEnabled(_pModel->isActionEnabled(ui.actionInsert_a_Parent->objectName().toStdString()));
	ui.actionInsert_a_Sibling->setEnabled(_pModel->isActionEnabled(ui.actionInsert_a_Sibling->objectName().toStdString()));
	ui.actionCut->setEnabled(_pModel->isActionEnabled(ui.actionCut->objectName().toStdString()));
	ui.actionCopy->setEnabled(_pModel->isActionEnabled(ui.actionCopy->objectName().toStdString()));
	ui.actionPaste->setEnabled(_pModel->isActionEnabled(ui.actionPaste->objectName().toStdString()));
	ui.actionUndo->setEnabled(_pModel->isActionEnabled(ui.actionUndo->objectName().toStdString()));
	ui.actionRedo->setEnabled(_pModel->isActionEnabled(ui.actionRedo->objectName().toStdString()));
	ui.actionAdd_Rectangle->setEnabled(_pModel->isActionEnabled(ui.actionAdd_Rectangle->objectName().toStdString()));
	ui.actionAdd_Circle->setEnabled(_pModel->isActionEnabled(ui.actionAdd_Circle->objectName().toStdString()));
	ui.actionAdd_Triangle->setEnabled(_pModel->isActionEnabled(ui.actionAdd_Triangle->objectName().toStdString()));
	ui.actionClean_styles->setEnabled(_pModel->isActionEnabled(ui.actionClean_styles->objectName().toStdString()));
	ui.actionMove_Up->setEnabled(_pModel->isActionEnabled(ui.actionMove_Up->objectName().toStdString()));
	ui.actionMove_Down->setEnabled(_pModel->isActionEnabled(ui.actionMove_Down->objectName().toStdString()));
	ui.actionCollapse->setEnabled(_pModel->isActionEnabled(ui.actionCollapse->objectName().toStdString()));
	ui.actionExpand->setEnabled(_pModel->isActionEnabled(ui.actionExpand->objectName().toStdString()));
}

void GraphicalUI::mousePressEvent(QMouseEvent *event)
{
	_pModel->clearSelect();
	refreshUI();
	QMainWindow::mousePressEvent(event);
}

void GraphicalUI::mouseDoubleClickEvent(QMouseEvent *event)
{
	refreshUI();
	QMainWindow::mouseDoubleClickEvent(event);
}

void GraphicalUI::actionUndo()
{
	_pModel->undo();
	refreshUI();
}

void GraphicalUI::actionRedo()
{
	_pModel->redo();
	refreshUI();
}

void GraphicalUI::actionAddRectangle()
{
	_pModel->addRectangleStyle();
	refreshUI();
}

void GraphicalUI::actionAddCircle()
{
	_pModel->addCircleStyle();
	refreshUI();
}

void GraphicalUI::actionAddTriangle()
{
	_pModel->addTriangleStyle();
	refreshUI();
}

void GraphicalUI::actionCleanStyles()
{
	_pModel->cleanStyles();
	refreshUI();
}

void GraphicalUI::actionMoveUp()
{
	_pModel->moveUp();
	refreshUI();
}

void GraphicalUI::actionMoveDown()
{
	_pModel->moveDown();
	refreshUI();
}

void GraphicalUI::actionCollapse()
{
	_pModel->collapse();
	refreshUI();
}

void GraphicalUI::actionExpand()
{
	_pModel->expand();
	refreshUI();
}