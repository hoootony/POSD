#include "ComponentFactory.h"
#include "Node.h"
#include "Root.h"


ComponentFactory::ComponentFactory()
{
	_count = 0;
}

ComponentFactory::~ComponentFactory()
{
}

Component* ComponentFactory::create(string type, string description)
{
	return create(_count, type, description);
}

Component* ComponentFactory::create(int id, string type, string description)
{
	if (type.compare("Root") == 0)
	{
		_count = id + 1;
		return new Root(description, id);
	}
	else if (type.compare("Node") == 0)
	{
		_count = id + 1;
		return new Node(description, id);
	}
	return NULL;
}