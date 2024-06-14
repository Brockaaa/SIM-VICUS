/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKEDITWIDGET_H
#define UI_SVPROPNETWORKEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ToolBox.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropNetworkEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxCurrentNetwork;
    QToolButton *toolButtonAssignToCurrent;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBoxShowAllNetworks;
    QtExt::ToolBox *toolBox;

    void setupUi(QWidget *SVPropNetworkEditWidget)
    {
        if (SVPropNetworkEditWidget->objectName().isEmpty())
            SVPropNetworkEditWidget->setObjectName(QString::fromUtf8("SVPropNetworkEditWidget"));
        SVPropNetworkEditWidget->resize(934, 894);
        verticalLayout = new QVBoxLayout(SVPropNetworkEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBoxCurrentNetwork = new QComboBox(SVPropNetworkEditWidget);
        comboBoxCurrentNetwork->setObjectName(QString::fromUtf8("comboBoxCurrentNetwork"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxCurrentNetwork->sizePolicy().hasHeightForWidth());
        comboBoxCurrentNetwork->setSizePolicy(sizePolicy);
        comboBoxCurrentNetwork->setMinimumSize(QSize(300, 30));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        comboBoxCurrentNetwork->setFont(font);
        comboBoxCurrentNetwork->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(comboBoxCurrentNetwork);

        toolButtonAssignToCurrent = new QToolButton(SVPropNetworkEditWidget);
        toolButtonAssignToCurrent->setObjectName(QString::fromUtf8("toolButtonAssignToCurrent"));
        toolButtonAssignToCurrent->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(toolButtonAssignToCurrent);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        checkBoxShowAllNetworks = new QCheckBox(SVPropNetworkEditWidget);
        checkBoxShowAllNetworks->setObjectName(QString::fromUtf8("checkBoxShowAllNetworks"));
        checkBoxShowAllNetworks->setChecked(true);

        horizontalLayout->addWidget(checkBoxShowAllNetworks);


        verticalLayout->addLayout(horizontalLayout);

        toolBox = new QtExt::ToolBox(SVPropNetworkEditWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(SVPropNetworkEditWidget);

        QMetaObject::connectSlotsByName(SVPropNetworkEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropNetworkEditWidget)
    {
        SVPropNetworkEditWidget->setWindowTitle(QCoreApplication::translate("SVPropNetworkEditWidget", "Form", nullptr));
        toolButtonAssignToCurrent->setText(QCoreApplication::translate("SVPropNetworkEditWidget", "assign ", nullptr));
        checkBoxShowAllNetworks->setText(QCoreApplication::translate("SVPropNetworkEditWidget", "show inactive networks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropNetworkEditWidget: public Ui_SVPropNetworkEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKEDITWIDGET_H
