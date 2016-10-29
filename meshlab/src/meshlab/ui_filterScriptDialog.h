/********************************************************************************
** Form generated from reading UI file 'filterScriptDialog.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERSCRIPTDIALOG_H
#define UI_FILTERSCRIPTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_scriptDialog
{
public:
    QGridLayout *gridLayout;
    QListWidget *scriptListWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *moveUpButton;
    QPushButton *moveDownButton;
    QPushButton *removeFilterButton;
    QPushButton *editParameterButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QPushButton *saveScriptButton;
    QPushButton *openScriptButton;
    QPushButton *clearScriptButton;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *scriptDialog)
    {
        if (scriptDialog->objectName().isEmpty())
            scriptDialog->setObjectName(QString::fromUtf8("scriptDialog"));
        scriptDialog->resize(727, 404);
        gridLayout = new QGridLayout(scriptDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scriptListWidget = new QListWidget(scriptDialog);
        scriptListWidget->setObjectName(QString::fromUtf8("scriptListWidget"));

        gridLayout->addWidget(scriptListWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        moveUpButton = new QPushButton(scriptDialog);
        moveUpButton->setObjectName(QString::fromUtf8("moveUpButton"));

        verticalLayout->addWidget(moveUpButton);

        moveDownButton = new QPushButton(scriptDialog);
        moveDownButton->setObjectName(QString::fromUtf8("moveDownButton"));

        verticalLayout->addWidget(moveDownButton);

        removeFilterButton = new QPushButton(scriptDialog);
        removeFilterButton->setObjectName(QString::fromUtf8("removeFilterButton"));

        verticalLayout->addWidget(removeFilterButton);

        editParameterButton = new QPushButton(scriptDialog);
        editParameterButton->setObjectName(QString::fromUtf8("editParameterButton"));

        verticalLayout->addWidget(editParameterButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        saveScriptButton = new QPushButton(scriptDialog);
        saveScriptButton->setObjectName(QString::fromUtf8("saveScriptButton"));

        hboxLayout->addWidget(saveScriptButton);

        openScriptButton = new QPushButton(scriptDialog);
        openScriptButton->setObjectName(QString::fromUtf8("openScriptButton"));

        hboxLayout->addWidget(openScriptButton);

        clearScriptButton = new QPushButton(scriptDialog);
        clearScriptButton->setObjectName(QString::fromUtf8("clearScriptButton"));

        hboxLayout->addWidget(clearScriptButton);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(scriptDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(scriptDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


        retranslateUi(scriptDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), scriptDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(scriptDialog);
    } // setupUi

    void retranslateUi(QDialog *scriptDialog)
    {
        scriptDialog->setWindowTitle(QApplication::translate("scriptDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        moveUpButton->setText(QApplication::translate("scriptDialog", "Move Up", 0, QApplication::UnicodeUTF8));
        moveDownButton->setText(QApplication::translate("scriptDialog", "Move Down", 0, QApplication::UnicodeUTF8));
        removeFilterButton->setText(QApplication::translate("scriptDialog", "Remove", 0, QApplication::UnicodeUTF8));
        editParameterButton->setText(QApplication::translate("scriptDialog", "Edit Parameters", 0, QApplication::UnicodeUTF8));
        saveScriptButton->setText(QApplication::translate("scriptDialog", "Save Script", 0, QApplication::UnicodeUTF8));
        openScriptButton->setText(QApplication::translate("scriptDialog", "Open Script", 0, QApplication::UnicodeUTF8));
        clearScriptButton->setText(QApplication::translate("scriptDialog", "Clear Script", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("scriptDialog", "Apply Script", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("scriptDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class scriptDialog: public Ui_scriptDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERSCRIPTDIALOG_H
