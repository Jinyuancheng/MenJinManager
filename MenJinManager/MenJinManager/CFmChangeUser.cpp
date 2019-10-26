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
	/*\ ��ʼ�ؼ���ʽ \*/
	this->InitControlStyle();
	/*\ ��ʼ������ \*/
	this->InitVarInfo();
	/*\ ���źźͲ� \*/
	this->BindSignalAndSlot();
}


CFmChangeUser::~CFmChangeUser()
{
}

/****************************************!
*@brief  ��ʼ���ؼ���ʽ
*@author Jinzi
*@date   2019/10/26 18:30:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::InitControlStyle()
{
	/*\ ���õ�ǰ���ں���Ĵ��ڲ��ܵ�� \*/
	this->setWindowModality(Qt::ApplicationModal);
	/*\ ���������С����ť \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("�޸��û�"));
	/*\ ���ؿ�����һ�� \*/
	ui.label->setVisible(false);
	ui.m_editCardNum->setVisible(false);
	/*\ ��ʾlabel��ԭ�������� \*/
}

/****************************************!
*@brief  ���÷�������Ϣ
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
*@brief  ���źźͲ�
*@author Jinzi
*@date   2019/10/26 18:31:01
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BindSignalAndSlot()
{
	/*\ ȡ����ť����¼� \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CFmChangeUser::BtnQuitClickSlot);
	/*\ ȷ�ϰ�ť����¼� \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CFmChangeUser::BtnOkClickSlot);
	/*\ �����ť \*/
	connect(ui.m_btnPicPath, &QPushButton::clicked, this, &CFmChangeUser::BtnPicPathClicSlot);
}

/****************************************!
*@brief  ��տؼ��Ļ���
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
*@brief  ��ʼ��������Ϣ
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
*@brief  ����Ҫ�޸ĵ��û���Ϣ
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
*@brief  ȷ�ϰ�ť����¼�]
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
		MessageBoxA(nullptr, "����������ֶ�����", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	if (!ui.m_editJobNum->text().isEmpty())
	{
		/*\ У���û������Ƿ�Ϸ� \*/
		CUtils::GetInstance()->JuageNumberLegal(ui.m_editJobNum->text());
	}
	/*\	�������� \*/
	QJsonObject json;
	/*\ ͼƬ��url��ַ \*/
	QString qsPicUrl = "http://" + m_oSvrInfo.m_qsSvrIp + ":" +
		m_oSvrInfo.m_qsCSvrPort + "/headinfo/" + m_oUserInfo.m_qsPicPath.toLocal8Bit().data();
	QString qsChangeUrl = "http://" + m_oSvrInfo.m_qsSvrIp +
		":" + m_oSvrInfo.m_qsSSvrPort + "/patroluser/updatePatrolUser";
	/*\ ˵���û�������ͼƬ������������ \*/
	if (m_qsPicPath != "")
	{
		/*\ У��ͼƬ�Ƿ���һ���� \*/
		QByteArray oSvrPicData = m_oHttpInstance.HttpGetPicDataWithUrl(qsPicUrl.toLocal8Bit().data());
		oSvrPicData = oSvrPicData.toBase64();
		QByteArray oLocalPicData = CUtils::GetInstance()->LocalImageToBase64(m_qsPicPath);
		/*\ ����ȵĻ�����Ϊtrue \*/
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
*@brief  �����ť����¼�
*@author Jinzi
*@date   2019/10/26 18:55:01
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BtnPicPathClicSlot()
{
	//�����ļ��Ի�����
	QFileDialog* fileDialog = new QFileDialog(this);
	//�����ļ��Ի������
	fileDialog->setWindowTitle(QString::fromLocal8Bit("��ͼƬ"));
	//����Ĭ���ļ�·��
	fileDialog->setDirectory(".");
	//�����ļ�������
	fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
	//���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//������ͼģʽ
	fileDialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	/*\ �����ļ�·�� \*/
	if (fileNames[0] != nullptr)
	{
		m_qsPicPath = fileNames[0];
	}
	/*\ ��ʾͼƬ��label�� \*/
	QPixmap pix;
	QImage* image = new QImage;//filename��ͼƬ��·������
	if (!image->load(m_qsPicPath))
	{
		MessageBoxA(nullptr, "ͼƬ����ʧ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ ��ʾͼƬ \*/
	ui.m_lbPic->setPixmap(pix.fromImage(*image));
	/*\ ��ͼƬ��������label \*/
	ui.m_lbPic->setScaledContents(true);
}
/****************************************!
*@brief  ȡ����ť����¼�
*@author Jinzi
*@date   2019/10/26 18:55:20
*@param[in]
*@param[out]
*@return
****************************************/
void CFmChangeUser::BtnQuitClickSlot()
{
	/*\	��տؼ���Ϣ \*/
	this->ClearEditInfo();
	/*\ �رմ��� \*/
	this->close();
}

 /****************************************!
 *@brief  �����û����������
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
		MessageBoxA(nullptr, "��������Ӧ����Ϊ��", "��ʾ", MB_OK | MB_ICONWARNING);
		return;
	}
	// ������ܵ�����;��ͼƬ����imgName��
	QByteArray replyContent = _opReplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toString() == 0)
	{
		/*\ ������ʾ�û���Ϣ \*/
		if (m_funcGetUserInfo != nullptr)
		{
			m_funcGetUserInfo();
		}
		this->ClearEditInfo();
		this->close();
		MessageBoxA(nullptr, "�޸��û��ɹ�", "��ʾ", MB_OK);
		return;
	}
	else
	{
		this->ClearEditInfo();
		this->close();
		MessageBoxA(nullptr, "�޸��û�ʧ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
}

 /****************************************!
 *@brief  �޸� �û���Ϣ֮ǰ��������ʾ
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
	/*\ ��ʾͼƬ��label�� \*/
	QPixmap pix;
	QImage* image = new QImage;//filename��ͼƬ��·������




	//if (!image->load())
	//{
	//	MessageBoxA(nullptr, "ͼƬ����ʧ��", "��ʾ", MB_OK | MB_ICONERROR);
	//	return;
	//}
	///*\ ��ʾͼƬ \*/
	//ui.m_lbPic->setPixmap(pix.fromImage(*image));
	///*\ ��ͼƬ��������label \*/
	//ui.m_lbPic->setScaledContents(true);
}