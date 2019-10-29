#include "CHikHandle.h"
#include <QString>
#include <QFile>
#include <QCoreApplication>
#include <iostream>
#include <QDateTime>
#include <QMetaType> /*\ 用来发送自定义数据 \*/

#ifndef _UTILS_H_
#include "../Utils/utils.h"
#endif

/****************************************!
*@brief  人脸下发的回调函数
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
			/*\ 登录ip \*/
			strcpy(oLoginInfo.sDeviceAddress, vecMenJinInfo[i].m_qsMenJinIp.toLatin1().data());
			/*\ 登录端口 \*/
			oLoginInfo.wPort = vecMenJinInfo[i].m_qsMenJinPort.toUShort(&bOk, 10);
			/*\ 用户名密码 \*/
			strcpy(oLoginInfo.sUserName, vecMenJinInfo[i].m_qsMenJinUser.toLatin1().data());
			strcpy(oLoginInfo.sPassword, vecMenJinInfo[i].m_qsMenJinPass.toLatin1().data());
			oLoginInfo.bUseAsynLogin = FALSE;
			oLoginInfo.byLoginMode = 0;
			/*\ 进行登录 \*/
			vecMenJinInfo[i].m_iLoginHandle = NET_DVR_Login_V40(&oLoginInfo, &oDevInfo);
			int iError = NET_DVR_GetLastError();
			if (vecMenJinInfo[i].m_iLoginHandle >= 0)
			{
				vecMenJinInfo[i].m_bIsLogin = true;
			}
		}
		/*\ 发送信号 \*/
		emit MenJinLoginSucc(vecMenJinInfo);
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
	m_iLongConnHandle = -1;
}

