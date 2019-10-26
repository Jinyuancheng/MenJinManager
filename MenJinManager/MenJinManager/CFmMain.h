#pragma once
#ifndef _FMMAIN_H_
#define _FMMAIN_H_
#include <QtWidgets/QMainWindow>
#include <QNetworkReply>
#include <vector>

#include "../uic/ui_fmMain.h"

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

#ifndef _CFMADDUSER_H_
#include "./CFmAddUser.h"
#endif

#ifndef _CFMCHANAGEUSER_H_
#include "./CFmChangeUser.h"
#endif

class CFmMain: 
	public QMainWindow
{
	Q_OBJECT
public:
	CFmMain(QWidget* parent = Q_NULLPTR);
	~CFmMain();
private:
	/*\ ��ʼ���ؼ���� \*/
	void InitControlStyle();
	/*\ ���źźͲ� \*/
	void BindSignalAndSlot();
	/*\ ��ʼ����Ա���� \*/
	void InitVarInfo();
	/*\ �ͷų�Ա���� \*/
	void DelVarInfo();
	/*\ ��ʼ���Ӵ����е����� \*/
	void InitMemberFunc();
public:
	/*\ �ӷ����ȡ�û��洢����ʾ \*/
	void GetUserInfo();
	/*\ �ӷ����ȡ�Ž���Ϣ�洢����ʾ \*/
	void GetMenJinInfo();
	/*\ ��ʾ�����û����ݵ�table view \*/
	void ShowAllUserToTV();
	/*\ ��ʾ�����Ž���Ϣ��table view\*/
	void ShowAllMenJinToTV();
public:
	/*\ ����HTTP�����û��洢���� ���ݻص����ú���\*/
	void GetUserInfoCallBack(QNetworkReply* _opReqplay);
	/*\ ����http�����Ž��洢���� ���ݻص����ú��� \*/
	void GetMenJinInfoCallBack(QNetworkReply* _opReqplay);
	/*\ ɾ���û���Ϣ�����ݻص������� \*/
	void DelUserInfoCallBack(QNetworkReply* _opReqplay);
public:
	/*\ ���÷�����Ϣ \*/
	void SetSvrInfo(SSvrInfo _SvrInfo);
public slots:
	/*\ ����û���ť����¼� \*/
	void BtnAddUserClickedSlot();
	/*\ ɾ���û���ť����¼� \*/
	void BtnDelUserClickedSlot();
	/*\ �޸��û���ť����¼� \*/
	void BtnChangeUserClickedSlot();
private:
	Ui::CFmMain				ui;					/*\ ui������� \*/
	SSvrInfo				m_opSvrInfo;		/*\ �洢������Ϣ \*/
	CHttpRequest			m_opHttpInstance;	/*\ ����http����Ĳ��� \*/
	std::vector<SUserInfo>	m_vecUserAllInfo;	/*\ �洢�û���Ϣ \*/
	std::vector<SMenJinInfo>m_vecMenJinInfo;	/*\ �Ž���Ϣ \*/
	CFmAddUser				m_fmAddUser;		/*\ ����û�ҳ�� \*/
	CFmChangeUser			m_fmChangeUser;		/*\ �޸��û�ҳ�� \*/
};

#endif


