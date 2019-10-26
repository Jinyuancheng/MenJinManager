#include "CMenJinManager.h"

CMenJinManager::CMenJinManager(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	/*\ 初始化控件样式 \*/
	this->InitControlStyle();
}

 /****************************************!
 *@brief  初始化控件样式
 *@author Jinzi
 *@date   2019/10/26 8:53:07
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CMenJinManager::InitControlStyle()
{
	/*\ 设置当前窗口后面的窗口不能点击 \*/
	this->setWindowModality(Qt::ApplicationModal);
	/*\ 隐藏最大化最小化按钮 \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("服务配置"));
	/*\ 设置edit中的默认值 \*/
	ui->m_editIp->setText(QString::fromLocal8Bit("192.168.3.43"));
	ui->m_editSPort->setText(QString::fromLocal8Bit(8086));
	ui->m_editCPort->setText(QString::fromLocal8Bit(8084));
}