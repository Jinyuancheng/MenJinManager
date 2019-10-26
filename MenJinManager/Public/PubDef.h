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
}SSvrInfo, * pSSvrInfo;
#endif
