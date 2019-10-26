#include "./MenJinManager/CMenJinManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMenJinManager w;
	w.show();
	return a.exec();
}
