#include "GraphicalUI.h"
#include <QtWidgets/QApplication>
#include "TextUIView.h"
#include "PresentationModel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PresentationModel pModel;
	TextUIView textUI(&pModel);
	GraphicalUI gUI(&pModel);
	string input;

	cout << "Please select the UI mode:" << endl;
	cout << "[textmode] Text UI " << endl;
	cout << "[otherwise] Graphical UI" << endl << ">";
	cin >> input;
	//input = 'b';
	if (input.compare("textmode") == 0)
	{
		textUI.run();
	}
	else
	{
		gUI.show();
	}
	return a.exec();
}
