#include "gtest/gtest.h"
#include "../MindMap/Component.h"
#include "../MindMap/Node.h"

class ComponentTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_component = new Node();
		_component->_id = 0;
		_component->_description = "Home";
	}

	virtual void TearDown()
	{
		delete _component;
	}

	Component* _component;
};

TEST_F(ComponentTest, component)
{
	ASSERT_EQ(0, _component->getId());
	ASSERT_EQ("Home", _component->getDescription());
	ASSERT_EQ("Node", _component->getType());

	_component->setDescription("House@123.456");
	ASSERT_EQ("House@123.456", _component->getDescription());
}