#include "CMenJinManager.h"

CMenJinManager::CMenJinManager(QWidget *parent)
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
	this->setWindowModality(Qt::ApplicationModal);
	/*\ ���������С����ť \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ ���ô��ڱ��� \*/
	this->setWindowTitle(QString::fromLocal8Bit("��������"));
	/*\ ����edit�е�Ĭ��ֵ \*/
	ui->m_editIp->setText(QString::fromLocal8Bit("192.168.3.43"));
	ui->m_editSPort->setText(QString::fromLocal8Bit(8086));
	ui->m_editCPort->setText(QString::fromLocal8Bit(8084));
}