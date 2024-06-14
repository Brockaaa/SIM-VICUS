/********************************************************************************
** Form generated from reading UI file 'SVDBAcousticBoundaryConditionEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBACOUSTICBOUNDARYCONDITIONEDITWIDGET_H
#define UI_SVDBACOUSTICBOUNDARYCONDITIONEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <SVDBAcousticBoundaryConditionTableWidget.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBAcousticBoundaryConditionEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *spinBoxLayerCount;
    QSpacerItem *horizontalSpacer_2;
    SVDBAcousticBoundaryConditionTableWidget *tableWidgetSoundAbsorptionLayers;
    QTableWidget *tableWidgetResult;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBAcousticBoundaryConditionEditWidget)
    {
        if (SVDBAcousticBoundaryConditionEditWidget->objectName().isEmpty())
            SVDBAcousticBoundaryConditionEditWidget->setObjectName(QString::fromUtf8("SVDBAcousticBoundaryConditionEditWidget"));
        SVDBAcousticBoundaryConditionEditWidget->resize(659, 1020);
        verticalLayout = new QVBoxLayout(SVDBAcousticBoundaryConditionEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBAcousticBoundaryConditionEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBAcousticBoundaryConditionEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBAcousticBoundaryConditionEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);
        pushButtonColor->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(pushButtonColor);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(SVDBAcousticBoundaryConditionEditWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label);

        spinBoxLayerCount = new QSpinBox(SVDBAcousticBoundaryConditionEditWidget);
        spinBoxLayerCount->setObjectName(QString::fromUtf8("spinBoxLayerCount"));
        spinBoxLayerCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLayerCount->setMinimum(1);
        spinBoxLayerCount->setMaximum(15);

        horizontalLayout_5->addWidget(spinBoxLayerCount);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        tableWidgetSoundAbsorptionLayers = new SVDBAcousticBoundaryConditionTableWidget(SVDBAcousticBoundaryConditionEditWidget);
        tableWidgetSoundAbsorptionLayers->setObjectName(QString::fromUtf8("tableWidgetSoundAbsorptionLayers"));

        verticalLayout->addWidget(tableWidgetSoundAbsorptionLayers);

        tableWidgetResult = new QTableWidget(SVDBAcousticBoundaryConditionEditWidget);
        tableWidgetResult->setObjectName(QString::fromUtf8("tableWidgetResult"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidgetResult->sizePolicy().hasHeightForWidth());
        tableWidgetResult->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(tableWidgetResult);

        verticalSpacer = new QSpacerItem(20, 151, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SVDBAcousticBoundaryConditionEditWidget);

        QMetaObject::connectSlotsByName(SVDBAcousticBoundaryConditionEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBAcousticBoundaryConditionEditWidget)
    {
        SVDBAcousticBoundaryConditionEditWidget->setWindowTitle(QCoreApplication::translate("SVDBAcousticBoundaryConditionEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBAcousticBoundaryConditionEditWidget", "Name:", nullptr));
        label->setText(QCoreApplication::translate("SVDBAcousticBoundaryConditionEditWidget", "Number of elements:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBAcousticBoundaryConditionEditWidget: public Ui_SVDBAcousticBoundaryConditionEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBACOUSTICBOUNDARYCONDITIONEDITWIDGET_H
