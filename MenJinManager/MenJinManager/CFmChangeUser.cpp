#include "CFmChangeUser.h"
#include <windows.h>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>

#ifndef _UTILS_H_
#include "../Utils/utils.h"
#endif

CFmChangeUser::CFmChangeUser(QWidget* parent)
{
	ui.setupUi(this);
	/*\ 初始控件样式 \*/
	this->InitControlStyle();
	/*\ 初始化变量 \*/
	this->InitVarInfo();
	/*\ 绑定信号和槽 \*/
	this->BindSignalAndSlot();
}


CFmChangeUser::~CFmChangeUser()
{
}

/****************************************!
*@brief  初始化控件样式
*@author Jinzi
*@date   2019/10/26 18:30:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::InitControlStyle()
{
	/*\ 设置当前窗口后面的窗口不能点击 \*/
	this->setWindowModality(Qt::ApplicationModal);
	/*\ 隐藏最大化最小化按钮 \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("修改用户"));
	/*\ 隐藏卡号那一列 \*/
	ui.label->setVisible(false);
	ui.m_editCardNum->setVisible(false);
	/*\ 显示label等原来的数据 \*/
}

/****************************************!
*@brief  设置服务器信息
*@author Jinzi
*@date   2019/10/26 18:25:55
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::SetSvrInfo(SSvrInfo _oSvrInfo)
{
	m_oSvrInfo = _oSvrInfo;
}

/****************************************!
*@brief  绑定信号和槽
*@author Jinzi
*@date   2019/10/26 18:31:01
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BindSignalAndSlot()
{
	/*\ 取消按钮点击事件 \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CFmChangeUser::BtnQuitClickSlot);
	/*\ 确认按钮点击事件 \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CFmChangeUser::BtnOkClickSlot);
	/*\ 浏览按钮 \*/
	connect(ui.m_btnPicPath, &QPushButton::clicked, this, &CFmChangeUser::BtnPicPathClicSlot);
}

