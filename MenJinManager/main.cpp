#include "./MenJinManager/CMenJinManager.h"
#include <QtWidgets/QApplication>

#ifndef _PUBDEF_H_
#include "./Public/PubDef.h"
#endif

SSvrInfo* gl_struSvrInfo;	/*\ �洢ȫ������ \*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMenJinManager w;
	w.show();
	return a.exec();
}
