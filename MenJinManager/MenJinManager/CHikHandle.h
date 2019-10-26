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

/*\ �����ص����� \*/
BOOL MsgHikCallBack(LONG _lCommand, NET_DVR_ALARMER* _pAlarmer,
	char* _pAlarmInfo, DWORD _dwBufLen, void* _pUser);

class CHikHandle : public CSingleton<CHikHandle>
{
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
public:
	/*\ �Ž�������¼ \*/
	void MenJinLogin(std::vector<SMenJinInfo>& _vecMenJinInfo);
public:
	MSGCallBack_V31				m_funcHikCallBack;	/*\ �����ص����� \*/
};
#endif


