#include "InsertAParentNodeCmd.h"

InsertAParentNodeCmd::InsertAParentNodeCmd(Model* model, Component* selected, Component* newNode)
{
	_model = model;
	_selected = selected;
	_newNode = newNode;
}

InsertAParentNodeCmd::~InsertAParentNodeCmd()
{
}

void InsertAParentNodeCmd::execute()
{
	_model->insertAParentNode(_selected, _newNode);
}

void InsertAParentNodeCmd::unexecute()
{
	_model->deleteComponent(_newNode);
}