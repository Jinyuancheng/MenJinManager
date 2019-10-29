#include "./CFmMain.h"

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <functional>
#include <windows.h>
#include <QVariantList>
#include <QStandardItemModel>
#include <QJsonArray>
#include <thread>
#include <QModelIndexList>
#include <QList>
#include <QAbstractItemView>
#include <thread>

#ifndef _HIKHANDLE_H_
#include "./CHikHandle.h"
#endif // !_HIKHANDLE_H_

CFmMain::CFmMain(QWidget* parent /* = Q_NULLPTR */)
{
	ui.setupUi(this);
	/*\ 初始化控件风格 \*/
	this->InitControlStyle();
	/*\ 绑定信号和槽 \*/
	this->BindSignalAndSlot();
	/*\ 初始化成员变量 \*/
	this->InitVarInfo();
	/*\ 初始化成员窗体中的函数指针 \*/
	this->InitMemberFunc();
}

CFmMain::~CFmMain()
{
	/*\ 释放成员变量 \*/
	this->DelVarInfo();
}

/****************************************!
*@brief  初始化成员窗口的函数指针
*@author Jinzi
*@date   2019/10/26 17:39:41
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::InitMemberFunc()
{
	m_fmAddUser.m_funcGetUserInfo = std::bind(&CFmMain::GetUserInfo, this);
	m_fmChangeUser.m_funcGetUserInfo = std::bind(&CFmMain::GetUserInfo, this);
}

/****************************************!
*@brief  初始化控件风格
*@author Jinzi
*@date   2019/10/26 11:42:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::InitControlStyle()
{
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("人员管理系统"));
}
/****************************************!
*@brief  绑定信号和槽
*@author Jinzi
*@date   2019/10/26 11:42:55
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BindSignalAndSlot()
{
	/*\ 添加用户按钮 \*/
	connect(ui.m_btnAddUser, &QPushButton::clicked, this, &CFmMain::BtnAddUserClickedSlot);
	/*\ 删除用户按钮 \*/
	connect(ui.m_btnDelUser, &QPushButton::clicked, this, &CFmMain::BtnDelUserClickedSlot);
	/*\ 修改用户信息按钮 \*/
	connect(ui.m_btnChangeUser, &QPushButton::clicked, this, &CFmMain::BtnChangeUserClickedSlot);
	/*\ 同步按钮点击事件 \*/
	connect(ui.m_btnSync, &QPushButton::clicked, this, &CFmMain::BtnSyncClickedSlot);
	/*\ 绑定登录成功的信号 \*/
	QObject::connect(&m_oHikApi, SIGNAL(MenJinLoginSucc(std::vector<SMenJinInfo>)),
		this, SLOT(ShowAllMenJinToTV(std::vector<SMenJinInfo>)), Qt::DirectConnection);
}
/****************************************!
*@brief  初始化成员变量
*@author Jinzi
*@date   2019/10/26 11:43:08
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::InitVarInfo()
{

}
/****************************************!
*@brief  释放成员变量
*@author Jinzi
*@date   2019/10/26 11:43:34
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::DelVarInfo()
{

}
/****************************************!
*@brief  设置服务信息
*@author Jinzi
*@date   2019/10/26 11:46:09
*@param[in]
   _SvrInfo	:	服务信息
*@param[out]
*@return
****************************************/
void CFmMain::SetSvrInfo(SSvrInfo _SvrInfo)
{
	m_opSvrInfo = _SvrInfo;
}

