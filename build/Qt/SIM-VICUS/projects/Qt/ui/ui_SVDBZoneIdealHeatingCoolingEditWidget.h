/********************************************************************************
** Form generated from reading UI file 'SVDBZoneIdealHeatingCoolingEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONEIDEALHEATINGCOOLINGEDITWIDGET_H
#define UI_SVDBZONEIDEALHEATINGCOOLINGEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBZoneIdealHeatingCoolingEditWidget
{
public:
    QVBoxLayout *gridLayoutMaster;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout;
    QLabel *labelConvectiveFactorUnit_3;
    QtExt::ValidatingLineEdit *lineEditCoolingLimit;
    QtExt::ValidatingLineEdit *lineEditHeatingLimit;
    QLabel *labelConvectiveFactorUnit;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBZoneIdealHeatingCoolingEditWidget)
    {
        if (SVDBZoneIdealHeatingCoolingEditWidget->objectName().isEmpty())
            SVDBZoneIdealHeatingCoolingEditWidget->setObjectName(QString::fromUtf8("SVDBZoneIdealHeatingCoolingEditWidget"));
        SVDBZoneIdealHeatingCoolingEditWidget->resize(590, 416);
        SVDBZoneIdealHeatingCoolingEditWidget->setMinimumSize(QSize(300, 0));
        gridLayoutMaster = new QVBoxLayout(SVDBZoneIdealHeatingCoolingEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelDisplayName = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        horizontalLayout_3->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBZoneIdealHeatingCoolingEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout_3->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBZoneIdealHeatingCoolingEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButtonColor);


        gridLayoutMaster->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayoutMaster->addItem(verticalSpacer_2);

        label_3 = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setWordWrap(true);

        gridLayoutMaster->addWidget(label_3);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayoutMaster->addItem(verticalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelConvectiveFactorUnit_3 = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        labelConvectiveFactorUnit_3->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_3"));

        gridLayout->addWidget(labelConvectiveFactorUnit_3, 1, 2, 1, 1);

        lineEditCoolingLimit = new QtExt::ValidatingLineEdit(SVDBZoneIdealHeatingCoolingEditWidget);
        lineEditCoolingLimit->setObjectName(QString::fromUtf8("lineEditCoolingLimit"));
        lineEditCoolingLimit->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditCoolingLimit, 1, 1, 1, 1);

        lineEditHeatingLimit = new QtExt::ValidatingLineEdit(SVDBZoneIdealHeatingCoolingEditWidget);
        lineEditHeatingLimit->setObjectName(QString::fromUtf8("lineEditHeatingLimit"));
        lineEditHeatingLimit->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditHeatingLimit, 0, 1, 1, 1);

        labelConvectiveFactorUnit = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayout->addWidget(labelConvectiveFactorUnit, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        label = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(SVDBZoneIdealHeatingCoolingEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        gridLayoutMaster->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayoutMaster->addItem(verticalSpacer);


        retranslateUi(SVDBZoneIdealHeatingCoolingEditWidget);

        QMetaObject::connectSlotsByName(SVDBZoneIdealHeatingCoolingEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBZoneIdealHeatingCoolingEditWidget)
    {
        SVDBZoneIdealHeatingCoolingEditWidget->setWindowTitle(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "Enter limits for heating and cooling power. This is needed to avoid excessive and unrealistic peaks in heating/cooling power when set points change. A value of 0 disables heating or cooling, respectively.", nullptr));
        labelConvectiveFactorUnit_3->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "W/m\302\262", nullptr));
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "W/m\302\262", nullptr));
        label->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "Max. heating limit:", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBZoneIdealHeatingCoolingEditWidget", "Max. cooling limit:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneIdealHeatingCoolingEditWidget: public Ui_SVDBZoneIdealHeatingCoolingEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONEIDEALHEATINGCOOLINGEDITWIDGET_H
