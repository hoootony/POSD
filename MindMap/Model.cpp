#include "Model.h"
#include "Node.h"
#include "Root.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertAChildNodeCmd.h"
#include "InsertAParentNodeCmd.h"
#include "InsertASiblingNodeCmd.h"
#include "CutNodeCommand.h"
#include "PasteNodeCommand.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "DisplayNodeVisitor.h"
#include "SaveNodeVisitor.h"

Model::Model()
{
	_selectedNode = NULL;
}

Model::~Model()
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		delete *it;
	}
}

void Model::createMindMap(string description) //建立MindMap
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		delete *it;
	}
	_mindMap.clear();
	Component *component = _factory.create(0, "Root", description);
	_mindMap.push_back(component);
}

void Model::insertNode(string description, string mode) //插入Node
{
	if (mode.compare("Child") == 0)
	{
		Component *newNode = _factory.create("Node", description);
		_commandManger.execute(new InsertAChildNodeCmd(this, _selectedNode, newNode));
	}
	else if (mode.compare("Parent") == 0)
	{
		Component *newNode = _factory.create("Node", description);
		_commandManger.execute(new InsertAParentNodeCmd(this, _selectedNode, newNode));
	}
	else if (mode.compare("Sibling") == 0)
	{
		Component *newNode = _factory.create("Node", description);
		_commandManger.execute(new InsertASiblingNodeCmd(this, _selectedNode, newNode));
	}
}

bool Model::readMindMapFile(string path)		//讀檔
{
	if (!ifstream(path))
		return false;

	char line[1000];		//檔案每行的文字
	ifstream myfile;
	int lineIndex = 0;
	list<list<int>> nodeChild;
	myfile.open(path, fstream::in);
	do
	{
		myfile.getline(line, sizeof(line));
		if (strlen(line) > 0)
		{
			if (lineIndex == 0)	//第一行為Root
			{
				nodeChild.push_back(loadFileLine(line, "Root"));
			}
			else
			{
				nodeChild.push_back(loadFileLine(line, "Node"));
			}
			lineIndex++;
		}
	} while (!myfile.eof());
	myfile.close();
	makeNodeChild(nodeChild);
	return true;
}

list<int> Model::loadFileLine(char* line, string type)	//分析檔案內容一行並新增 後回傳child list
{
	int id;
	string description;
	list<int> child;
	char *tok = strtok(line, "\"");
	id = atoi(tok);			//id
	tok = strtok(NULL, "\"");
	description = tok;		//description
	tok = strtok(NULL, " ");
	while (tok != NULL)
	{
		child.push_back(atoi(tok));
		tok = strtok(NULL, " ");
	}
	
	if (type.compare("Root") == 0)
	{
		createMindMap(description);
	}
	else
	{
		_mindMap.push_back(_factory.create(id, type, description));
	}
	return child;
}

void Model::makeNodeChild(list<list<int>> nodeChild)	//建立讀檔的關聯
{
	list<list<int>>::iterator i;
	list<int>::iterator j;
	list<Component *>::iterator node_it = _mindMap.begin();
	for (i = nodeChild.begin(); i != nodeChild.end(); ++i)
	{
		for (j = (*i).begin(); j != (*i).end(); ++j)
		{
			selectComponent(*j);
			Component* node = _selectedNode;
			(*node_it)->addChild(node);
			node->setParent(*node_it);
		}
		++node_it;
	}
}

bool Model::saveMindMapFile(string path) //儲存MindMap到檔案
{
	ofstream myfile;
	myfile.open(path, ofstream::out);
	myfile << fileContent().str();
	myfile.close();
	return true;
}

stringstream Model::fileContent()  //取得輸出文件格式內容
{
	stringstream content;
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		content << (**it).getId() << " \"" << (**it).getDescription() << "\"";
		list<Component *> child = (**it).getNodeList();
		for (list<Component *>::iterator j = child.begin(); j != child.end(); ++j)
		{
			content << " " << (**j).getId();
		}
		content << endl;
	}
	return content;
}

