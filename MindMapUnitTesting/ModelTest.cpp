#include "gtest/gtest.h"
#include "../MindMap/Model.h"
#include "..\MindMap\EditComponentCommand.h"
#include "..\MindMap\DeleteComponentCommand.h"
#include "..\MindMap\ChangeParentCommand.h"
#include "..\MindMap\InsertAChildNodeCmd.h"
#include "..\MindMap\InsertAParentNodeCmd.h"
#include "..\MindMap\InsertASiblingNodeCmd.h"

class ModelTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new Model();
		_model->createMindMap("TestMindMap");
		_selectedNode1 = _model->_factory.create(1, "Node", "Node1");
		_selectedNode2 = _model->_factory.create(2, "Node", "Node2");
		_selectedNode3 = _model->_factory.create(3, "Node", "Node3");
		_model->_mindMap.push_back(_selectedNode1);
		_model->_mindMap.push_back(_selectedNode2);
		_model->_mindMap.push_back(_selectedNode3);
		_model->_mindMap.front()->addChild(_selectedNode1);
		_selectedNode1->addChild(_selectedNode2);
		_selectedNode1->addSibling(_selectedNode3);
	}

	virtual void TearDown()
	{
		delete _model;
	}

	Model *_model;
	Component *_selectedNode1, *_selectedNode2, *_selectedNode3;
};

TEST_F(ModelTest, showMap)
{
	stringstream ss;
	ss << "The mind map TestMindMap is displayed as follows:" << endl;
	ss << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	ss << "¡@¡@¡U¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());
}

TEST_F(ModelTest, createMindMap)
{
	_model->createMindMap("NewMindMap");
	ASSERT_EQ("NewMindMap", _model->_mindMap.front()->getDescription());
	ASSERT_EQ("Root", _model->_mindMap.front()->getType());
	ASSERT_EQ(0, _model->_mindMap.front()->getId());
}

TEST_F(ModelTest, selectComponent)
{
	_model->selectComponent(-1);
	ASSERT_EQ(NULL, _model->_selectedNode);

	_model->selectComponent(4);
	ASSERT_EQ(NULL, _model->_selectedNode);

	_model->selectComponent(0);	//root
	ASSERT_EQ("Root", _model->_selectedNode->getType());
	ASSERT_EQ("TestMindMap", _model->_selectedNode->getDescription());
	ASSERT_EQ(0, _model->_selectedNode->getId());

	_model->selectComponent(3);	//node
	ASSERT_EQ("Node", _model->_selectedNode->getType());
	ASSERT_EQ("Node3", _model->_selectedNode->getDescription());
	ASSERT_EQ(3, _model->_selectedNode->getId());
}

//TEST_F(ModelTest, setInsertMode)
//{
//	_model->_selectedNode = _model->_mindMap.front();	//root
//	ASSERT_EQ("Root", _model->_selectedNode->getType());
//	ASSERT_FALSE(_model->setInsertMode("a"));
//	ASSERT_EQ("", _model->_insertMode);
//	ASSERT_FALSE(_model->setInsertMode("c"));
//	ASSERT_EQ("", _model->_insertMode);
//	ASSERT_TRUE(_model->setInsertMode("b"));
//	ASSERT_EQ("Child", _model->_insertMode);
//	ASSERT_FALSE(_model->setInsertMode("CHild"));
//	ASSERT_EQ("Child", _model->_insertMode);
//	_model->_insertMode = "";
//
//	_model->_selectedNode = _selectedNode1;
//	ASSERT_TRUE(_model->setInsertMode("b"));
//	ASSERT_EQ("Child", _model->_insertMode);
//	ASSERT_TRUE(_model->setInsertMode("a"));
//	ASSERT_EQ("Parent", _model->_insertMode);
//	ASSERT_TRUE(_model->setInsertMode("c"));
//	ASSERT_EQ("Sibling", _model->_insertMode);
//	ASSERT_FALSE(_model->setInsertMode("tenraP"));
//	ASSERT_EQ("Sibling", _model->_insertMode);
//	ASSERT_FALSE(_model->setInsertMode("123@SetMode!"));
//	ASSERT_EQ("Sibling", _model->_insertMode);
//}

TEST_F(ModelTest, insertNodeCommand)
{
	_model->insertNode("NotSussess", "");

	_model->_selectedNode = _selectedNode1;
	_model->insertNode("NewChildByTest", "Child");
	ASSERT_EQ(4, _selectedNode1->getNodeList().back()->getId());
	ASSERT_EQ("Node", _selectedNode1->getNodeList().back()->getType());
	ASSERT_EQ("NewChildByTest", _selectedNode1->getNodeList().back()->getDescription());
	ASSERT_EQ(_selectedNode1, _selectedNode1->getNodeList().back()->getParent());

	_model->_selectedNode = _selectedNode1;
	_model->insertNode("NewSiblingByTest", "Sibling");
	ASSERT_EQ(5, _selectedNode1->getParent()->getNodeList().back()->getId());
	ASSERT_EQ("Node", _selectedNode1->getParent()->getNodeList().back()->getType());
	ASSERT_EQ("NewSiblingByTest", _selectedNode1->getParent()->getNodeList().back()->getDescription());
	ASSERT_EQ(_selectedNode1->getParent(), _selectedNode1->getParent()->getNodeList().back()->getParent());

	_model->_selectedNode = _selectedNode2;
	_model->insertNode("NewParentByTest", "Parent");
	ASSERT_EQ(6, _selectedNode2->getParent()->getId());
	ASSERT_EQ("Node", _selectedNode2->getParent()->getType());
	ASSERT_EQ("NewParentByTest", _selectedNode2->getParent()->getDescription());
}

