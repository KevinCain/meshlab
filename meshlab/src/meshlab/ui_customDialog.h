/********************************************************************************
** Form generated from reading UI file 'customDialog.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMDIALOG_H
#define UI_CUSTOMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_customDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBoxBackground;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QPushButton *pushButtonBottomBg;
    QLabel *labelBottmBg;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QPushButton *pushButtonTopBg;
    QLabel *labelTopBg;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem3;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout2;
    QHBoxLayout *hboxLayout3;
    QLabel *labelInfoType;
    QComboBox *comboBoxInfoType;
    QSpacerItem *spacerItem4;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout4;
    QPushButton *pushButtonLogArea;
    QLabel *labelLogArea;
    QSpacerItem *spacerItem6;

    void setupUi(QDialog *customDialog)
    {
        if (customDialog->objectName().isEmpty())
            customDialog->setObjectName(QString::fromUtf8("customDialog"));
        customDialog->resize(310, 152);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customDialog->sizePolicy().hasHeightForWidth());
        customDialog->setSizePolicy(sizePolicy);
        customDialog->setModal(true);
        gridLayout = new QGridLayout(customDialog);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
        gridLayout->setContentsMargins(8, 8, 8, 8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBoxBackground = new QGroupBox(customDialog);
        groupBoxBackground->setObjectName(QString::fromUtf8("groupBoxBackground"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxBackground->sizePolicy().hasHeightForWidth());
        groupBoxBackground->setSizePolicy(sizePolicy1);
        gridLayout1 = new QGridLayout(groupBoxBackground);
#ifndef Q_OS_MAC
        gridLayout1->setSpacing(6);
#endif
        gridLayout1->setContentsMargins(8, 8, 8, 8);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacerItem, 2, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        pushButtonBottomBg = new QPushButton(groupBoxBackground);
        pushButtonBottomBg->setObjectName(QString::fromUtf8("pushButtonBottomBg"));

        hboxLayout->addWidget(pushButtonBottomBg);

        labelBottmBg = new QLabel(groupBoxBackground);
        labelBottmBg->setObjectName(QString::fromUtf8("labelBottmBg"));
        sizePolicy.setHeightForWidth(labelBottmBg->sizePolicy().hasHeightForWidth());
        labelBottmBg->setSizePolicy(sizePolicy);
        labelBottmBg->setMinimumSize(QSize(16, 16));
        labelBottmBg->setFrameShape(QFrame::Box);

        hboxLayout->addWidget(labelBottmBg);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        gridLayout1->addLayout(hboxLayout, 1, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        pushButtonTopBg = new QPushButton(groupBoxBackground);
        pushButtonTopBg->setObjectName(QString::fromUtf8("pushButtonTopBg"));

        hboxLayout1->addWidget(pushButtonTopBg);

        labelTopBg = new QLabel(groupBoxBackground);
        labelTopBg->setObjectName(QString::fromUtf8("labelTopBg"));
        sizePolicy.setHeightForWidth(labelTopBg->sizePolicy().hasHeightForWidth());
        labelTopBg->setSizePolicy(sizePolicy);
        labelTopBg->setMinimumSize(QSize(16, 16));
        labelTopBg->setFrameShape(QFrame::Box);

        hboxLayout1->addWidget(labelTopBg);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);


        gridLayout1->addLayout(hboxLayout1, 0, 0, 1, 1);


        gridLayout->addWidget(groupBoxBackground, 0, 0, 1, 1);

        hboxLayout2 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout2->setSpacing(6);
#endif
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacerItem3 = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem3);

        okButton = new QPushButton(customDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout2->addWidget(okButton);

        cancelButton = new QPushButton(customDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout2->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout2, 1, 0, 1, 2);

        groupBox = new QGroupBox(customDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout2 = new QGridLayout(groupBox);
#ifndef Q_OS_MAC
        gridLayout2->setSpacing(6);
#endif
        gridLayout2->setContentsMargins(8, 8, 8, 8);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        hboxLayout3 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout3->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
#endif
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        labelInfoType = new QLabel(groupBox);
        labelInfoType->setObjectName(QString::fromUtf8("labelInfoType"));

        hboxLayout3->addWidget(labelInfoType);

        comboBoxInfoType = new QComboBox(groupBox);
        comboBoxInfoType->setObjectName(QString::fromUtf8("comboBoxInfoType"));

        hboxLayout3->addWidget(comboBoxInfoType);

        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem4);


        gridLayout2->addLayout(hboxLayout3, 1, 0, 1, 1);

        spacerItem5 = new QSpacerItem(177, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout2->addItem(spacerItem5, 2, 0, 1, 1);

        hboxLayout4 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout4->setSpacing(6);
#endif
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
        pushButtonLogArea = new QPushButton(groupBox);
        pushButtonLogArea->setObjectName(QString::fromUtf8("pushButtonLogArea"));

        hboxLayout4->addWidget(pushButtonLogArea);

        labelLogArea = new QLabel(groupBox);
        labelLogArea->setObjectName(QString::fromUtf8("labelLogArea"));
        sizePolicy.setHeightForWidth(labelLogArea->sizePolicy().hasHeightForWidth());
        labelLogArea->setSizePolicy(sizePolicy);
        labelLogArea->setMinimumSize(QSize(16, 16));
        labelLogArea->setFrameShape(QFrame::Box);
        labelLogArea->setFrameShadow(QFrame::Plain);

        hboxLayout4->addWidget(labelLogArea);

        spacerItem6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacerItem6);


        gridLayout2->addLayout(hboxLayout4, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        labelInfoType->setBuddy(comboBoxInfoType);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(pushButtonTopBg, pushButtonBottomBg);
        QWidget::setTabOrder(pushButtonBottomBg, pushButtonLogArea);
        QWidget::setTabOrder(pushButtonLogArea, comboBoxInfoType);
        QWidget::setTabOrder(comboBoxInfoType, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(customDialog);

        QMetaObject::connectSlotsByName(customDialog);
    } // setupUi

    void retranslateUi(QDialog *customDialog)
    {
        customDialog->setWindowTitle(QApplication::translate("customDialog", "MeshLab options", 0, QApplication::UnicodeUTF8));
        groupBoxBackground->setTitle(QApplication::translate("customDialog", "Background Colors", 0, QApplication::UnicodeUTF8));
        pushButtonBottomBg->setText(QApplication::translate("customDialog", "Bottom Color", 0, QApplication::UnicodeUTF8));
        labelBottmBg->setText(QString());
        pushButtonTopBg->setText(QApplication::translate("customDialog", "Top Color", 0, QApplication::UnicodeUTF8));
        labelTopBg->setText(QString());
        okButton->setText(QApplication::translate("customDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("customDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("customDialog", "Misc settings", 0, QApplication::UnicodeUTF8));
        labelInfoType->setText(QApplication::translate("customDialog", "Info type", 0, QApplication::UnicodeUTF8));
        pushButtonLogArea->setText(QApplication::translate("customDialog", "Info Area", 0, QApplication::UnicodeUTF8));
        labelLogArea->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class customDialog: public Ui_customDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMDIALOG_H
