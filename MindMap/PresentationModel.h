#pragma once
#include "Model.h"
#include "CommandManger.h"
#include <QGraphicsScene>
#include "Subject.h"
#include <QMainWindow>

class PresentationModel : public Subject
{
private:
	Model _model;
	string _insertMode;
	bool _isPaste;
	map<string, bool> _actionEnabled;
	//CommandManger _commandManger;
	void setGuiRootEdit();
	void setGuiNodeEdit();
	void setGuiLoaded();
	void setGuiSelectNull();
	void setGuiCutAndCopy();
	void setGuiPaste();
public:
	PresentationModel();
	~PresentationModel();
	string showMap();
	bool setInsertMode(string description);
	void createMindMap(string description);
	void selectComponent(int id);
	void insertNode(string description);
	bool saveMindMapFile(string path);
	bool readMindMapFile(string path);
	bool undo();
	bool redo();
	bool isNodeExist(int id);
	bool isRoot(int id);
	void changeParentCommand(int myselfId, int newParentId);
	void editDescriptionCommand(int id, string description);
	void deleteComponentCommand(int id);
	void showGuiMap(QGraphicsScene *scene, QMainWindow *parent = 0);
	bool isActionEnabled(string actionName);
	void clearSelect(); 
	int getSelectNodeId();
	void refreshUI();
	bool haveCreateMindMap();
	void cutNode();
	void copyNode();
	void pasteNode();
};