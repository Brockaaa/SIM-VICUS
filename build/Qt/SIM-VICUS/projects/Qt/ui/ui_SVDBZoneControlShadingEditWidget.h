/********************************************************************************
** Form generated from reading UI file 'SVDBZoneControlShadingEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONECONTROLSHADINGEDITWIDGET_H
#define UI_SVDBZONECONTROLSHADINGEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBZoneControlShadingEditWidget
{
public:
    QVBoxLayout *gridLayoutMaster;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelMethod;
    QComboBox *comboBoxMethod;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *labelHorizontal;
    QtExt::ValidatingLineEdit *lineEditHorizontal;
    QLabel *labelHorizontalUnit;
    QLabel *labelNorth;
    QtExt::ValidatingLineEdit *lineEditNorth;
    QLabel *labelNorthUnit;
    QLabel *labelEast;
    QtExt::ValidatingLineEdit *lineEditEast;
    QLabel *labelEastUnit;
    QLabel *labelSouth;
    QtExt::ValidatingLineEdit *lineEditSouth;
    QLabel *labelSouthUnit;
    QLabel *labelWest;
    QtExt::ValidatingLineEdit *lineEditWest;
    QLabel *labelWestUnit;
    QLabel *labelDeadBand;
    QtExt::ValidatingLineEdit *lineEditDeadBand;
    QLabel *labelDeadBandUnit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBZoneControlShadingEditWidget)
    {
        if (SVDBZoneControlShadingEditWidget->objectName().isEmpty())
            SVDBZoneControlShadingEditWidget->setObjectName(QString::fromUtf8("SVDBZoneControlShadingEditWidget"));
        SVDBZoneControlShadingEditWidget->resize(518, 711);
        gridLayoutMaster = new QVBoxLayout(SVDBZoneControlShadingEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBZoneControlShadingEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBZoneControlShadingEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBZoneControlShadingEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButtonColor);


        gridLayoutMaster->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelMethod = new QLabel(SVDBZoneControlShadingEditWidget);
        labelMethod->setObjectName(QString::fromUtf8("labelMethod"));

        horizontalLayout_2->addWidget(labelMethod);

        comboBoxMethod = new QComboBox(SVDBZoneControlShadingEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        horizontalLayout_2->addWidget(comboBoxMethod);

        horizontalLayout_2->setStretch(1, 1);

        gridLayoutMaster->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(SVDBZoneControlShadingEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelHorizontal = new QLabel(groupBox);
        labelHorizontal->setObjectName(QString::fromUtf8("labelHorizontal"));

        gridLayout->addWidget(labelHorizontal, 0, 0, 1, 1);

        lineEditHorizontal = new QtExt::ValidatingLineEdit(groupBox);
        lineEditHorizontal->setObjectName(QString::fromUtf8("lineEditHorizontal"));
        lineEditHorizontal->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditHorizontal, 0, 1, 1, 1);

        labelHorizontalUnit = new QLabel(groupBox);
        labelHorizontalUnit->setObjectName(QString::fromUtf8("labelHorizontalUnit"));

        gridLayout->addWidget(labelHorizontalUnit, 0, 2, 1, 1);

        labelNorth = new QLabel(groupBox);
        labelNorth->setObjectName(QString::fromUtf8("labelNorth"));

        gridLayout->addWidget(labelNorth, 1, 0, 1, 1);

        lineEditNorth = new QtExt::ValidatingLineEdit(groupBox);
        lineEditNorth->setObjectName(QString::fromUtf8("lineEditNorth"));
        lineEditNorth->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditNorth, 1, 1, 1, 1);

        labelNorthUnit = new QLabel(groupBox);
        labelNorthUnit->setObjectName(QString::fromUtf8("labelNorthUnit"));

        gridLayout->addWidget(labelNorthUnit, 1, 2, 1, 1);

        labelEast = new QLabel(groupBox);
        labelEast->setObjectName(QString::fromUtf8("labelEast"));

        gridLayout->addWidget(labelEast, 2, 0, 1, 1);

        lineEditEast = new QtExt::ValidatingLineEdit(groupBox);
        lineEditEast->setObjectName(QString::fromUtf8("lineEditEast"));
        lineEditEast->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditEast, 2, 1, 1, 1);

        labelEastUnit = new QLabel(groupBox);
        labelEastUnit->setObjectName(QString::fromUtf8("labelEastUnit"));

        gridLayout->addWidget(labelEastUnit, 2, 2, 1, 1);

        labelSouth = new QLabel(groupBox);
        labelSouth->setObjectName(QString::fromUtf8("labelSouth"));

        gridLayout->addWidget(labelSouth, 3, 0, 1, 1);

        lineEditSouth = new QtExt::ValidatingLineEdit(groupBox);
        lineEditSouth->setObjectName(QString::fromUtf8("lineEditSouth"));
        lineEditSouth->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditSouth, 3, 1, 1, 1);

        labelSouthUnit = new QLabel(groupBox);
        labelSouthUnit->setObjectName(QString::fromUtf8("labelSouthUnit"));

        gridLayout->addWidget(labelSouthUnit, 3, 2, 1, 1);

        labelWest = new QLabel(groupBox);
        labelWest->setObjectName(QString::fromUtf8("labelWest"));

        gridLayout->addWidget(labelWest, 4, 0, 1, 1);

        lineEditWest = new QtExt::ValidatingLineEdit(groupBox);
        lineEditWest->setObjectName(QString::fromUtf8("lineEditWest"));
        lineEditWest->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditWest, 4, 1, 1, 1);

        labelWestUnit = new QLabel(groupBox);
        labelWestUnit->setObjectName(QString::fromUtf8("labelWestUnit"));

        gridLayout->addWidget(labelWestUnit, 4, 2, 1, 1);

        labelDeadBand = new QLabel(groupBox);
        labelDeadBand->setObjectName(QString::fromUtf8("labelDeadBand"));

        gridLayout->addWidget(labelDeadBand, 5, 0, 1, 1);

        lineEditDeadBand = new QtExt::ValidatingLineEdit(groupBox);
        lineEditDeadBand->setObjectName(QString::fromUtf8("lineEditDeadBand"));
        lineEditDeadBand->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditDeadBand, 5, 1, 1, 1);

        labelDeadBandUnit = new QLabel(groupBox);
        labelDeadBandUnit->setObjectName(QString::fromUtf8("labelDeadBandUnit"));

        gridLayout->addWidget(labelDeadBandUnit, 5, 2, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        gridLayoutMaster->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayoutMaster->addItem(verticalSpacer);


        retranslateUi(SVDBZoneControlShadingEditWidget);

        QMetaObject::connectSlotsByName(SVDBZoneControlShadingEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBZoneControlShadingEditWidget)
    {
        SVDBZoneControlShadingEditWidget->setWindowTitle(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Name:", nullptr));
        labelMethod->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Method:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Global Sensor Parameters", nullptr));
        labelHorizontal->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Horizontal:", nullptr));
        labelHorizontalUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
        labelNorth->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "North:", nullptr));
        labelNorthUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
        labelEast->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "East:", nullptr));
        labelEastUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
        labelSouth->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "South:", nullptr));
        labelSouthUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
        labelWest->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "West:", nullptr));
        labelWestUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
        labelDeadBand->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "Dead Band:", nullptr));
        labelDeadBandUnit->setText(QCoreApplication::translate("SVDBZoneControlShadingEditWidget", "W/m2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneControlShadingEditWidget: public Ui_SVDBZoneControlShadingEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONECONTROLSHADINGEDITWIDGET_H
