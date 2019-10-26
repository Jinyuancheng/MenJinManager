#pragma once

#include <QtWidgets/QMainWindow>
#include "../uic/ui_CMenJinManager.h"

class CMenJinManager : public QMainWindow
{
	Q_OBJECT

public:
	CMenJinManager(QWidget *parent = Q_NULLPTR);
private:
	/*\ ��ʼ���ؼ�״̬ \*/
	void InitControlStyle();
	/*\ ���źźͲ� \*/
	void BindSignalAndSlot();
public slots:
	/*\ ȷ�ϰ�ť����¼� \*/
	void BtnOkClickSlotFunc();
private:
	Ui::CMenJinManagerClass ui;
};
