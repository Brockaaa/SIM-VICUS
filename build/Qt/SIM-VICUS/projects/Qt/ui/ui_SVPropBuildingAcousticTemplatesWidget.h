/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingAcousticTemplatesWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGACOUSTICTEMPLATESWIDGET_H
#define UI_SVPROPBUILDINGACOUSTICTEMPLATESWIDGET_H

#include <QtCore/QVariant>
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

class Ui_SVPropBuildingAcousticTemplatesWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidgetAcousticTemplates;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSelect;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxSelectedRooms;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *labelSelectedAcousticTemplate;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButtonAssignAcousticTemplate;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonDeleteTemplate;

    void setupUi(QWidget *SVPropBuildingAcousticTemplatesWidget)
    {
        if (SVPropBuildingAcousticTemplatesWidget->objectName().isEmpty())
            SVPropBuildingAcousticTemplatesWidget->setObjectName(QString::fromUtf8("SVPropBuildingAcousticTemplatesWidget"));
        SVPropBuildingAcousticTemplatesWidget->resize(648, 703);
        verticalLayout_3 = new QVBoxLayout(SVPropBuildingAcousticTemplatesWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableWidgetAcousticTemplates = new QTableWidget(SVPropBuildingAcousticTemplatesWidget);
        tableWidgetAcousticTemplates->setObjectName(QString::fromUtf8("tableWidgetAcousticTemplates"));

        verticalLayout_3->addWidget(tableWidgetAcousticTemplates);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonSelect = new QPushButton(SVPropBuildingAcousticTemplatesWidget);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));
        pushButtonSelect->setEnabled(false);
        pushButtonSelect->setMinimumSize(QSize(80, 25));
        pushButtonSelect->setMaximumSize(QSize(80, 25));

        horizontalLayout->addWidget(pushButtonSelect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        groupBoxSelectedRooms = new QGroupBox(SVPropBuildingAcousticTemplatesWidget);
        groupBoxSelectedRooms->setObjectName(QString::fromUtf8("groupBoxSelectedRooms"));
        verticalLayout_4 = new QVBoxLayout(groupBoxSelectedRooms);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBoxSelectedRooms);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        labelSelectedAcousticTemplate = new QLabel(groupBoxSelectedRooms);
        labelSelectedAcousticTemplate->setObjectName(QString::fromUtf8("labelSelectedAcousticTemplate"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedAcousticTemplate->sizePolicy().hasHeightForWidth());
        labelSelectedAcousticTemplate->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(labelSelectedAcousticTemplate);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButtonAssignAcousticTemplate = new QPushButton(groupBoxSelectedRooms);
        pushButtonAssignAcousticTemplate->setObjectName(QString::fromUtf8("pushButtonAssignAcousticTemplate"));

        horizontalLayout_5->addWidget(pushButtonAssignAcousticTemplate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButtonDeleteTemplate = new QPushButton(groupBoxSelectedRooms);
        pushButtonDeleteTemplate->setObjectName(QString::fromUtf8("pushButtonDeleteTemplate"));

        horizontalLayout_5->addWidget(pushButtonDeleteTemplate);


        verticalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout_3->addWidget(groupBoxSelectedRooms);


        retranslateUi(SVPropBuildingAcousticTemplatesWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingAcousticTemplatesWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingAcousticTemplatesWidget)
    {
        SVPropBuildingAcousticTemplatesWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Form", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Select", nullptr));
        groupBoxSelectedRooms->setTitle(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Selected rooms", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Selected acoustic template:", nullptr));
        labelSelectedAcousticTemplate->setText(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "TextLabel", nullptr));
        pushButtonAssignAcousticTemplate->setText(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Assign", nullptr));
        pushButtonDeleteTemplate->setText(QCoreApplication::translate("SVPropBuildingAcousticTemplatesWidget", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingAcousticTemplatesWidget: public Ui_SVPropBuildingAcousticTemplatesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGACOUSTICTEMPLATESWIDGET_H
