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

/*\ 海康回调函数 \*/
BOOL MsgHikCallBack(LONG _lCommand, NET_DVR_ALARMER* _pAlarmer,
	char* _pAlarmInfo, DWORD _dwBufLen, void* _pUser);

/*\ 建立长连接 进行人员下发等信息的回调函数 \*/
void FuncRemoteConfigCallback(DWORD dwType,
	void* lpBuffer, DWORD dwBufLen, void* pUserData);

class CHikHandle : public QObject, public CSingleton<CHikHandle>
{
	Q_OBJECT
public:
	CHikHandle();
	~CHikHandle();
private:
	/*\ 初始化海康api \*/
	void InitHikSDK();
	/*\ 初始化成员变量 \*/
	void InitVarInfo();
	/*\ 释放海康api \*/
	void DelHikSDK();
private:
	/*\ 通过http获取图片数据 \*/
	QByteArray GetHttpPicData(QString _qsUrl);
public:
	/*\ 设置服务信息 \*/
	void SetSvrInfo(SSvrInfo _oSvrInfo);
public:
	/*\ 门禁主机登录 \*/
	void MenJinLogin(std::vector<SMenJinInfo> _vecMenJinInfo);
	/*\ 门禁人员下发 \*/
	std::vector<SMenJinSendDownInfo> MenJinUserSendDown(std::vector<SMenJinInfo>& _vecMenJinInfo,
		std::vector<SUserInfo>& _vecUserInfo);
	/*\ 下发人脸 \*/
	bool MenJinUserSendDownFace(QString& _qsCardNum, int _iLoginHandle, QString& _iPicPath);
	/*\ 根据卡号修改人员信息 \*/
	std::vector<SMenJinSendDownInfo> MenJinChangeUserInfo(std::vector<SMenJinInfo>& _vecMenJinInfo,
		std::vector<SUserInfo>& _vecUserInfo);
signals:
	/*\ 登录成功后发送该信号 \*/
	void MenJinLoginSucc(std::vector<SMenJinInfo>);
public:
	MSGCallBack_V31				m_funcHikCallBack;	/*\ 海康回调函数 \*/
	int							m_iLongConnHandle;	/*\ 长连接句柄 \*/
	CHttpRequest				m_oHttpInstance;	/*\ 操作http请求 \*/
	SSvrInfo					m_oSvrInfo;			/*\ 存储服务信息 \*/
};
#endif


