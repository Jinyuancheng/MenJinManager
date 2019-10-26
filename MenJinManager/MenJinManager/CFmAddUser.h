#pragma once
#ifndef _CFMADDUSER_H_
#define _CFMADDUSER_H_
#include <QMainWindow>
#include "../uic/ui_fmAddUser.h"
#include <vector>
#include <QNetworkReply>
#include <functional>

#ifndef _PUBDEF_H_
#include "../Public/PubDef.h"
#endif

#ifndef _CHTTPREQUEST_H_
#include "./CHttpRequest.h"
#endif

/*\ 调用CFmMain窗体中的GetUserInfo函数 \*/
typedef std::function<void(void)>	FuncGetUserInfo;

class CFmAddUser :
	public QMainWindow
{
	Q_OBJECT
public:
	CFmAddUser(QWidget* parent = Q_NULLPTR);
	~CFmAddUser();
private:
	/*\ 初始化成员变量 \*/
	void InitVarInfo();
	/*\ 初始化控件style \*/
	void InitControlStyle();
	/*\ 绑定信号和槽 \*/
	void BindSignalAndSlot();
	/*\ 清空edit中的数据 \*/
	void ClearEditData();
public:
	/*\ 设置服务等信息 \*/
	void SetSvrInfo(SSvrInfo _SvrInfo);
public:
	/*\ 用来处理添加用户信息的数据（服务器回调数据） \*/
	void SvrRetAddUserInfoHandle(QNetworkReply* _opReplay);
public slots:
	/*\ 确认按钮点击事件 \*/
	void BtnOkClickSlot();
	/*\ 浏览按钮点击事件 \*/
	void BtnPicPathClicSlot();
	/*\ 取消按钮点击事件 \*/
	void BtnQuitClickSlot();
public:
	/*\ 用来调用CFmMain中的GetUserInfo函数 \*/
	FuncGetUserInfo		m_funcGetUserInfo;
private:
	Ui::CFmAddUser		ui;				/*\ 操作ui界面 \*/
	QString				m_qsPicPath;	/*\ 存储图片路径 \*/
	CHttpRequest		m_oHttpInstance;/*\ 从来操作请求数据 \*/
	SSvrInfo			m_opSvrInfo;	/*\ 存储服务信息 \*/
};


#endif // !_CFMADDUSER_H_