TEST_F(ModelTest, fileContent)
{
	stringstream ss;
	ss << "0 \"TestMindMap\" 1 3" << endl;
	ss << "1 \"Node1\" 2" << endl;
	ss << "2 \"Node2\"" << endl;
	ss << "3 \"Node3\"" << endl;
	ASSERT_EQ(ss.str(), _model->fileContent().str());
}

TEST_F(ModelTest, saveMindMapFile)
{
	ASSERT_TRUE(_model->saveMindMapFile("TestFile.mm"));
	fstream fs("TestFile.mm", ios::out);
	ASSERT_TRUE(fs.is_open());
	fs.close();
}

TEST_F(ModelTest, readMindMapFile)
{
	ASSERT_FALSE(_model->readMindMapFile("TestFile_not_exist.mm"));

	ofstream myfile;
	myfile.open("TestFile.mm", ios_base::app);
	stringstream ss;
	ss << "0 \"TestMindMap\" 1 3" << endl;
	ss << "1 \"Node1\" 2" << endl;
	ss << "2 \"Node2\"" << endl;
	ss << "3 \"Node3\"" << endl;
	myfile << ss.str();
	myfile.close();

	ASSERT_TRUE(_model->readMindMapFile("TestFile.mm"));
	
	stringstream s; 
	s << "The mind map TestMindMap is displayed as follows:" << endl;
	s << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	s << "¡@¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	s << "¡@¡@¡U¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	s << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(s.str(), _model->showMap());
}

TEST_F(ModelTest, editDescriptionCommand)
{
	_model->editDescriptionCommand(0, "TestEditRoot");
	_model->selectComponent(0);
	ASSERT_EQ("TestEditRoot", _model->getComponent()->getDescription());
}

TEST_F(ModelTest, changeParentCommand)
{
	_model->changeParentCommand(1, 2);
	stringstream ss;
	ss << "The mind map TestMindMap is displayed as follows:" << endl;
	ss << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	ss << "¡@¡@¡U¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());
}

TEST_F(ModelTest, deleteComponentCommand)
{
	_model->deleteComponentCommand(1);
	stringstream ss;
	ss << "The mind map TestMindMap is displayed as follows:" << endl;
	ss << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());
}

TEST_F(ModelTest, isNodeExist)
{
	ASSERT_FALSE(_model->isNodeExist(-1));
	ASSERT_FALSE(_model->isNodeExist(4));
	ASSERT_TRUE(_model->isNodeExist(3));
	ASSERT_TRUE(_model->isNodeExist(0));
}

TEST_F(ModelTest, isRoot)
{
	ASSERT_FALSE(_model->isRoot(-1));
	ASSERT_FALSE(_model->isRoot(4));
	ASSERT_FALSE(_model->isRoot(3));
	ASSERT_TRUE(_model->isRoot(0));
}

TEST_F(ModelTest, redo)
{
	ASSERT_FALSE(_model->redo());

	_model->changeParentCommand(1, 2);
	_model->deleteComponentCommand(1);
	_model->selectComponent(0);
	Component *parent = _model->getComponent();
	_model->selectComponent(2);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
	ASSERT_TRUE(_model->undo());
	_model->selectComponent(0);
	parent = _model->getComponent();
	_model->selectComponent(2);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
	ASSERT_TRUE(_model->undo());
	ASSERT_FALSE(_model->undo());
	ASSERT_TRUE(_model->redo());
	ASSERT_TRUE(_model->redo());
	ASSERT_FALSE(_model->redo());
}

TEST_F(ModelTest, undo)
{
	ASSERT_FALSE(_model->undo());

	_model->changeParentCommand(1, 3);
	_model->editDescriptionCommand(0, "YOYO");
	ASSERT_TRUE(_model->undo());
	ASSERT_TRUE(_model->undo());
	ASSERT_FALSE(_model->undo());
}

TEST_F(ModelTest, cutAndPasteNode)
{
	_model->selectComponent(1);
	_model->cutNodeCommand();
	stringstream s;
	s << "The mind map TestMindMap is displayed as follows:" << endl;
	s << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	s << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(s.str(), _model->showMap());

	_model->selectComponent(3);
	_model->pasteNodeCommand();
	s.str("");
	s << "The mind map TestMindMap is displayed as follows:" << endl;
	s << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	s << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	s << "¡@¡@¡@¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	s << "¡@¡@¡@¡@¡@¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	ASSERT_EQ(s.str(), _model->showMap());
}

TEST_F(ModelTest, copyAndPasteNode)
{
	_model->selectComponent(1);
	_model->copyNodeCommand();
	stringstream s;
	s << "The mind map TestMindMap is displayed as follows:" << endl;
	s << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	s << "¡@¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	s << "¡@¡@¡U¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	s << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(s.str(), _model->showMap());


	_model->selectComponent(3);
	_model->pasteNodeCommand();
	s.str("");
	s << "The mind map TestMindMap is displayed as follows:" << endl;
	s << "¡Ï¡ÐTestMindMap(Root,ID:0)" << endl;
	s << "¡@¡@¡Ï¡ÐNode1(Node,ID:1)" << endl;
	s << "¡@¡@¡U¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	s << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	s << "¡@¡@¡@¡@¡Ï¡ÐNode1(Node,ID:4)" << endl;
	s << "¡@¡@¡@¡@¡@¡@¡Ï¡ÐNode2(Node,ID:5)" << endl;
	ASSERT_EQ(s.str(), _model->showMap());
}