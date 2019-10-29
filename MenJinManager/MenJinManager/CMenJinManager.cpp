#include "CMenJinManager.h"
#include <QString>
#include <windows.h>
#include <thread>


#ifndef _UTILS_H_
#include "../Utils/utils.h"
#endif // !_UTILS_H_

CMenJinManager::CMenJinManager(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*\ ��ʼ���ؼ���ʽ \*/
	this->InitControlStyle();
	/*\ ���źźͲ� \*/
	this->BindSignalAndSlot();
	/*\ ��ʼ����Ա������Ϣ��Ϣ \*/
	this->InitVarInfo();
}

CMenJinManager::~CMenJinManager()
{
	/*\ �ͷų�Ա������̬������ڴ� \*/
	this->DelVarInfo();
}

/****************************************!
*@brief  ��ʼ���ؼ���ʽ
*@author Jinzi
*@date   2019/10/26 8:53:07
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::InitControlStyle()
{
	/*\ ���õ�ǰ���ں���Ĵ��ڲ��ܵ�� \*/
	//this->setWindowModality(Qt::ApplicationModal);
	/*\ ���������С����ť \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("��������"));
	/*\ ����edit�е�Ĭ��ֵ \*/
	ui.m_editIp->setText("192.168.1.152");
	ui.m_editSPort->setText("8086");
	ui.m_editCPort->setText("8084");
}

/****************************************!
*@brief  ���źźͲۺ���
*@author Jinzi
*@date   2019/10/26 9:05:29
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::BindSignalAndSlot()
{
	/*\ ȷ�ϰ�ť�󶨲ۺ��� \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CMenJinManager::BtnOkClickSlotFunc);
	/*\ ȡ����ť����¼� \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CMenJinManager::close);
}

/****************************************!
*@brief  ȷ�ϰ�ť�ۺ���
*@author Jinzi
*@date   2019/10/26 9:09:14
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::BtnOkClickSlotFunc()
{
	/*\ ��ȡ�û����룬�ж��û������Ƿ�Ϸ� \*/
	if (!CUtils::GetInstance()->JuageIpLegal(ui.m_editIp->text()))
	{
		MessageBoxA(nullptr, "�������ip���Ϸ�,����������", "��ʾ", MB_OK | MB_ICONERROR);
		ui.m_editIp->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuagePortLegal(ui.m_editSPort->text()))
	{
		MessageBoxA(nullptr, "������ķ���˿ڲ��Ϸ�,����������", "��ʾ", MB_OK | MB_ICONERROR);
		ui.m_editSPort->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuagePortLegal(ui.m_editSPort->text()))
	{
		MessageBoxA(nullptr, "�������ǰ�˶˿ڲ��Ϸ�,����������", "��ʾ", MB_OK | MB_ICONERROR);
		ui.m_editCPort->setText("");
		return;
	}
	/*\ �������� \*/
	m_opSvrInfo->m_qsSvrIp = ui.m_editIp->text();
	m_opSvrInfo->m_qsSSvrPort = ui.m_editSPort->text();
	m_opSvrInfo->m_qsCSvrPort = ui.m_editCPort->text();
	/*\ ��ʾ���� \*/
	m_opFmMain->show();
	/*\ ������洢���������� \*/
	m_opFmMain->SetSvrInfo(*m_opSvrInfo);
	/*\ �õ��������д洢���û���Ϣ�����沢��ʾ \*/
	m_opFmMain->GetUserInfo();
	/*\ �õ����������Ž�����Ϣ ���� ��¼����ʾ \*/
	/*std::thread oThread(std::bind(&CFmMain::GetMenJinInfo, m_opFmMain));
	oThread.join();*/
	m_opFmMain->GetMenJinInfo();
	this->close();
}

/****************************************!
*@brief  ��ʼ��������Ϣ
*@author Jinzi
*@date   2019/10/26 10:20:58
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::InitVarInfo()
{
	m_opSvrInfo = new SSvrInfo();
	m_opFmMain = new CFmMain();
}

/****************************************!
*@brief  �ͷŶ�̬������ڴ�
*@author Jinzi
*@date   2019/10/26 10:22:28
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::DelVarInfo()
{
	if (m_opSvrInfo != nullptr)
	{
		delete m_opSvrInfo;
	}
	if (m_opFmMain != nullptr)
	{
		delete m_opFmMain;
	}
}