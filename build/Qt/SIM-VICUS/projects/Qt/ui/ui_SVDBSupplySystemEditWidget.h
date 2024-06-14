/********************************************************************************
** Form generated from reading UI file 'SVDBSupplySystemEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSUPPLYSYSTEMEDITWIDGET_H
#define UI_SVDBSUPPLYSYSTEMEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVDBSupplySystemEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBoxSupplyType;
    QStackedWidget *stackedWidgetSupply;
    QWidget *pageStandAlone;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QtExt::ValidatingLineEdit *lineEditMaxMassFlux;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_3;
    QtExt::ValidatingLineEdit *lineEditSupplyTemp;
    QSpacerItem *verticalSpacer;
    QWidget *pageSubNetwork;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSubNetwork;
    QToolButton *toolButtonSubNetwork;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageDatabaseFMU;
    QWidget *pageUserDefinedFMU;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QtExt::BrowseFilenameWidget *widgetBrowseFileNameSupplyFMU;
    QLabel *label_4;
    QtExt::ValidatingLineEdit *lineEditMaxMassFluxFMU;
    QLabel *label_7;
    QLabel *label_5;
    QtExt::ValidatingLineEdit *lineEditHeatingPowerFMU;
    QLabel *label_8;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVDBSupplySystemEditWidget)
    {
        if (SVDBSupplySystemEditWidget->objectName().isEmpty())
            SVDBSupplySystemEditWidget->setObjectName(QString::fromUtf8("SVDBSupplySystemEditWidget"));
        SVDBSupplySystemEditWidget->resize(607, 446);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVDBSupplySystemEditWidget->sizePolicy().hasHeightForWidth());
        SVDBSupplySystemEditWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SVDBSupplySystemEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBSupplySystemEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBSupplySystemEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBSupplySystemEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy1);
        pushButtonColor->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(pushButtonColor);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(SVDBSupplySystemEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label);

        comboBoxSupplyType = new QComboBox(groupBox);
        comboBoxSupplyType->setObjectName(QString::fromUtf8("comboBoxSupplyType"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBoxSupplyType->sizePolicy().hasHeightForWidth());
        comboBoxSupplyType->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(comboBoxSupplyType);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidgetSupply = new QStackedWidget(groupBox);
        stackedWidgetSupply->setObjectName(QString::fromUtf8("stackedWidgetSupply"));
        sizePolicy.setHeightForWidth(stackedWidgetSupply->sizePolicy().hasHeightForWidth());
        stackedWidgetSupply->setSizePolicy(sizePolicy);
        pageStandAlone = new QWidget();
        pageStandAlone->setObjectName(QString::fromUtf8("pageStandAlone"));
        gridLayout_2 = new QGridLayout(pageStandAlone);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(pageStandAlone);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditMaxMassFlux = new QtExt::ValidatingLineEdit(pageStandAlone);
        lineEditMaxMassFlux->setObjectName(QString::fromUtf8("lineEditMaxMassFlux"));

        gridLayout_2->addWidget(lineEditMaxMassFlux, 0, 1, 2, 1);

        label_9 = new QLabel(pageStandAlone);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 0, 2, 1, 1);

        label_10 = new QLabel(pageStandAlone);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 2, 2, 1);

        label_3 = new QLabel(pageStandAlone);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEditSupplyTemp = new QtExt::ValidatingLineEdit(pageStandAlone);
        lineEditSupplyTemp->setObjectName(QString::fromUtf8("lineEditSupplyTemp"));

        gridLayout_2->addWidget(lineEditSupplyTemp, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 252, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 1);

        stackedWidgetSupply->addWidget(pageStandAlone);
        pageSubNetwork = new QWidget();
        pageSubNetwork->setObjectName(QString::fromUtf8("pageSubNetwork"));
        verticalLayout_4 = new QVBoxLayout(pageSubNetwork);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEditSubNetwork = new QLineEdit(pageSubNetwork);
        lineEditSubNetwork->setObjectName(QString::fromUtf8("lineEditSubNetwork"));

        horizontalLayout_4->addWidget(lineEditSubNetwork);

        toolButtonSubNetwork = new QToolButton(pageSubNetwork);
        toolButtonSubNetwork->setObjectName(QString::fromUtf8("toolButtonSubNetwork"));

        horizontalLayout_4->addWidget(toolButtonSubNetwork);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 314, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        stackedWidgetSupply->addWidget(pageSubNetwork);
        pageDatabaseFMU = new QWidget();
        pageDatabaseFMU->setObjectName(QString::fromUtf8("pageDatabaseFMU"));
        stackedWidgetSupply->addWidget(pageDatabaseFMU);
        pageUserDefinedFMU = new QWidget();
        pageUserDefinedFMU->setObjectName(QString::fromUtf8("pageUserDefinedFMU"));
        gridLayout = new QGridLayout(pageUserDefinedFMU);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(pageUserDefinedFMU);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        widgetBrowseFileNameSupplyFMU = new QtExt::BrowseFilenameWidget(pageUserDefinedFMU);
        widgetBrowseFileNameSupplyFMU->setObjectName(QString::fromUtf8("widgetBrowseFileNameSupplyFMU"));

        gridLayout->addWidget(widgetBrowseFileNameSupplyFMU, 0, 1, 1, 2);

        label_4 = new QLabel(pageUserDefinedFMU);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineEditMaxMassFluxFMU = new QtExt::ValidatingLineEdit(pageUserDefinedFMU);
        lineEditMaxMassFluxFMU->setObjectName(QString::fromUtf8("lineEditMaxMassFluxFMU"));

        gridLayout->addWidget(lineEditMaxMassFluxFMU, 1, 1, 1, 1);

        label_7 = new QLabel(pageUserDefinedFMU);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        label_5 = new QLabel(pageUserDefinedFMU);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEditHeatingPowerFMU = new QtExt::ValidatingLineEdit(pageUserDefinedFMU);
        lineEditHeatingPowerFMU->setObjectName(QString::fromUtf8("lineEditHeatingPowerFMU"));

        gridLayout->addWidget(lineEditHeatingPowerFMU, 2, 1, 1, 1);

        label_8 = new QLabel(pageUserDefinedFMU);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 229, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 3, 1, 1, 1);

        stackedWidgetSupply->addWidget(pageUserDefinedFMU);

        verticalLayout_2->addWidget(stackedWidgetSupply);


        verticalLayout->addWidget(groupBox);


        retranslateUi(SVDBSupplySystemEditWidget);

        stackedWidgetSupply->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SVDBSupplySystemEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBSupplySystemEditWidget)
    {
        SVDBSupplySystemEditWidget->setWindowTitle(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Name:", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Supply type:", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Maximum mass flux:", nullptr));
        label_9->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "kg/s", nullptr));
        label_10->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "C", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Supply temperature:", nullptr));
        toolButtonSubNetwork->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "...", nullptr));
        label_6->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Supply FMU:", nullptr));
        label_4->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Maximum mass flux FMU:", nullptr));
        label_7->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "kg/s", nullptr));
        label_5->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "Heating power FMU:", nullptr));
        label_8->setText(QCoreApplication::translate("SVDBSupplySystemEditWidget", "kW", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBSupplySystemEditWidget: public Ui_SVDBSupplySystemEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSUPPLYSYSTEMEDITWIDGET_H