/****************************************!
*@brief  清空控件的缓存
*@author Jinzi
*@date   2019/10/26 18:34:08
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::ClearEditInfo()
{
	ui.m_editCardNum->setText("");
	ui.m_editJobNum->setText("");
	ui.m_editName->setText("");
	ui.m_lbPic->clear();
	m_qsPicPath = "";
}

/****************************************!
*@brief  初始化变量信息
*@author Jinzi
*@date   2019/10/26 18:35:40
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::InitVarInfo()
{
	m_qsPicPath = "";
}

/****************************************!
*@brief  设置要修改的用户信息
*@author Jinzi
*@date   2019/10/26 18:46:37
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::SetChangeUserInfo(SUserInfo _oUserInfo)
{
	m_oUserInfo = _oUserInfo;
}

/****************************************!
*@brief  确认按钮点击事件]
*@author Jinzi
*@date   2019/10/26 18:54:46
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BtnOkClickSlot()
{
	bool bIsOwn = false;
	if (ui.m_editName->text().isEmpty())
	{
		MessageBoxA(nullptr, "请输入必须字段姓名", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	if (!ui.m_editJobNum->text().isEmpty())
	{
		/*\ 校验用户输入是否合法 \*/
		CUtils::GetInstance()->JuageNumberLegal(ui.m_editJobNum->text());
	}
	/*\	请求数据 \*/
	QJsonObject json;
	/*\ 图片的url地址 \*/
	QString qsPicUrl = "http://" + m_oSvrInfo.m_qsSvrIp + ":" +
		m_oSvrInfo.m_qsCSvrPort + "/headinfo/" + m_oUserInfo.m_qsPicPath.toLocal8Bit().data();
	QString qsChangeUrl = "http://" + m_oSvrInfo.m_qsSvrIp +
		":" + m_oSvrInfo.m_qsSSvrPort + "/patroluser/updatePatrolUser";
	/*\ 说明用户更改了图片（满足条件） \*/
	if (m_qsPicPath != "")
	{
		/*\ 校验图片是否是一样的 \*/
		QByteArray oSvrPicData = m_oHttpInstance.HttpGetPicDataWithUrl(qsPicUrl.toLocal8Bit().data());
		oSvrPicData = oSvrPicData.toBase64();
		QByteArray oLocalPicData = CUtils::GetInstance()->LocalImageToBase64(m_qsPicPath);
		/*\ 不相等的话设置为true \*/
		if (oSvrPicData == oLocalPicData)
		{
			json.insert("file", "");
		}
		else
		{
			bIsOwn = true;
			json.insert("file", QString(oLocalPicData));
		}
	}
	json.insert("id", m_oUserInfo.m_qsUserId);
	json.insert("cardNumber", ui.m_editCardNum->text());
	json.insert("jobNumber", ui.m_editJobNum->text());
	json.insert("userName", ui.m_editName->text());
	json.insert("isOwn", bIsOwn);
	json.insert("faceTrait", "");
	json.insert("imgName", m_oUserInfo.m_qsPicPath);
	QJsonDocument jsonDocument(json);
	QByteArray oReqData = jsonDocument.toJson();
	m_oHttpInstance.HttpPostRequest(qsChangeUrl.toLocal8Bit().data(), oReqData,
		std::bind(&CFmChangeUser::SvrRetChangeUserInfoHandle, this, std::placeholders::_1));
}
/****************************************!
*@brief  浏览按钮点击事件
*@author Jinzi
*@date   2019/10/26 18:55:01
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BtnPicPathClicSlot()
{
	//定义文件对话框类
	QFileDialog* fileDialog = new QFileDialog(this);
	//定义文件对话框标题
	fileDialog->setWindowTitle(QString::fromLocal8Bit("打开图片"));
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	/*\ 保存文件路径 \*/
	if (fileNames[0] != nullptr)
	{
		m_qsPicPath = fileNames[0];
	}
	/*\ 显示图片到label中 \*/
	QPixmap pix;
	QImage* image = new QImage;//filename，图片的路径名字
	if (!image->load(m_qsPicPath))
	{
		MessageBoxA(nullptr, "图片加载失败", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ 显示图片 \*/
	ui.m_lbPic->setPixmap(pix.fromImage(*image));
	/*\ 让图片充满整个label \*/
	ui.m_lbPic->setScaledContents(true);
}
/****************************************!
*@brief  取消按钮点击事件
*@author Jinzi
*@date   2019/10/26 18:55:20
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BtnQuitClickSlot()
{
	/*\	清空控件信息 \*/
	this->ClearEditInfo();
	/*\ 关闭窗口 \*/
	this->close();
}

 /****************************************!
 *@brief  更改用户结果处理函数
 *@author Jinzi
 *@date   2019/10/26 19:22:28
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CFmChangeUser::SvrRetChangeUserInfoHandle(QNetworkReply* _opReplay)
{
	if (_opReplay == nullptr)
	{
		MessageBoxA(nullptr, "服务器响应数据为空", "提示", MB_OK | MB_ICONWARNING);
		return;
	}
	// 保存接受的数据;（图片名称imgName）
	QByteArray replyContent = _opReplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toString() == 0)
	{
		/*\ 更新显示用户信息 \*/
		if (m_funcGetUserInfo != nullptr)
		{
			m_funcGetUserInfo();
		}
		this->ClearEditInfo();
		this->close();
		MessageBoxA(nullptr, "修改用户成功", "提示", MB_OK);
		return;
	}
	else
	{
		this->ClearEditInfo();
		this->close();
		MessageBoxA(nullptr, "修改用户失败", "提示", MB_OK | MB_ICONERROR);
		return;
	}
}

 /****************************************!
 *@brief  修改 用户信息之前的数据显示
 *@author Jinzi
 *@date   2019/10/26 19:50:14
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CFmChangeUser::ShowAfterChangeData()
{
	ui.m_editName->setText(m_oUserInfo.m_qsUserName);
	ui.m_editJobNum->setText(m_oUserInfo.m_qsUserJobNum);
	/*\ 显示图片到label中 \*/
	QPixmap pix;
	QImage* image = new QImage;//filename，图片的路径名字




	//if (!image->load())
	//{
	//	MessageBoxA(nullptr, "图片加载失败", "提示", MB_OK | MB_ICONERROR);
	//	return;
	//}
	///*\ 显示图片 \*/
	//ui.m_lbPic->setPixmap(pix.fromImage(*image));
	///*\ 让图片充满整个label \*/
	//ui.m_lbPic->setScaledContents(true);
}