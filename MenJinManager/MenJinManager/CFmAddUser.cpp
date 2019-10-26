#include "./CFmAddUser.h"
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <windows.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#ifndef _UTILS_H_
#include "../Utils/utils.h"
#endif

CFmAddUser::CFmAddUser(QWidget* parent)
{
	ui.setupUi(this);
	/*\ 设置控件初始样式 \*/
	this->InitControlStyle();
	/*\ 初始化成员变量 \*/
	this->InitVarInfo();
	/*\ 绑定信号和槽 \*/
	this->BindSignalAndSlot();
}


CFmAddUser::~CFmAddUser()
{
}

/****************************************!
*@brief  初始化控件style
*@author Jinzi
*@date   2019/10/26 15:35:39
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::InitControlStyle()
{
	/*\ 设置当前窗口后面的窗口不能点击 \*/
	this->setWindowModality(Qt::ApplicationModal);
	/*\ 隐藏最大化最小化按钮 \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("添加用户"));
}

/****************************************!
*@brief  绑定信号和槽
*@author Jinzi
*@date   2019/10/26 15:38:04
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BindSignalAndSlot()
{
	/*\ 浏览按钮 \*/
	connect(ui.m_btnPicPath, &QPushButton::clicked, this, &CFmAddUser::BtnPicPathClicSlot);
	/*\ 确认按钮 \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CFmAddUser::BtnOkClickSlot);
	/*\ 取消按钮 \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CFmAddUser::BtnQuitClickSlot);
}

/****************************************!
*@brief  确认按钮点击事件
*@author Jinzi
*@date   2019/10/26 15:40:22
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnOkClickSlot()
{
	/*\ 判断用户输入 \*/
	if (ui.m_editCardNum->text().isEmpty())
	{
		MessageBoxA(nullptr, "请输入卡号", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	if (ui.m_editJobNum->text().isEmpty())
	{
		MessageBoxA(nullptr, "请输入工号", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	if (ui.m_editName->text().isEmpty())
	{
		MessageBoxA(nullptr, "请输入姓名", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_qsPicPath.isEmpty())
	{
		MessageBoxA(nullptr, "请选择人脸图片", "提示", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ 判断输入是否合法 \*/
	if (!CUtils::GetInstance()->JuageNumberLegal(ui.m_editCardNum->text()))
	{
		MessageBoxA(nullptr, "卡号不合法,请输入6位到10位的数字", "提示", MB_OK | MB_ICONERROR);
		ui.m_editCardNum->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuageNumberLegal(ui.m_editJobNum->text()))
	{
		MessageBoxA(nullptr, "工号不合法,请输入6位到10位的数字", "提示", MB_OK | MB_ICONERROR);
		ui.m_editJobNum->setText("");
		return;
	}
	/*\ 赋值 \*/
	QString qsUserName = ui.m_editName->text();
	QString qsUserCardNum = ui.m_editCardNum->text();
	QString qsUserJobNum = ui.m_editJobNum->text();
	/*\ 请求服务器 添加用户 \*/
	QString qsUrl = "http://" + m_opSvrInfo.m_qsSvrIp + ":" + m_opSvrInfo.m_qsSSvrPort + "/patroluser/addPatrolUser";
	QByteArray oPicBase64 = CUtils::GetInstance()->LocalImageToBase64(m_qsPicPath);
	QJsonObject jsonReqData;
	jsonReqData.insert("file", QString(oPicBase64));
	jsonReqData.insert("userName", qsUserName);
	jsonReqData.insert("faceTrait", "");
	jsonReqData.insert("cardNumber", qsUserCardNum);
	jsonReqData.insert("jobNumber", qsUserJobNum);
	QJsonDocument jsonDocument(jsonReqData);
	QByteArray reqData(jsonDocument.toJson());
	m_oHttpInstance.HttpPostRequest(qsUrl.toLocal8Bit().data(), reqData,
		std::bind(&CFmAddUser::SvrRetAddUserInfoHandle, this, std::placeholders::_1));
}

/****************************************!
*@brief  浏览按钮点击事件
*@author Jinzi
*@date   2019/10/26 15:40:29
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnPicPathClicSlot()
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
*@date   2019/10/26 15:43:14
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnQuitClickSlot()
{
	/*\ 清空页面中的edit数据 \*/
	this->ClearEditData();
	/*\ 关闭窗口 \*/
	this->close();
}

/****************************************!
*@brief  清除前文本框中的数据
*@author Jinzi
*@date   2019/10/26 15:44:01
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::ClearEditData()
{
	ui.m_editCardNum->setText("");
	ui.m_editJobNum->setText("");
	ui.m_editName->setText("");
	ui.m_lbPic->clear();
	m_qsPicPath = "";
}

/****************************************!
*@brief  初始化成员变量
*@author Jinzi
*@date   2019/10/26 15:48:08
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::InitVarInfo()
{
	m_qsPicPath = "";
}

 /****************************************!
 *@brief  设置服务器的ip信息等
 *@author Jinzi
 *@date   2019/10/26 17:15:26
 *@param[in]  
	_SvrInfo	:	存储服务器的ip 端口等信息
 *@param[out] 
 *@return     
 ****************************************/
void CFmAddUser::SetSvrInfo(SSvrInfo _SvrInfo)
{
	m_opSvrInfo = _SvrInfo;
}

 /****************************************!
 *@brief  处理添加用户信息返回数据
 *@author Jinzi
 *@date   2019/10/26 17:18:55
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CFmAddUser::SvrRetAddUserInfoHandle(QNetworkReply* _opReplay)
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
		/*\ 调用CFmMain中的GetUserInfo函数 显示最新的用户数据 \*/
		if (m_funcGetUserInfo != nullptr)
		{
			m_funcGetUserInfo();
		}
		MessageBoxA(nullptr, "添加用户成功", "提示", MB_OK | MB_ICONWARNING);
		this->ClearEditData();
		return;
	}
	else
	{
		MessageBoxA(nullptr, "添加用户失败", "提示", MB_OK | MB_ICONWARNING);
		this->ClearEditData();
		return;
	}
}