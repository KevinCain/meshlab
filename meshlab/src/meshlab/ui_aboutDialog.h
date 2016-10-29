/********************************************************************************
** Form generated from reading UI file 'aboutDialog.ui'
**
** Created: Mon Oct 6 22:40:50 2014
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBoxSx;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *labelMLLogo;
    QSpacerItem *spacerItem;
    QLabel *labelMLName;
    QLabel *labelMLLink;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout2;
    QLabel *label;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *labelVCGLogo_4;
    QLabel *labelVCGDescription;
    QVBoxLayout *vboxLayout3;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem3;
    QPushButton *okButton;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->resize(808, 643);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(aboutDialog->sizePolicy().hasHeightForWidth());
        aboutDialog->setSizePolicy(sizePolicy);
        aboutDialog->setMinimumSize(QSize(0, 0));
        aboutDialog->setMaximumSize(QSize(65536, 65536));
        QIcon icon;
        icon.addFile(QString::fromUtf8(""), QSize(), QIcon::Normal, QIcon::Off);
        aboutDialog->setWindowIcon(icon);
        aboutDialog->setModal(true);
        vboxLayout = new QVBoxLayout(aboutDialog);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBoxSx = new QGroupBox(aboutDialog);
        groupBoxSx->setObjectName(QString::fromUtf8("groupBoxSx"));
        groupBoxSx->setFlat(false);
        hboxLayout = new QHBoxLayout(groupBoxSx);
        hboxLayout->setSpacing(0);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        labelMLLogo = new QLabel(groupBoxSx);
        labelMLLogo->setObjectName(QString::fromUtf8("labelMLLogo"));
        labelMLLogo->setPixmap(QPixmap(QString::fromUtf8(":/images/eye_256_splash.png")));
        labelMLLogo->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(labelMLLogo);

        spacerItem = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);

        labelMLName = new QLabel(groupBoxSx);
        labelMLName->setObjectName(QString::fromUtf8("labelMLName"));
        QFont font;
        font.setPointSize(12);
        labelMLName->setFont(font);
        labelMLName->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(labelMLName);

        labelMLLink = new QLabel(groupBoxSx);
        labelMLLink->setObjectName(QString::fromUtf8("labelMLLink"));
        labelMLLink->setAlignment(Qt::AlignCenter);
        labelMLLink->setOpenExternalLinks(true);

        vboxLayout1->addWidget(labelMLLink);

        spacerItem1 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem1);


        hboxLayout->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        label = new QLabel(groupBoxSx);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);
        label->setOpenExternalLinks(true);

        vboxLayout2->addWidget(label);


        hboxLayout->addLayout(vboxLayout2);


        vboxLayout->addWidget(groupBoxSx);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        labelVCGLogo_4 = new QLabel(aboutDialog);
        labelVCGLogo_4->setObjectName(QString::fromUtf8("labelVCGLogo_4"));
        labelVCGLogo_4->setMinimumSize(QSize(186, 150));
        labelVCGLogo_4->setPixmap(QPixmap(QString::fromUtf8(":/images/logo.png")));
        labelVCGLogo_4->setScaledContents(false);

        hboxLayout2->addWidget(labelVCGLogo_4);

        labelVCGDescription = new QLabel(aboutDialog);
        labelVCGDescription->setObjectName(QString::fromUtf8("labelVCGDescription"));
        labelVCGDescription->setOpenExternalLinks(true);

        hboxLayout2->addWidget(labelVCGDescription);


        hboxLayout1->addLayout(hboxLayout2);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout3->addItem(spacerItem2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        spacerItem3 = new QSpacerItem(2, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem3);

        okButton = new QPushButton(aboutDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout3->addWidget(okButton);


        vboxLayout3->addLayout(hboxLayout3);


        hboxLayout1->addLayout(vboxLayout3);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(aboutDialog);
        QObject::connect(okButton, SIGNAL(clicked()), aboutDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QApplication::translate("aboutDialog", "About MeshLab", 0, QApplication::UnicodeUTF8));
        groupBoxSx->setTitle(QString());
        labelMLLogo->setText(QString());
        labelMLName->setText(QString());
        labelMLLink->setText(QApplication::translate("aboutDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg'; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg'; font-size:12pt;\"><a href=\"http://meshlab.sourceforge.net\"><span style=\" text-decoration: underline; color:#0000ff;\">http://meshlab.sourceforge.net/ </span></a> </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg'; font-size:12;\">Protected by the GPL</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("aboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">General Info</span><span style=\" font-size:10pt;\"> <br />MeshLab is an extensible mesh processing system, aimed to the user assisted cleaning, filtering, editing and rendering of unstructured 3D triangular meshes. The tool found its natural use for the processing of the meshes that usually arise in 3D scanning. The system is heavily based on the VCG library (</span><a href=\"http://vcg.sf.net\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">http://vcg.sf.net</span></a><span sty"
                        "le=\" font-size:10pt;\">). <br /></span><span style=\" font-size:10pt; font-weight:600;\">References</span><span style=\" font-size:10pt;\"><br />Please, when using this tool in any academic activity, cite its use with the following reference:<br /></span><span style=\" font-size:10pt; font-style:italic;\">MeshLab<br />Visual Computing Lab - ISTI - CNR<br />http://meshlab.sourceforge.net/</span><span style=\" font-size:10pt;\"> <br /></span><span style=\" font-size:10pt; font-weight:600;\">Contacts</span><span style=\" font-size:10pt;\"><br />For bug reports, feature requests and technical issues please use the following sourceforge services.<br />\302\240\302\240\302\240 - </span><a href=\"http://sourceforge.net/forum/forum.php?forum_id=499533\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">help forum</span></a><span style=\" font-size:10pt;\"><br />\302\240\302\240\302\240 - </span><a href=\"http://sourceforge.net/tracker/?group_id=149444&amp;atid=774731\"><span style=\" font-si"
                        "ze:10pt; text-decoration: underline; color:#0000ff;\">bug report tracking system </span></a><span style=\" font-size:10pt;\"><br />\302\240\302\240\302\240 - </span><a href=\"http://sourceforge.net/tracker/?group_id=149444&amp;atid=774734\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">feature request tracking system</span></a><span style=\" font-size:10pt;\"><br />For any other general, high level, question about MeshLab\302\240 (no bug issue or feature request please) please contact: <br /></span><a href=\"mailto:p.cignoni@isti.cnr.it?subject=%5BMeshLab%5D%20Info%20request\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">Paolo Cignoni ( p.cignoni@isti.cnr.it ) </span></a><span style=\" font-size:10pt;\"><br /></span><span style=\" font-size:10pt; font-weight:600;\">Authors</span><span style=\" font-size:10pt;\"> <br /></span><span style=\" font-size:10pt; font-style:italic;\">Main Designer</span><span style=\" font-size:10pt;\">:<br />\302\240\302\240"
                        "\302\240 - Paolo Cignoni</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">Release Manager</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    - Guido Ranzuglia<br /></span><span style=\" font-size:10pt; font-style:italic;\">Stable Contributors</span><span style=\" font-size:10pt;\">:<br />\302\240\302\240\302\240 - Marco Callieri<br />\302\240\302\240\302\240 - Massimiliano Corsini<br />\302\240\302\240\302\240 - Fabio Ganovelli</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    - Nico Pietroni</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span s"
                        "tyle=\" font-size:10pt;\">    - Marco Tarini<br />The complete list of authors is available </span><a href=\"http://meshlab.sourceforge.net/wiki/index.php/Developers\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">here </span></a><span style=\" font-size:10pt;\"><br />Some of the authors of MeshLab have received financial support from various projects, acknowledged </span><a href=\"http://meshlab.sourceforge.net/wiki/index.php/Licenses#Acknowledgments\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">here </span></a><span style=\" font-size:10pt;\"><br /></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelVCGLogo_4->setText(QString());
        labelVCGDescription->setText(QApplication::translate("aboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Copyright(C) 2005-2010<br /><br />Paolo Cignoni <br /></span><a href=\"http://vcg.isti.cnr.it/%7Ecignoni\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">http://vcg.isti.cnr.it/~cignoni</span></a><span style=\" font-size:10pt;\"> <br />Visual Computing Lab <br /></span><a href=\"http://vcg.isti.cnr.it\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\"> http://vcg.isti.cnr.it</span></a><span style=\" font-size:10pt;\"><br />ISTI - Italian National Research Council<br /><"
                        "/span><a href=\"http://www.isti.cnr.it\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\"> http://www.isti.cnr.it</span></a><span style=\" font-size:10pt;\"><br /></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("aboutDialog", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
