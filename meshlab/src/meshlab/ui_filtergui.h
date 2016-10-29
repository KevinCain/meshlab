/********************************************************************************
** Form generated from reading UI file 'filtergui.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERGUI_H
#define UI_FILTERGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include "additionalgui.h"

QT_BEGIN_NAMESPACE

class Ui_FilterCreatorGUI
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *nameLine;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    TreeWidgetWithMenu *paramviewer;
    QLabel *label_2;
    QLineEdit *functionLine;
    QLabel *label_4;
    CheckBoxList *category;
    QLabel *label_3;
    QComboBox *arity;
    QLabel *label_5;
    CheckBoxList *precond;
    QLabel *label_6;
    CheckBoxList *postcond;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPlainTextEdit *helpedit;
    QCheckBox *isinterr;

    void setupUi(QFrame *FilterCreatorGUI)
    {
        if (FilterCreatorGUI->objectName().isEmpty())
            FilterCreatorGUI->setObjectName(QString::fromUtf8("FilterCreatorGUI"));
        FilterCreatorGUI->resize(567, 325);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(247, 247, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(160, 160, 160, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        QBrush brush7(QColor(240, 32, 122, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        FilterCreatorGUI->setPalette(palette);
        FilterCreatorGUI->setFrameShape(QFrame::StyledPanel);
        FilterCreatorGUI->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(FilterCreatorGUI);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(FilterCreatorGUI);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        nameLine = new QLineEdit(FilterCreatorGUI);
        nameLine->setObjectName(QString::fromUtf8("nameLine"));

        gridLayout_3->addWidget(nameLine, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(FilterCreatorGUI);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        paramviewer = new TreeWidgetWithMenu(groupBox_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        paramviewer->setHeaderItem(__qtreewidgetitem);
        paramviewer->setObjectName(QString::fromUtf8("paramviewer"));

        gridLayout_2->addWidget(paramviewer, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 2, 8, 1);

        label_2 = new QLabel(FilterCreatorGUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        functionLine = new QLineEdit(FilterCreatorGUI);
        functionLine->setObjectName(QString::fromUtf8("functionLine"));

        gridLayout_3->addWidget(functionLine, 1, 1, 1, 1);

        label_4 = new QLabel(FilterCreatorGUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        category = new CheckBoxList(FilterCreatorGUI);
        category->setObjectName(QString::fromUtf8("category"));

        gridLayout_3->addWidget(category, 2, 1, 1, 1);

        label_3 = new QLabel(FilterCreatorGUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        arity = new QComboBox(FilterCreatorGUI);
        arity->setObjectName(QString::fromUtf8("arity"));

        gridLayout_3->addWidget(arity, 3, 1, 1, 1);

        label_5 = new QLabel(FilterCreatorGUI);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);

        precond = new CheckBoxList(FilterCreatorGUI);
        precond->setObjectName(QString::fromUtf8("precond"));

        gridLayout_3->addWidget(precond, 4, 1, 1, 1);

        label_6 = new QLabel(FilterCreatorGUI);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 5, 0, 1, 1);

        postcond = new CheckBoxList(FilterCreatorGUI);
        postcond->setObjectName(QString::fromUtf8("postcond"));

        gridLayout_3->addWidget(postcond, 5, 1, 1, 1);

        groupBox = new QGroupBox(FilterCreatorGUI);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        helpedit = new QPlainTextEdit(groupBox);
        helpedit->setObjectName(QString::fromUtf8("helpedit"));

        gridLayout->addWidget(helpedit, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 7, 0, 1, 2);

        isinterr = new QCheckBox(FilterCreatorGUI);
        isinterr->setObjectName(QString::fromUtf8("isinterr"));

        gridLayout_3->addWidget(isinterr, 6, 1, 1, 1);


        retranslateUi(FilterCreatorGUI);

        QMetaObject::connectSlotsByName(FilterCreatorGUI);
    } // setupUi

    void retranslateUi(QFrame *FilterCreatorGUI)
    {
        FilterCreatorGUI->setWindowTitle(QApplication::translate("FilterCreatorGUI", "Filter Editor", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FilterCreatorGUI", "Filter Name", 0, QApplication::UnicodeUTF8));
        nameLine->setText(QString());
        groupBox_2->setTitle(QApplication::translate("FilterCreatorGUI", "Parameters Viewer", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FilterCreatorGUI", "Filter JS Function ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FilterCreatorGUI", "Category", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FilterCreatorGUI", "Arity", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FilterCreatorGUI", "Pre-Conditions", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FilterCreatorGUI", "Post-Conditions", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FilterCreatorGUI", "Filter Help", 0, QApplication::UnicodeUTF8));
        isinterr->setText(QApplication::translate("FilterCreatorGUI", "Is Interruptible", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FilterCreatorGUI: public Ui_FilterCreatorGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERGUI_H
