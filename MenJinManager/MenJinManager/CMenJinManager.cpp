#include "CMenJinManager.h"
#include <QString>

CMenJinManager::CMenJinManager(QWidget* parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	/*\ ��ʼ���ؼ���ʽ \*/
	this->InitControlStyle();
}

/****************************************!
*@brief  ��ʼ���ؼ���ʽ
*@author Jinzi
*@date   2019/10/26 8:53:07
*@param[in]
*@param[out]
*@return
****************************************/
void CMenJinManager::InitControlStyle()
{
	/*\ ���õ�ǰ���ں���Ĵ��ڲ��ܵ�� \*/
	//this->setWindowModality(Qt::ApplicationModal);
	/*\ ���������С����ť \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("��������"));
	/*\ ����edit�е�Ĭ��ֵ \*/
	ui->m_editIp->setText("192.168.3.43");
	ui->m_editSPort->setText("8086");
	ui->m_editCPort->setText("8084");
}

 /****************************************!
 *@brief  ���źźͲۺ���
 *@author Jinzi
 *@date   2019/10/26 9:05:29
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CMenJinManager::BindSignalAndSlot()
{
	/*\ ȷ�ϰ�ť�󶨲ۺ��� \*/
	connect(ui->m_btnOk, &QPushButton::clicked, this, &CMenJinManager::BtnOkClickSlotFunc);
	/*\ ȡ����ť����¼� \*/
	connect(ui->m_btnQuit, &QPushButton::clicked, this, &CMenJinManager::close);
}

 /****************************************!
 *@brief  ȷ�ϰ�ť�ۺ���
 *@author Jinzi
 *@date   2019/10/26 9:09:14
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CMenJinManager::BtnOkClickSlotFunc()
{

}