/********************************************************************************
** Form generated from reading UI file 'savesnapshotDialog.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVESNAPSHOTDIALOG_H
#define UI_SAVESNAPSHOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SSDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *outDirLineEdit;
    QPushButton *browseDir;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QLineEdit *baseNameLineEdit;
    QLabel *label_3;
    QSpinBox *counterSpinBox;
    QSpacerItem *spacerItem1;
    QCheckBox *tiledSaveCheckBox;
    QHBoxLayout *hboxLayout2;
    QCheckBox *backgroundCheckBox;
    QSpacerItem *spacerItem2;
    QLabel *label_4;
    QSpinBox *resolutionSpinBox;
    QSpacerItem *horizontalSpacer;
    QCheckBox *alllayersCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *addToRastersCheckBox;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem3;
    QPushButton *cancelButton;
    QPushButton *saveButton;

    void setupUi(QDialog *SSDialog)
    {
        if (SSDialog->objectName().isEmpty())
            SSDialog->setObjectName(QString::fromUtf8("SSDialog"));
        SSDialog->resize(616, 225);
        vboxLayout = new QVBoxLayout(SSDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(SSDialog);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        outDirLineEdit = new QLineEdit(SSDialog);
        outDirLineEdit->setObjectName(QString::fromUtf8("outDirLineEdit"));

        hboxLayout->addWidget(outDirLineEdit);

        browseDir = new QPushButton(SSDialog);
        browseDir->setObjectName(QString::fromUtf8("browseDir"));
        browseDir->setMinimumSize(QSize(20, 20));
        browseDir->setMaximumSize(QSize(20, 20));

        hboxLayout->addWidget(browseDir);

        spacerItem = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label_2 = new QLabel(SSDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout1->addWidget(label_2);

        baseNameLineEdit = new QLineEdit(SSDialog);
        baseNameLineEdit->setObjectName(QString::fromUtf8("baseNameLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(baseNameLineEdit->sizePolicy().hasHeightForWidth());
        baseNameLineEdit->setSizePolicy(sizePolicy);
        baseNameLineEdit->setMinimumSize(QSize(200, 20));

        hboxLayout1->addWidget(baseNameLineEdit);

        label_3 = new QLabel(SSDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        hboxLayout1->addWidget(label_3);

        counterSpinBox = new QSpinBox(SSDialog);
        counterSpinBox->setObjectName(QString::fromUtf8("counterSpinBox"));
        counterSpinBox->setMaximum(999);

        hboxLayout1->addWidget(counterSpinBox);

        spacerItem1 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        tiledSaveCheckBox = new QCheckBox(SSDialog);
        tiledSaveCheckBox->setObjectName(QString::fromUtf8("tiledSaveCheckBox"));

        hboxLayout1->addWidget(tiledSaveCheckBox);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        backgroundCheckBox = new QCheckBox(SSDialog);
        backgroundCheckBox->setObjectName(QString::fromUtf8("backgroundCheckBox"));
        backgroundCheckBox->setChecked(true);

        hboxLayout2->addWidget(backgroundCheckBox);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem2);

        label_4 = new QLabel(SSDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        hboxLayout2->addWidget(label_4);

        resolutionSpinBox = new QSpinBox(SSDialog);
        resolutionSpinBox->setObjectName(QString::fromUtf8("resolutionSpinBox"));
        resolutionSpinBox->setMinimum(1);

        hboxLayout2->addWidget(resolutionSpinBox);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(horizontalSpacer);

        alllayersCheckBox = new QCheckBox(SSDialog);
        alllayersCheckBox->setObjectName(QString::fromUtf8("alllayersCheckBox"));

        hboxLayout2->addWidget(alllayersCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(horizontalSpacer_2);

        addToRastersCheckBox = new QCheckBox(SSDialog);
        addToRastersCheckBox->setObjectName(QString::fromUtf8("addToRastersCheckBox"));

        hboxLayout2->addWidget(addToRastersCheckBox);


        vboxLayout->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        spacerItem3 = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem3);

        cancelButton = new QPushButton(SSDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMinimumSize(QSize(0, 25));
        cancelButton->setMaximumSize(QSize(16777215, 25));

        hboxLayout3->addWidget(cancelButton);

        saveButton = new QPushButton(SSDialog);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setMinimumSize(QSize(0, 25));
        saveButton->setMaximumSize(QSize(16777215, 25));
        saveButton->setDefault(true);

        hboxLayout3->addWidget(saveButton);


        vboxLayout->addLayout(hboxLayout3);


        retranslateUi(SSDialog);

        QMetaObject::connectSlotsByName(SSDialog);
    } // setupUi

    void retranslateUi(QDialog *SSDialog)
    {
        SSDialog->setWindowTitle(QApplication::translate("SSDialog", "Save snapshot", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SSDialog", "Output folder  ", 0, QApplication::UnicodeUTF8));
        browseDir->setText(QApplication::translate("SSDialog", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SSDialog", "Base name  ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SSDialog", "Counter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tiledSaveCheckBox->setToolTip(QApplication::translate("SSDialog", "If checked, save each image independently, allowing to later combine the saved images into a very very large image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tiledSaveCheckBox->setText(QApplication::translate("SSDialog", "Tiled Save", 0, QApplication::UnicodeUTF8));
        backgroundCheckBox->setText(QApplication::translate("SSDialog", "Transparent Background", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("SSDialog", "The resolution of the screenshot is the resolution of the current window multiplied by this number", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("SSDialog", "Screen Multiplier  ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resolutionSpinBox->setToolTip(QApplication::translate("SSDialog", "The resolution of the screenshot is the resolution of the current window multiplied by this number", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alllayersCheckBox->setText(QApplication::translate("SSDialog", "Snap All Layers", 0, QApplication::UnicodeUTF8));
        addToRastersCheckBox->setText(QApplication::translate("SSDialog", "Add Snapshot as new Raster Layer", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("SSDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("SSDialog", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SSDialog: public Ui_SSDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVESNAPSHOTDIALOG_H
