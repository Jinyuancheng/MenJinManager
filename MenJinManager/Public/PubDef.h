#pragma once
#ifndef _PUBDEF_H_
#define _PUBDEF_H_

#include <QString>

/*\ 用来存储服务信息 \*/
typedef struct
{
	QString		m_qsSvrIp;		/*\ 服务器 \*/
	QString		m_qsSSvrPort;	/*\ 服务端口 \*/
	QString		m_qsCSvrPort;	/*\ 客户端服务端口 \*/
}SSvrInfo, *pSSvrInfo;

/*\ 存储服务器端返回的用户信息 \*/
typedef struct
{
	QString		m_qsUserId;		/*\ 用户id \*/
	QString		m_qsUserCardNum;/*\ 用户卡号 \*/
	QString		m_qsUserJobNum;	/*\ 用户工号 \*/
	QString		m_qsUserName;	/*\ 用户姓名 \*/
	QString		m_qsPicPath;	/*\ 图片路径 \*/
}SUserInfo, *pSUserInfo;

/*\ 存储门禁信息 \*/
typedef struct
{
	QString		m_qsMenJinName;	/*\ 门禁名称 \*/
	QString		m_qsMenJinIp;	/*\ 门禁Ip \*/
	QString		m_qsMenJinPort;	/*\ 门禁端口 \*/
	QString		m_qsMenJinUser;	/*\ 门禁用户名 \*/
	QString		m_qsMenJinPass; /*\ 门禁登录密码 \*/
	int			m_iLoginHandle; /*\ 登录句柄 \*/
	bool		m_bIsLogin;		/*\ 是否登录 true登录 false未登录\*/
}SMenJinInfo, *pSMenJinInfo;
#endif