/****************************************!
*@brief  请求服务器获取用户信息
*@author Jinzi
*@date   2019/10/26 13:21:37
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::GetUserInfo()
{
	QString qsUrl = "http://" + m_opSvrInfo.m_qsSvrIp + ":" + m_opSvrInfo.m_qsSSvrPort + "/patroluser/getPatrolUserList";
	QJsonObject jsonReqData;
	QJsonDocument jsonDocument(jsonReqData);
	QByteArray reqData(jsonDocument.toJson());
	m_opHttpInstance.HttpPostRequest(qsUrl.toLocal8Bit().data(), reqData,
		std::bind(&CFmMain::GetUserInfoCallBack, this, std::placeholders::_1));
}

/****************************************!
*@brief  从服务获取门禁信息并显示
*@author Jinzi
*@date   2019/10/26 13:22:40
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::GetMenJinInfo()
{
	QString qsUrl = "http://" + m_opSvrInfo.m_qsSvrIp + ":" + m_opSvrInfo.m_qsSSvrPort + "/interProvide/getAllRkeInfo";
	QJsonObject jsonReqData;
	QJsonDocument jsonDocument(jsonReqData);
	QByteArray reqData(jsonDocument.toJson());
	m_opHttpInstance.HttpPostRequest(qsUrl.toLocal8Bit().data(), reqData,
		std::bind(&CFmMain::GetMenJinInfoCallBack, this, std::placeholders::_1));
}

/****************************************!
*@brief  获取用户信息回调数据处理函数
*@author Jinzi
*@date   2019/10/26 13:38:43
*@param[in]
   _opReqplay	:	需要处理的数据（服务器返回的数据）
*@param[out]
*@return
****************************************/
void CFmMain::GetUserInfoCallBack(QNetworkReply* _opReqplay)
{
	if (_opReqplay == nullptr)
	{
		MessageBoxA(nullptr, "服务器响应数据为空", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	// 保存接受的数据;（图片名称imgName）
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		QJsonObject::iterator it = jsonResData.find("data");
		QJsonValueRef arrData = it.value();
		QVariantList jsonList = arrData.toArray().toVariantList();
		/*\ 判断存储用户信息的vector容器 不为空 先清空 \*/
		if (!m_vecUserAllInfo.empty())
		{
			m_vecUserAllInfo.clear();
		}
		/*\ 将用户信息存储起来 \*/
		for (int i = 0; i < jsonList.count(); i++)
		{
			QVariantMap map = jsonList[i].toMap();
			SUserInfo* opSvrInfo = new SUserInfo();
			opSvrInfo->m_qsUserId = map.value("id").toString();
			opSvrInfo->m_qsUserName = map.value("userName").toString();
			opSvrInfo->m_qsUserJobNum = map.value("jobNumber").toString();
			opSvrInfo->m_qsUserCardNum = map.value("cardNumber").toString();
			opSvrInfo->m_qsPicPath = map.value("imgName").toString();
			m_vecUserAllInfo.push_back(*opSvrInfo);
		}
	}
	/*\ 将查询的用户信息显示到控件中 \*/
	this->ShowAllUserToTV();
}

/****************************************!
*@brief  显示所有用户信息到tableview
*@author Jinzi
*@date   2019/10/26 13:47:51
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::ShowAllUserToTV()
{
	if (m_vecUserAllInfo.size() < 0)
	{
		MessageBoxA(nullptr, "查询所有用户信息失败", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	QStandardItemModel* opModelRet = (QStandardItemModel*)ui.m_tvUserInfo->model();
	if (opModelRet != nullptr)
	{
		opModelRet->clear();
	}
	QStandardItemModel* opModel = new QStandardItemModel();

	opModel->setColumnCount(3);
	opModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("卡号"));
	opModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("工号"));
	opModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
	/*\ 设置表的属性 \*/
	ui.m_tvUserInfo->setModel(opModel);
	/*\ 设置左对齐 \*/
	ui.m_tvUserInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//表列随着表格变化而自适应变化
	ui.m_tvUserInfo->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	//表行随着表格变化而自适应变化
	ui.m_tvUserInfo->verticalHeader()->sectionResizeMode(QHeaderView::Stretch);
	/*\ 设置只读 \*/
	ui.m_tvUserInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	/*\ 设置选中为选中行 \*/
	ui.m_tvUserInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	for (int i = 0; i < m_vecUserAllInfo.size(); i++)
	{
		/*\ 卡号 \*/
		opModel->setItem(i, 0, new QStandardItem(m_vecUserAllInfo[i].m_qsUserCardNum.toLocal8Bit().data()));
		/*\ 工号 \*/
		opModel->setItem(i, 1, new QStandardItem(m_vecUserAllInfo[i].m_qsUserJobNum.toLocal8Bit().data()));
		/*\ 姓名 \*/
		opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit(m_vecUserAllInfo[i].m_qsUserName.toLocal8Bit().data())));
		for (int j = 0; j < 3; j++)
		{
			//设置字符位置 
			opModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}
		//设置字符颜色 
		opModel->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	}
}

