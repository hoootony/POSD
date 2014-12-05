#include "Model.h"
#include "Node.h"
#include "Root.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertAChildNodeCmd.h"
#include "InsertAParentNodeCmd.h"
#include "InsertASiblingNodeCmd.h"

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
		_mindMap.push_back(newNode);
	}
	else if (mode.compare("Parent") == 0)
	{
		Component *newNode = _factory.create("Node", description);
		_commandManger.execute(new InsertAParentNodeCmd(this, _selectedNode, newNode));
		_mindMap.push_back(newNode);
	}
	else if (mode.compare("Sibling") == 0)
	{
		Component *newNode = _factory.create("Node", description);
		_commandManger.execute(new InsertASiblingNodeCmd(this, _selectedNode, newNode));
		_mindMap.push_back(newNode);
	}
}

bool Model::readMindMapFile(string path)		//讀檔
{
	if (!ifstream(path))
		return false;

	char line[100];		//檔案每行的文字
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
		myself->getParent()->removeChild(myself);
		list<Component *> nodeList = myself->getNodeList();
		for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
		{
			(*it)->setParent(myself->getParent());
			myself->getParent()->addChild(*it);
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
	list<Component *> nodelist = component->getNodeList();
	Component* parent = component->getParent();
	parent->removeChild(component);
	for (list<Component *>::iterator it = nodelist.begin(); it != nodelist.end(); ++it)
	{
		parent->addChild(*it);
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
		//component->addChild(*it);	//component 原先就有存nodelist 且未刪除 , 則無需再增加
	}
	parent->addChild(component);
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
}

void Model::insertAParentNode(Component* node, Component* newNode)
{
	node->addParent(newNode);
}

void Model::insertAChildNode(Component* node, Component* newNode)
{
	node->addChild(newNode);
}

void Model::showGuiMap()
{
	if (_mindMap.size() == 0)
		return;

	vector<int> heighDepthX(_mindMap.size(), 0);
	_mindMap.front()->showGuiMap(1, &heighDepthX);
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

void Model::cutNode()
{
	_clipBoardNodeList.clear();
	_clipBoardNode = _selectedNode;
	_selectedNode->setSelected(false);
	_selectedNode->getParent()->removeChild(_selectedNode);
	_selectedNode->setParent(NULL);
	_selectedNode->cutNode(_mindMap, _clipBoardNodeList);
}

void Model::copyNode()
{
	_clipBoardNodeList.clear();
	_clipBoardNode = _selectedNode->clone(&_factory, _clipBoardNodeList);
}

void Model::pasteNode()
{
	_selectedNode->addChild(_clipBoardNode);	//make releation
	for (list<Component *>::iterator it = _clipBoardNodeList.begin(); it != _clipBoardNodeList.end(); ++it)
	{
		_mindMap.push_back(*it);
	}
	_clipBoardNodeList.clear();
	_clipBoardNode = NULL;
}