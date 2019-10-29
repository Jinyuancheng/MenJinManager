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
	/*\ ��ʼ���ؼ���� \*/
	this->InitControlStyle();
	/*\ ���źźͲ� \*/
	this->BindSignalAndSlot();
	/*\ ��ʼ����Ա���� \*/
	this->InitVarInfo();
	/*\ ��ʼ����Ա�����еĺ���ָ�� \*/
	this->InitMemberFunc();
}

CFmMain::~CFmMain()
{
	/*\ �ͷų�Ա���� \*/
	this->DelVarInfo();
}

/****************************************!
*@brief  ��ʼ����Ա���ڵĺ���ָ��
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
*@brief  ��ʼ���ؼ����
*@author Jinzi
*@date   2019/10/26 11:42:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::InitControlStyle()
{
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("��Ա����ϵͳ"));
}
/****************************************!
*@brief  ���źźͲ�
*@author Jinzi
*@date   2019/10/26 11:42:55
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BindSignalAndSlot()
{
	/*\ ����û���ť \*/
	connect(ui.m_btnAddUser, &QPushButton::clicked, this, &CFmMain::BtnAddUserClickedSlot);
	/*\ ɾ���û���ť \*/
	connect(ui.m_btnDelUser, &QPushButton::clicked, this, &CFmMain::BtnDelUserClickedSlot);
	/*\ �޸��û���Ϣ��ť \*/
	connect(ui.m_btnChangeUser, &QPushButton::clicked, this, &CFmMain::BtnChangeUserClickedSlot);
	/*\ ͬ����ť����¼� \*/
	connect(ui.m_btnSync, &QPushButton::clicked, this, &CFmMain::BtnSyncClickedSlot);
	/*\ �󶨵�¼�ɹ����ź� \*/
	QObject::connect(&m_oHikApi, SIGNAL(MenJinLoginSucc(std::vector<SMenJinInfo>)),
		this, SLOT(ShowAllMenJinToTV(std::vector<SMenJinInfo>)), Qt::DirectConnection);
}
/****************************************!
*@brief  ��ʼ����Ա����
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
*@brief  �ͷų�Ա����
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
*@brief  ���÷�����Ϣ
*@author Jinzi
*@date   2019/10/26 11:46:09
*@param[in]
   _SvrInfo	:	������Ϣ
*@param[out]
*@return
****************************************/
void CFmMain::SetSvrInfo(SSvrInfo _SvrInfo)
{
	m_opSvrInfo = _SvrInfo;
}

/****************************************!
*@brief  �����������ȡ�û���Ϣ
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
*@brief  �ӷ����ȡ�Ž���Ϣ����ʾ
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
*@brief  ��ȡ�û���Ϣ�ص����ݴ�����
*@author Jinzi
*@date   2019/10/26 13:38:43
*@param[in]
   _opReqplay	:	��Ҫ��������ݣ����������ص����ݣ�
*@param[out]
*@return
****************************************/
void CFmMain::GetUserInfoCallBack(QNetworkReply* _opReqplay)
{
	if (_opReqplay == nullptr)
	{
		MessageBoxA(nullptr, "��������Ӧ����Ϊ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	// ������ܵ�����;��ͼƬ����imgName��
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		QJsonObject::iterator it = jsonResData.find("data");
		QJsonValueRef arrData = it.value();
		QVariantList jsonList = arrData.toArray().toVariantList();
		/*\ �жϴ洢�û���Ϣ��vector���� ��Ϊ�� ����� \*/
		if (!m_vecUserAllInfo.empty())
		{
			m_vecUserAllInfo.clear();
		}
		/*\ ���û���Ϣ�洢���� \*/
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
	/*\ ����ѯ���û���Ϣ��ʾ���ؼ��� \*/
	this->ShowAllUserToTV();
}

/****************************************!
*@brief  ��ʾ�����û���Ϣ��tableview
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
		MessageBoxA(nullptr, "��ѯ�����û���Ϣʧ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	QStandardItemModel* opModelRet = (QStandardItemModel*)ui.m_tvUserInfo->model();
	if (opModelRet != nullptr)
	{
		opModelRet->clear();
	}
	QStandardItemModel* opModel = new QStandardItemModel();

	opModel->setColumnCount(3);
	opModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("����"));
	opModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("����"));
	opModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("����"));
	/*\ ���ñ������ \*/
	ui.m_tvUserInfo->setModel(opModel);
	/*\ ��������� \*/
	ui.m_tvUserInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//�������ű��仯������Ӧ�仯
	ui.m_tvUserInfo->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	//�������ű��仯������Ӧ�仯
	ui.m_tvUserInfo->verticalHeader()->sectionResizeMode(QHeaderView::Stretch);
	/*\ ����ֻ�� \*/
	ui.m_tvUserInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	/*\ ����ѡ��Ϊѡ���� \*/
	ui.m_tvUserInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	for (int i = 0; i < m_vecUserAllInfo.size(); i++)
	{
		/*\ ���� \*/
		opModel->setItem(i, 0, new QStandardItem(m_vecUserAllInfo[i].m_qsUserCardNum.toLocal8Bit().data()));
		/*\ ���� \*/
		opModel->setItem(i, 1, new QStandardItem(m_vecUserAllInfo[i].m_qsUserJobNum.toLocal8Bit().data()));
		/*\ ���� \*/
		opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit(m_vecUserAllInfo[i].m_qsUserName.toLocal8Bit().data())));
		for (int j = 0; j < 3; j++)
		{
			//�����ַ�λ�� 
			opModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}
		//�����ַ���ɫ 
		opModel->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	}
}

