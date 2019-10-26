/********************************************************************************
** Form generated from reading UI file 'CMenJinManager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMENJINMANAGER_H
#define UI_CMENJINMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMenJinManagerClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *m_lbServerConfig;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *m_editIp;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *m_editSPort;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *m_editCPort;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_btnOk;
    QPushButton *m_btnQuit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMenJinManagerClass)
    {
        if (CMenJinManagerClass->objectName().isEmpty())
            CMenJinManagerClass->setObjectName(QString::fromUtf8("CMenJinManagerClass"));
        CMenJinManagerClass->resize(301, 225);
        centralWidget = new QWidget(CMenJinManagerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_lbServerConfig = new QLabel(centralWidget);
        m_lbServerConfig->setObjectName(QString::fromUtf8("m_lbServerConfig"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        m_lbServerConfig->setFont(font);
        m_lbServerConfig->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lbServerConfig);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 20, 203, 111));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_editIp = new QLineEdit(widget);
        m_editIp->setObjectName(QString::fromUtf8("m_editIp"));

        horizontalLayout->addWidget(m_editIp);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_editSPort = new QLineEdit(widget);
        m_editSPort->setObjectName(QString::fromUtf8("m_editSPort"));

        horizontalLayout_2->addWidget(m_editSPort);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        m_editCPort = new QLineEdit(widget);
        m_editCPort->setObjectName(QString::fromUtf8("m_editCPort"));

        horizontalLayout_3->addWidget(m_editCPort);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_btnOk = new QPushButton(widget);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));

        horizontalLayout_4->addWidget(m_btnOk);

        m_btnQuit = new QPushButton(widget);
        m_btnQuit->setObjectName(QString::fromUtf8("m_btnQuit"));

        horizontalLayout_4->addWidget(m_btnQuit);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 6);
        CMenJinManagerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CMenJinManagerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CMenJinManagerClass->setStatusBar(statusBar);

        retranslateUi(CMenJinManagerClass);

        QMetaObject::connectSlotsByName(CMenJinManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMenJinManagerClass)
    {
        CMenJinManagerClass->setWindowTitle(QApplication::translate("CMenJinManagerClass", "CMenJinManager", nullptr));
        m_lbServerConfig->setText(QApplication::translate("CMenJinManagerClass", "\346\234\215\345\212\241\351\205\215\347\275\256", nullptr));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("CMenJinManagerClass", "  Ip     :", nullptr));
        label_2->setText(QApplication::translate("CMenJinManagerClass", "\345\220\216\347\253\257\347\253\257\345\217\243 :", nullptr));
        label_3->setText(QApplication::translate("CMenJinManagerClass", "\345\211\215\347\253\257\347\253\257\345\217\243 :", nullptr));
        m_btnOk->setText(QApplication::translate("CMenJinManagerClass", "\347\241\256\345\256\232", nullptr));
        m_btnQuit->setText(QApplication::translate("CMenJinManagerClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMenJinManagerClass: public Ui_CMenJinManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMENJINMANAGER_H
