#include "gtest\gtest.h"
#include "..\MindMap\CommandManger.h"
#include "..\MindMap\EditComponentCommand.h"
#include "..\MindMap\DeleteComponentCommand.h"
#include "..\MindMap\ChangeParentCommand.h"
#include "..\MindMap\InsertAChildNodeCmd.h"
#include "..\MindMap\InsertAParentNodeCmd.h"
#include "..\MindMap\InsertASiblingNodeCmd.h"
#include "..\MindMap\Node.h"
#include "..\MindMap\Root.h"

class CommandMangerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new Model();
		_model->createMindMap("TestMindMap");
		_component1 = new Node("Node1", 1);
		_component2 = new Node("Node2", 2);
		_newComponent = new Node("NewNode", 3);
		_model->_mindMap.push_back(_component1);
		_model->_mindMap.push_back(_component2);
		_model->_mindMap.front()->addChild(_component1);
		_component1->addChild(_component2);
		
		_editComponentCmd = new EditComponentCommand(_model, _component1, "EditedNode");
		_deleteComponentCmd = new DeleteComponentCommand(_model, _component1);
		_changeParentCmd = new ChangeParentCommand(_model, _component1, _component2);
		_insertChildCmd = new InsertAChildNodeCmd(_model, _component2, _newComponent);
		_insertParentCmd = new InsertAParentNodeCmd(_model, _component1, _newComponent);
		_insertSiblingCmd = new InsertASiblingNodeCmd(_model, _component2, _newComponent);
		//_manger._undoCommands.push(_editComponentCmd);
		//_manger._undoCommands.push(_deleteComponentCmd);
		//_manger._undoCommands.push(_changeParentCmd);
		//_manger._redoCommands.push(_insertChildCmd);
		//_manger._redoCommands.push(_insertParentCmd);
		//_manger._redoCommands.push(_insertSiblingCmd);
	}
	virtual void TearDown()
	{
		//delete _editComponentCmd;
		//delete _deleteComponentCmd;
		//delete _changeParentCmd;
		//delete _insertChildCmd;
		//delete _insertParentCmd;
		//delete _insertSiblingCmd;
		delete _model;
	}
	Model *_model;
	Component *_component1, *_component2, *_newComponent;

	CommandManger _manger;
	Command *_editComponentCmd, *_deleteComponentCmd, *_changeParentCmd, *_insertChildCmd, *_insertParentCmd, *_insertSiblingCmd;
};

TEST_F(CommandMangerTest, execute)
{
	_manger._undoCommands.push(_editComponentCmd);
	_manger._undoCommands.push(_deleteComponentCmd);
	_manger._undoCommands.push(_changeParentCmd);
	_manger._redoCommands.push(_insertChildCmd);
	_manger._redoCommands.push(_insertParentCmd);
	_manger._redoCommands.push(_insertSiblingCmd);

	Command * editCmd = new EditComponentCommand(_model, _component2, "Edited by Test execute");
	_manger.execute(editCmd);
	ASSERT_EQ(editCmd, _manger._undoCommands.top());
	ASSERT_EQ(0, _manger._redoCommands.size());
	ASSERT_EQ(4, _manger._undoCommands.size());
}

TEST_F(CommandMangerTest, redo)
{
	//ASSERT_TRUE(_manger.redo());
	//ASSERT_EQ(2, _manger._redoCommands.size());
	//ASSERT_EQ(4, _manger._undoCommands.size());
	//ASSERT_TRUE(_manger.redo());
	//ASSERT_EQ(1, _manger._redoCommands.size());
	//ASSERT_EQ(5, _manger._undoCommands.size());
	//ASSERT_TRUE(_manger.redo());
	//ASSERT_EQ(0, _manger._redoCommands.size());
	//ASSERT_EQ(6, _manger._undoCommands.size());
	//ASSERT_FALSE(_manger.redo());
	//ASSERT_EQ(0, _manger._redoCommands.size());
	//ASSERT_EQ(6, _manger._undoCommands.size());
	_deleteComponentCmd->execute();
	_changeParentCmd->execute();
	_editComponentCmd->execute();
	_manger._redoCommands.push(_deleteComponentCmd);
	_manger._redoCommands.push(_changeParentCmd);
	_manger._redoCommands.push(_editComponentCmd);
	_manger._redoCommands.push(_insertSiblingCmd);
	_manger._redoCommands.push(_insertParentCmd);
	_manger._redoCommands.push(_insertChildCmd);

	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(5, _manger._redoCommands.size());
	ASSERT_EQ(1, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(4, _manger._redoCommands.size());
	ASSERT_EQ(2, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(3, _manger._redoCommands.size());
	ASSERT_EQ(3, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(2, _manger._redoCommands.size());
	ASSERT_EQ(4, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(1, _manger._redoCommands.size());
	ASSERT_EQ(5, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.redo());
	ASSERT_EQ(0, _manger._redoCommands.size());
	ASSERT_EQ(6, _manger._undoCommands.size());
	ASSERT_FALSE(_manger.redo());
	ASSERT_EQ(0, _manger._redoCommands.size());
	ASSERT_EQ(6, _manger._undoCommands.size());
}

TEST_F(CommandMangerTest, undo)
{
	//ASSERT_TRUE(_manger.undo());
	//ASSERT_EQ(4, _manger._redoCommands.size());
	//ASSERT_EQ(2, _manger._undoCommands.size());
	//ASSERT_TRUE(_manger.undo());
	//ASSERT_EQ(5, _manger._redoCommands.size());
	//ASSERT_EQ(1, _manger._undoCommands.size());
	//ASSERT_TRUE(_manger.undo());
	//ASSERT_EQ(6, _manger._redoCommands.size());
	//ASSERT_EQ(0, _manger._undoCommands.size());
	//ASSERT_FALSE(_manger.undo());
	//ASSERT_EQ(6, _manger._redoCommands.size());
	//ASSERT_EQ(0, _manger._undoCommands.size());
	_insertChildCmd->execute();
	_insertParentCmd->execute();
	_insertSiblingCmd->execute();
	_editComponentCmd->execute();
	_changeParentCmd->execute();
	_deleteComponentCmd->execute();
	_manger._undoCommands.push(_insertChildCmd);
	_manger._undoCommands.push(_insertParentCmd);
	_manger._undoCommands.push(_insertSiblingCmd);
	_manger._undoCommands.push(_editComponentCmd);
	_manger._undoCommands.push(_changeParentCmd);
	_manger._undoCommands.push(_deleteComponentCmd);

	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(1, _manger._redoCommands.size());
	ASSERT_EQ(5, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(2, _manger._redoCommands.size());
	ASSERT_EQ(4, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(3, _manger._redoCommands.size());
	ASSERT_EQ(3, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(4, _manger._redoCommands.size());
	ASSERT_EQ(2, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(5, _manger._redoCommands.size());
	ASSERT_EQ(1, _manger._undoCommands.size());
	ASSERT_TRUE(_manger.undo());
	ASSERT_EQ(6, _manger._redoCommands.size());
	ASSERT_EQ(0, _manger._undoCommands.size());
	ASSERT_FALSE(_manger.undo());
	ASSERT_EQ(6, _manger._redoCommands.size());
	ASSERT_EQ(0, _manger._undoCommands.size());
}