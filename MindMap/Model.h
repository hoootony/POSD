#pragma once
#include "Component.h"
#include "Composite.h"
#include "ComponentFactory.h"
#include "CommandManger.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "gtest\gtest_prod.h"
#include <QGraphicsScene>

using namespace std;

class Model
{
	friend class CommandMangerTest;
	friend class ModelTest;
	FRIEND_TEST(ModelTest, createMindMap);
	FRIEND_TEST(ModelTest, setInsertMode);
	FRIEND_TEST(ModelTest, selectComponent);
	FRIEND_TEST(ModelTest, insertNodeCommand);
	FRIEND_TEST(ModelTest, fileContent);
private:
	list<Component *> _mindMap; 
	Component *_selectedNode;	//選擇到的節點 可以做編輯或複製等
	Component* _clipBoardNode;
	list<Component *> _clipBoardNodeList;	//最後面存放root點
	ComponentFactory _factory;
	CommandManger _commandManger;
	list<int> loadFileLine(char* line, string type);
	void makeNodeChild(list<list<int>> nodeChild);
	stringstream fileContent();
public:
	list<Component *> _mindMapDecorter{};
	Model();
	~Model();
	void createMindMap(string description);
	void insertNode(string description, string mode);
	bool readMindMapFile(string path);
	bool saveMindMapFile(string path);
	Component* selectComponent(int id);
	string showMap();
	Component* getComponent();
	void editDescription(Component* component, string description);
	void changeParentByNode(Component* myselfId, Component* newParentId);
	void changeParentWithList(Component* myselfId, Component* oldParentId, list<Component*> nodeList);
	void deleteComponent(Component* node);
	void addComponentWithList(Component* node, Component* parent, list<Component*> nodelist);
	bool isNodeExist(int id);
	bool isRoot(int id);
	void insertASiblingNode(Component* node, Component* newNode);
	void insertAParentNode(Component* node, Component* newNode);
	void insertAChildNode(Component* node, Component* newNode);
	void showGuiMap();
	void clearSelect();
	list<Component *> getMindMap();
	void changeParentCommand(int myselfId, int newParentId);
	void editDescriptionCommand(int id, string description);
	void deleteComponentCommand(int id);
	bool redo();
	bool undo();
	list<Component *> cutNode(Component* selectedNode);
	void copyNode();
	void pasteNode(Component *, list<Component *> clipBoardNodeList);
	bool canRedo();
	bool canUndo();
	void cutNodeCommand();
	void copyNodeCommand();
	void pasteNodeCommand();
	bool canPaste();
	void addRectangleStyle();
	void addCircleStyle();
	void addTriangleStyle();
	void cleanStyles();
};