/****************************************!
*@brief  门禁人员下发
*@author Jinzi
*@date   2019/10/28 8:29:53
*@param[in]
	_vecMenJinInfo	:	门禁主机的存储信息
	_vecUserInfo	:	用户信息
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
		/*\ 判断只有登录成功的门禁才下发 \*/
		if (_vecMenJinInfo[i].m_bIsLogin)
		{
			for (int j = 0; j < _vecUserInfo.size(); j++)
			{
				/*\ 将用户id添加进去 \*/
				SUserSendDownInfo oUserSendDownInfo = { 0 };
				oUserSendDownInfo.m_qsUserId = _vecUserInfo[j].m_qsUserId;
				oUserSendDownInfo.m_bIsUserSucc = false;
				oUserSendDownInfo.m_bIsPicSucc = false;
				/*\ 与门禁设备进行通信 \*/
				oAddCardInfo.dwSize = sizeof(oAddCardInfo);
				oAddCardInfo.dwCardNum = 1;
				oAddCardInfo.byCheckCardNo = 1;
				oAddCardInfo.wLocalControllerID = 0; /*\ 0表示门禁主机 \*/
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
					MessageBoxA(nullptr, "错误码 : " + iError, "提示", MB_OK | MB_ICONERROR);
					continue;
				}
				/*\ 下发卡信息 \*/
				NET_DVR_CARD_CFG_V50* opSendCardInfo = new NET_DVR_CARD_CFG_V50();
				if (opSendCardInfo == nullptr)
				{
					continue;
				}
				opSendCardInfo->dwSize = sizeof(NET_DVR_CARD_CFG_V50);
				opSendCardInfo->dwModifyParamType = 0x00040d8d; //0x000c80;//工号 姓名 密码
				/*\ 门权限模板 开启魔板 \*/
				opSendCardInfo->dwPlanTemplate = 1;//1.全天开启
				/*\ 门权限 \*/
				opSendCardInfo->byDoorRight[0] = 1;
				/*\ 卡模板参数 \*/
				opSendCardInfo->wCardRightPlan[0][0] = 1;
				opSendCardInfo->wCardRightPlan[0][1] = 2;
				/*\ 卡号 \*/
				strcpy((char*)(opSendCardInfo->byCardNo), _vecUserInfo[j].m_qsUserCardNum.toLocal8Bit().data());
				/*\ 卡密码 \*/
				strcpy((char*)opSendCardInfo->byCardPassword, "111111");
				/*\ 工号,不能以0开头，且不能重复 \*/
				opSendCardInfo->dwEmployeeNo = _vecUserInfo[j].m_qsUserJobNum.toUInt(&bOk, 10);
				/*\ 用户名 \*/
				strcpy((char*)opSendCardInfo->byName, _vecUserInfo[j].m_qsUserName.toLocal8Bit().data());
				/*\ 卡类型 \*/
				opSendCardInfo->byCardType = 1;
				/*\ 卡是否有效 \*/
				opSendCardInfo->byCardValid = 1;
				/*\ 用户类型 \*/
				opSendCardInfo->byUserType = 0;
				/*\ 发送数据 \*/
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
					/*\ 下发人脸信息,返回true表示人脸下发成功 \*/
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
*@brief  门禁用户下发人脸信息
*@author Jinzi
*@date   2019/10/28 8:53:10
*@param[in]
	_qsCardNum		:	卡号
	_iLoginHandle	:	海康登录句柄
	_iPicPath		:	人脸图片路径
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
	/*\ 建立长连接 \*/
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
	/*\ 发送数据 \*/
	NET_DVR_FACE_PARAM_CFG oSendFaceInfo = { 0 };
	oSendFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
	oSendFaceInfo.byFaceDataType = 1;
	oSendFaceInfo.byFaceID = 1;
	oSendFaceInfo.byEnableCardReader[0] = 1;
	/*\ 卡号 \*/
	strcpy((char*)oSendFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ 图片的url地址 \*/
	QString qsPicUrl = "http://" + m_oSvrInfo.m_qsSvrIp + ":" +
		m_oSvrInfo.m_qsCSvrPort + "/headinfo/" + _iPicPath.toLocal8Bit().data();
	QByteArray oPicData = this->GetHttpPicData(qsPicUrl);
	/*\ 将图片数据存储到文件中 \*/
	//QString qsFileName = QCoreApplication::applicationDirPath() + "/imageformats/" + _qsCardNum + ".jpg";
	/*FILE* opFileW = fopen(qsFileName.toLocal8Bit().data(), "wb");
	if (!opFileW)
	{
		return false;
	}
	fwrite(oPicData.data(), 1, oPicData.length(), opFileW);
	fclose(opFileW);*/
	/*\ 读取文件信息 \*/
	//char* chpBuf = new char[200 * 1024];
	//memset(chpBuf, 0, 200 * 1024);
	//FILE* fileI = fopen(std::string(qsFileName.toLocal8Bit().data()).c_str(), "rb");
	//FILE* fileI = fopen(std::string(qsFileName.toLocal8Bit().data()).c_str(), "rb");
	//if (!fileI)
	//{
	//	return false;
	//}
	///*\ 给char*分配内存 \*/
	//int iLength = fread(chpBuf, 1, 200 * 1024, fileI);
	//fclose(fileI);
	/*\ 赋值 \*/
	oSendFaceInfo.pFaceBuffer = oPicData.data();
	oSendFaceInfo.dwFaceLen = oPicData.length();
	/*\ 发送数据 \*/
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
	/*\ 为了防止后面的图片上传不了 \*/
	Sleep(1300);
	return bIsSucc;
}

/****************************************!
*@brief  根据http返回图片数据
*@author Jinzi
*@date   2019/10/28 9:03:28
*@param[in]
	_qsUrl	:	图片的url
*@param[out]
*@return
****************************************/
QByteArray CHikHandle::GetHttpPicData(QString _qsUrl)
{
	/*\ 返回图片数据 \*/
	QByteArray oSvrPicData = m_oHttpInstance.HttpGetPicDataWithUrl(_qsUrl.toLocal8Bit().data());
	return oSvrPicData;
}

/****************************************!
*@brief  设置服务器信息
*@author Jinzi
*@date   2019/10/28 9:08:03
*@param[in]
	_oSvrInfo	:	服务器配置信息
*@param[out]
*@return
****************************************/
void CHikHandle::SetSvrInfo(SSvrInfo _oSvrInfo)
{
	m_oSvrInfo = _oSvrInfo;
}

/****************************************!
*@brief  修改门禁用户信息
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
			/*\ 门禁信息 \*/
			SMenJinSendDownInfo oMenJinSendDownInfo;
			oMenJinSendDownInfo.m_bIsSendDown = false;
			oMenJinSendDownInfo.m_qsMenJinIp = _vecMenJinInfo[i].m_qsMenJinIp;

			/*\ 人员信息 \*/
			SUserSendDownInfo oUserSendDownInfo = { 0 };
			oUserSendDownInfo.m_qsUserId = _oChangeUser.m_qsUserId;
			oUserSendDownInfo.m_bIsPicSucc = false;
			oUserSendDownInfo.m_bIsUserSucc = false;

			/*\ 判断门禁主机是否登录成功 \*/
			if (_vecMenJinInfo[i].m_bIsLogin)
			{
				DWORD dwType = 0x00000000;
				/*\ 建立长连接 \*/
				NET_DVR_CARD_CFG_COND oCreateLoginInfo = { 0 };
				/*\ 修改用户信息 \*/
				NET_DVR_CARD_CFG_V50 oModifyInfo = { 0 };
				oCreateLoginInfo.dwSize = sizeof(NET_DVR_CARD_CFG_COND);
				oCreateLoginInfo.dwCardNum = 1;
				oCreateLoginInfo.byCheckCardNo = 1;
				/*\ 建立长连接 \*/
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

				/*\ 判断用户都修改了哪些数据 \*/
				/*\ 修改了工号 \*/
				if (!_oChangeUser.m_qsUserJobNum.isEmpty())
				{
					dwType |= 1 << 10;
					oModifyInfo.dwEmployeeNo = _oChangeUser.m_qsUserJobNum.toUInt();
				}
				/*\ 修改了姓名 \*/
				if (!_oChangeUser.m_qsUserName.isEmpty())
				{
					dwType |= 1 << 11;
					strcpy((char*)oModifyInfo.byName, _oChangeUser.m_qsUserName.toLocal8Bit().data());
				}
				/*\ 给修改了哪个字段的字段赋值 \*/
				oModifyInfo.dwModifyParamType = dwType;
				oModifyInfo.dwSize = sizeof(NET_DVR_CARD_CFG_V50);
				strcpy((char*)oModifyInfo.byCardNo, _oChangeUser.m_qsUserCardNum.toLocal8Bit().data());

				/*\ 修改 \*/
				if (!NET_DVR_SendRemoteConfig(
					m_iLongConnHandle,
					ENUM_ACS_SEND_DATA,
					(char*)& oModifyInfo,
					sizeof(NET_DVR_CARD_CFG_V50)
				))
				{
					/*\ 失败 \*/
					oUserSendDownInfo.m_bIsUserSucc = false;
					NET_DVR_StopRemoteConfig(m_iLongConnHandle);
				}
				else
				{
					/*\ 成功 \*/
					oUserSendDownInfo.m_bIsPicSucc = true;
					NET_DVR_StopRemoteConfig(m_iLongConnHandle);
				}
				/*\ 修改了图片 \*/
				if (!_oChangeUser.m_qsPicPath.isEmpty())
				{
					/*\ 先删除人脸 \*/
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
*@brief  本地图片进行人脸下发
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
	/*\ 建立长连接 \*/
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
	/*\ 发送数据 \*/
	NET_DVR_FACE_PARAM_CFG oSendFaceInfo = { 0 };
	oSendFaceInfo.dwSize = sizeof(NET_DVR_FACE_PARAM_CFG);
	oSendFaceInfo.byFaceDataType = 1;
	oSendFaceInfo.byFaceID = 1;
	oSendFaceInfo.byEnableCardReader[0] = 1;
	/*\ 卡号 \*/
	strcpy((char*)oSendFaceInfo.byCardNo, _qsCardNum.toLocal8Bit().data());
	/*\ 读取文件信息 \*/
	//char chpBuf[200 * 1024] = { 0 };
	char* chpBuf = new char[200 * 1024];
	FILE* fileI = fopen(std::string(_iPicPath.toLocal8Bit().data()).c_str(), "rb");
	if (!fileI)
	{
		return bIsSucc;
	}
	/*\ 给char*分配内存 \*/
	int iLength = fread(chpBuf, 1, 200 * 1024, fileI);
	fclose(fileI);
	/*\ 赋值 \*/
	oSendFaceInfo.pFaceBuffer = chpBuf;
	oSendFaceInfo.dwFaceLen = iLength;
	/*\ 发送数据 \*/
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
	/*\ 为了防止后面的图片上传不了 \*/
	Sleep(1300);
	return bIsSucc;
}

 /****************************************!
 *@brief  根据卡号删除人脸
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
	oDelFaceInfo.byMode = 0; /*\ 0根据卡号删除 \*/
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