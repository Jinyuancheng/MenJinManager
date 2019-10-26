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
	/*\ ��ʼ���ؼ�״̬ \*/
	void InitControlStyle();
	/*\ ���źźͲ� \*/
	void BindSignalAndSlot();
	/*\ ��ʼ������ \*/
	void InitVarInfo();
	/*\ �ͷų�Ա�������ڴ� \*/
	void DelVarInfo();
public slots:
	/*\ ȷ�ϰ�ť����¼� \*/
	void BtnOkClickSlotFunc();
private:
	Ui::CMenJinManagerClass ui;				/*\ ���������Ϣ \*/
	SSvrInfo*				m_opSvrInfo;	/*\ �����洢�û�����ķ�����Ϣ \*/
	CFmMain*				m_opFmMain;		/*\ ������ \*/
};
