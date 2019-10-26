#pragma once
#ifndef _CFMADDUSER_H_
#define _CFMADDUSER_H_
#include <QMainWindow>
#include "../uic/ui_fmAddUser.h"

class CFmAddUser :
	public QMainWindow
{
	Q_OBJECT
public:
	CFmAddUser(QWidget* parent = Q_NULLPTR);
	~CFmAddUser();
private:
	Ui::CFmAddUser		ui;	/*\ ²Ù×÷ui½çÃæ \*/
};


#endif // !_CFMADDUSER_H_



