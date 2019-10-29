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
	/*\ 初始化控件样式 \*/
	this->InitControlStyle();
	/*\ 绑定信号和槽 \*/
	this->BindSignalAndSlot();
	/*\ 初始化成员变量信息信息 \*/
	this->InitVarInfo();
}

CMenJinManager::~CMenJinManager()
{
	/*\ 释放成员变量动态申请的内存 \*/
	this->DelVarInfo();
}

/****************************************!
*@brief  初始化控件样式
*@author Jinzi
*@date   2019/10/26 8:53:07
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::InitControlStyle()
{
	/*\ 设置当前窗口后面的窗口不能点击 \*/
	//this->setWindowModality(Qt::ApplicationModal);
	/*\ 隐藏最大化最小化按钮 \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("服务配置"));
	/*\ 设置edit中的默认值 \*/
	ui.m_editIp->setText("192.168.1.152");
	ui.m_editSPort->setText("8086");
	ui.m_editCPort->setText("8084");
}

/****************************************!
*@brief  绑定信号和槽函数
*@author Jinzi
*@date   2019/10/26 9:05:29
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::BindSignalAndSlot()
{
	/*\ 确认按钮绑定槽函数 \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CMenJinManager::BtnOkClickSlotFunc);
	/*\ 取消按钮点击事件 \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CMenJinManager::close);
}

/****************************************!
*@brief  确认按钮槽函数
*@author Jinzi
*@date   2019/10/26 9:09:14
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::BtnOkClickSlotFunc()
{
	/*\ 获取用户输入，判断用户输入是否合法 \*/
	if (!CUtils::GetInstance()->JuageIpLegal(ui.m_editIp->text()))
	{
		MessageBoxA(nullptr, "您输入的ip不合法,请重新输入", "提示", MB_OK | MB_ICONERROR);
		ui.m_editIp->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuagePortLegal(ui.m_editSPort->text()))
	{
		MessageBoxA(nullptr, "您输入的服务端口不合法,请重新输入", "提示", MB_OK | MB_ICONERROR);
		ui.m_editSPort->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuagePortLegal(ui.m_editSPort->text()))
	{
		MessageBoxA(nullptr, "您输入的前端端口不合法,请重新输入", "提示", MB_OK | MB_ICONERROR);
		ui.m_editCPort->setText("");
		return;
	}
	/*\ 保存数据 \*/
	m_opSvrInfo->m_qsSvrIp = ui.m_editIp->text();
	m_opSvrInfo->m_qsSSvrPort = ui.m_editSPort->text();
	m_opSvrInfo->m_qsCSvrPort = ui.m_editCPort->text();
	/*\ 显示窗口 \*/
	m_opFmMain->show();
	/*\ 将输入存储到主窗口中 \*/
	m_opFmMain->SetSvrInfo(*m_opSvrInfo);
	/*\ 得到服务器中存储的用户信息，保存并显示 \*/
	m_opFmMain->GetUserInfo();
	/*\ 得到服务器中门禁的信息 保存 登录并显示 \*/
	/*std::thread oThread(std::bind(&CFmMain::GetMenJinInfo, m_opFmMain));
	oThread.join();*/
	m_opFmMain->GetMenJinInfo();
	this->close();
}

/****************************************!
*@brief  初始化变量信息
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
*@brief  释放动态申请的内存
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