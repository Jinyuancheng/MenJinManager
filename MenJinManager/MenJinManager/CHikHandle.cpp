#include "CHikHandle.h"
#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <iostream>
#include <QDateTime>
#include <QMetaType> /*\ ���������Զ������� \*/

#ifndef _UTILS_H_
#include "../Utils/utils.h"
#endif

/****************************************!
*@brief  �����·��Ļص�����
*@author Jinzi
*@date   2019/10/29 8:43:57
*@param[in]
*@param[out]
*@return
****************************************/
void FuncRemoteConfigCallback(DWORD dwType,
	void* lpBuffer, DWORD dwBufLen, void* pUserData)
{

}

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
void CHikHandle::MenJinLogin(std::vector<SMenJinInfo> _vecMenJinInfo)
{
	std::vector<SMenJinInfo> vecMenJinInfo = _vecMenJinInfo;
	bool bOk;
	NET_DVR_USER_LOGIN_INFO oLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 oDevInfo = { 0 };
	if (vecMenJinInfo.size() > 0)
	{
		for (int i = 0; i < vecMenJinInfo.size(); i++)
		{
			/*\ ��¼ip \*/
			strcpy(oLoginInfo.sDeviceAddress, vecMenJinInfo[i].m_qsMenJinIp.toLatin1().data());
			/*\ ��¼�˿� \*/
			oLoginInfo.wPort = vecMenJinInfo[i].m_qsMenJinPort.toUShort(&bOk, 10);
			/*\ �û������� \*/
			strcpy(oLoginInfo.sUserName, vecMenJinInfo[i].m_qsMenJinUser.toLatin1().data());
			strcpy(oLoginInfo.sPassword, vecMenJinInfo[i].m_qsMenJinPass.toLatin1().data());
			oLoginInfo.bUseAsynLogin = FALSE;
			oLoginInfo.byLoginMode = 0;
			/*\ ���е�¼ \*/
			vecMenJinInfo[i].m_iLoginHandle = NET_DVR_Login_V40(&oLoginInfo, &oDevInfo);
			int iError = NET_DVR_GetLastError();
			if (vecMenJinInfo[i].m_iLoginHandle >= 0)
			{
				vecMenJinInfo[i].m_bIsLogin = true;
			}
		}
		/*\ �����ź� \*/
		emit MenJinLoginSucc(vecMenJinInfo);
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
	m_iLongConnHandle = -1;
}

/****************************************!
*@brief  �Ž���Ա�·�
*@author Jinzi
*@date   2019/10/28 8:29:53
*@param[in]
	_vecMenJinInfo	:	�Ž������Ĵ洢��Ϣ
	_vecUserInfo	:	�û���Ϣ
*@param[out]
*@return
****************************************/
std::vector<SMenJinSendDownInfo> CHikHandle::MenJinUserSendDown(std::vector<SMenJinInfo>& _vecMenJinInfo, std::vector<SUserInfo>& _vecUserInfo)
{
	bool bOk;
	NET_DVR_CARD_CFG_COND oAddCardInfo = { 0 };
	std::vector<SMenJinSendDownInfo> vecMenJinSendDownInfo;
	for (int i = 0; i < _vecMenJinInfo.size(); i++)
	{
		SMenJinSendDownInfo oMenJinSendDownInfo = { 0 };
		oMenJinSendDownInfo.m_qsMenJinIp = _vecMenJinInfo[i].m_qsMenJinIp;
		oMenJinSendDownInfo.m_bIsSendDown = false;
		/*\ �ж�ֻ�е�¼�ɹ����Ž����·� \*/
		if (_vecMenJinInfo[i].m_bIsLogin)
		{
			for (int j = 0; j < _vecUserInfo.size(); j++)
			{
				/*\ ���û�id��ӽ�ȥ \*/
				SUserSendDownInfo oUserSendDownInfo = { 0 };
				oUserSendDownInfo.m_qsUserId = _vecUserInfo[j].m_qsUserId;
				oUserSendDownInfo.m_bIsUserSucc = false;
				oUserSendDownInfo.m_bIsPicSucc = false;
				/*\ ���Ž��豸����ͨ�� \*/
				oAddCardInfo.dwSize = sizeof(oAddCardInfo);
				oAddCardInfo.dwCardNum = 1;
				oAddCardInfo.byCheckCardNo = 1;
				oAddCardInfo.wLocalControllerID = 0; /*\ 0��ʾ�Ž����� \*/
				m_iLongConnHandle = NET_DVR_StartRemoteConfig(
					_vecMenJinInfo[i].m_iLoginHandle,
					NET_DVR_SET_CARD_CFG_V50,
					&oAddCardInfo,
					static_cast<DWORD>(sizeof(oAddCardInfo)),
					nullptr,
					nullptr
				);
				if (m_iLongConnHandle == -1)
				{
					int iError = NET_DVR_GetLastError();
					MessageBoxA(nullptr, "������ : " + iError, "��ʾ", MB_OK | MB_ICONERROR);
					continue;
				}
				/*\ �·�����Ϣ \*/
				NET_DVR_CARD_CFG_V50* opSendCardInfo = new NET_DVR_CARD_CFG_V50();
				if (opSendCardInfo == nullptr)
				{
					continue;
				}
				opSendCardInfo->dwSize = sizeof(NET_DVR_CARD_CFG_V50);
				opSendCardInfo->dwModifyParamType = 0x00040d8d; //0x000c80;//���� ���� ����
				/*\ ��Ȩ��ģ�� ����ħ�� \*/
				opSendCardInfo->dwPlanTemplate = 1;//1.ȫ�쿪��
				/*\ ��Ȩ�� \*/
				opSendCardInfo->byDoorRight[0] = 1;
				/*\ ��ģ����� \*/
				opSendCardInfo->wCardRightPlan[0][0] = 1;
				opSendCardInfo->wCardRightPlan[0][1] = 2;
				/*\ ���� \*/
				strcpy((char*)(opSendCardInfo->byCardNo), _vecUserInfo[j].m_qsUserCardNum.toLocal8Bit().data());
				/*\ ������ \*/
				strcpy((char*)opSendCardInfo->byCardPassword, "111111");
				/*\ ����,������0��ͷ���Ҳ����ظ� \*/
				opSendCardInfo->dwEmployeeNo = _vecUserInfo[j].m_qsUserJobNum.toUInt(&bOk, 10);
				/*\ �û��� \*/
				strcpy((char*)opSendCardInfo->byName, _vecUserInfo[j].m_qsUserName.toLocal8Bit().data());
				/*\ ������ \*/
				opSendCardInfo->byCardType = 1;
				/*\ ���Ƿ���Ч \*/
				opSendCardInfo->byCardValid = 1;
				/*\ �û����� \*/
				opSendCardInfo->byUserType = 0;
				/*\ �������� \*/
				if (!NET_DVR_SendRemoteConfig(
					m_iLongConnHandle,
					ENUM_ACS_SEND_DATA,
					(char*)opSendCardInfo,
					sizeof(NET_DVR_CARD_CFG_V50)))
				{
					if (opSendCardInfo != nullptr)
					{
						delete opSendCardInfo;
						opSendCardInfo = nullptr;
					}
					int iError = NET_DVR_GetLastError();
					if (opSendCardInfo != nullptr)
					{
						delete opSendCardInfo;
						opSendCardInfo = nullptr;
					}
					continue;
				}
				else
				{
					NET_DVR_StopRemoteConfig(m_iLongConnHandle);
					if (opSendCardInfo != nullptr)
					{
						delete opSendCardInfo;
						opSendCardInfo = nullptr;
					}
					oUserSendDownInfo.m_bIsUserSucc = true;
					/*\ �·�������Ϣ,����true��ʾ�����·��ɹ� \*/
					if (this->MenJinUserSendDownFace(_vecUserInfo[j].m_qsUserCardNum,
						_vecMenJinInfo[i].m_iLoginHandle, _vecUserInfo[j].m_qsPicPath))
					{
						oUserSendDownInfo.m_bIsPicSucc = true;
					}
				}
				oMenJinSendDownInfo.m_vecUserSendDownInfo.push_back(oUserSendDownInfo);
			}
			vecMenJinSendDownInfo.push_back(oMenJinSendDownInfo);
		}
		else
		{
			vecMenJinSendDownInfo.push_back(oMenJinSendDownInfo);
		}
	}
	return vecMenJinSendDownInfo;
}

/****************************************!
*@brief  �Ž��û��·�������Ϣ
*@author Jinzi
*@date   2019/10/28 8:53:10
*@param[in]
	_qsCardNum		:	����
	_iLoginHandle	:	������¼���
	_iPicPath		:	����ͼƬ·��
*@param[out]
*@return
****************************************/
bool CHikHandle::MenJinUserSendDownFace(QString& _qsCardNum, int _iLoginHandle, QString& _iPicPath)
{
	bool bIsSucc = false;
	NET_DVR_FACE_PARAM_COND oStartFaceInfo = { 0 };
	oStartFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_COND);
	oStartFaceInfo.dwFaceNum = 1;
	oStartFaceInfo.byFaceID = 1;
	oStartFaceInfo.byEnableCardReader[0] = 1;
	strcpy((char*)oStartFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ ���������� \*/
	m_iLongConnHandle = NET_DVR_StartRemoteConfig(
		_iLoginHandle,
		NET_DVR_SET_FACE_PARAM_CFG,
		&oStartFaceInfo,
		static_cast<DWORD>(sizeof(NET_DVR_FACE_PARAM_COND)),
		(fRemoteConfigCallback)FuncRemoteConfigCallback,
		nullptr
	);
	if (m_iLongConnHandle == -1)
	{
		int iError = NET_DVR_GetLastError();
		return bIsSucc;
	}
	/*\ �������� \*/
	NET_DVR_FACE_PARAM_CFG oSendFaceInfo = { 0 };
	oSendFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
	oSendFaceInfo.byFaceDataType = 1;
	oSendFaceInfo.byFaceID = 1;
	oSendFaceInfo.byEnableCardReader[0] = 1;
	/*\ ���� \*/
	strcpy((char*)oSendFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ ͼƬ��url��ַ \*/
	QString qsPicUrl = "http://" + m_oSvrInfo.m_qsSvrIp + ":" +
		m_oSvrInfo.m_qsCSvrPort + "/headinfo/" + _iPicPath.toLocal8Bit().data();
	QByteArray oPicData = this->GetHttpPicData(qsPicUrl);
	/*\ ��ͼƬ���ݴ洢���ļ��� \*/
	//QString qsFileName = QCoreApplication::applicationDirPath() + "/imageformats/" + _qsCardNum + ".jpg";
	/*FILE* opFileW = fopen(qsFileName.toLocal8Bit().data(), "wb");
	if (!opFileW)
	{
		return false;
	}
	fwrite(oPicData.data(), 1, oPicData.length(), opFileW);
	fclose(opFileW);*/
	/*\ ��ȡ�ļ���Ϣ \*/
	//char* chpBuf = new char[200 * 1024];
	//memset(chpBuf, 0, 200 * 1024);
	//FILE* fileI = fopen(std::string(qsFileName.toLocal8Bit().data()).c_str(), "rb");
	//FILE* fileI = fopen(std::string(qsFileName.toLocal8Bit().data()).c_str(), "rb");
	//if (!fileI)
	//{
	//	return false;
	//}
	///*\ ��char*�����ڴ� \*/
	//int iLength = fread(chpBuf, 1, 200 * 1024, fileI);
	//fclose(fileI);
	/*\ ��ֵ \*/
	oSendFaceInfo.pFaceBuffer = oPicData.data();
	oSendFaceInfo.dwFaceLen = oPicData.length();
	/*\ �������� \*/
	if (!NET_DVR_SendRemoteConfig(
		m_iLongConnHandle,
		ENUM_ACS_INTELLIGENT_IDENTITY_DATA,
		(char*)& oSendFaceInfo,
		static_cast<DWORD>(sizeof(NET_DVR_FACE_PARAM_CFG))))
	{
		int iError = -1;
		iError = NET_DVR_GetLastError();
		NET_DVR_StopRemoteConfig(m_iLongConnHandle);
		//delete chpBuf;
	}
	else
	{
		NET_DVR_StopRemoteConfig(m_iLongConnHandle);
		//CUtils::GetInstance()->DelFile(qsFileName);
		bIsSucc = true;
		//delete chpBuf;
	}
	/*\ Ϊ�˷�ֹ�����ͼƬ�ϴ����� \*/
	Sleep(1300);
	return bIsSucc;
}

/****************************************!
*@brief  ����http����ͼƬ����
*@author Jinzi
*@date   2019/10/28 9:03:28
*@param[in]
	_qsUrl	:	ͼƬ��url
*@param[out]
*@return
****************************************/
QByteArray CHikHandle::GetHttpPicData(QString _qsUrl)
{
	/*\ ����ͼƬ���� \*/
	QByteArray oSvrPicData = m_oHttpInstance.HttpGetPicDataWithUrl(_qsUrl.toLocal8Bit().data());
	return oSvrPicData;
}

/****************************************!
*@brief  ���÷�������Ϣ
*@author Jinzi
*@date   2019/10/28 9:08:03
*@param[in]
	_oSvrInfo	:	������������Ϣ
*@param[out]
*@return
****************************************/
void CHikHandle::SetSvrInfo(SSvrInfo _oSvrInfo)
{
	m_oSvrInfo = _oSvrInfo;
}

/****************************************!
*@brief  �޸��Ž��û���Ϣ
*@author Jinzi
*@date   2019/10/28 15:48:21
*@param[in]
*@param[out]
*@return
****************************************/
std::vector<SMenJinSendDownInfo> CHikHandle::MenJinChangeUserInfo(
	std::vector<SMenJinInfo>& _vecMenJinInfo,
	QString _qsCardNum,
	SUserInfo _oChangeUser)
{
	std::vector<SMenJinSendDownInfo> vecMenJinSuccInfo;
	if (_vecMenJinInfo.size() > 0)
	{
		for (int i = 0; i < _vecMenJinInfo.size(); i++)
		{
			/*\ �Ž���Ϣ \*/
			SMenJinSendDownInfo oMenJinSendDownInfo;
			oMenJinSendDownInfo.m_bIsSendDown = false;
			oMenJinSendDownInfo.m_qsMenJinIp = _vecMenJinInfo[i].m_qsMenJinIp;

			/*\ ��Ա��Ϣ \*/
			SUserSendDownInfo oUserSendDownInfo = { 0 };
			oUserSendDownInfo.m_qsUserId = _oChangeUser.m_qsUserId;
			oUserSendDownInfo.m_bIsPicSucc = false;
			oUserSendDownInfo.m_bIsUserSucc = false;

			/*\ �ж��Ž������Ƿ��¼�ɹ� \*/
			if (_vecMenJinInfo[i].m_bIsLogin)
			{
				DWORD dwType = 0x00000000;
				/*\ ���������� \*/
				NET_DVR_CARD_CFG_COND oCreateLoginInfo = { 0 };
				/*\ �޸��û���Ϣ \*/
				NET_DVR_CARD_CFG_V50 oModifyInfo = { 0 };
				oCreateLoginInfo.dwSize = sizeof(NET_DVR_CARD_CFG_COND);
				oCreateLoginInfo.dwCardNum = 1;
				oCreateLoginInfo.byCheckCardNo = 1;
				/*\ ���������� \*/
				m_iLongConnHandle = -1;
				m_iLongConnHandle = NET_DVR_StartRemoteConfig(
					_vecMenJinInfo[i].m_iLoginHandle,
					NET_DVR_SET_CARD_CFG_V50,
					&oCreateLoginInfo,
					sizeof(NET_DVR_CARD_CFG_COND),
					nullptr,
					nullptr
				);
				if (m_iLongConnHandle == -1)
				{
					continue;
				}

				/*\ �ж��û����޸�����Щ���� \*/
				/*\ �޸��˹��� \*/
				if (!_oChangeUser.m_qsUserJobNum.isEmpty())
				{
					dwType |= 1 << 10;
					oModifyInfo.dwEmployeeNo = _oChangeUser.m_qsUserJobNum.toUInt();
				}
				/*\ �޸������� \*/
				if (!_oChangeUser.m_qsUserName.isEmpty())
				{
					dwType |= 1 << 11;
					strcpy((char*)oModifyInfo.byName, _oChangeUser.m_qsUserName.toLocal8Bit().data());
				}
				/*\ ���޸����ĸ��ֶε��ֶθ�ֵ \*/
				oModifyInfo.dwModifyParamType = dwType;
				oModifyInfo.dwSize = sizeof(NET_DVR_CARD_CFG_V50);
				strcpy((char*)oModifyInfo.byCardNo, _oChangeUser.m_qsUserCardNum.toLocal8Bit().data());

				/*\ �޸� \*/
				if (!NET_DVR_SendRemoteConfig(
					m_iLongConnHandle,
					ENUM_ACS_SEND_DATA,
					(char*)& oModifyInfo,
					sizeof(NET_DVR_CARD_CFG_V50)
				))
				{
					/*\ ʧ�� \*/
					oUserSendDownInfo.m_bIsUserSucc = false;
					NET_DVR_StopRemoteConfig(m_iLongConnHandle);
				}
				else
				{
					/*\ �ɹ� \*/
					oUserSendDownInfo.m_bIsPicSucc = true;
					NET_DVR_StopRemoteConfig(m_iLongConnHandle);
				}
				/*\ �޸���ͼƬ \*/
				if (!_oChangeUser.m_qsPicPath.isEmpty())
				{
					/*\ ��ɾ������ \*/
					if (this->MenJinDelFaceInfoWithCard(_qsCardNum, _vecMenJinInfo[i].m_iLoginHandle))
					{
						if (this->MenJinLocalPicSendDownFace(_oChangeUser.m_qsUserCardNum,
							_vecMenJinInfo[i].m_iLoginHandle, _oChangeUser.m_qsPicPath))
						{
							oUserSendDownInfo.m_bIsPicSucc = true;
						}
					}
				}
				oMenJinSendDownInfo.m_vecUserSendDownInfo.push_back(oUserSendDownInfo);
				vecMenJinSuccInfo.push_back(oMenJinSendDownInfo);
			}
			else
			{
				oMenJinSendDownInfo.m_vecUserSendDownInfo.push_back(oUserSendDownInfo);
				vecMenJinSuccInfo.push_back(oMenJinSendDownInfo);
			}
			
		}
	}
	return vecMenJinSuccInfo;
}

/****************************************!
*@brief  ����ͼƬ���������·�
*@author Jinzi
*@date   2019/10/29 13:18:57
*@param[in]

*@param[out]
*@return
****************************************/
bool CHikHandle::MenJinLocalPicSendDownFace(QString& _qsCardNum, int _iLoginHandle, QString& _iPicPath)
{
	bool bIsSucc = false;
	NET_DVR_FACE_PARAM_COND oStartFaceInfo = { 0 };
	oStartFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_COND);
	oStartFaceInfo.dwFaceNum = 1;
	oStartFaceInfo.byFaceID = 1;
	oStartFaceInfo.byEnableCardReader[0] = 1;
	strcpy((char*)oStartFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ ���������� \*/
	m_iLongConnHandle = NET_DVR_StartRemoteConfig(
		_iLoginHandle,
		NET_DVR_SET_FACE_PARAM_CFG,
		&oStartFaceInfo,
		static_cast<DWORD>(sizeof(NET_DVR_FACE_PARAM_COND)),
		nullptr,
		nullptr
	);
	if (m_iLongConnHandle == -1)
	{
		int iError = NET_DVR_GetLastError();
		return bIsSucc;
	}
	/*\ �������� \*/
	NET_DVR_FACE_PARAM_CFG oSendFaceInfo = { 0 };
	oSendFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
	oSendFaceInfo.byFaceDataType = 1;
	oSendFaceInfo.byFaceID = 1;
	oSendFaceInfo.byEnableCardReader[0] = 1;
	/*\ ���� \*/
	strcpy((char*)oSendFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ ��ȡ�ļ���Ϣ \*/
	//char chpBuf[200 * 1024] = { 0 };
	char* chpBuf = new char[200 * 1024];
	FILE* fileI = fopen(std::string(_iPicPath.toLocal8Bit().data()).c_str(), "rb");
	if (!fileI)
	{
		return bIsSucc;
	}
	/*\ ��char*�����ڴ� \*/
	int iLength = fread(chpBuf, 1, 200 * 1024, fileI);
	fclose(fileI);
	/*\ ��ֵ \*/
	oSendFaceInfo.pFaceBuffer = chpBuf;
	oSendFaceInfo.dwFaceLen = iLength;
	/*\ �������� \*/
	if (!NET_DVR_SendRemoteConfig(
		m_iLongConnHandle,
		ENUM_ACS_INTELLIGENT_IDENTITY_DATA,
		(char*)& oSendFaceInfo,
		static_cast<DWORD>(sizeof(NET_DVR_FACE_PARAM_CFG))))
	{
		int iError = -1;
		iError = NET_DVR_GetLastError();
		NET_DVR_StopRemoteConfig(m_iLongConnHandle);
		delete chpBuf;
	}
	else
	{
		NET_DVR_StopRemoteConfig(m_iLongConnHandle);
		bIsSucc = true;
		delete chpBuf;
	}
	/*\ Ϊ�˷�ֹ�����ͼƬ�ϴ����� \*/
	Sleep(1300);
	return bIsSucc;
}

 /****************************************!
 *@brief  ���ݿ���ɾ������
 *@author Jinzi
 *@date   2019/10/29 14:35:19
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
bool CHikHandle::MenJinDelFaceInfoWithCard(QString _qsCardNum, int _iLoginHandle)
{
	bool bIsSucc = false;
	NET_DVR_FACE_PARAM_CTRL oDelFaceInfo = { 0 };
	oDelFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_CTRL);
	oDelFaceInfo.byMode = 0; /*\ 0���ݿ���ɾ�� \*/
	strcpy((char*)oDelFaceInfo.struProcessMode.struByCard.byCardNo, _qsCardNum.toLocal8Bit().data());
	oDelFaceInfo.struProcessMode.struByCard.byEnableCardReader[0] = 1;
	oDelFaceInfo.struProcessMode.struByCard.byFaceID[0] = 1;

	if (!NET_DVR_RemoteControl(
		_iLoginHandle,
		NET_DVR_DEL_FACE_PARAM_CFG,
		&oDelFaceInfo,
		sizeof(NET_DVR_FACE_PARAM_CTRL)
	))
	{
		return bIsSucc;
	}
	else
	{
		bIsSucc = true;
	}
	return bIsSucc;
}