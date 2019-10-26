#pragma once
#ifndef _CFMADDUSER_H_
#define _CFMADDUSER_H_
#include <QMainWindow>
#include "../uic/ui_fmAddUser.h"
#include <vector>
#include <QNetworkReply>
#include <functional>

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

/*\ ����CFmMain�����е�GetUserInfo���� \*/
typedef std::function<void(void)>	FuncGetUserInfo;

class CFmAddUser :
	public QMainWindow
{
	Q_OBJECT
public:
	CFmAddUser(QWidget* parent = Q_NULLPTR);
	~CFmAddUser();
private:
	/*\ ��ʼ����Ա���� \*/
	void InitVarInfo();
	/*\ ��ʼ���ؼ�style \*/
	void InitControlStyle();
	/*\ ���źźͲ� \*/
	void BindSignalAndSlot();
	/*\ ���edit�е����� \*/
	void ClearEditData();
public:
	/*\ ���÷������Ϣ \*/
	void SetSvrInfo(SSvrInfo _SvrInfo);
public:
	/*\ ������������û���Ϣ�����ݣ��������ص����ݣ� \*/
	void SvrRetAddUserInfoHandle(QNetworkReply* _opReplay);
public slots:
	/*\ ȷ�ϰ�ť����¼� \*/
	void BtnOkClickSlot();
	/*\ �����ť����¼� \*/
	void BtnPicPathClicSlot();
	/*\ ȡ����ť����¼� \*/
	void BtnQuitClickSlot();
public:
	/*\ ��������CFmMain�е�GetUserInfo���� \*/
	FuncGetUserInfo		m_funcGetUserInfo;
private:
	Ui::CFmAddUser		ui;				/*\ ����ui���� \*/
	QString				m_qsPicPath;	/*\ �洢ͼƬ·�� \*/
	CHttpRequest		m_oHttpInstance;/*\ ���������������� \*/
	SSvrInfo			m_opSvrInfo;	/*\ �洢������Ϣ \*/
};


#endif // !_CFMADDUSER_H_



