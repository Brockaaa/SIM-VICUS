/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingSoundProtectionTemplatesWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGSOUNDPROTECTIONTEMPLATESWIDGET_H
#define UI_SVPROPBUILDINGSOUNDPROTECTIONTEMPLATESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_SVPropBuildingSoundProtectionTemplatesWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBoxBuildingType;
    QTableWidget *tableWidgetAcousticTemplates;
    QHBoxLayout *horizontalLayout_2;
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

    void setupUi(QWidget *SVPropBuildingSoundProtectionTemplatesWidget)
    {
        if (SVPropBuildingSoundProtectionTemplatesWidget->objectName().isEmpty())
            SVPropBuildingSoundProtectionTemplatesWidget->setObjectName(QString::fromUtf8("SVPropBuildingSoundProtectionTemplatesWidget"));
        SVPropBuildingSoundProtectionTemplatesWidget->resize(648, 703);
        verticalLayout_3 = new QVBoxLayout(SVPropBuildingSoundProtectionTemplatesWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SVPropBuildingSoundProtectionTemplatesWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxBuildingType = new QComboBox(SVPropBuildingSoundProtectionTemplatesWidget);
        comboBoxBuildingType->setObjectName(QString::fromUtf8("comboBoxBuildingType"));

        horizontalLayout->addWidget(comboBoxBuildingType);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout);

        tableWidgetAcousticTemplates = new QTableWidget(SVPropBuildingSoundProtectionTemplatesWidget);
        tableWidgetAcousticTemplates->setObjectName(QString::fromUtf8("tableWidgetAcousticTemplates"));

        verticalLayout_3->addWidget(tableWidgetAcousticTemplates);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonSelect = new QPushButton(SVPropBuildingSoundProtectionTemplatesWidget);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));
        pushButtonSelect->setEnabled(false);
        pushButtonSelect->setMinimumSize(QSize(80, 25));
        pushButtonSelect->setMaximumSize(QSize(80, 25));

        horizontalLayout_2->addWidget(pushButtonSelect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        groupBoxSelectedRooms = new QGroupBox(SVPropBuildingSoundProtectionTemplatesWidget);
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


        retranslateUi(SVPropBuildingSoundProtectionTemplatesWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingSoundProtectionTemplatesWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingSoundProtectionTemplatesWidget)
    {
        SVPropBuildingSoundProtectionTemplatesWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Building type:", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Select", nullptr));
        groupBoxSelectedRooms->setTitle(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Selected rooms", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Selected sound protection template:", nullptr));
        labelSelectedAcousticTemplate->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "TextLabel", nullptr));
        pushButtonAssignAcousticTemplate->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Assign", nullptr));
        pushButtonDeleteTemplate->setText(QCoreApplication::translate("SVPropBuildingSoundProtectionTemplatesWidget", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingSoundProtectionTemplatesWidget: public Ui_SVPropBuildingSoundProtectionTemplatesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGSOUNDPROTECTIONTEMPLATESWIDGET_H
