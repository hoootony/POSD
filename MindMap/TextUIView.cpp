#include "TextUIView.h"
#include <QtWidgets/QApplication>

TextUIView::TextUIView()
{
}

TextUIView::TextUIView(PresentationModel *pModel)
{
	_pModel = pModel;
}

TextUIView::~TextUIView()
{
}

void TextUIView::printMenu() //印出選單
{
	cout << "Please enter your choice:" << endl;
	cout << "1. Create a new mind map" << endl;
	cout << "2. Insert a new node" << endl;
	cout << "3. Edit a node" << endl;
	cout << "4. Display mind map" << endl;
	cout << "5. Save mind map" << endl;
	cout << "6. Load a mind map" << endl;
	cout << "7. Redo" << endl;
	cout << "8. Undo" << endl;
	cout << "9. Exit" << endl;
	cout << ">";
}

void TextUIView::printInsertMenu() //印出插入選單
{
	cout << "a. Insert a parent node " << endl;
	cout << "b. Insert a child node" << endl;
	cout << "c. Insert a sibling node" << endl;
	cout << ">";
} 

void TextUIView::printEditMenu() //印出編輯節點選單
{
	cout << endl;
	cout << "a. Edit the description of a node" << endl;
	cout << "b. Change the parent of a node" << endl;
	cout << "c. Delete a node" << endl;
	cout << ">";
}

void TextUIView::run() //執行選單主程式
{
	while (1)
	{
		char choice;
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case '1':
			createMindMap();
			break;
		case '2':
			insertNode();
			break;
		case '3':
			editNode();
			break;
		case '4':
			cout << _pModel->showMap();
			break;
		case '5':
			saveMindMap();
			break;
		case '6':
			loadMindMapFile();
			break;
		case '7':
			redo();
			break;
		case '8':
			undo();
			break;
		case '9':
			exit(0);
			return;
			break;
		case '0':
			break;
		default:
			break;
		}
	}
}

void TextUIView::createMindMap() //建立新的MindMap
{
	string inputString;
	cout << "Please enter the topic:" << endl << ">";
	cin >> inputString;
	_pModel->createMindMap(inputString);
	cout << _pModel->showMap();
}

void TextUIView::insertNode() //插入新的節點
{
	if (!_pModel->haveCreateMindMap())
	{
		cout << "Need to create the MindMap first." << endl << endl;
		return;
	}

	int inputInt;
	string inputString;
	cout << _pModel->showMap();
	cout << "Enter the node ID" << endl << ">";
	cin >> inputInt;
	_pModel->selectComponent(inputInt);
	printInsertMenu();
	cin >> inputString;
	if (_pModel->setInsertMode(inputString))
	{
		cout << "Enter the node name:" << endl << ">";
		cin >> inputString;
		_pModel->insertNode(inputString);
	}
	cout << _pModel->showMap();
}

void TextUIView::saveMindMap() //輸出MindMap到文件
{
	cout << _pModel->showMap();
	string path;
	cout << "Please input a file path: ";
	cin >> path;
	_pModel->saveMindMapFile(path);
	cout << "Save MindMap Success!!!" << endl << endl;
}

void TextUIView::loadMindMapFile()	//讀取檔案
{
	string path;
	cout << "Please input a file path: ";
	cin >> path;
	if (!_pModel->readMindMapFile(path))
		cout << "File not found!!" << endl << endl;
	else
		cout << _pModel->showMap();
}

void TextUIView::editNode()
{
	if (!_pModel->haveCreateMindMap())
	{
		cout << "Need to create the MindMap first." << endl << endl;
		return;
	}
	cout << _pModel->showMap();

	//enter edit node id
	string idString;
	int id;
	while (1)
	{
		cout << "Enter the edit node ID: ";
		cin >> idString;
		try
		{
			id = stoi(idString);
		}
		catch (exception)
		{
			cout << "The node is not exist!!" << endl << endl;
			continue;
		}

		if (!_pModel->isNodeExist(id))
		{
			cout << "The node is not exist!!" << endl << endl;
			continue;
		}
		break;
	}

	string input;
	while (1)
	{
		//enter edit mode
		printEditMenu();
		cin >> input;
		if (input.compare("a") == 0)
		{
			editDescription(id);
			break;
		}
		else if (input.compare("b") == 0)
		{
			changeParent(id);
			break;
		}
		else if (input.compare("c") == 0)
		{
			deleteNode(id);
			break;
		}
		else
		{
			cout << "The command is not found!!" << endl << endl;
		}
	}

}

void TextUIView::editDescription(int id)
{
	cin.get();
	string description;
	cout << "Enter the description: ";
	getline(cin, description);
	_pModel->editDescriptionCommand(id, description);
	cout << _pModel->showMap();
}

void TextUIView::changeParent(int myselfId)
{
	if (_pModel->isRoot(myselfId))
	{
		cout << "Root can't be changed the parent." << endl << endl;
		return;
	}

	string parentString;
	int parentId;
	while (1)
	{
		cout << "Enter the parent ID: ";
		cin >> parentString;
		try
		{
			parentId = stoi(parentString);
		}
		catch (exception)
		{
			cout << "The node is not exist!!" << endl << endl;
			continue;
		}
		if (!_pModel->isNodeExist(parentId))
		{
			cout << "The node is not exist!!" << endl << endl;
			continue;
		}

		if (myselfId == parentId)
		{
			cout << "You can't select itself!!" << endl << endl;
			continue;
		}

		break;
	}
	_pModel->changeParentCommand(myselfId, parentId);
	cout << _pModel->showMap();
}

void TextUIView::deleteNode(int id)
{
	if (_pModel->isRoot(id))
	{
		cout << "You can't delete the root." << endl << endl;
		return;
	}
		
	_pModel->deleteComponentCommand(id);
	cout << _pModel->showMap();
}

void TextUIView::redo()
{
	if (!_pModel->redo())
		cout << "Can't Redo!" << endl << endl;
	else
		cout << _pModel->showMap();
}

void TextUIView::undo()
{
	if (!_pModel->undo())
		cout << "Can't Undo!" << endl << endl;
	else
		cout << _pModel->showMap();
}