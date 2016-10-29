/********************************************************************************
** Form generated from reading UI file 'congratsDialog.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONGRATSDIALOG_H
#define UI_CONGRATSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CongratsDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTextBrowser *congratsTextBrowser;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CongratsDialog)
    {
        if (CongratsDialog->objectName().isEmpty())
            CongratsDialog->setObjectName(QString::fromUtf8("CongratsDialog"));
        CongratsDialog->setWindowModality(Qt::ApplicationModal);
        CongratsDialog->resize(641, 449);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CongratsDialog->sizePolicy().hasHeightForWidth());
        CongratsDialog->setSizePolicy(sizePolicy);
        vboxLayout = new QVBoxLayout(CongratsDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        congratsTextBrowser = new QTextBrowser(CongratsDialog);
        congratsTextBrowser->setObjectName(QString::fromUtf8("congratsTextBrowser"));
        congratsTextBrowser->setSource(QUrl(QString::fromUtf8("qrc:/images/100mesh.html")));
        congratsTextBrowser->setOpenExternalLinks(true);

        vboxLayout->addWidget(congratsTextBrowser);

        buttonBox = new QDialogButtonBox(CongratsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(CongratsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CongratsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CongratsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CongratsDialog);
    } // setupUi

    void retranslateUi(QDialog *CongratsDialog)
    {
        CongratsDialog->setWindowTitle(QApplication::translate("CongratsDialog", "MeshLab Congratulations!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CongratsDialog: public Ui_CongratsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONGRATSDIALOG_H
