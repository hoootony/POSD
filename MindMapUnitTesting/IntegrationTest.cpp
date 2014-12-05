#include "gtest\gtest.h"
#include "..\MindMap\Model.h" 
#include <direct.h>

class IntegrationTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new Model();
		//_mkdir("testdata");
		system("mkdir testdata");
		stringstream ss;
		ss << "0 \"Computer\" 2 7" << endl;
		ss << "1 \"windows\" 5 6" << endl;
		ss << "2 \"OS\" 1 3 4" << endl;
		ss << "3 \"IOS\"" << endl;
		ss << "4 \"Linux\"" << endl;
		ss << "5 \"DirectX\"" << endl;
		ss << "6 \"Microsoft Office\"" << endl;
		ss << "7 \"Network\" 8 9" << endl;
		ss << "8 \"Wireless\"" << endl;
		ss << "9 \"Cable\"" << endl;
		
		ofstream myfile;
		//myfile.open("testdata\\test_file1.mm", ofstream::out | ofstream::trunc);
		myfile.open("testdata\\test_file1.mm", ofstream::out);
		myfile << ss.str();
		myfile.close();
	}
	virtual void TearDown()
	{
		//_rmdir("testdata");
		system("rmdir /s /q testdata");
	}
	Model * _model;
};

TEST_F(IntegrationTest, testLoadFileNotExist)
{
	ASSERT_FALSE(_model->readMindMapFile("testdata\\file_not_exist.mm"));
}

TEST_F(IntegrationTest, testUndoDeleteNode)
{
	ASSERT_TRUE(_model->readMindMapFile("testdata\\test_file1.mm"));
	stringstream ss;
	ss << "The mind map Computer is displayed as follows:" << endl;
	ss << "�ϡ�Computer(Root,ID:0)" << endl;
	ss << "�@�@�ϡ�OS(Node,ID:2)" << endl;
	ss << "�@�@�U�@�ϡ�windows(Node,ID:1)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�DirectX(Node,ID:5)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�Microsoft Office(Node,ID:6)" << endl;
	ss << "�@�@�U�@�ϡ�IOS(Node,ID:3)" << endl;
	ss << "�@�@�U�@�ϡ�Linux(Node,ID:4)" << endl;
	ss << "�@�@�ϡ�Network(Node,ID:7)" << endl;
	ss << "�@�@�@�@�ϡ�Wireless(Node,ID:8)" << endl;
	ss << "�@�@�@�@�ϡ�Cable(Node,ID:9)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());

	_model->selectComponent(4);
	_model->insertNode("Test", "Child");
	Component *parent = _model->getComponent();
	_model->selectComponent(10);
	ASSERT_EQ(parent, _model->getComponent()->getParent());

	_model->selectComponent(10);
	parent = _model->getComponent()->getParent();
	_model->deleteComponentCommand(10);
	ASSERT_FALSE(parent->isChild(_model->getComponent()));

	_model->undo();
	_model->selectComponent(10);
	ASSERT_EQ("Test", _model->getComponent()->getDescription());
}

TEST_F(IntegrationTest, testRedoDeleteNode)
{
	ASSERT_TRUE(_model->readMindMapFile("testdata\\test_file1.mm"));
	stringstream ss;
	ss << "The mind map Computer is displayed as follows:" << endl;
	ss << "�ϡ�Computer(Root,ID:0)" << endl;
	ss << "�@�@�ϡ�OS(Node,ID:2)" << endl;
	ss << "�@�@�U�@�ϡ�windows(Node,ID:1)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�DirectX(Node,ID:5)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�Microsoft Office(Node,ID:6)" << endl;
	ss << "�@�@�U�@�ϡ�IOS(Node,ID:3)" << endl;
	ss << "�@�@�U�@�ϡ�Linux(Node,ID:4)" << endl;
	ss << "�@�@�ϡ�Network(Node,ID:7)" << endl;
	ss << "�@�@�@�@�ϡ�Wireless(Node,ID:8)" << endl;
	ss << "�@�@�@�@�ϡ�Cable(Node,ID:9)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());

	_model->selectComponent(9);
	_model->insertNode("Test", "Child");
	Component *parent = _model->getComponent();
	_model->selectComponent(10);
	ASSERT_EQ(parent, _model->getComponent()->getParent());

	_model->selectComponent(10);
	parent = _model->getComponent()->getParent();
	_model->deleteComponentCommand(10);
	ASSERT_FALSE(parent->isChild(_model->getComponent()));

	_model->undo();
	_model->selectComponent(10);
	ASSERT_EQ("Test", _model->getComponent()->getDescription());
	ASSERT_TRUE(_model->getComponent()->getParent()->isChild(_model->getComponent()));

	_model->redo();
	_model->selectComponent(10);
	ASSERT_FALSE(_model->getComponent()->getParent()->isChild(_model->getComponent()));
}

TEST_F(IntegrationTest, testChangeNodeParent)
{
	ASSERT_TRUE(_model->readMindMapFile("testdata\\test_file1.mm"));
	stringstream ss;
	ss << "The mind map Computer is displayed as follows:" << endl;
	ss << "�ϡ�Computer(Root,ID:0)" << endl;
	ss << "�@�@�ϡ�OS(Node,ID:2)" << endl;
	ss << "�@�@�U�@�ϡ�windows(Node,ID:1)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�DirectX(Node,ID:5)" << endl;
	ss << "�@�@�U�@�U�@�ϡ�Microsoft Office(Node,ID:6)" << endl;
	ss << "�@�@�U�@�ϡ�IOS(Node,ID:3)" << endl;
	ss << "�@�@�U�@�ϡ�Linux(Node,ID:4)" << endl;
	ss << "�@�@�ϡ�Network(Node,ID:7)" << endl;
	ss << "�@�@�@�@�ϡ�Wireless(Node,ID:8)" << endl;
	ss << "�@�@�@�@�ϡ�Cable(Node,ID:9)" << endl;
	ASSERT_EQ(ss.str(), _model->showMap());

	_model->changeParentCommand(1, 6);
	_model->selectComponent(6);
	Component *parent = _model->getComponent();
	_model->selectComponent(1);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
	_model->selectComponent(2);
	parent = _model->getComponent();
	_model->selectComponent(6);
	ASSERT_EQ(parent, _model->getComponent()->getParent());

	_model->undo();
	_model->selectComponent(2);
	parent = _model->getComponent();
	_model->selectComponent(1);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
	_model->selectComponent(1);
	parent = _model->getComponent();
	_model->selectComponent(6);
	ASSERT_EQ(parent, _model->getComponent()->getParent());

	_model->redo();
	_model->selectComponent(6);
	parent = _model->getComponent();
	_model->selectComponent(1);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
	_model->selectComponent(2);
	parent = _model->getComponent();
	_model->selectComponent(6);
	ASSERT_EQ(parent, _model->getComponent()->getParent());
}