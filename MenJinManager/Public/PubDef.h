#pragma once
#ifndef _PUBDEF_H_
#define _PUBDEF_H_

#include <QString>
/*\ �����洢������Ϣ \*/
typedef struct
{
	QString		m_qsSvrIp;		/*\ ������ \*/
	QString		m_qsSSvrPort;	/*\ ����˿� \*/
	QString		m_qsCSvrPort;	/*\ �ͻ��˷���˿� \*/
}SSvrInfo, * pSSvrInfo;
#endif
