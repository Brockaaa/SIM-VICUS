/********************************************************************************
** Form generated from reading UI file 'SVLcaLccSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVLCALCCSETTINGSWIDGET_H
#define UI_SVLCALCCSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVLcaLccSettingsWidget
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tabSettings;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QLabel *label_16;
    QtExt::ValidatingLineEdit *lineEditGasConsumption;
    QLabel *label_19;
    QLabel *label_17;
    QtExt::ValidatingLineEdit *lineEditElectricityConsumption;
    QLabel *label0;
    QLabel *label_18;
    QtExt::ValidatingLineEdit *lineEditCoalConsumption;
    QLabel *label1;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_7;
    QFrame *line_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_13;
    QGridLayout *gridLayout_5;
    QLabel *label_9;
    QtExt::ValidatingLineEdit *lineEditArea;
    QLabel *label_10;
    QPushButton *pushButtonAreaDetection;
    QLabel *label;
    QSpinBox *spinBoxTimePeriod;
    QLabel *label_3;
    QFrame *line_8;
    QLabel *label_8;
    QGridLayout *gridLayout;
    QLabel *label_30;
    QtExt::BrowseFilenameWidget *filepathOekoBauDat;
    QPushButton *pushButtonImportOkoebaudat;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_6;
    QFrame *line_7;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QFrame *line_5;
    QLabel *label_4;
    QLabel *label_36;
    QLabel *label_41;
    QtExt::ValidatingLineEdit *lineEditElectricityPrice;
    QLabel *label_32;
    QLabel *label_34;
    QLabel *label_31;
    QLabel *label_33;
    QtExt::ValidatingLineEdit *lineEditPriceIncreaseGeneral;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_37;
    QFrame *line_2;
    QtExt::ValidatingLineEdit *lineEditCoalPrice;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_38;
    QLabel *label_35;
    QtExt::ValidatingLineEdit *lineEditInterestRate;
    QtExt::ValidatingLineEdit *lineEditGasPrice;
    QLabel *label_39;
    QLabel *label_42;
    QLabel *label_40;
    QSpacerItem *verticalSpacer_2;
    QtExt::ValidatingLineEdit *lineEditPriceIncreaseEnergy;
    QSpacerItem *verticalSpacer_11;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBoxCatA;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBoxA1;
    QCheckBox *checkBoxA2;
    QCheckBox *checkBoxA3;
    QCheckBox *checkBoxA4;
    QCheckBox *checkBoxA5;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBoxCatB;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBoxB1;
    QCheckBox *checkBoxB2;
    QCheckBox *checkBoxB3;
    QCheckBox *checkBoxB4;
    QCheckBox *checkBoxB5;
    QCheckBox *checkBoxB6;
    QCheckBox *checkBoxB7;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBoxCatC;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkBoxC1;
    QCheckBox *checkBoxC2;
    QCheckBox *checkBoxC3;
    QCheckBox *checkBoxC4;
    QSpacerItem *verticalSpacer_10;
    QGroupBox *groupBoxCatD;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBoxD;
    QSpacerItem *verticalSpacer_9;
    QComboBox *comboBoxCertificationSystem;
    QLabel *label_14;
    QFrame *line_15;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *verticalSpacer_8;
    QComboBox *comboBoxCalculationMode;
    QLabel *label_5;
    QGridLayout *gridLayout_15;
    QLabel *label_68;
    QLineEdit *lineEditEpdGas;
    QToolButton *toolButtonSelectGas;
    QLabel *label_69;
    QLineEdit *lineEditEpdElectricity;
    QToolButton *toolButtonSelectElectricity;
    QLabel *label_70;
    QLineEdit *lineEditEpdCoal;
    QToolButton *toolButtonSelectCoal;
    QLabel *label_11;
    QFrame *line_16;
    QPushButton *pushButtonCalculate;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *SVLcaLccSettingsWidget)
    {
        if (SVLcaLccSettingsWidget->objectName().isEmpty())
            SVLcaLccSettingsWidget->setObjectName(QString::fromUtf8("SVLcaLccSettingsWidget"));
        SVLcaLccSettingsWidget->resize(1588, 902);
        gridLayout_4 = new QGridLayout(SVLcaLccSettingsWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(9, 9, 9, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(SVLcaLccSettingsWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(false);
        tabSettings = new QWidget();
        tabSettings->setObjectName(QString::fromUtf8("tabSettings"));
        gridLayout_8 = new QGridLayout(tabSettings);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_16 = new QLabel(tabSettings);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_7->addWidget(label_16, 0, 0, 1, 1);

        lineEditGasConsumption = new QtExt::ValidatingLineEdit(tabSettings);
        lineEditGasConsumption->setObjectName(QString::fromUtf8("lineEditGasConsumption"));

        gridLayout_7->addWidget(lineEditGasConsumption, 0, 1, 1, 1);

        label_19 = new QLabel(tabSettings);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_7->addWidget(label_19, 0, 2, 1, 1);

        label_17 = new QLabel(tabSettings);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_7->addWidget(label_17, 1, 0, 1, 1);

        lineEditElectricityConsumption = new QtExt::ValidatingLineEdit(tabSettings);
        lineEditElectricityConsumption->setObjectName(QString::fromUtf8("lineEditElectricityConsumption"));

        gridLayout_7->addWidget(lineEditElectricityConsumption, 1, 1, 1, 1);

        label0 = new QLabel(tabSettings);
        label0->setObjectName(QString::fromUtf8("label0"));

        gridLayout_7->addWidget(label0, 1, 2, 1, 1);

        label_18 = new QLabel(tabSettings);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_7->addWidget(label_18, 2, 0, 1, 1);

        lineEditCoalConsumption = new QtExt::ValidatingLineEdit(tabSettings);
        lineEditCoalConsumption->setObjectName(QString::fromUtf8("lineEditCoalConsumption"));

        gridLayout_7->addWidget(lineEditCoalConsumption, 2, 1, 1, 1);

        label1 = new QLabel(tabSettings);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayout_7->addWidget(label1, 2, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 14, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 446, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_5, 15, 1, 1, 1);

        label_7 = new QLabel(tabSettings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font;
        font.setBold(false);
        label_7->setFont(font);

        gridLayout_8->addWidget(label_7, 4, 0, 1, 1);

        line_6 = new QFrame(tabSettings);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_6, 5, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(754, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_2, 10, 2, 1, 1);

        label_13 = new QLabel(tabSettings);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        gridLayout_8->addWidget(label_13, 12, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_9 = new QLabel(tabSettings);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        lineEditArea = new QtExt::ValidatingLineEdit(tabSettings);
        lineEditArea->setObjectName(QString::fromUtf8("lineEditArea"));

        gridLayout_5->addWidget(lineEditArea, 0, 1, 1, 1);

        label_10 = new QLabel(tabSettings);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 0, 2, 1, 1);

        pushButtonAreaDetection = new QPushButton(tabSettings);
        pushButtonAreaDetection->setObjectName(QString::fromUtf8("pushButtonAreaDetection"));

        gridLayout_5->addWidget(pushButtonAreaDetection, 0, 3, 1, 1);

        label = new QLabel(tabSettings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 1, 0, 1, 1);

        spinBoxTimePeriod = new QSpinBox(tabSettings);
        spinBoxTimePeriod->setObjectName(QString::fromUtf8("spinBoxTimePeriod"));
        spinBoxTimePeriod->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTimePeriod->setMinimum(1);
        spinBoxTimePeriod->setMaximum(200);

        gridLayout_5->addWidget(spinBoxTimePeriod, 1, 1, 1, 1);

        label_3 = new QLabel(tabSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_5->addWidget(label_3, 1, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout_5, 6, 0, 1, 2);

        line_8 = new QFrame(tabSettings);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_8, 13, 0, 1, 2);

        label_8 = new QLabel(tabSettings);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout_8->addWidget(label_8, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_30 = new QLabel(tabSettings);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout->addWidget(label_30, 0, 0, 1, 1);

        filepathOekoBauDat = new QtExt::BrowseFilenameWidget(tabSettings);
        filepathOekoBauDat->setObjectName(QString::fromUtf8("filepathOekoBauDat"));
        filepathOekoBauDat->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(filepathOekoBauDat, 0, 1, 1, 1);

        pushButtonImportOkoebaudat = new QPushButton(tabSettings);
        pushButtonImportOkoebaudat->setObjectName(QString::fromUtf8("pushButtonImportOkoebaudat"));
        pushButtonImportOkoebaudat->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(pushButtonImportOkoebaudat, 0, 2, 1, 1);

        label_6 = new QLabel(tabSettings);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setItalic(true);
        label_6->setFont(font1);
        label_6->setOpenExternalLinks(true);
        label_6->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(label_6, 1, 1, 1, 2);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_8->addLayout(gridLayout, 2, 0, 1, 2);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_8->addItem(verticalSpacer_7, 3, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_8->addItem(verticalSpacer_6, 10, 0, 2, 1);

        line_7 = new QFrame(tabSettings);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_7, 1, 0, 1, 2);

        tabWidget->addTab(tabSettings, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        line_5 = new QFrame(widget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_5, 8, 0, 1, 4);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_36 = new QLabel(widget);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_2->addWidget(label_36, 11, 3, 1, 1);

        label_41 = new QLabel(widget);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_2->addWidget(label_41, 2, 3, 1, 1);

        lineEditElectricityPrice = new QtExt::ValidatingLineEdit(widget);
        lineEditElectricityPrice->setObjectName(QString::fromUtf8("lineEditElectricityPrice"));

        gridLayout_2->addWidget(lineEditElectricityPrice, 4, 2, 1, 1);

        label_32 = new QLabel(widget);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 3, 0, 1, 1);

        label_34 = new QLabel(widget);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_2->addWidget(label_34, 2, 0, 1, 1);

        label_31 = new QLabel(widget);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_2->addWidget(label_31, 3, 3, 1, 1);

        label_33 = new QLabel(widget);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 10, 3, 1, 1);

        lineEditPriceIncreaseGeneral = new QtExt::ValidatingLineEdit(widget);
        lineEditPriceIncreaseGeneral->setObjectName(QString::fromUtf8("lineEditPriceIncreaseGeneral"));

        gridLayout_2->addWidget(lineEditPriceIncreaseGeneral, 10, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(653, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 4, 4, 1, 1);

        label_37 = new QLabel(widget);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_2->addWidget(label_37, 9, 3, 1, 1);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 1, 0, 1, 4);

        lineEditCoalPrice = new QtExt::ValidatingLineEdit(widget);
        lineEditCoalPrice->setObjectName(QString::fromUtf8("lineEditCoalPrice"));

        gridLayout_2->addWidget(lineEditCoalPrice, 2, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 595, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 12, 1, 1, 1);

        label_38 = new QLabel(widget);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout_2->addWidget(label_38, 11, 0, 1, 2);

        label_35 = new QLabel(widget);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_2->addWidget(label_35, 4, 3, 1, 1);

        lineEditInterestRate = new QtExt::ValidatingLineEdit(widget);
        lineEditInterestRate->setObjectName(QString::fromUtf8("lineEditInterestRate"));

        gridLayout_2->addWidget(lineEditInterestRate, 11, 2, 1, 1);

        lineEditGasPrice = new QtExt::ValidatingLineEdit(widget);
        lineEditGasPrice->setObjectName(QString::fromUtf8("lineEditGasPrice"));

        gridLayout_2->addWidget(lineEditGasPrice, 3, 2, 1, 1);

        label_39 = new QLabel(widget);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout_2->addWidget(label_39, 4, 0, 1, 2);

        label_42 = new QLabel(widget);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_2->addWidget(label_42, 10, 0, 1, 2);

        label_40 = new QLabel(widget);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout_2->addWidget(label_40, 9, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_2->addItem(verticalSpacer_2, 5, 0, 1, 1);

        lineEditPriceIncreaseEnergy = new QtExt::ValidatingLineEdit(widget);
        lineEditPriceIncreaseEnergy->setObjectName(QString::fromUtf8("lineEditPriceIncreaseEnergy"));

        gridLayout_2->addWidget(lineEditPriceIncreaseEnergy, 9, 2, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_11, 6, 0, 1, 1);

        tabWidget->addTab(widget, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(828, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 3, 5, 1, 1);

        line_4 = new QFrame(tab);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_4, 1, 1, 1, 4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBoxCatA = new QGroupBox(tab);
        groupBoxCatA->setObjectName(QString::fromUtf8("groupBoxCatA"));
        verticalLayout_5 = new QVBoxLayout(groupBoxCatA);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBoxA1 = new QCheckBox(groupBoxCatA);
        checkBoxA1->setObjectName(QString::fromUtf8("checkBoxA1"));
        checkBoxA1->setChecked(false);

        verticalLayout_5->addWidget(checkBoxA1);

        checkBoxA2 = new QCheckBox(groupBoxCatA);
        checkBoxA2->setObjectName(QString::fromUtf8("checkBoxA2"));
        checkBoxA2->setChecked(false);

        verticalLayout_5->addWidget(checkBoxA2);

        checkBoxA3 = new QCheckBox(groupBoxCatA);
        checkBoxA3->setObjectName(QString::fromUtf8("checkBoxA3"));
        checkBoxA3->setChecked(false);

        verticalLayout_5->addWidget(checkBoxA3);

        checkBoxA4 = new QCheckBox(groupBoxCatA);
        checkBoxA4->setObjectName(QString::fromUtf8("checkBoxA4"));

        verticalLayout_5->addWidget(checkBoxA4);

        checkBoxA5 = new QCheckBox(groupBoxCatA);
        checkBoxA5->setObjectName(QString::fromUtf8("checkBoxA5"));

        verticalLayout_5->addWidget(checkBoxA5);

        verticalSpacer_3 = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);


        horizontalLayout_2->addWidget(groupBoxCatA);

        groupBoxCatB = new QGroupBox(tab);
        groupBoxCatB->setObjectName(QString::fromUtf8("groupBoxCatB"));
        verticalLayout_6 = new QVBoxLayout(groupBoxCatB);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        checkBoxB1 = new QCheckBox(groupBoxCatB);
        checkBoxB1->setObjectName(QString::fromUtf8("checkBoxB1"));

        verticalLayout_6->addWidget(checkBoxB1);

        checkBoxB2 = new QCheckBox(groupBoxCatB);
        checkBoxB2->setObjectName(QString::fromUtf8("checkBoxB2"));

        verticalLayout_6->addWidget(checkBoxB2);

        checkBoxB3 = new QCheckBox(groupBoxCatB);
        checkBoxB3->setObjectName(QString::fromUtf8("checkBoxB3"));

        verticalLayout_6->addWidget(checkBoxB3);

        checkBoxB4 = new QCheckBox(groupBoxCatB);
        checkBoxB4->setObjectName(QString::fromUtf8("checkBoxB4"));

        verticalLayout_6->addWidget(checkBoxB4);

        checkBoxB5 = new QCheckBox(groupBoxCatB);
        checkBoxB5->setObjectName(QString::fromUtf8("checkBoxB5"));

        verticalLayout_6->addWidget(checkBoxB5);

        checkBoxB6 = new QCheckBox(groupBoxCatB);
        checkBoxB6->setObjectName(QString::fromUtf8("checkBoxB6"));

        verticalLayout_6->addWidget(checkBoxB6);

        checkBoxB7 = new QCheckBox(groupBoxCatB);
        checkBoxB7->setObjectName(QString::fromUtf8("checkBoxB7"));

        verticalLayout_6->addWidget(checkBoxB7);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_2->addWidget(groupBoxCatB);

        groupBoxCatC = new QGroupBox(tab);
        groupBoxCatC->setObjectName(QString::fromUtf8("groupBoxCatC"));
        verticalLayout_7 = new QVBoxLayout(groupBoxCatC);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        checkBoxC1 = new QCheckBox(groupBoxCatC);
        checkBoxC1->setObjectName(QString::fromUtf8("checkBoxC1"));

        verticalLayout_7->addWidget(checkBoxC1);

        checkBoxC2 = new QCheckBox(groupBoxCatC);
        checkBoxC2->setObjectName(QString::fromUtf8("checkBoxC2"));

        verticalLayout_7->addWidget(checkBoxC2);

        checkBoxC3 = new QCheckBox(groupBoxCatC);
        checkBoxC3->setObjectName(QString::fromUtf8("checkBoxC3"));

        verticalLayout_7->addWidget(checkBoxC3);

        checkBoxC4 = new QCheckBox(groupBoxCatC);
        checkBoxC4->setObjectName(QString::fromUtf8("checkBoxC4"));

        verticalLayout_7->addWidget(checkBoxC4);

        verticalSpacer_10 = new QSpacerItem(20, 84, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_10);


        horizontalLayout_2->addWidget(groupBoxCatC);

        groupBoxCatD = new QGroupBox(tab);
        groupBoxCatD->setObjectName(QString::fromUtf8("groupBoxCatD"));
        verticalLayout_8 = new QVBoxLayout(groupBoxCatD);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        checkBoxD = new QCheckBox(groupBoxCatD);
        checkBoxD->setObjectName(QString::fromUtf8("checkBoxD"));

        verticalLayout_8->addWidget(checkBoxD);

        verticalSpacer_9 = new QSpacerItem(20, 171, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_9);


        horizontalLayout_2->addWidget(groupBoxCatD);


        gridLayout_3->addLayout(horizontalLayout_2, 5, 1, 1, 4);

        comboBoxCertificationSystem = new QComboBox(tab);
        comboBoxCertificationSystem->setObjectName(QString::fromUtf8("comboBoxCertificationSystem"));

        gridLayout_3->addWidget(comboBoxCertificationSystem, 3, 2, 1, 3);

        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        gridLayout_3->addWidget(label_14, 7, 1, 1, 3);

        line_15 = new QFrame(tab);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_15, 4, 0, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_13, 6, 2, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 359, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_8, 10, 2, 1, 1);

        comboBoxCalculationMode = new QComboBox(tab);
        comboBoxCalculationMode->setObjectName(QString::fromUtf8("comboBoxCalculationMode"));

        gridLayout_3->addWidget(comboBoxCalculationMode, 2, 2, 1, 3);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout_3->addWidget(label_5, 0, 1, 1, 2);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_68 = new QLabel(tab);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        gridLayout_15->addWidget(label_68, 0, 0, 1, 1);

        lineEditEpdGas = new QLineEdit(tab);
        lineEditEpdGas->setObjectName(QString::fromUtf8("lineEditEpdGas"));
        lineEditEpdGas->setEnabled(false);

        gridLayout_15->addWidget(lineEditEpdGas, 0, 1, 1, 1);

        toolButtonSelectGas = new QToolButton(tab);
        toolButtonSelectGas->setObjectName(QString::fromUtf8("toolButtonSelectGas"));

        gridLayout_15->addWidget(toolButtonSelectGas, 0, 2, 1, 1);

        label_69 = new QLabel(tab);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        gridLayout_15->addWidget(label_69, 1, 0, 1, 1);

        lineEditEpdElectricity = new QLineEdit(tab);
        lineEditEpdElectricity->setObjectName(QString::fromUtf8("lineEditEpdElectricity"));
        lineEditEpdElectricity->setEnabled(false);

        gridLayout_15->addWidget(lineEditEpdElectricity, 1, 1, 1, 1);

        toolButtonSelectElectricity = new QToolButton(tab);
        toolButtonSelectElectricity->setObjectName(QString::fromUtf8("toolButtonSelectElectricity"));

        gridLayout_15->addWidget(toolButtonSelectElectricity, 1, 2, 1, 1);

        label_70 = new QLabel(tab);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        gridLayout_15->addWidget(label_70, 2, 0, 1, 1);

        lineEditEpdCoal = new QLineEdit(tab);
        lineEditEpdCoal->setObjectName(QString::fromUtf8("lineEditEpdCoal"));
        lineEditEpdCoal->setEnabled(false);

        gridLayout_15->addWidget(lineEditEpdCoal, 2, 1, 1, 1);

        toolButtonSelectCoal = new QToolButton(tab);
        toolButtonSelectCoal->setObjectName(QString::fromUtf8("toolButtonSelectCoal"));

        gridLayout_15->addWidget(toolButtonSelectCoal, 2, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_15, 9, 1, 1, 4);

        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 2, 1, 1, 1);

        line_16 = new QFrame(tab);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_16, 8, 1, 1, 4);

        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 2);

        pushButtonCalculate = new QPushButton(SVLcaLccSettingsWidget);
        pushButtonCalculate->setObjectName(QString::fromUtf8("pushButtonCalculate"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        pushButtonCalculate->setFont(font2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/play-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCalculate->setIcon(icon);

        gridLayout_4->addWidget(pushButtonCalculate, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 1, 1, 1, 1);


        retranslateUi(SVLcaLccSettingsWidget);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SVLcaLccSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVLcaLccSettingsWidget)
    {
        SVLcaLccSettingsWidget->setWindowTitle(QCoreApplication::translate("SVLcaLccSettingsWidget", "LCA / LCC Settings", nullptr));
        label_16->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Gas:", nullptr));
        label_19->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "kWh/a", nullptr));
        label_17->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Electricity:", nullptr));
        label0->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "kWh/a", nullptr));
        label_18->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Coal:", nullptr));
        label1->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "kWh/a", nullptr));
        label_7->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "General", nullptr));
        label_13->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Energy consumption", nullptr));
        label_9->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Net usage area:", nullptr));
        lineEditArea->setPlaceholderText(QString());
        label_10->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "m<sup>2</sup>", nullptr));
        pushButtonAreaDetection->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "auto-detect", nullptr));
        label->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Evaluation time period:", nullptr));
        label_3->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "a", nullptr));
        label_8->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "EPD database", nullptr));
        label_30->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Database path:", nullptr));
        pushButtonImportOkoebaudat->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Import \303\226KOBAUDAT", nullptr));
        label_6->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "<html><head/><body><p>The database file may be downloaded for free at <a href=\"https://www.oekobaudat.de/service/downloads.html\"><span style=\" text-decoration: underline; color:#0000ff;\">https://www.oekobaudat.de/service/downloads.html</span></a>.</p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSettings), QCoreApplication::translate("SVLcaLccSettingsWidget", "General settings", nullptr));
        label_4->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Energy prices", nullptr));
        label_36->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "%", nullptr));
        label_41->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "\342\202\254/kWh", nullptr));
        label_32->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Gas:", nullptr));
        label_34->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Coal:", nullptr));
        label_31->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "\342\202\254/kWh", nullptr));
        label_33->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "%", nullptr));
        label_37->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "%", nullptr));
        label_2->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Price increase", nullptr));
        label_38->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Discounting interest rate:", nullptr));
        label_35->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "\342\202\254/kWh", nullptr));
        label_39->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Electricity:", nullptr));
        label_42->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Price increase general:", nullptr));
        label_40->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Price increase energy:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(widget), QCoreApplication::translate("SVLcaLccSettingsWidget", "Life cycle cost (LCC) settings", nullptr));
        label_12->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Certification system:", nullptr));
        groupBoxCatA->setTitle(QCoreApplication::translate("SVLcaLccSettingsWidget", "Category A (Production)", nullptr));
        checkBoxA1->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "A1", nullptr));
        checkBoxA2->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "A2", nullptr));
        checkBoxA3->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "A3", nullptr));
        checkBoxA4->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "A4", nullptr));
        checkBoxA5->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "A5", nullptr));
        groupBoxCatB->setTitle(QCoreApplication::translate("SVLcaLccSettingsWidget", "Category B (Usage)", nullptr));
        checkBoxB1->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B1", nullptr));
        checkBoxB2->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B2", nullptr));
        checkBoxB3->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B3", nullptr));
        checkBoxB4->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B4", nullptr));
        checkBoxB5->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B5", nullptr));
        checkBoxB6->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B6", nullptr));
        checkBoxB7->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "B7", nullptr));
        groupBoxCatC->setTitle(QCoreApplication::translate("SVLcaLccSettingsWidget", "Category C (Disposal)", nullptr));
        checkBoxC1->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "C1", nullptr));
        checkBoxC2->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "C2", nullptr));
        checkBoxC3->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "C3", nullptr));
        checkBoxC4->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "C4", nullptr));
        groupBoxCatD->setTitle(QCoreApplication::translate("SVLcaLccSettingsWidget", "Category D (Deposit)", nullptr));
        checkBoxD->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "D", nullptr));
        label_14->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Energy emissions (EPD)", nullptr));
        label_5->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "General LCA settings", nullptr));
        label_68->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Gas", nullptr));
        toolButtonSelectGas->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "...", nullptr));
        label_69->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Electricity", nullptr));
        toolButtonSelectElectricity->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "...", nullptr));
        label_70->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Coal", nullptr));
        toolButtonSelectCoal->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "...", nullptr));
        label_11->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "LCA mode:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SVLcaLccSettingsWidget", "Life cycle assessment (LCA) settings", nullptr));
        pushButtonCalculate->setText(QCoreApplication::translate("SVLcaLccSettingsWidget", "Run life-cycle evaluation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVLcaLccSettingsWidget: public Ui_SVLcaLccSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVLCALCCSETTINGSWIDGET_H
