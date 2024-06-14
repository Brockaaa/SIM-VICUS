/********************************************************************************
** Form generated from reading UI file 'SVZoneInformationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVZONEINFORMATIONDIALOG_H
#define UI_SVZONEINFORMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SVZoneInformationDialog
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidgetSurfaceList;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLabel *labelSoundprotectionTemplate;
    QLabel *labelAcousticTemplate;
    QLabel *labelZoneTemplate;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *labelBuildingType;
    QLabel *label_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QtExt::ValidatingLineEdit *lineEditHeatCapacity;
    QLabel *labelName;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_8;
    QtExt::ValidatingLineEdit *lineEditVolume;
    QtExt::ValidatingLineEdit *lineEditArea;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_6;

    void setupUi(QDialog *SVZoneInformationDialog)
    {
        if (SVZoneInformationDialog->objectName().isEmpty())
            SVZoneInformationDialog->setObjectName(QString::fromUtf8("SVZoneInformationDialog"));
        SVZoneInformationDialog->resize(1005, 537);
        gridLayout = new QGridLayout(SVZoneInformationDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidgetSurfaceList = new QTableWidget(SVZoneInformationDialog);
        tableWidgetSurfaceList->setObjectName(QString::fromUtf8("tableWidgetSurfaceList"));

        gridLayout->addWidget(tableWidgetSurfaceList, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SVZoneInformationDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(SVZoneInformationDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        labelSoundprotectionTemplate = new QLabel(groupBox_2);
        labelSoundprotectionTemplate->setObjectName(QString::fromUtf8("labelSoundprotectionTemplate"));

        gridLayout_2->addWidget(labelSoundprotectionTemplate, 2, 1, 1, 1);

        labelAcousticTemplate = new QLabel(groupBox_2);
        labelAcousticTemplate->setObjectName(QString::fromUtf8("labelAcousticTemplate"));

        gridLayout_2->addWidget(labelAcousticTemplate, 1, 1, 1, 1);

        labelZoneTemplate = new QLabel(groupBox_2);
        labelZoneTemplate->setObjectName(QString::fromUtf8("labelZoneTemplate"));

        gridLayout_2->addWidget(labelZoneTemplate, 0, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        labelBuildingType = new QLabel(groupBox_2);
        labelBuildingType->setObjectName(QString::fromUtf8("labelBuildingType"));

        gridLayout_2->addWidget(labelBuildingType, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(SVZoneInformationDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        lineEditHeatCapacity = new QtExt::ValidatingLineEdit(groupBox);
        lineEditHeatCapacity->setObjectName(QString::fromUtf8("lineEditHeatCapacity"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditHeatCapacity->sizePolicy().hasHeightForWidth());
        lineEditHeatCapacity->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lineEditHeatCapacity, 3, 1, 1, 1);

        labelName = new QLabel(groupBox);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout_3->addWidget(labelName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_8, 3, 2, 1, 1);

        lineEditVolume = new QtExt::ValidatingLineEdit(groupBox);
        lineEditVolume->setObjectName(QString::fromUtf8("lineEditVolume"));
        sizePolicy.setHeightForWidth(lineEditVolume->sizePolicy().hasHeightForWidth());
        lineEditVolume->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lineEditVolume, 2, 1, 1, 1);

        lineEditArea = new QtExt::ValidatingLineEdit(groupBox);
        lineEditArea->setObjectName(QString::fromUtf8("lineEditArea"));
        sizePolicy.setHeightForWidth(lineEditArea->sizePolicy().hasHeightForWidth());
        lineEditArea->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(lineEditArea, 1, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_11, 2, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_12, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        label_6 = new QLabel(SVZoneInformationDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);


        retranslateUi(SVZoneInformationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVZoneInformationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVZoneInformationDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVZoneInformationDialog);
    } // setupUi

    void retranslateUi(QDialog *SVZoneInformationDialog)
    {
        SVZoneInformationDialog->setWindowTitle(QCoreApplication::translate("SVZoneInformationDialog", "Room Information", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVZoneInformationDialog", "Templates", nullptr));
        label_9->setText(QCoreApplication::translate("SVZoneInformationDialog", "Acoustic sound protection template:", nullptr));
        labelSoundprotectionTemplate->setText(QCoreApplication::translate("SVZoneInformationDialog", "TextLabel", nullptr));
        labelAcousticTemplate->setText(QCoreApplication::translate("SVZoneInformationDialog", "TextLabel", nullptr));
        labelZoneTemplate->setText(QCoreApplication::translate("SVZoneInformationDialog", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("SVZoneInformationDialog", "Acoustic template:", nullptr));
        label_4->setText(QCoreApplication::translate("SVZoneInformationDialog", "Thermal zone template:", nullptr));
        labelBuildingType->setText(QCoreApplication::translate("SVZoneInformationDialog", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("SVZoneInformationDialog", "Acoustic building type:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVZoneInformationDialog", "General information", nullptr));
        label->setText(QCoreApplication::translate("SVZoneInformationDialog", "Name:", nullptr));
        labelName->setText(QCoreApplication::translate("SVZoneInformationDialog", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("SVZoneInformationDialog", "Area:", nullptr));
        label_7->setText(QCoreApplication::translate("SVZoneInformationDialog", "Extra heat capacity:", nullptr));
        label_3->setText(QCoreApplication::translate("SVZoneInformationDialog", "Volume:", nullptr));
        label_8->setText(QCoreApplication::translate("SVZoneInformationDialog", "J/K", nullptr));
        label_11->setText(QCoreApplication::translate("SVZoneInformationDialog", "m\302\263", nullptr));
        label_12->setText(QCoreApplication::translate("SVZoneInformationDialog", "m\302\262", nullptr));
        label_6->setText(QCoreApplication::translate("SVZoneInformationDialog", "Surface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVZoneInformationDialog: public Ui_SVZoneInformationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVZONEINFORMATIONDIALOG_H
