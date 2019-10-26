#include "CHikHandle.h"


/****************************************!
*@brief  �����ص�����
*@author Jinzi
*@date   2019/09/02 16:27:42
*@param[in]
   _lCommand		:	�ϴ�����Ϣ���ͣ���ͬ�ı�����Ϣ��Ӧ��ͬ�����ͣ�ͨ������������ʲô������Ϣ
   _pAlarmer		:	�����豸��Ϣ�������豸���кš�IP��ַ����¼IUserID�����
   _pAlarmInfo		:	������Ϣ��ͨ��lCommandֵ�ж�pAlarmer��Ӧ�Ľṹ��
   _dwBufLen		:	������Ϣ�����С
   _pUser			:	�û�����
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
	/*\ ��ʼ����Ա���� \*/
	this->InitVarInfo();
	/*\ ��ʼ������api \*/
	this->InitHikSDK();
}


CHikHandle::~CHikHandle()
{
	/*\ �ͷź���api \*/
	this->DelHikSDK();
}

 /****************************************!
 *@brief  �Ž���¼
 *@author Jinzi
 *@date   2019/10/26 14:31:49
 *@param[in]  
	_vecMenJinInfo	:	�Ž���¼��Ϣ
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
			/*\ ��¼ip \*/
			strcpy(oLoginInfo.sDeviceAddress, _vecMenJinInfo[i].m_qsMenJinIp.toLatin1().data());
			/*\ ��¼�˿� \*/
			oLoginInfo.wPort = _vecMenJinInfo[i].m_qsMenJinPort.toUShort(&bOk, 10);
			/*\ �û������� \*/
			strcpy(oLoginInfo.sUserName, _vecMenJinInfo[i].m_qsMenJinUser.toLatin1().data());
			strcpy(oLoginInfo.sPassword, _vecMenJinInfo[i].m_qsMenJinPass.toLatin1().data());
			oLoginInfo.bUseAsynLogin = FALSE;
			oLoginInfo.byLoginMode = 0;
			/*\ ���е�¼ \*/
			_vecMenJinInfo[i].m_iLoginHandle = NET_DVR_Login_V40(&oLoginInfo, &oDevInfo);
			if (_vecMenJinInfo[i].m_iLoginHandle >= 0)
			{
				_vecMenJinInfo[i].m_bIsLogin = true;
			}
		}
	}
}

 /****************************************!
 *@brief  ��ʼ������sdk
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
 *@brief  �ͷź���sdk
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
 *@brief  ��ʼ����Ա������Ϣ
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