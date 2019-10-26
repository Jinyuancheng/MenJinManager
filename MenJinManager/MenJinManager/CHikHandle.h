#pragma once
#ifndef _HIKHANDLE_H_
#define _HIKHANDLE_H_

#include <vector>

#ifndef _TEMPLATE_H_
#include "../Utils/template.h"
#endif

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif // !_PUBDEF_H_

#ifndef _HC_NET_SDK_H_
#include "../HIKSDK/HCNetSDK.h"
#endif

/*\ 海康回调函数 \*/
BOOL MsgHikCallBack(LONG _lCommand, NET_DVR_ALARMER* _pAlarmer,
	char* _pAlarmInfo, DWORD _dwBufLen, void* _pUser);

class CHikHandle : public CSingleton<CHikHandle>
{
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
public:
	/*\ 门禁主机登录 \*/
	void MenJinLogin(std::vector<SMenJinInfo>& _vecMenJinInfo);
public:
	MSGCallBack_V31				m_funcHikCallBack;	/*\ 海康回调函数 \*/
};
#endif


