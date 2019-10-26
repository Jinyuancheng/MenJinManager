/********************************************************************************
** Form generated from reading UI file 'fmAddUser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FMADDUSER_H
#define UI_FMADDUSER_H

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

class Ui_CFmAddUser
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QPushButton *m_btnOk;
    QPushButton *m_btnQuit;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *m_editCardNum;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *m_editJobNum;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *m_editName;
    QGroupBox *groupBox_3;
    QPushButton *m_btnPicPath;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *m_lbPic;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(502, 263);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        m_btnOk = new QPushButton(groupBox_2);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        m_btnOk->setGeometry(QRect(50, 140, 81, 31));
        m_btnQuit = new QPushButton(groupBox_2);
        m_btnQuit->setObjectName(QString::fromUtf8("m_btnQuit"));
        m_btnQuit->setGeometry(QRect(153, 140, 81, 31));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(52, 32, 181, 80));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        m_editCardNum = new QLineEdit(layoutWidget);
        m_editCardNum->setObjectName(QString::fromUtf8("m_editCardNum"));

        horizontalLayout_2->addWidget(m_editCardNum);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        m_editJobNum = new QLineEdit(layoutWidget);
        m_editJobNum->setObjectName(QString::fromUtf8("m_editJobNum"));

        horizontalLayout_3->addWidget(m_editJobNum);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        m_editName = new QLineEdit(layoutWidget);
        m_editName->setObjectName(QString::fromUtf8("m_editName"));

        horizontalLayout_4->addWidget(m_editName);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        m_btnPicPath = new QPushButton(groupBox_3);
        m_btnPicPath->setObjectName(QString::fromUtf8("m_btnPicPath"));
        m_btnPicPath->setGeometry(QRect(49, 147, 75, 23));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(30, 20, 111, 111));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_lbPic = new QLabel(groupBox_4);
        m_lbPic->setObjectName(QString::fromUtf8("m_lbPic"));

        gridLayout_3->addWidget(m_lbPic, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 3);

        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 4);
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
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        m_btnOk->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        m_btnQuit->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        label->setText(QApplication::translate("MainWindow", "\345\215\241\345\217\267: ", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\267\245\345\217\267: ", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\247\223\345\220\215: ", nullptr));
        groupBox_3->setTitle(QString());
        m_btnPicPath->setText(QApplication::translate("MainWindow", "\346\265\217\350\247\210", nullptr));
        groupBox_4->setTitle(QString());
        m_lbPic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CFmAddUser : public Ui_CFmAddUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FMADDUSER_H
