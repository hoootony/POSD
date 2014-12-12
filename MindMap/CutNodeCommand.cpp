#include "CutNodeCommand.h"


CutNodeCommand::CutNodeCommand(Model* model, Component* selectedNode)
{
	_model = model;
	_selectedNode = selectedNode;
	_parent = selectedNode->getParent();
}

CutNodeCommand::~CutNodeCommand()
{
	for (list<Component*>::iterator it = _clipBoardNodeList.begin(); it != _clipBoardNodeList.end(); ++it)
	{
		//delete (*it);
	}
}

void CutNodeCommand::execute()
{
	_clipBoardNodeList = _model->cutNode(_selectedNode);
}

void CutNodeCommand::unexecute()
{
	_model->pasteNode(_parent, _clipBoardNodeList);
}