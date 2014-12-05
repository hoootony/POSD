#include "gtest/gtest.h"
#include "../MindMap/Root.h"
#include "../MindMap/Node.h"

class RootTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_root = new Root("Family", 0);
	}
	virtual void TearDown()
	{
		delete _root;
	}
	Root *_root;
};

TEST_F(RootTest, newRoot)
{
	ASSERT_EQ(0, _root->getId()); 
	ASSERT_EQ("Family", _root->getDescription());
	ASSERT_EQ("Root", _root->getType());
}

TEST_F(RootTest, addParent)
{
	_root->addParent(new Root("Home", 1));
	ASSERT_EQ(NULL, _root->getParent());
}

TEST_F(RootTest, addSibling)
{
	_root->addSibling(new Root("Sibling", 99));
	ASSERT_EQ(NULL, _root->getParent());
}

TEST_F(RootTest, setParent)
{
	_root->setParent(new Root("House", 10));
	ASSERT_EQ(NULL, _root->getParent());

}