#include "InsertASiblingNodeCmd.h"

InsertASiblingNodeCmd::InsertASiblingNodeCmd(Model* model, Component* selected, Component* newNode)
{
	_model = model;
	_selected = selected;
	_newNode = newNode;
}

InsertASiblingNodeCmd::~InsertASiblingNodeCmd()
{
}

void InsertASiblingNodeCmd::execute()
{
	_model->insertASiblingNode(_selected, _newNode);
}

void InsertASiblingNodeCmd::unexecute()
{
	_model->deleteComponent(_newNode);
}