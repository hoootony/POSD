#include "gtest\gtest.h"
#include "../MindMap/Composite.h"
#include "../MindMap/Node.h"

class CompositeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_composite1 = new Node("Node1", 1);
		_composite2 = new Node("Node2", 2);
		_composite3 = new Node("Node3", 3);
		_composite4 = new Node("Node4", 4);

		_composite1->_nodeList.push_back(_composite2);
		_composite2->setParent(_composite1);

		_composite1->_nodeList.push_back(_composite3);
		_composite3->setParent(_composite1);

		_composite2->_nodeList.push_back(_composite4);
		_composite4->setParent(_composite2);
	}
	virtual void TearDown()
	{
		delete _composite1;
		delete _composite2;
		delete _composite3;
		delete _composite4;
	}
	Composite *_composite1, *_composite2, *_composite3, *_composite4;
};

TEST_F(CompositeTest, addChild)
{
	Composite *newNode = new Node("newNode", 5);
	_composite2->addChild(newNode);
	ASSERT_EQ(_composite2, newNode->getParent());
	ASSERT_TRUE(_composite2->isChild(newNode));
}

TEST_F(CompositeTest, removeChild)
{
	_composite1->removeChild(_composite3);
	ASSERT_FALSE(_composite1->isChild(_composite3));
}

TEST_F(CompositeTest, isChild)
{
	ASSERT_TRUE(_composite1->isChild(_composite2));
	ASSERT_TRUE(_composite1->isChild(_composite3));
	ASSERT_FALSE(_composite2->isChild(_composite1));
	ASSERT_FALSE(_composite3->isChild(_composite2));
	//ASSERT_FALSE(_composite3->isChild(_composite3));
}

TEST_F(CompositeTest, haveSibling)
{
	ASSERT_FALSE(_composite1->haveSibling());
	ASSERT_TRUE(_composite2->haveSibling());
	ASSERT_FALSE(_composite3->haveSibling());
}

TEST_F(CompositeTest, getMap)
{
	stringstream ss;
	ss << "¡Ï¡ÐNode1(Node,ID:1)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode2(Node,ID:2)" << endl;
	ss << "¡@¡@¡U¡@¡Ï¡ÐNode4(Node,ID:4)" << endl;
	ss << "¡@¡@¡Ï¡ÐNode3(Node,ID:3)" << endl;
	ASSERT_EQ(ss.str(), _composite1->getMap(1).str());
}