/****************************************!
*@brief  显示所有门禁信息到table view
*@author Jinzi
*@date   2019/10/26 14:02:39
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::ShowAllMenJinToTV(std::vector<SMenJinInfo> _vecMenJinInfo)
{
	if (m_vecMenJinInfo.size() > 0)
	{
		m_vecMenJinInfo.clear();
	}
	m_vecMenJinInfo = _vecMenJinInfo;
	if (m_vecMenJinInfo.size() < 0)
	{
		MessageBoxA(nullptr, "查询所有门禁信息失败", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	QStandardItemModel* opModelRet = (QStandardItemModel*)ui.m_tvMenJinInfo->model();
	if (opModelRet != nullptr)
	{
		opModelRet->clear();
	}
	QStandardItemModel* opModel = new QStandardItemModel();

	opModel->setColumnCount(4);
	opModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("站点"));
	opModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Ip"));
	opModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("登录状态"));
	opModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("下发状态"));
	/*\ 设置表的属性 \*/
	ui.m_tvMenJinInfo->setModel(opModel);
	/*\ 设置左对齐 \*/
	ui.m_tvMenJinInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//表列随着表格变化而自适应变化
	ui.m_tvMenJinInfo->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	//表行随着表格变化而自适应变化
	ui.m_tvMenJinInfo->verticalHeader()->sectionResizeMode(QHeaderView::Stretch);
	/*\ 设置只读 \*/
	ui.m_tvMenJinInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	/*\ 设置选中为选中行 \*/
	ui.m_tvMenJinInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	for (int i = 0; i < m_vecMenJinInfo.size(); i++)
	{
		/*\ 站点名称 \*/
		opModel->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(m_vecMenJinInfo[i].m_qsMenJinName.toLocal8Bit().data())));
		/*\ Ip \*/
		opModel->setItem(i, 1, new QStandardItem(m_vecMenJinInfo[i].m_qsMenJinIp.toLocal8Bit().data()));
		/*\ 是否登录成功 \*/
		if (m_vecMenJinInfo[i].m_bIsLogin)
		{
			opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("登录成功")));
		}
		else
		{
			opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("登录失败")));
		}
		/*\ 是否下发成功 \*/
		opModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit("未下发")));
		for (int j = 0; j < 4; j++)
		{
			//设置字符位置 
			opModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}
		//设置字符颜色 
		opModel->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	}
	/*\ 给修改用户页面赋值 \*/
	m_fmChangeUser.SetMenJinInfo(m_vecMenJinInfo);
}

/****************************************!
*@brief  获取门禁数据的处理函数
*@author Jinzi
*@date   2019/10/26 14:09:29
*@param[in]
   _opReqplay	:	服务返回的数据
*@param[out]
*@return
****************************************/
void CFmMain::GetMenJinInfoCallBack(QNetworkReply* _opReqplay)
{
	if (_opReqplay == nullptr)
	{
		MessageBoxA(nullptr, "服务器响应数据为空", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	// 保存接受的数据;（图片名称imgName）
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		QJsonObject::iterator it = jsonResData.find("data");
		QJsonValueRef arrData = it.value();
		QVariantList jsonList = arrData.toArray().toVariantList();
		/*\ 判断存储用户信息的vector容器 不为空 先清空 \*/
		if (!m_vecMenJinInfo.empty())
		{
			m_vecMenJinInfo.clear();
		}
		/*\ 将用户信息存储起来 \*/
		for (int i = 0; i < jsonList.count(); i++)
		{
			QVariantMap map = jsonList[i].toMap();
			SMenJinInfo* opMenJinInfo = new SMenJinInfo();
			opMenJinInfo->m_qsMenJinIp = map.value("rkeIp").toString();
			opMenJinInfo->m_qsMenJinName = map.value("stationName").toString();
			opMenJinInfo->m_qsMenJinUser = map.value("strUser").toString();
			opMenJinInfo->m_qsMenJinPass = map.value("strPsw").toString();
			opMenJinInfo->m_qsMenJinPort = "8000";
			opMenJinInfo->m_iLoginHandle = -1;
			opMenJinInfo->m_bIsLogin = false;
			m_vecMenJinInfo.push_back(*opMenJinInfo);
		}
	}
	std::thread oThread(std::bind(&CHikHandle::MenJinLogin, &m_oHikApi, std::placeholders::_1), m_vecMenJinInfo);
	oThread.detach();
	/*\ 进行门禁登录 \*/
	//CHikHandle::GetInstance()->MenJinLogin(m_vecMenJinInfo);
	/*\ 显示门禁信息 \*/
	//this->ShowAllMenJinToTV();
}

/****************************************!
*@brief  添加用户按钮点击事件
*@author Jinzi
*@date   2019/10/26 15:28:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnAddUserClickedSlot()
{
	/*\ 将服务信息存储到fmAddUser中 \*/
	m_fmAddUser.SetSvrInfo(m_opSvrInfo);
	m_fmAddUser.show();
}

