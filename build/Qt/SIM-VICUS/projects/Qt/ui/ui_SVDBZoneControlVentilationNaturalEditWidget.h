/********************************************************************************
** Form generated from reading UI file 'SVDBZoneControlVentilationNaturalEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONECONTROLVENTILATIONNATURALEDITWIDGET_H
#define UI_SVDBZONECONTROLVENTILATIONNATURALEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBZoneControlVentilationNaturalEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QLabel *labelTemperatureAirRoomMaximum;
    QtExt::ValidatingLineEdit *lineEditTemperatureAirRoomMaximum;
    QLabel *labelConvectiveFactorUnit;
    QLabel *labelConvectiveFactorUnit_11;
    QLabel *labelConvectiveFactorUnit_2;
    QLabel *labelTemperatureAirRoomMinimum;
    QtExt::ValidatingLineEdit *lineEditTemperatureAirRoomMinimum;
    QtExt::ValidatingLineEdit *lineEditWindSpeedMax;
    QtExt::ValidatingLineEdit *lineEditMaximumAirChangeRateComfort;
    QLabel *labelWindSpeedMax;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QSpacerItem *verticalSpacer;
    QLabel *labelMaximumAirChangeRateComfort;
    QLabel *labelConvectiveFactorUnit_12;

    void setupUi(QWidget *SVDBZoneControlVentilationNaturalEditWidget)
    {
        if (SVDBZoneControlVentilationNaturalEditWidget->objectName().isEmpty())
            SVDBZoneControlVentilationNaturalEditWidget->setObjectName(QString::fromUtf8("SVDBZoneControlVentilationNaturalEditWidget"));
        SVDBZoneControlVentilationNaturalEditWidget->resize(578, 408);
        gridLayoutMaster = new QGridLayout(SVDBZoneControlVentilationNaturalEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        labelTemperatureAirRoomMaximum = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelTemperatureAirRoomMaximum->setObjectName(QString::fromUtf8("labelTemperatureAirRoomMaximum"));

        gridLayoutMaster->addWidget(labelTemperatureAirRoomMaximum, 2, 0, 1, 1);

        lineEditTemperatureAirRoomMaximum = new QtExt::ValidatingLineEdit(SVDBZoneControlVentilationNaturalEditWidget);
        lineEditTemperatureAirRoomMaximum->setObjectName(QString::fromUtf8("lineEditTemperatureAirRoomMaximum"));
        lineEditTemperatureAirRoomMaximum->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditTemperatureAirRoomMaximum, 2, 1, 1, 1);

        labelConvectiveFactorUnit = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit, 1, 2, 1, 1);

        labelConvectiveFactorUnit_11 = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelConvectiveFactorUnit_11->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_11"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_11, 3, 2, 1, 1);

        labelConvectiveFactorUnit_2 = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelConvectiveFactorUnit_2->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_2"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_2, 2, 2, 1, 1);

        labelTemperatureAirRoomMinimum = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelTemperatureAirRoomMinimum->setObjectName(QString::fromUtf8("labelTemperatureAirRoomMinimum"));

        gridLayoutMaster->addWidget(labelTemperatureAirRoomMinimum, 1, 0, 1, 1);

        lineEditTemperatureAirRoomMinimum = new QtExt::ValidatingLineEdit(SVDBZoneControlVentilationNaturalEditWidget);
        lineEditTemperatureAirRoomMinimum->setObjectName(QString::fromUtf8("lineEditTemperatureAirRoomMinimum"));
        lineEditTemperatureAirRoomMinimum->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditTemperatureAirRoomMinimum, 1, 1, 1, 1);

        lineEditWindSpeedMax = new QtExt::ValidatingLineEdit(SVDBZoneControlVentilationNaturalEditWidget);
        lineEditWindSpeedMax->setObjectName(QString::fromUtf8("lineEditWindSpeedMax"));
        lineEditWindSpeedMax->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditWindSpeedMax, 3, 1, 1, 1);

        lineEditMaximumAirChangeRateComfort = new QtExt::ValidatingLineEdit(SVDBZoneControlVentilationNaturalEditWidget);
        lineEditMaximumAirChangeRateComfort->setObjectName(QString::fromUtf8("lineEditMaximumAirChangeRateComfort"));
        lineEditMaximumAirChangeRateComfort->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditMaximumAirChangeRateComfort, 5, 1, 1, 1);

        labelWindSpeedMax = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelWindSpeedMax->setObjectName(QString::fromUtf8("labelWindSpeedMax"));

        gridLayoutMaster->addWidget(labelWindSpeedMax, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBZoneControlVentilationNaturalEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBZoneControlVentilationNaturalEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButtonColor);


        gridLayoutMaster->addLayout(horizontalLayout, 0, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayoutMaster->addItem(verticalSpacer, 7, 0, 1, 1);

        labelMaximumAirChangeRateComfort = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelMaximumAirChangeRateComfort->setObjectName(QString::fromUtf8("labelMaximumAirChangeRateComfort"));

        gridLayoutMaster->addWidget(labelMaximumAirChangeRateComfort, 5, 0, 1, 1);

        labelConvectiveFactorUnit_12 = new QLabel(SVDBZoneControlVentilationNaturalEditWidget);
        labelConvectiveFactorUnit_12->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_12"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_12, 5, 2, 1, 1);


        retranslateUi(SVDBZoneControlVentilationNaturalEditWidget);

        QMetaObject::connectSlotsByName(SVDBZoneControlVentilationNaturalEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBZoneControlVentilationNaturalEditWidget)
    {
        SVDBZoneControlVentilationNaturalEditWidget->setWindowTitle(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Form", nullptr));
        labelTemperatureAirRoomMaximum->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Room air temperature maximum:", nullptr));
        lineEditTemperatureAirRoomMaximum->setText(QString());
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "C", nullptr));
        labelConvectiveFactorUnit_11->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "m/s", nullptr));
        labelConvectiveFactorUnit_2->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "C", nullptr));
        labelTemperatureAirRoomMinimum->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Room air temperature minimum:", nullptr));
        lineEditTemperatureAirRoomMinimum->setText(QString());
        lineEditWindSpeedMax->setText(QString());
        lineEditMaximumAirChangeRateComfort->setText(QString());
        labelWindSpeedMax->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Wind speed maximum:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Name:", nullptr));
        labelMaximumAirChangeRateComfort->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "Maximum air change rate comfort:", nullptr));
        labelConvectiveFactorUnit_12->setText(QCoreApplication::translate("SVDBZoneControlVentilationNaturalEditWidget", "1/h", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneControlVentilationNaturalEditWidget: public Ui_SVDBZoneControlVentilationNaturalEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONECONTROLVENTILATIONNATURALEDITWIDGET_H
