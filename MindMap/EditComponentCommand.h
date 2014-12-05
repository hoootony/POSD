#pragma once
#include "Command.h"
#include "Model.h"
#include "Component.h"
#include <string>

using namespace std;

class EditComponentCommand : public Command
{
private:
	Model* _model;
	Component* _component;
	string _prevDescription;
	string _newDescription;
public:
	EditComponentCommand(Model* model, Component* component, string description);
	~EditComponentCommand();
	void execute();
	void unexecute();
};

