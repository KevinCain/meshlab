/********************************************************************************
** Form generated from reading UI file 'renametexture.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENAMETEXTURE_H
#define UI_RENAMETEXTURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenameTextureDialog
{
public:
    QSplitter *splitter;
    QSplitter *splitter_2;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QSplitter *splitter_4;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *newtexturename;
    QLabel *label;
    QPushButton *searchButton;

    void setupUi(QDialog *RenameTextureDialog)
    {
        if (RenameTextureDialog->objectName().isEmpty())
            RenameTextureDialog->setObjectName(QString::fromUtf8("RenameTextureDialog"));
        RenameTextureDialog->resize(473, 71);
        splitter = new QSplitter(RenameTextureDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 10, 351, 17));
        splitter->setOrientation(Qt::Horizontal);
        splitter_2 = new QSplitter(RenameTextureDialog);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(10, 10, 238, 23));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_3 = new QSplitter(RenameTextureDialog);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(10, 10, 391, 17));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(RenameTextureDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 351, 33));
        splitter_4 = new QSplitter(RenameTextureDialog);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(10, 30, 367, 23));
        splitter_4->setOrientation(Qt::Horizontal);
        okButton = new QPushButton(RenameTextureDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(390, 40, 71, 23));
        cancelButton = new QPushButton(RenameTextureDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(320, 40, 71, 23));
        newtexturename = new QLineEdit(RenameTextureDialog);
        newtexturename->setObjectName(QString::fromUtf8("newtexturename"));
        newtexturename->setGeometry(QRect(82, 10, 291, 21));
        label = new QLabel(RenameTextureDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 67, 21));
        searchButton = new QPushButton(RenameTextureDialog);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(380, 10, 81, 23));

        retranslateUi(RenameTextureDialog);
        QObject::connect(okButton, SIGNAL(clicked()), RenameTextureDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), RenameTextureDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RenameTextureDialog);
    } // setupUi

    void retranslateUi(QDialog *RenameTextureDialog)
    {
        RenameTextureDialog->setWindowTitle(QApplication::translate("RenameTextureDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("RenameTextureDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("RenameTextureDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        newtexturename->setText(QString());
        label->setText(QApplication::translate("RenameTextureDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:MS Shell Dlg; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Texture Name</p></body></html>", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("RenameTextureDialog", "Search Texture", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RenameTextureDialog: public Ui_RenameTextureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENAMETEXTURE_H
