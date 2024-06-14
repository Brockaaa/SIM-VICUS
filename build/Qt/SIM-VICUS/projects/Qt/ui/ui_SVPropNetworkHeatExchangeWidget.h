/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkHeatExchangeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKHEATEXCHANGEWIDGET_H
#define UI_SVPROPNETWORKHEATEXCHANGEWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropNetworkHeatExchangeWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxHeatExchange;
    QGridLayout *gridLayout_10;
    QComboBox *comboBoxZoneId;
    QComboBox *comboBoxHeatExchangeType;
    QtExt::ValidatingLineEdit *lineEditHeatFlux;
    QLabel *labelHXTransferCoefficient;
    QLabel *labelZoneId;
    QtExt::ValidatingLineEdit *lineEditHXTransferCoefficient;
    QLabel *labelHeatFlux_2;
    QtExt::ValidatingLineEdit *lineEditTemperature;
    QHBoxLayout *horizontalLayout;
    QLabel *labelHeatExchangeSpline;
    QToolButton *toolButtonHeatExchangeSpline;
    QLabel *labelHeatFlux;
    QLabel *labelTemperature;
    QLabel *labelDataFile;
    QLabel *labelHeatFlux_3;
    QLabel *labelTemperature_2;
    QLabel *labelHXTransferCoefficient_2;
    QGroupBox *groupBoxCurrentHeatExchange;
    QGridLayout *gridLayout_9;
    QTableWidget *tableWidgetHeatExchange;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *SVPropNetworkHeatExchangeWidget)
    {
        if (SVPropNetworkHeatExchangeWidget->objectName().isEmpty())
            SVPropNetworkHeatExchangeWidget->setObjectName(QString::fromUtf8("SVPropNetworkHeatExchangeWidget"));
        SVPropNetworkHeatExchangeWidget->resize(435, 521);
        verticalLayout = new QVBoxLayout(SVPropNetworkHeatExchangeWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxHeatExchange = new QGroupBox(SVPropNetworkHeatExchangeWidget);
        groupBoxHeatExchange->setObjectName(QString::fromUtf8("groupBoxHeatExchange"));
        gridLayout_10 = new QGridLayout(groupBoxHeatExchange);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        comboBoxZoneId = new QComboBox(groupBoxHeatExchange);
        comboBoxZoneId->setObjectName(QString::fromUtf8("comboBoxZoneId"));

        gridLayout_10->addWidget(comboBoxZoneId, 5, 1, 1, 1);

        comboBoxHeatExchangeType = new QComboBox(groupBoxHeatExchange);
        comboBoxHeatExchangeType->setObjectName(QString::fromUtf8("comboBoxHeatExchangeType"));

        gridLayout_10->addWidget(comboBoxHeatExchangeType, 0, 1, 1, 1);

        lineEditHeatFlux = new QtExt::ValidatingLineEdit(groupBoxHeatExchange);
        lineEditHeatFlux->setObjectName(QString::fromUtf8("lineEditHeatFlux"));

        gridLayout_10->addWidget(lineEditHeatFlux, 1, 1, 1, 1);

        labelHXTransferCoefficient = new QLabel(groupBoxHeatExchange);
        labelHXTransferCoefficient->setObjectName(QString::fromUtf8("labelHXTransferCoefficient"));

        gridLayout_10->addWidget(labelHXTransferCoefficient, 3, 0, 1, 1);

        labelZoneId = new QLabel(groupBoxHeatExchange);
        labelZoneId->setObjectName(QString::fromUtf8("labelZoneId"));

        gridLayout_10->addWidget(labelZoneId, 5, 0, 1, 1);

        lineEditHXTransferCoefficient = new QtExt::ValidatingLineEdit(groupBoxHeatExchange);
        lineEditHXTransferCoefficient->setObjectName(QString::fromUtf8("lineEditHXTransferCoefficient"));

        gridLayout_10->addWidget(lineEditHXTransferCoefficient, 3, 1, 1, 1);

        labelHeatFlux_2 = new QLabel(groupBoxHeatExchange);
        labelHeatFlux_2->setObjectName(QString::fromUtf8("labelHeatFlux_2"));

        gridLayout_10->addWidget(labelHeatFlux_2, 0, 0, 1, 1);

        lineEditTemperature = new QtExt::ValidatingLineEdit(groupBoxHeatExchange);
        lineEditTemperature->setObjectName(QString::fromUtf8("lineEditTemperature"));

        gridLayout_10->addWidget(lineEditTemperature, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelHeatExchangeSpline = new QLabel(groupBoxHeatExchange);
        labelHeatExchangeSpline->setObjectName(QString::fromUtf8("labelHeatExchangeSpline"));

        horizontalLayout->addWidget(labelHeatExchangeSpline);

        toolButtonHeatExchangeSpline = new QToolButton(groupBoxHeatExchange);
        toolButtonHeatExchangeSpline->setObjectName(QString::fromUtf8("toolButtonHeatExchangeSpline"));

        horizontalLayout->addWidget(toolButtonHeatExchangeSpline);


        gridLayout_10->addLayout(horizontalLayout, 4, 1, 1, 1);

        labelHeatFlux = new QLabel(groupBoxHeatExchange);
        labelHeatFlux->setObjectName(QString::fromUtf8("labelHeatFlux"));

        gridLayout_10->addWidget(labelHeatFlux, 1, 0, 1, 1);

        labelTemperature = new QLabel(groupBoxHeatExchange);
        labelTemperature->setObjectName(QString::fromUtf8("labelTemperature"));

        gridLayout_10->addWidget(labelTemperature, 2, 0, 1, 1);

        labelDataFile = new QLabel(groupBoxHeatExchange);
        labelDataFile->setObjectName(QString::fromUtf8("labelDataFile"));

        gridLayout_10->addWidget(labelDataFile, 4, 0, 1, 1);

        labelHeatFlux_3 = new QLabel(groupBoxHeatExchange);
        labelHeatFlux_3->setObjectName(QString::fromUtf8("labelHeatFlux_3"));

        gridLayout_10->addWidget(labelHeatFlux_3, 1, 2, 1, 1);

        labelTemperature_2 = new QLabel(groupBoxHeatExchange);
        labelTemperature_2->setObjectName(QString::fromUtf8("labelTemperature_2"));

        gridLayout_10->addWidget(labelTemperature_2, 2, 2, 1, 1);

        labelHXTransferCoefficient_2 = new QLabel(groupBoxHeatExchange);
        labelHXTransferCoefficient_2->setObjectName(QString::fromUtf8("labelHXTransferCoefficient_2"));

        gridLayout_10->addWidget(labelHXTransferCoefficient_2, 3, 2, 1, 1);


        verticalLayout->addWidget(groupBoxHeatExchange);

        groupBoxCurrentHeatExchange = new QGroupBox(SVPropNetworkHeatExchangeWidget);
        groupBoxCurrentHeatExchange->setObjectName(QString::fromUtf8("groupBoxCurrentHeatExchange"));
        gridLayout_9 = new QGridLayout(groupBoxCurrentHeatExchange);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        tableWidgetHeatExchange = new QTableWidget(groupBoxCurrentHeatExchange);
        tableWidgetHeatExchange->setObjectName(QString::fromUtf8("tableWidgetHeatExchange"));

        gridLayout_9->addWidget(tableWidgetHeatExchange, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBoxCurrentHeatExchange);

        verticalSpacer_5 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        retranslateUi(SVPropNetworkHeatExchangeWidget);

        QMetaObject::connectSlotsByName(SVPropNetworkHeatExchangeWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropNetworkHeatExchangeWidget)
    {
        SVPropNetworkHeatExchangeWidget->setWindowTitle(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Form", nullptr));
        groupBoxHeatExchange->setTitle(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Heat Exchange", nullptr));
        labelHXTransferCoefficient->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "External heat transfer coefficient:", nullptr));
        labelZoneId->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Zone Id:", nullptr));
        labelHeatFlux_2->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Type:", nullptr));
        labelHeatExchangeSpline->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "TextLabel", nullptr));
        toolButtonHeatExchangeSpline->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "...", nullptr));
        labelHeatFlux->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Heat flux:", nullptr));
        labelTemperature->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Temperature:", nullptr));
        labelDataFile->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Data spline:", nullptr));
        labelHeatFlux_3->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "W", nullptr));
        labelTemperature_2->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "C", nullptr));
        labelHXTransferCoefficient_2->setText(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "W/m\302\262K", nullptr));
        groupBoxCurrentHeatExchange->setTitle(QCoreApplication::translate("SVPropNetworkHeatExchangeWidget", "Heat Exchange Types used in current project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropNetworkHeatExchangeWidget: public Ui_SVPropNetworkHeatExchangeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKHEATEXCHANGEWIDGET_H
