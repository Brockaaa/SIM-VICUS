/********************************************************************************
** Form generated from reading UI file 'SVAboutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVABOUTDIALOG_H
#define UI_SVABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVAboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *SVAboutDialog)
    {
        if (SVAboutDialog->objectName().isEmpty())
            SVAboutDialog->setObjectName(QString::fromUtf8("SVAboutDialog"));
        SVAboutDialog->resize(769, 788);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVAboutDialog->sizePolicy().hasHeightForWidth());
        SVAboutDialog->setSizePolicy(sizePolicy);
        QPalette palette;
        SVAboutDialog->setPalette(palette);
        SVAboutDialog->setAutoFillBackground(true);
        SVAboutDialog->setModal(true);
        verticalLayout = new QVBoxLayout(SVAboutDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(SVAboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 100));
        label->setMaximumSize(QSize(16777215, 100));
        label->setOpenExternalLinks(true);

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(SVAboutDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setOpenExternalLinks(true);

        verticalLayout->addWidget(textBrowser);


        retranslateUi(SVAboutDialog);

        QMetaObject::connectSlotsByName(SVAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *SVAboutDialog)
    {
        textBrowser->setHtml(QCoreApplication::translate("SVAboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic;\">Copyright 2024</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">SIM-VICUS</span> is dev"
                        "eloped by the <a href=\"https://tu-dresden.de/ibk\"><span style=\" text-decoration: underline; color:#007af4;\">Institute of Building Climatology</span></a> at the TU-Dresden.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">SIM-VICUS Website: <a href=\"\\&quot;https://sim-vicus.de\\&quot;\"><span style=\" text-decoration: underline; color:#007af4;\">https://sim-vicus.de</span></a><br />SIM-VICUS Github-Page: <a href=\"https://github.com/ghorwin/SIM-VICUS\"><span style=\" text-decoration: underline; color:#007af4;\">https://github.com/ghorwin/SIM-VICUS</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; text-decoration: underline; color:#007af4;\"><br /></p>\n"
"<p"
                        " style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Used open-source libraries:</p>\n"
"<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">\n"
"<li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">CCM</span> - <span style=\" font-style:italic;\">Climate Calculation Module</span> (CCM), implements climate data loading and calculation of solar radiation loads</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">clipper</span> - implements robust clipping calculation for two-dimensional polygons</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">RoomClipper</span> - i"
                        "mplements robust clipping and connection generation via component instances of VICUS rooms and their surfaces</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">DataIO</span> - utility lib for writing DataIO output containers (needed when profiles across wall constructions are written)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">IBK</span> - core utility library, extends c++ standard library by useful functions (so we do not need boost and other heavy libs)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">IBKMK</span> - IBK math kernel lib, low level optimized routines for efficient number crunching</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-lef"
                        "t:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">IDFReader</span> - library for IDF file parsing and data import to VICUS</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">IntegratorFramework</span> - library that includes several numerical integration libraries and provides a convenient framework to error-controlled time integration</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">ITSOL2</span> - implements ILUT preconditioner (included in IntegratorFramework, this directory contains the original sources)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">libdxfrw</span> - library to read and write DXF files in both format"
                        "s, ascii and binary form. It also has rudimentary capabilities to read DWG files</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Nandrad</span> - the NANDRAD data model library (holds the project data for the NANDRAD solver)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">QtExt</span> - Qt extension library from IBK, lots of utility functions and widgets to assist with UI development</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">QuaZIP</span> - zip-support (needed for creating FMU archives)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">qwt</span> "
                        "- plotting library/charts</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Shading</span> - implements shading factors calculation</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">SuiteSparse</span> - implements sparse direct solver KLU</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">sundials</span> - includes CVODE integrator, and GMRES and BiCGStab iterative les solvers</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">TiCPP</span> - TinyXML parser library, used for reading/writing XML files</li>\n"
"<li style=\" margin-top:0px; margin-bottom:0px; margi"
                        "n-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Vicus</span> - SIM-VICUS data model library (holds the data model for the user interface)</li>\n"
"<li style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Zeppelin</span> - graphing library (see <a href=\"https://de.wikipedia.org/wiki/Ferdinand_von_Zeppelin\"><span style=\" text-decoration: underline; color:#007af4;\">Graf Zeppelin</span></a> :-), needed to determine evaluation order of the NANDRAD model objects</li></ul></body></html>", nullptr));
        (void)SVAboutDialog;
    } // retranslateUi

};

namespace Ui {
    class SVAboutDialog: public Ui_SVAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVABOUTDIALOG_H