/****************************************!
*@brief  ��ʾ�����Ž���Ϣ��table view
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
		MessageBoxA(nullptr, "��ѯ�����Ž���Ϣʧ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	QStandardItemModel* opModelRet = (QStandardItemModel*)ui.m_tvMenJinInfo->model();
	if (opModelRet != nullptr)
	{
		opModelRet->clear();
	}
	QStandardItemModel* opModel = new QStandardItemModel();

	opModel->setColumnCount(4);
	opModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("վ��"));
	opModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Ip"));
	opModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("��¼״̬"));
	opModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("�·�״̬"));
	/*\ ���ñ������ \*/
	ui.m_tvMenJinInfo->setModel(opModel);
	/*\ ��������� \*/
	ui.m_tvMenJinInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//�������ű��仯������Ӧ�仯
	ui.m_tvMenJinInfo->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	//�������ű��仯������Ӧ�仯
	ui.m_tvMenJinInfo->verticalHeader()->sectionResizeMode(QHeaderView::Stretch);
	/*\ ����ֻ�� \*/
	ui.m_tvMenJinInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	/*\ ����ѡ��Ϊѡ���� \*/
	ui.m_tvMenJinInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	for (int i = 0; i < m_vecMenJinInfo.size(); i++)
	{
		/*\ վ������ \*/
		opModel->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(m_vecMenJinInfo[i].m_qsMenJinName.toLocal8Bit().data())));
		/*\ Ip \*/
		opModel->setItem(i, 1, new QStandardItem(m_vecMenJinInfo[i].m_qsMenJinIp.toLocal8Bit().data()));
		/*\ �Ƿ��¼�ɹ� \*/
		if (m_vecMenJinInfo[i].m_bIsLogin)
		{
			opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("��¼�ɹ�")));
		}
		else
		{
			opModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("��¼ʧ��")));
		}
		/*\ �Ƿ��·��ɹ� \*/
		opModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit("δ�·�")));
		for (int j = 0; j < 4; j++)
		{
			//�����ַ�λ�� 
			opModel->item(i, j)->setTextAlignment(Qt::AlignCenter);
		}
		//�����ַ���ɫ 
		opModel->item(i, 0)->setForeground(QBrush(QColor(255, 0, 0)));
	}
	/*\ ���޸��û�ҳ�渳ֵ \*/
	m_fmChangeUser.SetMenJinInfo(m_vecMenJinInfo);
}

