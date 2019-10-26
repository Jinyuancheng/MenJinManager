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
	/*\ ���ÿؼ���ʼ��ʽ \*/
	this->InitControlStyle();
	/*\ ��ʼ����Ա���� \*/
	this->InitVarInfo();
	/*\ ���źźͲ� \*/
	this->BindSignalAndSlot();
}


CFmAddUser::~CFmAddUser()
{
}

/****************************************!
*@brief  ��ʼ���ؼ�style
*@author Jinzi
*@date   2019/10/26 15:35:39
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::InitControlStyle()
{
	/*\ ���õ�ǰ���ں���Ĵ��ڲ��ܵ�� \*/
	this->setWindowModality(Qt::ApplicationModal);
	/*\ ���������С����ť \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("����û�"));
}

/****************************************!
*@brief  ���źźͲ�
*@author Jinzi
*@date   2019/10/26 15:38:04
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BindSignalAndSlot()
{
	/*\ �����ť \*/
	connect(ui.m_btnPicPath, &QPushButton::clicked, this, &CFmAddUser::BtnPicPathClicSlot);
	/*\ ȷ�ϰ�ť \*/
	connect(ui.m_btnOk, &QPushButton::clicked, this, &CFmAddUser::BtnOkClickSlot);
	/*\ ȡ����ť \*/
	connect(ui.m_btnQuit, &QPushButton::clicked, this, &CFmAddUser::BtnQuitClickSlot);
}

/****************************************!
*@brief  ȷ�ϰ�ť����¼�
*@author Jinzi
*@date   2019/10/26 15:40:22
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnOkClickSlot()
{
	/*\ �ж��û����� \*/
	if (ui.m_editCardNum->text().isEmpty())
	{
		MessageBoxA(nullptr, "�����뿨��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	if (ui.m_editJobNum->text().isEmpty())
	{
		MessageBoxA(nullptr, "�����빤��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	if (ui.m_editName->text().isEmpty())
	{
		MessageBoxA(nullptr, "����������", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_qsPicPath.isEmpty())
	{
		MessageBoxA(nullptr, "��ѡ������ͼƬ", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ �ж������Ƿ�Ϸ� \*/
	if (!CUtils::GetInstance()->JuageNumberLegal(ui.m_editCardNum->text()))
	{
		MessageBoxA(nullptr, "���Ų��Ϸ�,������6λ��10λ������", "��ʾ", MB_OK | MB_ICONERROR);
		ui.m_editCardNum->setText("");
		return;
	}
	if (!CUtils::GetInstance()->JuageNumberLegal(ui.m_editJobNum->text()))
	{
		MessageBoxA(nullptr, "���Ų��Ϸ�,������6λ��10λ������", "��ʾ", MB_OK | MB_ICONERROR);
		ui.m_editJobNum->setText("");
		return;
	}
	/*\ ��ֵ \*/
	QString qsUserName = ui.m_editName->text();
	QString qsUserCardNum = ui.m_editCardNum->text();
	QString qsUserJobNum = ui.m_editJobNum->text();
	/*\ ��������� ����û� \*/
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
*@brief  �����ť����¼�
*@author Jinzi
*@date   2019/10/26 15:40:29
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnPicPathClicSlot()
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
*@date   2019/10/26 15:43:14
*@param[in]
*@param[out]
*@return
****************************************/
void CFmAddUser::BtnQuitClickSlot()
{
	/*\ ���ҳ���е�edit���� \*/
	this->ClearEditData();
	/*\ �رմ��� \*/
	this->close();
}

/****************************************!
*@brief  ���ǰ�ı����е�����
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
*@brief  ��ʼ����Ա����
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
 *@brief  ���÷�������ip��Ϣ��
 *@author Jinzi
 *@date   2019/10/26 17:15:26
 *@param[in]  
	_SvrInfo	:	�洢��������ip �˿ڵ���Ϣ
 *@param[out] 
 *@return     
 ****************************************/
void CFmAddUser::SetSvrInfo(SSvrInfo _SvrInfo)
{
	m_opSvrInfo = _SvrInfo;
}

 /****************************************!
 *@brief  ��������û���Ϣ��������
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
		MessageBoxA(nullptr, "��������Ӧ����Ϊ��", "��ʾ", MB_OK | MB_ICONWARNING);
		return;
	}
	// ������ܵ�����;��ͼƬ����imgName��
	QByteArray replyContent = _opReplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toString() == 0)
	{
		/*\ ����CFmMain�е�GetUserInfo���� ��ʾ���µ��û����� \*/
		if (m_funcGetUserInfo != nullptr)
		{
			m_funcGetUserInfo();
		}
		MessageBoxA(nullptr, "����û��ɹ�", "��ʾ", MB_OK | MB_ICONWARNING);
		this->ClearEditData();
		return;
	}
	else
	{
		MessageBoxA(nullptr, "����û�ʧ��", "��ʾ", MB_OK | MB_ICONWARNING);
		this->ClearEditData();
		return;
	}
}