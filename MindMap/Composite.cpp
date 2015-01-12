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
	/*
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
	*/
	_nodeList.push_back(node);	//加入節點
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
}

void Composite::showGuiMap(int depthX, double* depthY)
{
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		Component* composite = (*it)->getComposite();

		composite->showGuiMap(depthX + 1, depthY);
		composite->setX(depthX);
		if (composite->getNodeList().size() == 0)	//判斷有無child
		{// leaf node
			composite->setY(*depthY);
			//(*depthY) += (composite->getHeigh() + Component::AFTER_SPACE);
			(*depthY) += ((*it)->getHeigh() + Component::AFTER_SPACE);
		}
		else
		{// non leaf nodes
			double beginY = composite->getNodeList().front()->getY();
			double endY = composite->getNodeList().back()->getY();
			composite->setY((endY + beginY) / 2);
			//(*depthY) = max((*depthY), composite->getY() + composite->getHeigh() + Component::AFTER_SPACE);
			(*depthY) = max((*depthY), (*it)->getY() + (*it)->getHeigh() + Component::AFTER_SPACE);
		}
		/*
		(*it)->showGuiMap(depthX + 1, depthY);
		(*it)->setX(depthX);
		if ((*it)->getNodeList().size() == 0)	//判斷有無child
		{// leaf node
			(*it)->setY(*depthY);
			(*depthY) += ((*it)->getHeigh() + Component::AFTER_SPACE);
		}
		else
		{// non leaf nodes
			double beginY = (*it)->getNodeList().front()->getY();
			double endY = (*it)->getNodeList().back()->getY();
			(*it)->setY((endY + beginY) / 2);
			(*depthY) = max((*depthY), (*it)->getY() + (*it)->getHeigh() + Component::AFTER_SPACE);
		}
		*/
	}

	if (_type.compare("Root") == 0)
	{
		_x = depthX - 1;
		//_y = getNodeYLevel() / 2.0 - 0.5;
		if (_nodeList.size() == 0)
			_y = *depthY;
		else
		{
			double endY = getNodeList().front()->getY();
			double beginY = getNodeList().back()->getY();
			_y = (endY + beginY) / 2;
		}
	}
}

int Composite::getNodeYLevel()	//取得總共有幾個末端節點
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

void Composite::draw()
{
	cout << "Node: " << _description << "(" << _x << ", " << _y << ", " << _width << ", " << _heigh << ")" << endl;
	for (list<Component *>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		(*it)->draw();
	}
}

Component* Composite::getComposite()
{
	return this;
}

void Composite::replaceChild(Component* oldNode, Component* newNode)
{
	newNode->setParent(oldNode->getParent());
	std::replace(_nodeList.begin(), _nodeList.end(), oldNode, newNode);
}

void Composite::moveUp()
{
	Component* parent = this->getParent();
	list<Component*> childList = parent->getNodeList();
	list<Component*>::iterator it;
	for (it = childList.begin(); it != childList.end(); ++it)
	{
		if ((*it) == this && (*it) != childList.front())
		{
			--it;
			parent->removeChild(this);
			parent->insertChild((*it), this);
			break;
		}
	}
}

void Composite::moveDown()
{
	Component* parent = this->getParent();
	list<Component*> childList = parent->getNodeList();
	list<Component*>::iterator it;
	for (it = childList.begin(); it != childList.end(); ++it)
	{
		if ((*it) == this && (*it) != childList.back())
		{
			++it;
			if ((*it) == childList.back())
			{
				parent->removeChild(this);
				parent->addChild(this);
			}
			else
			{
				++it;
				parent->removeChild(this);
				parent->insertChild((*it), this);
			}
			break;
		}
	}
}

void Composite::insertChild(Component* location, Component* newNode)
{
	if (location == NULL)
	{
		_nodeList.push_back(newNode);
		return;
	}

	for (list<Component*>::iterator it = _nodeList.begin(); it != _nodeList.end(); ++it)
	{
		if ((*it) == location)
		{
			_nodeList.insert(it, newNode);
		}
	}
}

Component* Composite::getNextChild()
{
	if (!this->haveSibling())
		return NULL;

	list<Component*> childList = this->getParent()->getNodeList();
	list<Component*>::iterator it;
	for (it = childList.begin(); it != childList.end(); ++it)
	{
		if ((*it) == this)
		{
			++it;
			break;
		}
	}
	return (*it);
}