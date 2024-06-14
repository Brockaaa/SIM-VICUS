/********************************************************************************
** Form generated from reading UI file 'SVPreferencesPageTools.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPREFERENCESPAGETOOLS_H
#define UI_SVPREFERENCESPAGETOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVPreferencesPageTools
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QtExt::BrowseFilenameWidget *filePath7Zip;
    QPushButton *pushButtonAutoDetectDWD;
    QtExt::BrowseFilenameWidget *filePathDWDConverter;
    QLabel *label_4;
    QtExt::BrowseFilenameWidget *filepathPostProc;
    QtExt::BrowseFilenameWidget *filePathCCMEditor;
    QLabel *label_5;
    QLabel *label_2;
    QPushButton *pushButtonAutoDetectCCM;
    QPushButton *pushButtonAutoDetect7zip;
    QPushButton *pushButtonAutoDetectTextEditor;
    QPushButton *pushButtonAutoDetectPP2;
    QLabel *label_6;
    QtExt::BrowseFilenameWidget *filePathMasterSim;
    QPushButton *pushButtonAutoDetectMasterSim;
    QLabel *label_3;
    QtExt::BrowseFilenameWidget *filepathTextEditor;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVPreferencesPageTools)
    {
        if (SVPreferencesPageTools->objectName().isEmpty())
            SVPreferencesPageTools->setObjectName(QString::fromUtf8("SVPreferencesPageTools"));
        SVPreferencesPageTools->resize(600, 247);
        SVPreferencesPageTools->setMinimumSize(QSize(600, 0));
        verticalLayout = new QVBoxLayout(SVPreferencesPageTools);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(SVPreferencesPageTools);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        filePath7Zip = new QtExt::BrowseFilenameWidget(groupBox_2);
        filePath7Zip->setObjectName(QString::fromUtf8("filePath7Zip"));

        gridLayout->addWidget(filePath7Zip, 2, 1, 1, 1);

        pushButtonAutoDetectDWD = new QPushButton(groupBox_2);
        pushButtonAutoDetectDWD->setObjectName(QString::fromUtf8("pushButtonAutoDetectDWD"));

        gridLayout->addWidget(pushButtonAutoDetectDWD, 4, 2, 1, 1);

        filePathDWDConverter = new QtExt::BrowseFilenameWidget(groupBox_2);
        filePathDWDConverter->setObjectName(QString::fromUtf8("filePathDWDConverter"));

        gridLayout->addWidget(filePathDWDConverter, 4, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        filepathPostProc = new QtExt::BrowseFilenameWidget(groupBox_2);
        filepathPostProc->setObjectName(QString::fromUtf8("filepathPostProc"));
        filepathPostProc->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(filepathPostProc, 0, 1, 1, 1);

        filePathCCMEditor = new QtExt::BrowseFilenameWidget(groupBox_2);
        filePathCCMEditor->setObjectName(QString::fromUtf8("filePathCCMEditor"));

        gridLayout->addWidget(filePathCCMEditor, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pushButtonAutoDetectCCM = new QPushButton(groupBox_2);
        pushButtonAutoDetectCCM->setObjectName(QString::fromUtf8("pushButtonAutoDetectCCM"));

        gridLayout->addWidget(pushButtonAutoDetectCCM, 3, 2, 1, 1);

        pushButtonAutoDetect7zip = new QPushButton(groupBox_2);
        pushButtonAutoDetect7zip->setObjectName(QString::fromUtf8("pushButtonAutoDetect7zip"));

        gridLayout->addWidget(pushButtonAutoDetect7zip, 2, 2, 1, 1);

        pushButtonAutoDetectTextEditor = new QPushButton(groupBox_2);
        pushButtonAutoDetectTextEditor->setObjectName(QString::fromUtf8("pushButtonAutoDetectTextEditor"));

        gridLayout->addWidget(pushButtonAutoDetectTextEditor, 1, 2, 1, 1);

        pushButtonAutoDetectPP2 = new QPushButton(groupBox_2);
        pushButtonAutoDetectPP2->setObjectName(QString::fromUtf8("pushButtonAutoDetectPP2"));

        gridLayout->addWidget(pushButtonAutoDetectPP2, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        filePathMasterSim = new QtExt::BrowseFilenameWidget(groupBox_2);
        filePathMasterSim->setObjectName(QString::fromUtf8("filePathMasterSim"));

        gridLayout->addWidget(filePathMasterSim, 5, 1, 1, 1);

        pushButtonAutoDetectMasterSim = new QPushButton(groupBox_2);
        pushButtonAutoDetectMasterSim->setObjectName(QString::fromUtf8("pushButtonAutoDetectMasterSim"));

        gridLayout->addWidget(pushButtonAutoDetectMasterSim, 5, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        filepathTextEditor = new QtExt::BrowseFilenameWidget(groupBox_2);
        filepathTextEditor->setObjectName(QString::fromUtf8("filepathTextEditor"));
        filepathTextEditor->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(filepathTextEditor, 1, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(SVPreferencesPageTools);

        QMetaObject::connectSlotsByName(SVPreferencesPageTools);
    } // setupUi

    void retranslateUi(QWidget *SVPreferencesPageTools)
    {
        groupBox_2->setTitle(QCoreApplication::translate("SVPreferencesPageTools", "External tools", nullptr));
        pushButtonAutoDetectDWD->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        label_4->setText(QCoreApplication::translate("SVPreferencesPageTools", "CCM Editor:", nullptr));
        label_5->setText(QCoreApplication::translate("SVPreferencesPageTools", "MasterSim:", nullptr));
        label_2->setText(QCoreApplication::translate("SVPreferencesPageTools", "PostProc 2:", nullptr));
        pushButtonAutoDetectCCM->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        pushButtonAutoDetect7zip->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        pushButtonAutoDetectTextEditor->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        pushButtonAutoDetectPP2->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        label_6->setText(QCoreApplication::translate("SVPreferencesPageTools", "DWD Weather Converter:", nullptr));
        pushButtonAutoDetectMasterSim->setText(QCoreApplication::translate("SVPreferencesPageTools", "Auto-detect", nullptr));
        label_3->setText(QCoreApplication::translate("SVPreferencesPageTools", "7-Zip:", nullptr));
        label->setText(QCoreApplication::translate("SVPreferencesPageTools", "Text editor:", nullptr));
        (void)SVPreferencesPageTools;
    } // retranslateUi

};

namespace Ui {
    class SVPreferencesPageTools: public Ui_SVPreferencesPageTools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPREFERENCESPAGETOOLS_H
