/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingStructuralUnitWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGSTRUCTURALUNITWIDGET_H
#define UI_SVPROPBUILDINGSTRUCTURALUNITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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

class Ui_SVPropBuildingStructuralUnitWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetStructuralUnit;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAddStructuralUnit;
    QPushButton *pushButtonRemoveStructuralUnit;
    QPushButton *pushButtonSelect;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxSelectedRooms;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *labelSelectedStructuralUnit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonAssignStructuralUnit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonRemoveAssignment;

    void setupUi(QWidget *SVPropBuildingStructuralUnitWidget)
    {
        if (SVPropBuildingStructuralUnitWidget->objectName().isEmpty())
            SVPropBuildingStructuralUnitWidget->setObjectName(QString::fromUtf8("SVPropBuildingStructuralUnitWidget"));
        SVPropBuildingStructuralUnitWidget->resize(537, 645);
        verticalLayout = new QVBoxLayout(SVPropBuildingStructuralUnitWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidgetStructuralUnit = new QTableWidget(SVPropBuildingStructuralUnitWidget);
        tableWidgetStructuralUnit->setObjectName(QString::fromUtf8("tableWidgetStructuralUnit"));

        verticalLayout->addWidget(tableWidgetStructuralUnit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonAddStructuralUnit = new QPushButton(SVPropBuildingStructuralUnitWidget);
        pushButtonAddStructuralUnit->setObjectName(QString::fromUtf8("pushButtonAddStructuralUnit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddStructuralUnit->setIcon(icon);

        horizontalLayout_4->addWidget(pushButtonAddStructuralUnit);

        pushButtonRemoveStructuralUnit = new QPushButton(SVPropBuildingStructuralUnitWidget);
        pushButtonRemoveStructuralUnit->setObjectName(QString::fromUtf8("pushButtonRemoveStructuralUnit"));
        pushButtonRemoveStructuralUnit->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemoveStructuralUnit->setIcon(icon1);

        horizontalLayout_4->addWidget(pushButtonRemoveStructuralUnit);

        pushButtonSelect = new QPushButton(SVPropBuildingStructuralUnitWidget);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));
        pushButtonSelect->setEnabled(false);

        horizontalLayout_4->addWidget(pushButtonSelect);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        groupBoxSelectedRooms = new QGroupBox(SVPropBuildingStructuralUnitWidget);
        groupBoxSelectedRooms->setObjectName(QString::fromUtf8("groupBoxSelectedRooms"));
        verticalLayout_2 = new QVBoxLayout(groupBoxSelectedRooms);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBoxSelectedRooms);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        labelSelectedStructuralUnit = new QLabel(groupBoxSelectedRooms);
        labelSelectedStructuralUnit->setObjectName(QString::fromUtf8("labelSelectedStructuralUnit"));

        horizontalLayout->addWidget(labelSelectedStructuralUnit);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonAssignStructuralUnit = new QPushButton(groupBoxSelectedRooms);
        pushButtonAssignStructuralUnit->setObjectName(QString::fromUtf8("pushButtonAssignStructuralUnit"));

        horizontalLayout_2->addWidget(pushButtonAssignStructuralUnit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonRemoveAssignment = new QPushButton(groupBoxSelectedRooms);
        pushButtonRemoveAssignment->setObjectName(QString::fromUtf8("pushButtonRemoveAssignment"));

        horizontalLayout_2->addWidget(pushButtonRemoveAssignment);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBoxSelectedRooms);


        retranslateUi(SVPropBuildingStructuralUnitWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingStructuralUnitWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingStructuralUnitWidget)
    {
        SVPropBuildingStructuralUnitWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Form", nullptr));
        pushButtonAddStructuralUnit->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Add unit", nullptr));
        pushButtonRemoveStructuralUnit->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Remove unit", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Select", nullptr));
        groupBoxSelectedRooms->setTitle(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Selected rooms", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Selected structural unit:", nullptr));
        labelSelectedStructuralUnit->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "TextLabel", nullptr));
        pushButtonAssignStructuralUnit->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Assign", nullptr));
        pushButtonRemoveAssignment->setText(QCoreApplication::translate("SVPropBuildingStructuralUnitWidget", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingStructuralUnitWidget: public Ui_SVPropBuildingStructuralUnitWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGSTRUCTURALUNITWIDGET_H
