/********************************************************************************
** Form generated from reading UI file 'SVDBNetworkFluidEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBNETWORKFLUIDEDITWIDGET_H
#define UI_SVDBNETWORKFLUIDEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBNetworkFluidEditWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QGroupBox *groupBoxModelParameters;
    QGridLayout *gridLayout_2;
    QtExt::ValidatingLineEdit *lineEditHeatCapacity;
    QtExt::ValidatingLineEdit *lineEditDensity;
    QLabel *label_4;
    QTableWidget *tableWidgetViscosity;
    QLabel *label_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonAddViscosityPoint;
    QToolButton *toolButtonRemoveViscosityPoint;
    QSpacerItem *verticalSpacer;
    QtExt::ValidatingLineEdit *lineEditThermalConductivity;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_5;

    void setupUi(QWidget *SVDBNetworkFluidEditWidget)
    {
        if (SVDBNetworkFluidEditWidget->objectName().isEmpty())
            SVDBNetworkFluidEditWidget->setObjectName(QString::fromUtf8("SVDBNetworkFluidEditWidget"));
        SVDBNetworkFluidEditWidget->resize(591, 562);
        gridLayout = new QGridLayout(SVDBNetworkFluidEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelDisplayName = new QLabel(SVDBNetworkFluidEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(labelDisplayName, 2, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBNetworkFluidEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 2, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBNetworkFluidEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonColor, 2, 2, 1, 1);

        groupBoxModelParameters = new QGroupBox(SVDBNetworkFluidEditWidget);
        groupBoxModelParameters->setObjectName(QString::fromUtf8("groupBoxModelParameters"));
        gridLayout_2 = new QGridLayout(groupBoxModelParameters);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditHeatCapacity = new QtExt::ValidatingLineEdit(groupBoxModelParameters);
        lineEditHeatCapacity->setObjectName(QString::fromUtf8("lineEditHeatCapacity"));

        gridLayout_2->addWidget(lineEditHeatCapacity, 1, 1, 1, 1);

        lineEditDensity = new QtExt::ValidatingLineEdit(groupBoxModelParameters);
        lineEditDensity->setObjectName(QString::fromUtf8("lineEditDensity"));

        gridLayout_2->addWidget(lineEditDensity, 0, 1, 1, 1);

        label_4 = new QLabel(groupBoxModelParameters);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        tableWidgetViscosity = new QTableWidget(groupBoxModelParameters);
        tableWidgetViscosity->setObjectName(QString::fromUtf8("tableWidgetViscosity"));

        gridLayout_2->addWidget(tableWidgetViscosity, 4, 0, 1, 2);

        label_3 = new QLabel(groupBoxModelParameters);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label = new QLabel(groupBoxModelParameters);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonAddViscosityPoint = new QToolButton(groupBoxModelParameters);
        toolButtonAddViscosityPoint->setObjectName(QString::fromUtf8("toolButtonAddViscosityPoint"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddViscosityPoint->setIcon(icon);

        verticalLayout_2->addWidget(toolButtonAddViscosityPoint);

        toolButtonRemoveViscosityPoint = new QToolButton(groupBoxModelParameters);
        toolButtonRemoveViscosityPoint->setObjectName(QString::fromUtf8("toolButtonRemoveViscosityPoint"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveViscosityPoint->setIcon(icon1);

        verticalLayout_2->addWidget(toolButtonRemoveViscosityPoint);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout_2, 4, 2, 1, 1);

        lineEditThermalConductivity = new QtExt::ValidatingLineEdit(groupBoxModelParameters);
        lineEditThermalConductivity->setObjectName(QString::fromUtf8("lineEditThermalConductivity"));

        gridLayout_2->addWidget(lineEditThermalConductivity, 3, 1, 1, 1);

        label_2 = new QLabel(groupBoxModelParameters);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        label_6 = new QLabel(groupBoxModelParameters);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 2, 1, 1);

        label_5 = new QLabel(groupBoxModelParameters);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 2, 1, 1);


        gridLayout->addWidget(groupBoxModelParameters, 4, 0, 1, 3);


        retranslateUi(SVDBNetworkFluidEditWidget);

        QMetaObject::connectSlotsByName(SVDBNetworkFluidEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBNetworkFluidEditWidget)
    {
        SVDBNetworkFluidEditWidget->setWindowTitle(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Name:", nullptr));
        groupBoxModelParameters->setTitle(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Fluid properties", nullptr));
        label_4->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Thermal conductivity:", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Spec. heat capacity:", nullptr));
        label->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "Density:", nullptr));
        toolButtonAddViscosityPoint->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "...", nullptr));
        toolButtonRemoveViscosityPoint->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "...", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "kg/m3", nullptr));
        label_6->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "J/kg K", nullptr));
        label_5->setText(QCoreApplication::translate("SVDBNetworkFluidEditWidget", "W/mK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBNetworkFluidEditWidget: public Ui_SVDBNetworkFluidEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBNETWORKFLUIDEDITWIDGET_H
