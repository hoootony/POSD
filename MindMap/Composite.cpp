#include "Composite.h"
#include "GraphicsNode.h"

Composite::Composite()
{
	//_nodeList.clear();
}

Composite::~Composite()
{
}

void Composite::addChild(Component *node)
{
	if (_nodeList.size() == 0) 
	{
		_nodeList.push_back(node);	//加入節點
	}
	else	//插入在ID比自己大的前面
	{
		list<Component *>::iterator it;
		for (it = _nodeList.begin(); it != _nodeList.end(); ++it)
		{
			if ((*it)->getId() > node->getId())
			{
				break;
			}
		}
		_nodeList.insert(it, node);
	}
	node->setParent(this);	//設定父母親
}

void Composite::removeChild(Component *node)
{
	_nodeList.remove(node);
	//node->setParent(NULL);
}

list<Component *> Composite::getNodeList()
{
	return _nodeList;
}

stringstream Composite::getMap(int depth)  //印出MindMap
{
	stringstream ss;
	string blank(depth * 2, ' ');  //計算深度的空白數量
	int indexDepth = 0;
	ss << "＋－" << _description << "(" << _type << "," << "ID:" << _id << ")" << endl;  //印出節點內容
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		for (indexDepth = 0; indexDepth < depth; indexDepth++)	//print 前置空白
		{
			Component* parent = (*it);
			for (int i = 0; i < depth - indexDepth; i++)
			{
				parent = parent->getParent();
			}
			if (indexDepth >= 1 && parent->haveSibling()) // not root && have sibling
				ss << "｜　";
			else
				ss << "　　";  //two sapce
		}
		ss << (**it).getMap(depth+1).str();
	}
	return ss;
}

bool Composite::isChild(Component *node)	//check have node child
{
	if (_id == node->getId())
		return true;

	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		if ((**it).isChild(node)) return true;
	}
	return false;
}

bool Composite::haveSibling()	//find node next have node
{
	Component* node = this;
	if (node->getParent() == NULL)
		return false;
	
	Component* parent = node->getParent();
	list<Component *> nodeList = parent->getNodeList();
	bool haveSibling = false;
	for (list<Component *>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		if (node->getId() == (*it)->getId())	//find node itself
		{
			if (++it == nodeList.end())		//node next sibling havn't node
				haveSibling = false;
			else							//node next sibling have node
				haveSibling = true;
			break;
		}
	}
	return haveSibling;
	//return false; //error
}

void Composite::showGuiMap(int depthX, vector<int>* heighDepthX)
{
	if (_type.compare("Root") == 0)
	{
		_x = depthX - 1;
		_y = getNodeYLevel() / 2.0 - 0.5;
	}

	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		(*it)->showGuiMap(depthX + 1, heighDepthX);
		(*it)->setX(depthX);
		if ((*it)->getNodeList().size() == 0)	//leaf node
			(*it)->setY((*heighDepthX)[0]++);
		else
		{
			double endY = (*it)->getNodeList().front()->getY();
			double beginY = (*it)->getNodeList().back()->getY();
			(*it)->setY((endY + beginY) / 2);
		}
	}
}

int Composite::getX()
{
	return _x;
}

double Composite::getY()
{
	return _y;
}

void Composite::setX(int x)
{
	_x = x;
}

void Composite::setY(double y)
{
	_y = y;
}

int Composite::getNodeYLevel()
{
	if (_nodeList.size() == 0)
		return 1;

	int sum = 0;
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		sum += (*it)->getNodeYLevel();
	}
	return sum;
}

Component* Composite::clone(ComponentFactory* factory, list<Component *>& clipBoardList)
{
	Component* newRoot = factory->create(_type, _description);	
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		Component* node = (*it)->clone(factory, clipBoardList);
		newRoot->addChild(node);
		//node->setParent(newRoot);
	}
	clipBoardList.push_back(newRoot);
	return newRoot;
}

void Composite::cutNode(list<Component *>& mindmap, list<Component *>& clipBoardList)
{
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		(*it)->cutNode(mindmap, clipBoardList);
	}
	clipBoardList.push_back(this);
	mindmap.remove(this);
}