/****************************************!
*@brief  删除按钮的点击事件
*@author Jinzi
*@date   2019/10/26 17:51:16
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnDelUserClickedSlot()
{
	/*\ 判断用户都选择的哪个要删除的用户 \*/
	QModelIndexList selected = ui.m_tvUserInfo->selectionModel()->selectedRows();
	if (selected.size() == 0)
	{
		MessageBoxA(nullptr, "请选择要删除的用户", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	QJsonArray jsonArray;
	foreach(const QModelIndex & index, selected)
	{
		jsonArray.append(m_vecUserAllInfo[index.row()].m_qsUserId);
		/*\ 删除人脸信息 \*/
		for (int i = 0; i < m_vecMenJinInfo.size(); i++)
		{
			if (m_vecMenJinInfo[i].m_bIsLogin)
			{
				CHikHandle::GetInstance()->MenJinDelFaceInfoWithCard(
					m_vecUserAllInfo[index.row()].m_qsUserCardNum,
					m_vecMenJinInfo[i].m_iLoginHandle);
			}
		}
	}
	QString qsUrl = "http://" + m_opSvrInfo.m_qsSvrIp + ":" + m_opSvrInfo.m_qsSSvrPort + "/patroluser/deletePatroUserList";
	QJsonObject jsonReqData;
	jsonReqData.insert("idList", jsonArray);
	QJsonDocument jsonDocument(jsonReqData);
	QByteArray reqData(jsonDocument.toJson());
	m_opHttpInstance.HttpPostRequest(qsUrl.toLocal8Bit().data(), reqData,
		std::bind(&CFmMain::DelUserInfoCallBack, this, std::placeholders::_1));
}

/****************************************!
*@brief  删除用户信息的处理函数（服务器回调数据）
*@author Jinzi
*@date   2019/10/26 18:08:22
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::DelUserInfoCallBack(QNetworkReply* _opReqplay)
{
	if (_opReqplay == nullptr)
	{
		MessageBoxA(nullptr, "服务器响应数据为空", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	// 保存接受的数据;（图片名称imgName）
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		/*\ 得到用户信息 \*/
		this->GetUserInfo();
		MessageBoxA(nullptr, "删除用户成功", "提示", MB_OK);
		return;
	}
	else
	{
		MessageBoxA(nullptr, "删除用户失败", "提示", MB_OK | MB_ICONERROR);
		return;
	}
}

/****************************************!
*@brief  修改按钮的点击事件
*@author Jinzi
*@date   2019/10/26 18:22:18
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnChangeUserClickedSlot()
{
	/*\ 判断用户选择的是哪个用户 \*/
	QModelIndexList selected = ui.m_tvUserInfo->selectionModel()->selectedRows();
	if (selected.size() > 1)
	{
		MessageBoxA(nullptr, "请只选择一个用户", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	int iIndex = ui.m_tvUserInfo->currentIndex().row();
	if (iIndex == -1)
	{
		MessageBoxA(nullptr, "请选择一个要修改的用户", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ 请等待门禁登录 \*/
	if (!ui.m_tvMenJinInfo->verticalHeader()->count())
	{
		MessageBoxA(nullptr, "请等待门禁登录", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ 设置选中的用户信息 \*/
	m_fmChangeUser.SetChangeUserInfo(m_vecUserAllInfo[iIndex]);
	/*\ 设置服务器Ip等信息 \*/
	m_fmChangeUser.SetSvrInfo(m_opSvrInfo);
	/*\ 显示未修改前的数据 \*/
	//m_fmChangeUser.ShowAfterChangeData();
	/*\ 显示页面 \*/
	m_fmChangeUser.show();
}

/****************************************!
*@brief  同步按钮点击事件（人员下发）
*@author Jinzi
*@date   2019/10/28 9:17:35
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnSyncClickedSlot()
{
	/*\ 设置服务信息 \*/
	m_oHikApi.SetSvrInfo(m_opSvrInfo);
	/*\ 调用人员下发接口 \*/
	std::vector<SMenJinSendDownInfo> vecMenJinSuccInfo = m_oHikApi.MenJinUserSendDown(m_vecMenJinInfo, m_vecUserAllInfo);
	/*\ 显示下发结束 \*/
	MessageBoxA(nullptr, "人员下发结束", "提示", MB_OK);
}

/****************************************!
*@brief  修改tableview中门禁状态信息
*@author Jinzi
*@date   2019/10/28 16:13:05
*@param[in]
   _qsStatus	:	要显示的状态
   _iRow		:	行
   _iColum		:	列
*@param[out]
*@return
****************************************/
void CFmMain::ChangeTvMenJinStatus(QString _qsStatus, int _iRow, int _iColumn)
{
	/*QAbstractItemModel* oModel = ui.m_tvMenJinInfo->model();
	oModel->setItem(_iRow, _iColumn, new QStandardItem(QString::fromLocal8Bit(_qsStatus.toLocal8Bit().data())));*/

}

 /****************************************!
 *@brief  设置显示状态信息 
 *@author Jinzi
 *@date   2019/10/29 15:19:28
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CFmMain::SetShowStatusInfo()
{

}