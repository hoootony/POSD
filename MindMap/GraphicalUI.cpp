#include "GraphicalUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "GraphicsNode.h"
#include <QTimer>
#include "IObserver.h"

MindMap::MindMap(PresentationModel *pModel, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.graphicsView->setMouseTracking(true);

	_pModel = pModel;
	_pModel->attach(this);
	_scene = new QGraphicsScene(this);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(actionExit()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(actionCreateMindMap()));
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(actionLoadMindMap()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(actionSaveMindMap()));
	connect(ui.actionEdit, SIGNAL(triggered()), this, SLOT(actionEditNode()));
	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(actionDeleteNode()));
	connect(ui.actionInsert_a_Child, SIGNAL(triggered()), this, SLOT(actionInsertAChild()));
	connect(ui.actionInsert_a_Sibling, SIGNAL(triggered()), this, SLOT(actionInsertASibling()));
	connect(ui.actionInsert_a_Parent, SIGNAL(triggered()), this, SLOT(actionInsertAParent()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.actionCut, SIGNAL(triggered()), this, SLOT(actionCut()));
	connect(ui.actionCopy, SIGNAL(triggered()), this, SLOT(actionCopy()));
	connect(ui.actionPaste, SIGNAL(triggered()), this, SLOT(actionPaste()));

	refreshUI();
}

MindMap::~MindMap()
{
	delete _scene;
}

void MindMap::actionExit()
{
	exit(0);
}

void MindMap::actionCreateMindMap()
{
	string description = showInputDialog("Please input your description:");
	_pModel->createMindMap(description);
	refreshUI();
}

void MindMap::actionLoadMindMap()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open MindMap File"), QDir::currentPath(), tr("All files (*.*)"));
	_pModel->readMindMapFile(fileName.toStdString());
	refreshUI();
}

void MindMap::actionSaveMindMap()
{
	string fileName = QFileDialog::getSaveFileName(this, tr("Save MindMap File"), QDir::currentPath(), tr("All files (*.*)")).toStdString();
	_pModel->saveMindMapFile(fileName);
	_pModel->selectComponent(1);
	refreshUI();
}

void MindMap::actionEditNode()
{
	int id = _pModel->getSelectNodeId();
	_pModel->editDescriptionCommand(id, showInputDialog("Please input your description:"));
	refreshUI();
}

void MindMap::actionDeleteNode()
{
	int id = _pModel->getSelectNodeId();
	_pModel->deleteComponentCommand(id);
	refreshUI();
}

void MindMap::actionInsertAChild()
{
	_pModel->setInsertMode("Child");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void MindMap::actionInsertASibling()
{
	_pModel->setInsertMode("Sibling");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void MindMap::actionInsertAParent()
{
	_pModel->setInsertMode("Parent");
	_pModel->insertNode(showInputDialog("Please input your description:"));
	refreshUI();
}

void MindMap::about()
{
	QMessageBox::about(this, tr("About MindMap dialog"),
		tr("Student ID: 103598041\n"
		   "Student Name: Chang,Cheng-Yu\n"
		   "Courese Name: POSD"));
}

void MindMap::actionCut()
{
	_pModel->cutNode();
	refreshUI();
}

void MindMap::actionCopy()
{
	_pModel->copyNode();
	refreshUI();
}

void MindMap::actionPaste()
{
	_pModel->pasteNode();
	refreshUI();
}

string MindMap::showInputDialog(string title)
{
	//title = "Please input your description:";
	bool isOK;
	QString input = QInputDialog::getText(this, "Input Dialog", title.c_str(), QLineEdit::Normal, "your comment", &isOK);
	if (isOK)
		return input.toStdString();
	return "";
}

void MindMap::refreshUI()
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
}

void MindMap::mousePressEvent(QMouseEvent *event)
{
	_pModel->clearSelect();
	refreshUI();
	QMainWindow::mousePressEvent(event);
}

void MindMap::mouseDoubleClickEvent(QMouseEvent *event)
{
	refreshUI();
	QMainWindow::mouseDoubleClickEvent(event);
}