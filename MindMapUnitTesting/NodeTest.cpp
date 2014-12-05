#include "gtest\gtest.h"
#include "../MindMap/Node.h"

class NodeTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_node = new Node("Home", 1);
		_node1 = new Node("Monther", 2);
		_node2 = new Node("Father", 3);
		_node3 = new Node("Son", 4);
		_node4 = new Node("GrandSon", 5);

		_node->_nodeList.push_back(_node1);
		_node1->_parent = _node;

		_node->_nodeList.push_back(_node2);
		_node2->_parent = _node;

		_node1->_nodeList.push_back(_node3);
		_node3->_parent = _node1;

		_node3->_nodeList.push_back(_node4);
		_node4->_parent = _node3;
	}

	virtual void TearDown()
	{
		delete _node;
		delete _node1;
		delete _node2;
		delete _node3;
		delete _node4;
	}
	Node *_node, *_node1, *_node2, *_node3, *_node4;
};

TEST_F(NodeTest, newNode)
{
	ASSERT_EQ(2, _node1->getId());
	ASSERT_EQ("Monther", _node1->getDescription());
	ASSERT_EQ("Node", _node1->getType());
}

TEST_F(NodeTest, addParent)
{
	Node *newNode = new Node("GrandMonther", 6);
	_node1->addParent(newNode);
	ASSERT_EQ(newNode, _node1->getParent());
	ASSERT_EQ(_node, newNode->getParent());
	ASSERT_EQ(_node1, _node3->getParent());
	delete newNode;
}

TEST_F(NodeTest, addSibling)
{
	Node *newNode = new Node("Daughter", 6);
	_node3->addSibling(newNode);
	ASSERT_EQ(newNode->getParent(), _node3->getParent());
	delete newNode;
}

TEST_F(NodeTest, setParetn)
{

}