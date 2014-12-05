//#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
	//return a.exec();
	return 0;
}
