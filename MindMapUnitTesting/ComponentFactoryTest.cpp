#include "gtest\gtest.h"
#include "..\MindMap\ComponentFactory.h"
#include "..\MindMap\Component.h"

class ComponentFactoryTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		
	}
	ComponentFactory _factory;
};

TEST_F(ComponentFactoryTest, addRoot)
{
	Component* root = _factory.create("ToorF", "FamilyA");
	ASSERT_EQ(NULL, root);
	root = _factory.create(99, "Toor", "FamilyB");
	ASSERT_EQ(NULL, root);

	root = _factory.create("Root", "Family0");
	ASSERT_EQ(0, root->getId());
	ASSERT_EQ("Family0", root->getDescription());
	ASSERT_EQ("Root", root->getType());

	root = _factory.create("Root", "Family1");
	ASSERT_EQ(1, root->getId());
	ASSERT_EQ("Family1", root->getDescription());
	ASSERT_EQ("Root", root->getType());

	root = _factory.create(10, "Root", "Home10");
	ASSERT_EQ(10, root->getId());
	ASSERT_EQ("Home10", root->getDescription());
	ASSERT_EQ("Root", root->getType());
	delete root;
}


TEST_F(ComponentFactoryTest, addNode)
{
	Component* node = _factory.create("EdonF", "FamilyA");
	ASSERT_EQ(NULL, node);
	node = _factory.create(99, "Edon", "FamilyB");
	ASSERT_EQ(NULL, node);

	node = _factory.create("Node", "Family0");
	ASSERT_EQ(0, node->getId());
	ASSERT_EQ("Family0", node->getDescription());
	ASSERT_EQ("Node", node->getType());

	node = _factory.create("Node", "Family1");
	ASSERT_EQ(1, node->getId());
	ASSERT_EQ("Family1", node->getDescription());
	ASSERT_EQ("Node", node->getType());

	node = _factory.create(10, "Node", "Home10");
	ASSERT_EQ(10, node->getId());
	ASSERT_EQ("Home10", node->getDescription());
	ASSERT_EQ("Node", node->getType());
	delete node;
}