string Model::showMap() //印出MindMap
{
	_mindMap.front()->accept(new DisplayNodeVisitor());
	
	if (_mindMap.size() == 0)
		return "";
	stringstream ss;
	ss << "The mind map " << _mindMap.front()->getDescription() << " is displayed as follows:" << endl;
	ss << _mindMap.front()->getMap(1).str();
	//cout << ss.str();
	return ss.str();
}

Component* Model::selectComponent(int id) //選取節點做插入etc...
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		if (id == (*it)->getId())
		{
			_selectedNode = *it;
			break;
		}
	}

	Component* composite = _selectedNode;
	for (list<Component *>::iterator it = _mindMapDecorter.begin(); it != _mindMapDecorter.end(); ++it)
	{
		if (composite == (*it)->getComposite())
		{
			_selectedNode = *it;
		}
	}
	return _selectedNode;
}

Component* Model::getComponent()
{
	return _selectedNode;
}

void Model::editDescription(Component* component, string description)		//edit component description
{
	component->setDescription(description);
}

void Model::changeParentByNode(Component* myself, Component* newParent)		//change parent execute
{
	if (myself->isChild(newParent))	//new parent is child 
	{
		Component* location = myself->getNextChild();
		myself->getParent()->removeChild(myself);
		list<Component *> nodeList = myself->getNodeList();
		for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
		{
			(*it)->setParent(myself->getParent());
			//myself->getParent()->addChild(*it);
			myself->getParent()->insertChild(location, *it);
			myself->removeChild(*it);
		}
		myself->setParent(newParent);
		newParent->addChild(myself);
	}
	else	//new parent is parent
	{
		myself->getParent()->removeChild(myself);
		myself->setParent(newParent);
		newParent->addChild(myself);
	}
}

void Model::changeParentWithList(Component* myself, Component* oldParent, list<Component*> childNodeList)	//change parent unexecute
{
	myself->getParent()->removeChild(myself);
	myself->setParent(oldParent);
	oldParent->addChild(myself);
	for (list<Component *>::iterator it = childNodeList.begin(); it != childNodeList.end(); ++it)
	{
		(*it)->getParent()->removeChild(*it);
		myself->addChild(*it);
	}
}

void Model::deleteComponent(Component* component)	//delete node
{
	component->setSelected(false);
	list<Component *> nodelist = component->getNodeList();
	Component* parent = component->getParent();
	Component* location = component->getNextChild();
	parent->removeChild(component);
	for (list<Component *>::iterator it = nodelist.begin(); it != nodelist.end(); ++it)
	{
		//parent->addChild(*it);
		parent->insertChild(location, *it);
		component->removeChild(*it);
	}
	_mindMap.remove(component);
	//delete component;
}

void Model::addComponentWithList(Component* component, Component* parent, list<Component*> nodelist)
{
	for (list<Component *>::iterator it = nodelist.begin(); it != nodelist.end(); ++it)
	{
		parent->removeChild(*it);
		(*it)->setParent(component);
		component->addChild(*it);	//component 原先就有存nodelist 且未刪除 , 則無需再增加
	}
	parent->addChild(component);
	_mindMap.push_back(component);
}

bool Model::isNodeExist(int id)		//check Is node exist
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		if ((**it).getId() == id)
			return true;
	}
	return false;
}

bool Model::isRoot(int id)		//check Component is root
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		if ((**it).getId() == id && (**it).getType().compare("Root") == 0)
			return true;
	}
	return false;
}

void Model::insertASiblingNode(Component* node, Component* newNode)
{
	node->addSibling(newNode);
	_mindMap.push_back(newNode);
}

void Model::insertAParentNode(Component* node, Component* newNode)
{
	node->addParent(newNode);
	_mindMap.push_back(newNode);
}

void Model::insertAChildNode(Component* node, Component* newNode)
{
	node->addChild(newNode);
	_mindMap.push_back(newNode);
}

void Model::showGuiMap()
{
	if (_mindMap.size() == 0)
		return;

	double depthY;
	_mindMap.front()->showGuiMap(1, &depthY);
	//_mindMap.front()->draw();
}

