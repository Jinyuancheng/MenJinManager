#include "CMenJinManager.h"
#include <QString>

CMenJinManager::CMenJinManager(QWidget* parent)
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
	//this->setWindowModality(Qt::ApplicationModal);
	/*\ 隐藏最大化最小化按钮 \*/
	this->setWindowFlags(this->windowFlags() & ~(Qt::WindowMinMaxButtonsHint));
	/*\ 设置窗口标题 \*/
	this->setWindowTitle(QString::fromLocal8Bit("服务配置"));
	/*\ 设置edit中的默认值 \*/
	ui->m_editIp->setText("192.168.3.43");
	ui->m_editSPort->setText("8086");
	ui->m_editCPort->setText("8084");
}

 /****************************************!
 *@brief  绑定信号和槽函数
 *@author Jinzi
 *@date   2019/10/26 9:05:29
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CMenJinManager::BindSignalAndSlot()
{
	/*\ 确认按钮绑定槽函数 \*/
	connect(ui->m_btnOk, &QPushButton::clicked, this, &CMenJinManager::BtnOkClickSlotFunc);
	/*\ 取消按钮点击事件 \*/
	connect(ui->m_btnQuit, &QPushButton::clicked, this, &CMenJinManager::close);
}

 /****************************************!
 *@brief  确认按钮槽函数
 *@author Jinzi
 *@date   2019/10/26 9:09:14
 *@param[in]  
 *@param[out] 
 *@return     
 ****************************************/
void CMenJinManager::BtnOkClickSlotFunc()
{

}