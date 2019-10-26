#pragma once

#include <QtWidgets/QMainWindow>
#include "../uic/ui_CMenJinManager.h"

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _FMMAIN_H_
#include "./CFmMain.h"
#endif // !_FMMAIN_H_


class CMenJinManager : public QMainWindow
{
	Q_OBJECT

public:
	CMenJinManager(QWidget *parent = Q_NULLPTR);
	~CMenJinManager();
private:
	/*\ 初始化控件状态 \*/
	void InitControlStyle();
	/*\ 绑定信号和槽 \*/
	void BindSignalAndSlot();
	/*\ 初始化变量 \*/
	void InitVarInfo();
	/*\ 释放成员变量的内存 \*/
	void DelVarInfo();
public slots:
	/*\ 确认按钮点击事件 \*/
	void BtnOkClickSlotFunc();
private:
	Ui::CMenJinManagerClass ui;				/*\ 界面操作信息 \*/
	SSvrInfo*				m_opSvrInfo;	/*\ 用来存储用户输入的服务信息 \*/
	CFmMain*				m_opFmMain;		/*\ 主窗体 \*/
};
