/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingSurfaceHeatingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGSURFACEHEATINGWIDGET_H
#define UI_SVPROPBUILDINGSURFACEHEATINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingSurfaceHeatingWidget
{
public:
    QGridLayout *mainGridLayout;
    QLabel *label_6;
    QComboBox *comboBoxSurfaceHeatingComponentFilter;
    QLabel *label_8;
    QTableWidget *tableWidgetSurfaceHeating;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonRemoveSurfaceHeating;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBoxSelectedComponent2;
    QGridLayout *gridLayout_2;
    QLabel *labelSelectedCIWithActiveLayer;
    QGridLayout *gridLayout;
    QPushButton *pushButtonAssignSurfaceHeatingControlZone;
    QPushButton *pushButtonRemoveSelectedSurfaceHeating;
    QPushButton *pushButtonAssignSurfaceHeating;
    QPushButton *pushButtonSwitchControlZone;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *SVPropBuildingSurfaceHeatingWidget)
    {
        if (SVPropBuildingSurfaceHeatingWidget->objectName().isEmpty())
            SVPropBuildingSurfaceHeatingWidget->setObjectName(QString::fromUtf8("SVPropBuildingSurfaceHeatingWidget"));
        SVPropBuildingSurfaceHeatingWidget->resize(653, 532);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVPropBuildingSurfaceHeatingWidget->sizePolicy().hasHeightForWidth());
        SVPropBuildingSurfaceHeatingWidget->setSizePolicy(sizePolicy);
        mainGridLayout = new QGridLayout(SVPropBuildingSurfaceHeatingWidget);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        label_6 = new QLabel(SVPropBuildingSurfaceHeatingWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        mainGridLayout->addWidget(label_6, 0, 0, 1, 1);

        comboBoxSurfaceHeatingComponentFilter = new QComboBox(SVPropBuildingSurfaceHeatingWidget);
        comboBoxSurfaceHeatingComponentFilter->setObjectName(QString::fromUtf8("comboBoxSurfaceHeatingComponentFilter"));
        comboBoxSurfaceHeatingComponentFilter->setEditable(true);

        mainGridLayout->addWidget(comboBoxSurfaceHeatingComponentFilter, 0, 1, 1, 1);

        label_8 = new QLabel(SVPropBuildingSurfaceHeatingWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        mainGridLayout->addWidget(label_8, 1, 0, 1, 2);

        tableWidgetSurfaceHeating = new QTableWidget(SVPropBuildingSurfaceHeatingWidget);
        tableWidgetSurfaceHeating->setObjectName(QString::fromUtf8("tableWidgetSurfaceHeating"));
        tableWidgetSurfaceHeating->setSelectionMode(QAbstractItemView::ExtendedSelection);

        mainGridLayout->addWidget(tableWidgetSurfaceHeating, 2, 0, 1, 2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButtonRemoveSurfaceHeating = new QPushButton(SVPropBuildingSurfaceHeatingWidget);
        pushButtonRemoveSurfaceHeating->setObjectName(QString::fromUtf8("pushButtonRemoveSurfaceHeating"));
        pushButtonRemoveSurfaceHeating->setIconSize(QSize(24, 24));

        gridLayout_4->addWidget(pushButtonRemoveSurfaceHeating, 0, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(280, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_9, 0, 1, 1, 1);


        mainGridLayout->addLayout(gridLayout_4, 3, 0, 1, 2);

        groupBoxSelectedComponent2 = new QGroupBox(SVPropBuildingSurfaceHeatingWidget);
        groupBoxSelectedComponent2->setObjectName(QString::fromUtf8("groupBoxSelectedComponent2"));
        sizePolicy.setHeightForWidth(groupBoxSelectedComponent2->sizePolicy().hasHeightForWidth());
        groupBoxSelectedComponent2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBoxSelectedComponent2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelSelectedCIWithActiveLayer = new QLabel(groupBoxSelectedComponent2);
        labelSelectedCIWithActiveLayer->setObjectName(QString::fromUtf8("labelSelectedCIWithActiveLayer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelSelectedCIWithActiveLayer->sizePolicy().hasHeightForWidth());
        labelSelectedCIWithActiveLayer->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(labelSelectedCIWithActiveLayer, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonAssignSurfaceHeatingControlZone = new QPushButton(groupBoxSelectedComponent2);
        pushButtonAssignSurfaceHeatingControlZone->setObjectName(QString::fromUtf8("pushButtonAssignSurfaceHeatingControlZone"));
        pushButtonAssignSurfaceHeatingControlZone->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonAssignSurfaceHeatingControlZone, 0, 1, 1, 1);

        pushButtonRemoveSelectedSurfaceHeating = new QPushButton(groupBoxSelectedComponent2);
        pushButtonRemoveSelectedSurfaceHeating->setObjectName(QString::fromUtf8("pushButtonRemoveSelectedSurfaceHeating"));

        gridLayout->addWidget(pushButtonRemoveSelectedSurfaceHeating, 1, 0, 1, 1);

        pushButtonAssignSurfaceHeating = new QPushButton(groupBoxSelectedComponent2);
        pushButtonAssignSurfaceHeating->setObjectName(QString::fromUtf8("pushButtonAssignSurfaceHeating"));
        pushButtonAssignSurfaceHeating->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonAssignSurfaceHeating, 0, 0, 1, 1);

        pushButtonSwitchControlZone = new QPushButton(groupBoxSelectedComponent2);
        pushButtonSwitchControlZone->setObjectName(QString::fromUtf8("pushButtonSwitchControlZone"));

        gridLayout->addWidget(pushButtonSwitchControlZone, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 1, 1, 1);


        mainGridLayout->addWidget(groupBoxSelectedComponent2, 4, 0, 1, 2);

        mainGridLayout->setRowStretch(2, 1);

        retranslateUi(SVPropBuildingSurfaceHeatingWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingSurfaceHeatingWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingSurfaceHeatingWidget)
    {
        SVPropBuildingSurfaceHeatingWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Component filter:", nullptr));
        label_8->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Components with active layers:", nullptr));
        pushButtonRemoveSurfaceHeating->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Remove surface-heating", nullptr));
        groupBoxSelectedComponent2->setTitle(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Selected component instances with active layers", nullptr));
        labelSelectedCIWithActiveLayer->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "TextLabel", nullptr));
        pushButtonAssignSurfaceHeatingControlZone->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Set control zone...", nullptr));
        pushButtonRemoveSelectedSurfaceHeating->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Remove surface heating", nullptr));
        pushButtonAssignSurfaceHeating->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Assign surface heating...", nullptr));
        pushButtonSwitchControlZone->setText(QCoreApplication::translate("SVPropBuildingSurfaceHeatingWidget", "Switch control zone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingSurfaceHeatingWidget: public Ui_SVPropBuildingSurfaceHeatingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGSURFACEHEATINGWIDGET_H
