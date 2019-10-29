#pragma once
#ifndef _HIKHANDLE_H_
#define _HIKHANDLE_H_

#include <vector>
#include <QByteArray>
#include <QString>
#include <QObject>

#ifndef _TEMPLATE_H_
#include "../Utils/template.h"
#endif

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif // !_PUBDEF_H_

#ifndef _HC_NET_SDK_H_
#include "../HIKSDK/HCNetSDK.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

/*\ �����ص����� \*/
BOOL MsgHikCallBack(LONG _lCommand, NET_DVR_ALARMER* _pAlarmer,
	char* _pAlarmInfo, DWORD _dwBufLen, void* _pUser);

/*\ ���������� ������Ա�·�����Ϣ�Ļص����� \*/
void FuncRemoteConfigCallback(DWORD dwType,
	void* lpBuffer, DWORD dwBufLen, void* pUserData);

class CHikHandle : public QObject, public CSingleton<CHikHandle>
{
	Q_OBJECT
public:
	CHikHandle();
	~CHikHandle();
private:
	/*\ ��ʼ������api \*/
	void InitHikSDK();
	/*\ ��ʼ����Ա���� \*/
	void InitVarInfo();
	/*\ �ͷź���api \*/
	void DelHikSDK();
private:
	/*\ ͨ��http��ȡͼƬ���� \*/
	QByteArray GetHttpPicData(QString _qsUrl);
public:
	/*\ ���÷�����Ϣ \*/
	void SetSvrInfo(SSvrInfo _oSvrInfo);
public:
	/*\ �Ž�������¼ \*/
	void MenJinLogin(std::vector<SMenJinInfo> _vecMenJinInfo);
	/*\ �Ž���Ա�·� \*/
	std::vector<SMenJinSendDownInfo> MenJinUserSendDown(std::vector<SMenJinInfo>& _vecMenJinInfo,
		std::vector<SUserInfo>& _vecUserInfo);
	/*\ �·����� \*/
	bool MenJinUserSendDownFace(QString& _qsCardNum, int _iLoginHandle, QString& _iPicPath);
	/*\ ���ݿ����޸���Ա��Ϣ \*/
	std::vector<SMenJinSendDownInfo> MenJinChangeUserInfo(std::vector<SMenJinInfo>& _vecMenJinInfo,
		std::vector<SUserInfo>& _vecUserInfo);
signals:
	/*\ ��¼�ɹ����͸��ź� \*/
	void MenJinLoginSucc(std::vector<SMenJinInfo>);
public:
	MSGCallBack_V31				m_funcHikCallBack;	/*\ �����ص����� \*/
	int							m_iLongConnHandle;	/*\ �����Ӿ�� \*/
	CHttpRequest				m_oHttpInstance;	/*\ ����http���� \*/
	SSvrInfo					m_oSvrInfo;			/*\ �洢������Ϣ \*/
};
#endif


