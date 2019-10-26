#pragma once

#include <QtWidgets/QMainWindow>
#include "../uic/ui_CMenJinManager.h"

class CMenJinManager : public QMainWindow
{
	Q_OBJECT

public:
	CMenJinManager(QWidget *parent = Q_NULLPTR);
private:
	/*\ 初始化控件状态 \*/
	void InitControlStyle();
	/*\ 绑定信号和槽 \*/
	void BindSignalAndSlot();
public slots:
	/*\ 确认按钮点击事件 \*/
	void BtnOkClickSlotFunc();
private:
	Ui::CMenJinManagerClass ui;
};
