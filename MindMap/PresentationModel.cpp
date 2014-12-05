#include "PresentationModel.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "GraphicsNode.h"

PresentationModel::PresentationModel()
{
	_actionEnabled["actionNew"] = true;
	_actionEnabled["actionSave"] = false;
	_actionEnabled["actionLoad"] = true;
	_actionEnabled["actionEdit"] = false;
	_actionEnabled["actionDelete"] = false;
	_actionEnabled["actionInsert_a_Child"] = false;
	_actionEnabled["actionInsert_a_Sibling"] = false;
	_actionEnabled["actionInsert_a_Parent"] = false;
	_actionEnabled["actionCut"] = false;
	_actionEnabled["actionCopy"] = false;
	_actionEnabled["actionPaste"] = false;
	_isPaste = false;
}

PresentationModel::~PresentationModel()
{
}

string PresentationModel::showMap()
{
	return _model.showMap();
}

bool PresentationModel::setInsertMode(string mode) //設定插入節點的模式
{
	if (mode.compare("a") == 0) //父母親
	{
		_insertMode = "Parent";
	}
	else if (mode.compare("b") == 0) //小孩
	{
		_insertMode = "Child";
	}
	else if (mode.compare("c") == 0) //兄弟姊妹
	{
		_insertMode = "Sibling";
	}
	else
	{
		_insertMode = mode;
		return false;
	}
	return true;
}

void PresentationModel::insertNode(string description)
{
	if (description.compare("") == 0 || _model.getMindMap().size() == 0)
		return;
	_model.insertNode(description, _insertMode);
}

void PresentationModel::createMindMap(string description)
{
	if (description.compare("") == 0)
		return;
	_model.createMindMap(description); 
	setGuiSelectNull();
}

void PresentationModel::selectComponent(int id)
{
	if (!_model.isNodeExist(id))
		return;

	if (_model.isRoot(id)) setGuiRootEdit();
	else setGuiNodeEdit();

	_model.selectComponent(id);
}

bool PresentationModel::saveMindMapFile(string path)
{
	return _model.saveMindMapFile(path);
}

bool PresentationModel::readMindMapFile(string path)
{
	setGuiLoaded(); 
	setGuiSelectNull();
	return _model.readMindMapFile(path);
}

bool PresentationModel::undo()
{
	//return _commandManger.undo();
	return _model.undo();
}

bool PresentationModel::redo()
{
	//return _commandManger.redo();
	return _model.redo();
}

bool PresentationModel::isNodeExist(int id)
{
	return _model.isNodeExist(id);
}

bool PresentationModel::isRoot(int id)
{
	return _model.isRoot(id);
}

void PresentationModel::changeParentCommand(int myselfId, int newParentId)
{
	//selectComponent(myselfId);
	//Component *myself = _model.getComponent();
	//selectComponent(newParentId);
	//Component *newParent = _model.getComponent();
	//_commandManger.execute(new ChangeParentCommand(&_model, myself, newParent));
	_model.changeParentCommand(myselfId, newParentId);
}

void PresentationModel::editDescriptionCommand(int id, string description)
{
	//selectComponent(id);
	//_commandManger.execute(new EditComponentCommand(&_model, _model.getComponent(), description));
	_model.editDescriptionCommand(id, description); 
	setGuiSelectNull();
}

void PresentationModel::deleteComponentCommand(int id)
{
	//selectComponent(id);
	//_commandManger.execute(new DeleteComponentCommand(&_model, _model.getComponent()));
	_model.deleteComponentCommand(id);
	setGuiSelectNull();
}

