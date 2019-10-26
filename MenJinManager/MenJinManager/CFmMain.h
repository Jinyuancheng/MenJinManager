#pragma once
#ifndef _FMMAIN_H_
#define _FMMAIN_H_
#include <QtWidgets/QMainWindow>
#include <QNetworkReply>
#include <vector>

#include "../uic/ui_fmMain.h"

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

#ifndef _CFMADDUSER_H_
#include "./CFmAddUser.h"
#endif

#ifndef _CFMCHANAGEUSER_H_
#include "./CFmChangeUser.h"
#endif

class CFmMain: 
	public QMainWindow
{
	Q_OBJECT
public:
	CFmMain(QWidget* parent = Q_NULLPTR);
	~CFmMain();
private:
	/*\ 初始化控件风格 \*/
	void InitControlStyle();
	/*\ 绑定信号和槽 \*/
	void BindSignalAndSlot();
	/*\ 初始化成员变量 \*/
	void InitVarInfo();
	/*\ 释放成员变量 \*/
	void DelVarInfo();
	/*\ 初始化子窗体中的数据 \*/
	void InitMemberFunc();
public:
	/*\ 从服务获取用户存储并显示 \*/
	void GetUserInfo();
	/*\ 从服务获取门禁信息存储并显示 \*/
	void GetMenJinInfo();
	/*\ 显示所有用户数据到table view \*/
	void ShowAllUserToTV();
	/*\ 显示所有门禁信息到table view\*/
	void ShowAllMenJinToTV();
public:
	/*\ 请求HTTP服务用户存储数据 数据回调调用函数\*/
	void GetUserInfoCallBack(QNetworkReply* _opReqplay);
	/*\ 请求http服务门禁存储数据 数据回调调用函数 \*/
	void GetMenJinInfoCallBack(QNetworkReply* _opReqplay);
	/*\ 删除用户信息的数据回调处理函数 \*/
	void DelUserInfoCallBack(QNetworkReply* _opReqplay);
public:
	/*\ 设置服务信息 \*/
	void SetSvrInfo(SSvrInfo _SvrInfo);
public slots:
	/*\ 添加用户按钮点击事件 \*/
	void BtnAddUserClickedSlot();
	/*\ 删除用户按钮点击事件 \*/
	void BtnDelUserClickedSlot();
	/*\ 修改用户按钮点击事件 \*/
	void BtnChangeUserClickedSlot();
private:
	Ui::CFmMain				ui;					/*\ ui界面操作 \*/
	SSvrInfo				m_opSvrInfo;		/*\ 存储服务信息 \*/
	CHttpRequest			m_opHttpInstance;	/*\ 操作http请求的操作 \*/
	std::vector<SUserInfo>	m_vecUserAllInfo;	/*\ 存储用户信息 \*/
	std::vector<SMenJinInfo>m_vecMenJinInfo;	/*\ 门禁信息 \*/
	CFmAddUser				m_fmAddUser;		/*\ 添加用户页面 \*/
	CFmChangeUser			m_fmChangeUser;		/*\ 修改用户页面 \*/
};

#endif


