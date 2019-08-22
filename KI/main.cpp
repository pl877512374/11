#include "ki.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	/*QString s = "./lib";
	LPCWSTR path = s.toStdWString().c_str();*/
	//SetDllDirectory(L"lib\\");
	QApplication a(argc, argv);
	QApplication::addLibraryPath("./plugins");
	KI w;
	w.show();
	w.move((QApplication::desktop()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2);
 	return a.exec();
}