void PresentationModel::showGuiMap(QGraphicsScene *scene, QMainWindow *parent)
{
	_model.showGuiMap();
	list<Component *> mindMap = _model.getMindMap();
	
	for (list<Component *>::iterator it = mindMap.begin(); it != mindMap.end(); ++it)
	{
		if ((*it)->getType() == "Root" || (*it)->getParent() != NULL)
		{
			qreal x = (*it)->getX() * (GraphicsNode::WIDTH + GraphicsNode::AFTER_SPACE);
			qreal y = (*it)->getY() * (GraphicsNode::HEIGH + GraphicsNode::AFTER_SPACE);
			QGraphicsItem *qNode = new GraphicsNode(x, y, (*it), this, parent);
			scene->addItem(qNode);
			if ((*it)->getType() != "Root")
				scene->addLine(x, y + GraphicsNode::HEIGH / 2, (*it)->getParent()->getX()* (GraphicsNode::WIDTH + GraphicsNode::AFTER_SPACE) + GraphicsNode::WIDTH, (*it)->getParent()->getY()* (GraphicsNode::HEIGH + GraphicsNode::AFTER_SPACE) + GraphicsNode::HEIGH / 2);

			//for debug use cout
			//cout << "Description:" << (*it)->getDescription() << ", X:" << (*it)->getX() << ", Y:" << (*it)->getY() << endl;
		}
	}
	//cout << _model.showMap();
}

bool PresentationModel::isActionEnabled(string actionName)
{
	return _actionEnabled[actionName];
}

void PresentationModel::clearSelect()
{
	_model.clearSelect();
	setGuiSelectNull();
}

int PresentationModel::getSelectNodeId()
{
	return _model.getComponent()->getId();
}

void PresentationModel::setGuiRootEdit()
{
	_actionEnabled["actionEdit"] = true;
	_actionEnabled["actionDelete"] = false;
	_actionEnabled["actionInsert_a_Child"] = true;
	_actionEnabled["actionInsert_a_Sibling"] = false;
	_actionEnabled["actionInsert_a_Parent"] = false;
	//cut, copy, paste
	_actionEnabled["actionCut"] = false;
	_actionEnabled["actionCopy"] = false;
	setGuiPaste();
}

void PresentationModel::setGuiNodeEdit()
{
	_actionEnabled["actionEdit"] = true;
	_actionEnabled["actionDelete"] = true;
	_actionEnabled["actionInsert_a_Child"] = true;
	_actionEnabled["actionInsert_a_Sibling"] = true;
	_actionEnabled["actionInsert_a_Parent"] = true;
	setGuiCutAndCopy();
	setGuiPaste();
}

void PresentationModel::setGuiLoaded()
{
	_actionEnabled["actionNew"] = true;
	_actionEnabled["actionSave"] = true;
	_actionEnabled["actionLoad"] = true;
}

void PresentationModel::setGuiSelectNull()
{
	//edit menu
	_actionEnabled["actionEdit"] = false;
	_actionEnabled["actionDelete"] = false;
	_actionEnabled["actionInsert_a_Child"] = false;
	_actionEnabled["actionInsert_a_Sibling"] = false;
	_actionEnabled["actionInsert_a_Parent"] = false;
	//cut, copy, paste
	_actionEnabled["actionCut"] = false;
	_actionEnabled["actionCopy"] = false;
	_actionEnabled["actionPaste"] = false;
}

void PresentationModel::setGuiCutAndCopy()
{
	_actionEnabled["actionCut"] = true;
	_actionEnabled["actionCopy"] = true;
}

void PresentationModel::setGuiPaste()
{
	_actionEnabled["actionPaste"] = _isPaste;
}

void PresentationModel::refreshUI()
{
	notify();
}

bool PresentationModel::haveCreateMindMap()
{
	if (_model.getMindMap().size() == 0)
		return false;
	return true;
}

void PresentationModel::cutNode()
{
	_model.cutNode();
	_isPaste = true;
	setGuiPaste();
}

void PresentationModel::copyNode()
{
	_model.copyNode();
	_isPaste = true;
	setGuiPaste();
}

void PresentationModel::pasteNode()
{
	_model.pasteNode();
	_isPaste = false;
	setGuiPaste();
}