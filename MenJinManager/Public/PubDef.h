#pragma once
#ifndef _PUBDEF_H_
#define _PUBDEF_H_

#include <QString>
#include <vector>

/*\ �����洢������Ϣ \*/
typedef struct
{
	QString		m_qsSvrIp;		/*\ ������ \*/
	QString		m_qsSSvrPort;	/*\ ����˿� \*/
	QString		m_qsCSvrPort;	/*\ �ͻ��˷���˿� \*/
}SSvrInfo, *pSSvrInfo;

/*\ �洢�������˷��ص��û���Ϣ \*/
typedef struct
{
	QString		m_qsUserId;		/*\ �û�id \*/
	QString		m_qsUserCardNum;/*\ �û����� \*/
	QString		m_qsUserJobNum;	/*\ �û����� \*/
	QString		m_qsUserName;	/*\ �û����� \*/
	QString		m_qsPicPath;	/*\ ͼƬ·�� \*/
}SUserInfo, *pSUserInfo;

/*\ �洢�Ž���Ϣ \*/
typedef struct
{
	QString		m_qsMenJinName;	/*\ �Ž����� \*/
	QString		m_qsMenJinIp;	/*\ �Ž�Ip \*/
	QString		m_qsMenJinPort;	/*\ �Ž��˿� \*/
	QString		m_qsMenJinUser;	/*\ �Ž��û��� \*/
	QString		m_qsMenJinPass; /*\ �Ž���¼���� \*/
	int			m_iLoginHandle; /*\ ��¼��� \*/
	bool		m_bIsLogin;		/*\ �Ƿ��¼ true��¼ falseδ��¼\*/
}SMenJinInfo, *pSMenJinInfo;

/*\ �洢�û��Ƿ��·��ɹ� \*/
typedef struct
{
	QString		m_qsUserId;		/*\ �û�ID \*/
	bool		m_bIsUserSucc;	/*\ �Ƿ���Ա�·��ɹ� \*/
	bool		m_bIsPicSucc;	/*\ ͼƬ�Ƿ��·��ɹ� \*/
}SUserSendDownInfo, *pSUserSendDownInfo;

/*\ �����洢�Ž���Ա��Ϣ \*/
typedef struct
{
	QString							m_qsMenJinIp;			/*\ �Ž�Ip \*/
	bool							m_bIsSendDown;			/*\ �Ƿ��·���Ա�ɹ� \*/
	std::vector<SUserSendDownInfo>	m_vecUserSendDownInfo;	/*\ �û��·���Ϣ \*/
}SMenJinSendDownInfo, *pSMenJinSendDownInfo;

#endif
