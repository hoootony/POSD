#pragma once
//#include <QtCore/QCoreApplication>
#include "TextUIView.h"
#include "Model.h"
#include "PresentationModel.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class TextUIView
{
private:
	PresentationModel* _pModel;
	void printMenu();
	void printInsertMenu();
	void printEditMenu();
	void createMindMap();
	void insertNode();
	void saveMindMap();
	void loadMindMapFile();
	void editNode();
	void editDescription(int id);
	void changeParent(int id);
	void deleteNode(int id);
	void redo();
	void undo();
public:
	TextUIView();
	TextUIView(PresentationModel *pModel);
	~TextUIView();
	void run();
};

