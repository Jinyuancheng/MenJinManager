#include "CHikHandle.h"


/****************************************!
*@brief  海康回调函数
*@author Jinzi
*@date   2019/09/02 16:27:42
*@param[in]
   _lCommand		:	上传的消息类型，不同的报警信息对应不同的类型，通过类型区分是什么报警信息
   _pAlarmer		:	报警设备信息，包括设备序列号、IP地址、登录IUserID句柄等
   _pAlarmInfo		:	报警信息，通过lCommand值判断pAlarmer对应的结构体
   _dwBufLen		:	报警信息缓存大小
   _pUser			:	用户数据
*@param[out]
*@return
****************************************/
BOOL MsgHikCallBack(LONG _lCommand, NET_DVR_ALARMER* _pAlarmer,
	char* _pAlarmInfo, DWORD _dwBufLen, void* _pUser)
{
	return TRUE;
}

CHikHandle::CHikHandle()
{
	/*\ 初始化成员变量 \*/
	this->InitVarInfo();
	/*\ 初始化海康api \*/
	this->InitHikSDK();
}


CHikHandle::~CHikHandle()
{
	/*\ 释放海康api \*/
	this->DelHikSDK();
}

 /****************************************!
 *@brief  门禁登录
 *@author Jinzi
 *@date   2019/10/26 14:31:49
 *@param[in]  
	_vecMenJinInfo	:	门禁登录信息
 *@param[out] 
 *@return     
 ****************************************/
void CHikHandle::MenJinLogin(std::vector<SMenJinInfo>& _vecMenJinInfo)
{
	bool bOk;
	NET_DVR_USER_LOGIN_INFO oLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 oDevInfo = { 0 };
	if (_vecMenJinInfo.size() > 0)
	{
		for (int i = 0; i < _vecMenJinInfo.size(); i++)
		{
			/*\ 登录ip \*/
			strcpy(oLoginInfo.sDeviceAddress, _vecMenJinInfo[i].m_qsMenJinIp.toLatin1().data());
			/*\ 登录端口 \*/
			oLoginInfo.wPort = _vecMenJinInfo[i].m_qsMenJinPort.toUShort(&bOk, 10);
			/*\ 用户名密码 \*/
			strcpy(oLoginInfo.sUserName, _vecMenJinInfo[i].m_qsMenJinUser.toLatin1().data());
			strcpy(oLoginInfo.sPassword, _vecMenJinInfo[i].m_qsMenJinPass.toLatin1().data());
			oLoginInfo.bUseAsynLogin = FALSE;
			oLoginInfo.byLoginMode = 0;
			/*\ 进行登录 \*/
			_vecMenJinInfo[i].m_iLoginHandle = NET_DVR_Login_V40(&oLoginInfo, &oDevInfo);
			if (_vecMenJinInfo[i].m_iLoginHandle >= 0)
			{
				_vecMenJinInfo[i].m_bIsLogin = true;
			}
		}
	}
}

 /****************************************!
 *@brief  初始化海康sdk
 *@author Jinzi
 *@date   2019/10/26 14:35:45
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CHikHandle::InitHikSDK()
{
	if (NET_DVR_Init())
	{
		NET_DVR_SetDVRMessageCallBack_V31(this->m_funcHikCallBack, nullptr);
	}
}

 /****************************************!
 *@brief  释放海康sdk
 *@author Jinzi
 *@date   2019/10/26 14:41:42
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CHikHandle::DelHikSDK()
{
	NET_DVR_Cleanup();
}

 /****************************************!
 *@brief  初始化成员变量信息
 *@author Jinzi
 *@date   2019/10/26 14:39:46
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CHikHandle::InitVarInfo()
{
	m_funcHikCallBack = (MSGCallBack_V31)MsgHikCallBack;
}