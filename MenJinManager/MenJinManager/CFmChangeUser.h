#pragma once
#ifndef _CFMCHANAGEUSER_H_
#define _CFMCHANAGEUSER_H_
#include <QMainWindow>
#include <QString>
#include <functional>

#include "../uic/ui_fmChangeUser.h"

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

/*\ ��������CFmMain�е� GetUserInfo���� \*/
typedef std::function<void(void)>	FuncGetUserInfo;
/*\ ��������CFmMain�е� SetShowStatusInfo���� \*/
typedef std::function<void(std::vector<SMenJinSendDownInfo>)> FuncSetShowStatusInfo;

class CFmChangeUser :
	public QMainWindow
{
	Q_OBJECT
public:
	CFmChangeUser(QWidget* parent = Q_NULLPTR);
	~CFmChangeUser();
private:
	/*\ ��ʼ���ؼ���ʽ \*/
	void InitControlStyle();
	/*\ ���źźͲ� \*/
	void BindSignalAndSlot();
	/*\ ��տؼ���Ϣ \*/
	void ClearEditInfo();
	/*\ ��ʼ����Ա��������Ϣ \*/
	void InitVarInfo();
public:
	/*\ ��ʾ δ�޸�ǰ���� \*/
	void ShowAfterChangeData();
public:
	/*\ �����Ž���Ϣ \*/
	void SetMenJinInfo(std::vector<SMenJinInfo> _vecMenJinInfo);
	/*\ ���÷�������Ϣ \*/
	void SetSvrInfo(SSvrInfo _oSvrInfo);
	/*\ ����ѡ���û���Ϣ \*/
	void SetChangeUserInfo(SUserInfo _oUserInfo);
public:
	/*\ ���������޸��û���Ϣ�����ݣ��������ص����ݣ� \*/
	void SvrRetChangeUserInfoHandle(QNetworkReply* _opReplay);
public slots:
	/*\ ȷ�ϰ�ť����¼� \*/
	void BtnOkClickSlot();
	/*\ �����ť����¼� \*/
	void BtnPicPathClicSlot();
	/*\ ȡ����ť����¼� \*/
	void BtnQuitClickSlot();
public:
	/*\  ��������CFmMain�е� GetUserInfo����  \*/
	FuncGetUserInfo			m_funcGetUserInfo;
	/*\ ��������CFmMain�е� SetShowStatusInfo���� \*/
	FuncSetShowStatusInfo	m_funcSetShowStatusInfo;
private:
	Ui::CFmChangeUser	ui;			        /*\ ����ui�ľ�� \*/
	SSvrInfo			m_oSvrInfo;	        /*\ �洢��������Ϣ \*/
	QString				m_qsPicPath;        /*\ ͼƬ·�� \*/
	SUserInfo			m_oUserInfo;        /*\ �û�ѡ��Ҫ�޸ĵ��û���Ϣ \*/
	CHttpRequest		m_oHttpInstance;	/*\ ����http���� \*/
	std::vector<SMenJinInfo> m_vecMenJinInfo;/*\ �Ž���Ϣ \*/
};

#endif

