/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkSubStationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKSUBSTATIONWIDGET_H
#define UI_SVPROPNETWORKSUBSTATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropNetworkSubStationWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxCurrentSubNetworks;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonExchangeSubNetwork;
    QPushButton *pushButtonEditSubNetworks;
    QPushButton *pushButtonSelectNodesWithSubNetwork;
    QTableWidget *tableWidgetSubNetworks;
    QGroupBox *groupBoxSelectedSubNetwork;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QPushButton *pushButtonAssignSubNetwork;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelSelectedSubNetwork;
    QLabel *label_16;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *SVPropNetworkSubStationWidget)
    {
        if (SVPropNetworkSubStationWidget->objectName().isEmpty())
            SVPropNetworkSubStationWidget->setObjectName(QString::fromUtf8("SVPropNetworkSubStationWidget"));
        SVPropNetworkSubStationWidget->resize(590, 657);
        verticalLayout = new QVBoxLayout(SVPropNetworkSubStationWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxCurrentSubNetworks = new QGroupBox(SVPropNetworkSubStationWidget);
        groupBoxCurrentSubNetworks->setObjectName(QString::fromUtf8("groupBoxCurrentSubNetworks"));
        gridLayout_7 = new QGridLayout(groupBoxCurrentSubNetworks);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(280, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        pushButtonExchangeSubNetwork = new QPushButton(groupBoxCurrentSubNetworks);
        pushButtonExchangeSubNetwork->setObjectName(QString::fromUtf8("pushButtonExchangeSubNetwork"));
        pushButtonExchangeSubNetwork->setIconSize(QSize(24, 24));

        gridLayout_7->addWidget(pushButtonExchangeSubNetwork, 1, 1, 1, 1);

        pushButtonEditSubNetworks = new QPushButton(groupBoxCurrentSubNetworks);
        pushButtonEditSubNetworks->setObjectName(QString::fromUtf8("pushButtonEditSubNetworks"));
        pushButtonEditSubNetworks->setIconSize(QSize(24, 24));

        gridLayout_7->addWidget(pushButtonEditSubNetworks, 1, 0, 1, 1);

        pushButtonSelectNodesWithSubNetwork = new QPushButton(groupBoxCurrentSubNetworks);
        pushButtonSelectNodesWithSubNetwork->setObjectName(QString::fromUtf8("pushButtonSelectNodesWithSubNetwork"));
        pushButtonSelectNodesWithSubNetwork->setIconSize(QSize(24, 24));

        gridLayout_7->addWidget(pushButtonSelectNodesWithSubNetwork, 1, 4, 1, 1);

        tableWidgetSubNetworks = new QTableWidget(groupBoxCurrentSubNetworks);
        tableWidgetSubNetworks->setObjectName(QString::fromUtf8("tableWidgetSubNetworks"));

        gridLayout_7->addWidget(tableWidgetSubNetworks, 0, 0, 1, 5);


        verticalLayout->addWidget(groupBoxCurrentSubNetworks);

        groupBoxSelectedSubNetwork = new QGroupBox(SVPropNetworkSubStationWidget);
        groupBoxSelectedSubNetwork->setObjectName(QString::fromUtf8("groupBoxSelectedSubNetwork"));
        gridLayout_8 = new QGridLayout(groupBoxSelectedSubNetwork);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBoxSelectedSubNetwork);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        pushButtonAssignSubNetwork = new QPushButton(groupBoxSelectedSubNetwork);
        pushButtonAssignSubNetwork->setObjectName(QString::fromUtf8("pushButtonAssignSubNetwork"));
        pushButtonAssignSubNetwork->setIconSize(QSize(24, 24));

        horizontalLayout_4->addWidget(pushButtonAssignSubNetwork);

        horizontalSpacer_5 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        gridLayout_8->addLayout(horizontalLayout_4, 1, 0, 1, 2);

        labelSelectedSubNetwork = new QLabel(groupBoxSelectedSubNetwork);
        labelSelectedSubNetwork->setObjectName(QString::fromUtf8("labelSelectedSubNetwork"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedSubNetwork->sizePolicy().hasHeightForWidth());
        labelSelectedSubNetwork->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(labelSelectedSubNetwork, 0, 1, 1, 1);

        label_16 = new QLabel(groupBoxSelectedSubNetwork);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_8->addWidget(label_16, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxSelectedSubNetwork);

        verticalSpacer_4 = new QSpacerItem(20, 268, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(SVPropNetworkSubStationWidget);

        QMetaObject::connectSlotsByName(SVPropNetworkSubStationWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropNetworkSubStationWidget)
    {
        SVPropNetworkSubStationWidget->setWindowTitle(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Form", nullptr));
        groupBoxCurrentSubNetworks->setTitle(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Sub networks used in current project", nullptr));
        pushButtonExchangeSubNetwork->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Exchange...", nullptr));
        pushButtonEditSubNetworks->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Edit...", nullptr));
        pushButtonSelectNodesWithSubNetwork->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Select", nullptr));
        groupBoxSelectedSubNetwork->setTitle(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Selected sub network", nullptr));
        label->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Assign sub network:", nullptr));
        pushButtonAssignSubNetwork->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "DB...", nullptr));
        labelSelectedSubNetwork->setText(QString());
        label_16->setText(QCoreApplication::translate("SVPropNetworkSubStationWidget", "Selected:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropNetworkSubStationWidget: public Ui_SVPropNetworkSubStationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKSUBSTATIONWIDGET_H
