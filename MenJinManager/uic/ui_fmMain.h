/********************************************************************************
** Form generated from reading UI file 'fmMain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FMMAIN_H
#define UI_FMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFmMain
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QTableView *m_tvUserInfo;
    QPushButton *m_btnSync;
    QTableView *m_tvMenJinInfo;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *m_btnAddUser;
    QPushButton *m_btnChangeUser;
    QPushButton *m_btnDelUser;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1006, 642);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(41);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_tvUserInfo = new QTableView(groupBox);
        m_tvUserInfo->setObjectName(QString::fromUtf8("m_tvUserInfo"));

        horizontalLayout_3->addWidget(m_tvUserInfo);

        m_btnSync = new QPushButton(groupBox);
        m_btnSync->setObjectName(QString::fromUtf8("m_btnSync"));

        horizontalLayout_3->addWidget(m_btnSync);

        m_tvMenJinInfo = new QTableView(groupBox);
        m_tvMenJinInfo->setObjectName(QString::fromUtf8("m_tvMenJinInfo"));

        horizontalLayout_3->addWidget(m_tvMenJinInfo);


        gridLayout_3->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_btnAddUser = new QPushButton(groupBox_3);
        m_btnAddUser->setObjectName(QString::fromUtf8("m_btnAddUser"));

        gridLayout_4->addWidget(m_btnAddUser, 0, 0, 1, 1);

        m_btnChangeUser = new QPushButton(groupBox_3);
        m_btnChangeUser->setObjectName(QString::fromUtf8("m_btnChangeUser"));

        gridLayout_4->addWidget(m_btnChangeUser, 0, 1, 1, 1);

        m_btnDelUser = new QPushButton(groupBox_3);
        m_btnDelUser->setObjectName(QString::fromUtf8("m_btnDelUser"));

        gridLayout_4->addWidget(m_btnDelUser, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 3, 1, 1);

        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 1);
        gridLayout_4->setColumnStretch(2, 1);
        gridLayout_4->setColumnStretch(3, 20);

        horizontalLayout_4->addWidget(groupBox_3);


        gridLayout_3->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));

        horizontalLayout->addWidget(groupBox_4);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_3, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(11);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(12);
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_5);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 2);

        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 2);
        gridLayout_3->setRowStretch(1, 2);
        gridLayout_3->setRowStretch(2, 20);
        gridLayout_3->setRowStretch(3, 1);

        verticalLayout->addWidget(groupBox);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "\344\272\272\345\221\230\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        groupBox->setTitle(QString());
        m_btnSync->setText(QApplication::translate("MainWindow", "\345\220\214\346\255\245>>", nullptr));
        groupBox_3->setTitle(QString());
        m_btnAddUser->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        m_btnChangeUser->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        m_btnDelUser->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QString());
        groupBox_4->setTitle(QString());
        label_3->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        label_4->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\351\227\250\347\246\201\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CFmMain : public Ui_CFmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FMMAIN_H
