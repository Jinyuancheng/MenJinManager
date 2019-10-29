#pragma once
#ifndef _CFMCHANAGEUSER_H_
#define _CFMCHANAGEUSER_H_
#include <QMainWindow>
#include <QString>
#include <functional>

#include "../uic/ui_fmChangeUser.h"

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

/*\ 用来调用CFmMain中的 GetUserInfo函数 \*/
typedef std::function<void(void)>	FuncGetUserInfo;
/*\ 用来调用CFmMain中的 SetShowStatusInfo函数 \*/
typedef std::function<void(std::vector<SMenJinSendDownInfo>)> FuncSetShowStatusInfo;

class CFmChangeUser :
	public QMainWindow
{
	Q_OBJECT
public:
	CFmChangeUser(QWidget* parent = Q_NULLPTR);
	~CFmChangeUser();
private:
	/*\ 初始化控件样式 \*/
	void InitControlStyle();
	/*\ 绑定信号和槽 \*/
	void BindSignalAndSlot();
	/*\ 清空控件信息 \*/
	void ClearEditInfo();
	/*\ 初始化成员变量的信息 \*/
	void InitVarInfo();
public:
	/*\ 显示 未修改前数据 \*/
	void ShowAfterChangeData();
public:
	/*\ 设置门禁信息 \*/
	void SetMenJinInfo(std::vector<SMenJinInfo> _vecMenJinInfo);
	/*\ 设置服务器信息 \*/
	void SetSvrInfo(SSvrInfo _oSvrInfo);
	/*\ 设置选中用户信息 \*/
	void SetChangeUserInfo(SUserInfo _oUserInfo);
public:
	/*\ 用来处理修改用户信息的数据（服务器回调数据） \*/
	void SvrRetChangeUserInfoHandle(QNetworkReply* _opReplay);
public slots:
	/*\ 确认按钮点击事件 \*/
	void BtnOkClickSlot();
	/*\ 浏览按钮点击事件 \*/
	void BtnPicPathClicSlot();
	/*\ 取消按钮点击事件 \*/
	void BtnQuitClickSlot();
public:
	/*\  用来调用CFmMain中的 GetUserInfo函数  \*/
	FuncGetUserInfo			m_funcGetUserInfo;
	/*\ 用来调用CFmMain中的 SetShowStatusInfo函数 \*/
	FuncSetShowStatusInfo	m_funcSetShowStatusInfo;
private:
	Ui::CFmChangeUser	ui;			        /*\ 操作ui的句柄 \*/
	SSvrInfo			m_oSvrInfo;	        /*\ 存储服务器信息 \*/
	QString				m_qsPicPath;        /*\ 图片路径 \*/
	SUserInfo			m_oUserInfo;        /*\ 用户选中要修改的用户信息 \*/
	CHttpRequest		m_oHttpInstance;	/*\ 操作http请求 \*/
	std::vector<SMenJinInfo> m_vecMenJinInfo;/*\ 门禁信息 \*/
};

#endif

