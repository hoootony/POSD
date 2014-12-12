#include "PasteNodeCommand.h"


PasteNodeCommand::PasteNodeCommand(Model* model, Component* selectedNode, list<Component*> clipBoardNodeList)
{
	_model = model;
	_selectedNode = selectedNode;
	_clipBoardNodeList = clipBoardNodeList;
}

PasteNodeCommand::~PasteNodeCommand()
{
}

void PasteNodeCommand::execute()
{
	_model->pasteNode(_selectedNode, _clipBoardNodeList);
}

void PasteNodeCommand::unexecute()
{
	_clipBoardNodeList = _model->cutNode(_clipBoardNodeList.back());
}