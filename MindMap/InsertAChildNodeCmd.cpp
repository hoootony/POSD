#include "InsertAChildNodeCmd.h"

InsertAChildNodeCmd::InsertAChildNodeCmd(Model* model, Component* selected, Component* newNode)
{
	_model = model;
	_selected = selected;
	_newNode = newNode;
}

InsertAChildNodeCmd::~InsertAChildNodeCmd()
{
}

void InsertAChildNodeCmd::execute()
{
	_model->insertAChildNode(_selected, _newNode);
}

void InsertAChildNodeCmd::unexecute()
{
	_model->deleteComponent(_newNode);
}