/****************************************!
*@brief  ��ȡ�Ž����ݵĴ�����
*@author Jinzi
*@date   2019/10/26 14:09:29
*@param[in]
   _opReqplay	:	���񷵻ص�����
*@param[out]
*@return
****************************************/
void CFmMain::GetMenJinInfoCallBack(QNetworkReply* _opReqplay)
{
	if (_opReqplay == nullptr)
	{
		MessageBoxA(nullptr, "��������Ӧ����Ϊ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	// ������ܵ�����;��ͼƬ����imgName��
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		QJsonObject::iterator it = jsonResData.find("data");
		QJsonValueRef arrData = it.value();
		QVariantList jsonList = arrData.toArray().toVariantList();
		/*\ �жϴ洢�û���Ϣ��vector���� ��Ϊ�� ����� \*/
		if (!m_vecMenJinInfo.empty())
		{
			m_vecMenJinInfo.clear();
		}
		/*\ ���û���Ϣ�洢���� \*/
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
	/*\ �����Ž���¼ \*/
	//CHikHandle::GetInstance()->MenJinLogin(m_vecMenJinInfo);
	/*\ ��ʾ�Ž���Ϣ \*/
	//this->ShowAllMenJinToTV();
}

/****************************************!
*@brief  ����û���ť����¼�
*@author Jinzi
*@date   2019/10/26 15:28:45
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnAddUserClickedSlot()
{
	/*\ ��������Ϣ�洢��fmAddUser�� \*/
	m_fmAddUser.SetSvrInfo(m_opSvrInfo);
	m_fmAddUser.show();
}

/****************************************!
*@brief  ɾ����ť�ĵ���¼�
*@author Jinzi
*@date   2019/10/26 17:51:16
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnDelUserClickedSlot()
{
	/*\ �ж��û���ѡ����ĸ�Ҫɾ�����û� \*/
	QModelIndexList selected = ui.m_tvUserInfo->selectionModel()->selectedRows();
	if (selected.size() == 0)
	{
		MessageBoxA(nullptr, "��ѡ��Ҫɾ�����û�", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	QJsonArray jsonArray;
	foreach(const QModelIndex & index, selected)
	{
		jsonArray.append(m_vecUserAllInfo[index.row()].m_qsUserId);
		/*\ ɾ��������Ϣ \*/
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
*@brief  ɾ���û���Ϣ�Ĵ��������������ص����ݣ�
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
		MessageBoxA(nullptr, "��������Ӧ����Ϊ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	// ������ܵ�����;��ͼƬ����imgName��
	QByteArray replyContent = _opReqplay->readAll();
	QJsonObject jsonResData = QJsonDocument::fromJson(replyContent).object();
	if (jsonResData.value("code").toInt() == 0)
	{
		/*\ �õ��û���Ϣ \*/
		this->GetUserInfo();
		MessageBoxA(nullptr, "ɾ���û��ɹ�", "��ʾ", MB_OK);
		return;
	}
	else
	{
		MessageBoxA(nullptr, "ɾ���û�ʧ��", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
}

/****************************************!
*@brief  �޸İ�ť�ĵ���¼�
*@author Jinzi
*@date   2019/10/26 18:22:18
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnChangeUserClickedSlot()
{
	/*\ �ж��û�ѡ������ĸ��û� \*/
	QModelIndexList selected = ui.m_tvUserInfo->selectionModel()->selectedRows();
	if (selected.size() > 1)
	{
		MessageBoxA(nullptr, "��ֻѡ��һ���û�", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	int iIndex = ui.m_tvUserInfo->currentIndex().row();
	if (iIndex == -1)
	{
		MessageBoxA(nullptr, "��ѡ��һ��Ҫ�޸ĵ��û�", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ ��ȴ��Ž���¼ \*/
	if (!ui.m_tvMenJinInfo->verticalHeader()->count())
	{
		MessageBoxA(nullptr, "��ȴ��Ž���¼", "��ʾ", MB_OK | MB_ICONERROR);
		return;
	}
	/*\ ����ѡ�е��û���Ϣ \*/
	m_fmChangeUser.SetChangeUserInfo(m_vecUserAllInfo[iIndex]);
	/*\ ���÷�����Ip����Ϣ \*/
	m_fmChangeUser.SetSvrInfo(m_opSvrInfo);
	/*\ ��ʾδ�޸�ǰ������ \*/
	//m_fmChangeUser.ShowAfterChangeData();
	/*\ ��ʾҳ�� \*/
	m_fmChangeUser.show();
}

/****************************************!
*@brief  ͬ����ť����¼�����Ա�·���
*@author Jinzi
*@date   2019/10/28 9:17:35
*@param[in]
*@param[out]
*@return
****************************************/
void CFmMain::BtnSyncClickedSlot()
{
	/*\ ���÷�����Ϣ \*/
	m_oHikApi.SetSvrInfo(m_opSvrInfo);
	/*\ ������Ա�·��ӿ� \*/
	std::vector<SMenJinSendDownInfo> vecMenJinSuccInfo = m_oHikApi.MenJinUserSendDown(m_vecMenJinInfo, m_vecUserAllInfo);
	/*\ ��ʾ�·����� \*/
	MessageBoxA(nullptr, "��Ա�·�����", "��ʾ", MB_OK);
}

/****************************************!
*@brief  �޸�tableview���Ž�״̬��Ϣ
*@author Jinzi
*@date   2019/10/28 16:13:05
*@param[in]
   _qsStatus	:	Ҫ��ʾ��״̬
   _iRow		:	��
   _iColum		:	��
*@param[out]
*@return
****************************************/
void CFmMain::ChangeTvMenJinStatus(QString _qsStatus, int _iRow, int _iColumn)
{
	/*QAbstractItemModel* oModel = ui.m_tvMenJinInfo->model();
	oModel->setItem(_iRow, _iColumn, new QStandardItem(QString::fromLocal8Bit(_qsStatus.toLocal8Bit().data())));*/

}

 /****************************************!
 *@brief  ������ʾ״̬��Ϣ 
 *@author Jinzi
 *@date   2019/10/29 15:19:28
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CFmMain::SetShowStatusInfo()
{

}