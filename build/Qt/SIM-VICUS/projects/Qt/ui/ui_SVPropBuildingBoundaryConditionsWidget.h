/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingBoundaryConditionsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGBOUNDARYCONDITIONSWIDGET_H
#define UI_SVPROPBUILDINGBOUNDARYCONDITIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingBoundaryConditionsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonFromInside;
    QRadioButton *radioButtonFromOutside;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidgetBoundaryConditions;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonEditBoundaryConditions;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonSelectBoundaryConditions;

    void setupUi(QWidget *SVPropBuildingBoundaryConditionsWidget)
    {
        if (SVPropBuildingBoundaryConditionsWidget->objectName().isEmpty())
            SVPropBuildingBoundaryConditionsWidget->setObjectName(QString::fromUtf8("SVPropBuildingBoundaryConditionsWidget"));
        SVPropBuildingBoundaryConditionsWidget->resize(649, 519);
        verticalLayout = new QVBoxLayout(SVPropBuildingBoundaryConditionsWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButtonFromInside = new QRadioButton(SVPropBuildingBoundaryConditionsWidget);
        radioButtonFromInside->setObjectName(QString::fromUtf8("radioButtonFromInside"));

        horizontalLayout_2->addWidget(radioButtonFromInside);

        radioButtonFromOutside = new QRadioButton(SVPropBuildingBoundaryConditionsWidget);
        radioButtonFromOutside->setObjectName(QString::fromUtf8("radioButtonFromOutside"));

        horizontalLayout_2->addWidget(radioButtonFromOutside);

        horizontalSpacer = new QSpacerItem(448, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidgetBoundaryConditions = new QTableWidget(SVPropBuildingBoundaryConditionsWidget);
        tableWidgetBoundaryConditions->setObjectName(QString::fromUtf8("tableWidgetBoundaryConditions"));

        verticalLayout->addWidget(tableWidgetBoundaryConditions);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonEditBoundaryConditions = new QPushButton(SVPropBuildingBoundaryConditionsWidget);
        pushButtonEditBoundaryConditions->setObjectName(QString::fromUtf8("pushButtonEditBoundaryConditions"));
        pushButtonEditBoundaryConditions->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonEditBoundaryConditions);

        horizontalSpacer_4 = new QSpacerItem(452, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButtonSelectBoundaryConditions = new QPushButton(SVPropBuildingBoundaryConditionsWidget);
        pushButtonSelectBoundaryConditions->setObjectName(QString::fromUtf8("pushButtonSelectBoundaryConditions"));
        pushButtonSelectBoundaryConditions->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonSelectBoundaryConditions);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SVPropBuildingBoundaryConditionsWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingBoundaryConditionsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingBoundaryConditionsWidget)
    {
        SVPropBuildingBoundaryConditionsWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingBoundaryConditionsWidget", "Form", nullptr));
        radioButtonFromInside->setText(QCoreApplication::translate("SVPropBuildingBoundaryConditionsWidget", "view from inside", nullptr));
        radioButtonFromOutside->setText(QCoreApplication::translate("SVPropBuildingBoundaryConditionsWidget", "view from outside", nullptr));
        pushButtonEditBoundaryConditions->setText(QCoreApplication::translate("SVPropBuildingBoundaryConditionsWidget", "Edit...", nullptr));
        pushButtonSelectBoundaryConditions->setText(QCoreApplication::translate("SVPropBuildingBoundaryConditionsWidget", "Select...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingBoundaryConditionsWidget: public Ui_SVPropBuildingBoundaryConditionsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGBOUNDARYCONDITIONSWIDGET_H