void Model::clearSelect()
{
	for (list<Component *>::iterator it = _mindMap.begin(); it != _mindMap.end(); ++it)
	{
		(*it)->setSelected(false);
	}
}

list<Component *> Model::getMindMap()
{
	return _mindMap;
}

void Model::changeParentCommand(int myselfId, int newParentId)
{
	selectComponent(myselfId);
	Component *myself = getComponent();
	selectComponent(newParentId);
	Component *newParent = getComponent();
	_commandManger.execute(new ChangeParentCommand(this, myself, newParent));
}

void Model::editDescriptionCommand(int id, string description)
{
	selectComponent(id);
	_commandManger.execute(new EditComponentCommand(this, getComponent(), description));
}

void Model::deleteComponentCommand(int id)
{
	selectComponent(id);
	_commandManger.execute(new DeleteComponentCommand(this, getComponent()));
}

bool Model::undo()
{
	return _commandManger.undo();
}

bool Model::redo()
{
	return _commandManger.redo();
}

list<Component *> Model::cutNode(Component* selectedNode)
{
	_clipBoardNodeList.clear();
	_clipBoardNode = selectedNode;
	selectedNode->setSelected(false);
	selectedNode->getParent()->removeChild(selectedNode);
	selectedNode->setParent(NULL);
	selectedNode->cutNode(_mindMap, _clipBoardNodeList);
	return _clipBoardNodeList;
}

void Model::copyNode()
{
	_clipBoardNodeList.clear();
	_clipBoardNode = _selectedNode->clone(&_factory, _clipBoardNodeList);
}

void Model::pasteNode(Component* node, list<Component *> clipBoardNodeList)
{
	_clipBoardNodeList.clear();
	_clipBoardNode = NULL;
	node->addChild(clipBoardNodeList.back());	//make releation
	//node->addChild(_clipBoardNode);
	for (list<Component *>::iterator it = clipBoardNodeList.begin(); it != clipBoardNodeList.end(); ++it)
	{
		_mindMap.push_back(*it);
	}
	clipBoardNodeList.clear();
}

bool Model::canRedo()
{
	return _commandManger.canRedo();
}

bool Model::canUndo()
{
	return _commandManger.canUndo();
}

void Model::cutNodeCommand()
{
	_commandManger.execute(new CutNodeCommand(this, _selectedNode));
}

void Model::copyNodeCommand()
{
	copyNode();
}

void Model::pasteNodeCommand()
{
	_commandManger.execute(new PasteNodeCommand(this, _selectedNode, _clipBoardNodeList));
}

bool Model::canPaste()
{
	if (_clipBoardNode == NULL || _clipBoardNodeList.size() == 0)
		return false;
	else
		return true;
}

void Model::addRectangleStyle()
{
	_selectedNode = new Rectangle(_selectedNode);
	_mindMapDecorter.push_back(_selectedNode);
}

void Model::addCircleStyle()
{
	_selectedNode = new Circle(_selectedNode);
	_mindMapDecorter.push_back(_selectedNode);
}

void Model::addTriangleStyle()
{
	_selectedNode = new Triangle(_selectedNode);
	_mindMapDecorter.push_back(_selectedNode);
}

void Model::cleanStyles()
{
	_selectedNode = _selectedNode->getComposite();

	list<Component *> temp;
	for (list<Component *>::iterator it = _mindMapDecorter.begin(); it != _mindMapDecorter.end(); ++it)
	{
		Component* decortor = (*it);
		if (decortor->getComposite() == _selectedNode)
		{
			temp.push_back(decortor);
		}
	}

	for (list<Component *>::iterator it = temp.begin(); it != temp.end(); ++it)
	{
		_selectedNode->getParent()->replaceChild(*it, _selectedNode);
		_mindMapDecorter.remove(*it);
		//delete (*it);
	}
}

void Model::moveUp()
{
	_selectedNode->moveUp();
}

void Model::moveDown()
{
	_selectedNode->moveDown();
}