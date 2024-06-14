/********************************************************************************
** Form generated from reading UI file 'SVNetworkComponentHeatExchangeEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H
#define UI_SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SVNetworkComponentHeatExchangeEditWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBoxExternallyDefined;
    QComboBox *comboBoxHeatExchange;
    QStackedWidget *stackedWidgetHeatExchange;
    QWidget *pageTemperatureConstant;
    QVBoxLayout *verticalLayoutPageTemperatureConstant;
    QGridLayout *gridLayout_2;
    QLabel *labelTemperatureConstantTemperature;
    QtExt::ValidatingLineEdit *lineEditTemperatureConstantTemperature;
    QLabel *labelTemperatureConstantHeatTransferCoefficientUnit;
    QLabel *labelTemperatureConstantTemperatureUnit;
    QtExt::ValidatingLineEdit *lineEditTemperatureConstantHeatTransferCoefficient;
    QCheckBox *checkBoxTemperatureConstantHeatTransferCoeff;
    QSpacerItem *verticalSpacerTemperatureConstant;
    QWidget *pageTemperatureSpline;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_5;
    QtExt::ValidatingLineEdit *lineEditTemperatureSplineHeatTransferCoefficient;
    QLabel *labelTemperatureSplineHeatTransferCoefficientUnit;
    QComboBox *comboBoxTemperatureSpline;
    QLabel *labelTemperatureConstantHeatTransferCoefficient_3;
    QCheckBox *checkBoxTemperatureSplineHeatTransferCoefficient;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTemperatureSplineHeatFilePath;
    QtExt::BrowseFilenameWidget *widgetTemperatureSplineFilePathDataFile;
    QWidget *widgetTemperatureSplineSelectColumn;
    QVBoxLayout *verticalLayout;
    QLabel *labelTemperatureSplineSelectColumn;
    QListWidget *listWidgetTemperatureSplineSelectColumn;
    QwtPlot *widgetPlotTemperatureSpline;
    QSpacerItem *verticalSpacerTemperatureSpline;
    QWidget *pageHeatLossConstant;
    QVBoxLayout *verticalLayoutPageHeatLossConstant;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_4;
    QtExt::ValidatingLineEdit *lineEditHeatLossConstantSupplyTemperature;
    QLabel *labelHeatLossConstantUserHeatFlux;
    QtExt::ValidatingLineEdit *lineEditHeatLossConstantUser;
    QLabel *labelHeatLossConstantSupplyTemperatureUnit;
    QLabel *labelHeatLossConstantUserUnit;
    QLabel *labelHeatLossConstantSupplyTemperature;
    QSpacerItem *verticalSpacerHeatLossConstant;
    QWidget *pageHeatLossSpline;
    QVBoxLayout *verticalLayout_8;
    QWidget *widgetDefineHeatExchangeSpline;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_6;
    QToolButton *toolButtonSetDefaultValues;
    QLabel *labelHeatLossSplineUserBuildingType;
    QComboBox *comboBoxHeatLossSplineBuildingType;
    QStackedWidget *stackedWidgetHeatLossSpline;
    QWidget *page;
    QVBoxLayout *verticalLayout_10;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QWidget *widgetHeating;
    QGridLayout *gridLayout;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineMaximumHeatingLoad;
    QLabel *labelHeatLossSplineHeatingEnergyDemand;
    QLabel *labelHeatLossSplineMaximumHeatingLoadUnit;
    QLabel *labelHeatLossSplineHeatingSupplyTemp;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineHeatingSupplyTemperature;
    QLabel *labelHeatLossSplineMaximumHeatingLoad;
    QLabel *labelHeatLossSplineHeatingEnergyDemandUnit;
    QLabel *labelHeatLossSplineHeatingSupplyTempUnit;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineHeatingEnergyDemand;
    QCheckBox *checkBoxDHW;
    QWidget *widgetDHW;
    QGridLayout *gridLayout_10;
    QLabel *labelHeatLossSplineDomesticHotWaterDemandUnit;
    QLabel *labelHeatLossSplineDomesticHotWaterDemandUnit_3;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineDomesticHotWaterDemand;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineDomesticHotWaterShare;
    QLabel *labelHeatLossSplineDomesticHotWaterDemand;
    QLabel *labelHeatLossSplineDomesticHotWaterDemand_2;
    QLabel *labelHeatLossSplineDHWSupplyTemp;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineDHWSupplyTemperature;
    QLabel *labelHeatLossSplineDHWSupplyTempUnit;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBoxCooling;
    QWidget *widgetCooling;
    QGridLayout *gridLayout_3;
    QLabel *labelHeatLossSplineCoolingEnergyDemand;
    QLabel *labelHeatLossSplineMaximumCoolingLoad;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineMaximumCoolingLoad;
    QLabel *labelHeatLossSplineCoolingEnergyDemandUnit;
    QLabel *labelHeatLossSplineMaximumCoolingLoadUnit;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineCoolingEnergyDemand;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayoutHeatLossSplineFloorArea;
    QCheckBox *checkBoxHeatLossSplineAreaRelatedValues;
    QtExt::ValidatingLineEdit *lineEditHeatLossSplineFloorArea;
    QLabel *labelHeatLossSplineFloorAreaUnit;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayoutFilePath;
    QLabel *labelFilePath;
    QtExt::BrowseFilenameWidget *filepathDataFile;
    QLabel *labelHeatLossSplineSelectColumn;
    QListWidget *listWidgetHeatLossSplineSelectColumn;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QwtPlot *widgetPlotHeatLossSpline;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonShowYear;
    QRadioButton *radioButtonShowDay;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_7;
    QWidget *pageNone;
    QVBoxLayout *verticalLayoutPageNone;
    QLabel *labelPageNone;
    QSpacerItem *verticalSpacerNone;

    void setupUi(QWidget *SVNetworkComponentHeatExchangeEditWidget)
    {
        if (SVNetworkComponentHeatExchangeEditWidget->objectName().isEmpty())
            SVNetworkComponentHeatExchangeEditWidget->setObjectName(QString::fromUtf8("SVNetworkComponentHeatExchangeEditWidget"));
        SVNetworkComponentHeatExchangeEditWidget->resize(814, 1518);
        verticalLayout_4 = new QVBoxLayout(SVNetworkComponentHeatExchangeEditWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        checkBoxExternallyDefined = new QCheckBox(SVNetworkComponentHeatExchangeEditWidget);
        checkBoxExternallyDefined->setObjectName(QString::fromUtf8("checkBoxExternallyDefined"));

        verticalLayout_4->addWidget(checkBoxExternallyDefined);

        comboBoxHeatExchange = new QComboBox(SVNetworkComponentHeatExchangeEditWidget);
        comboBoxHeatExchange->setObjectName(QString::fromUtf8("comboBoxHeatExchange"));

        verticalLayout_4->addWidget(comboBoxHeatExchange);

        stackedWidgetHeatExchange = new QStackedWidget(SVNetworkComponentHeatExchangeEditWidget);
        stackedWidgetHeatExchange->setObjectName(QString::fromUtf8("stackedWidgetHeatExchange"));
        pageTemperatureConstant = new QWidget();
        pageTemperatureConstant->setObjectName(QString::fromUtf8("pageTemperatureConstant"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(pageTemperatureConstant->sizePolicy().hasHeightForWidth());
        pageTemperatureConstant->setSizePolicy(sizePolicy);
        verticalLayoutPageTemperatureConstant = new QVBoxLayout(pageTemperatureConstant);
        verticalLayoutPageTemperatureConstant->setSpacing(10);
        verticalLayoutPageTemperatureConstant->setObjectName(QString::fromUtf8("verticalLayoutPageTemperatureConstant"));
        verticalLayoutPageTemperatureConstant->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelTemperatureConstantTemperature = new QLabel(pageTemperatureConstant);
        labelTemperatureConstantTemperature->setObjectName(QString::fromUtf8("labelTemperatureConstantTemperature"));

        gridLayout_2->addWidget(labelTemperatureConstantTemperature, 0, 0, 1, 1);

        lineEditTemperatureConstantTemperature = new QtExt::ValidatingLineEdit(pageTemperatureConstant);
        lineEditTemperatureConstantTemperature->setObjectName(QString::fromUtf8("lineEditTemperatureConstantTemperature"));
        lineEditTemperatureConstantTemperature->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(lineEditTemperatureConstantTemperature, 0, 1, 1, 1);

        labelTemperatureConstantHeatTransferCoefficientUnit = new QLabel(pageTemperatureConstant);
        labelTemperatureConstantHeatTransferCoefficientUnit->setObjectName(QString::fromUtf8("labelTemperatureConstantHeatTransferCoefficientUnit"));

        gridLayout_2->addWidget(labelTemperatureConstantHeatTransferCoefficientUnit, 1, 2, 1, 1);

        labelTemperatureConstantTemperatureUnit = new QLabel(pageTemperatureConstant);
        labelTemperatureConstantTemperatureUnit->setObjectName(QString::fromUtf8("labelTemperatureConstantTemperatureUnit"));
        labelTemperatureConstantTemperatureUnit->setMaximumSize(QSize(48, 16777215));

        gridLayout_2->addWidget(labelTemperatureConstantTemperatureUnit, 0, 2, 1, 1);

        lineEditTemperatureConstantHeatTransferCoefficient = new QtExt::ValidatingLineEdit(pageTemperatureConstant);
        lineEditTemperatureConstantHeatTransferCoefficient->setObjectName(QString::fromUtf8("lineEditTemperatureConstantHeatTransferCoefficient"));

        gridLayout_2->addWidget(lineEditTemperatureConstantHeatTransferCoefficient, 1, 1, 1, 1);

        checkBoxTemperatureConstantHeatTransferCoeff = new QCheckBox(pageTemperatureConstant);
        checkBoxTemperatureConstantHeatTransferCoeff->setObjectName(QString::fromUtf8("checkBoxTemperatureConstantHeatTransferCoeff"));

        gridLayout_2->addWidget(checkBoxTemperatureConstantHeatTransferCoeff, 1, 0, 1, 1);


        verticalLayoutPageTemperatureConstant->addLayout(gridLayout_2);

        verticalSpacerTemperatureConstant = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutPageTemperatureConstant->addItem(verticalSpacerTemperatureConstant);

        stackedWidgetHeatExchange->addWidget(pageTemperatureConstant);
        pageTemperatureSpline = new QWidget();
        pageTemperatureSpline->setObjectName(QString::fromUtf8("pageTemperatureSpline"));
        sizePolicy.setHeightForWidth(pageTemperatureSpline->sizePolicy().hasHeightForWidth());
        pageTemperatureSpline->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(pageTemperatureSpline);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lineEditTemperatureSplineHeatTransferCoefficient = new QtExt::ValidatingLineEdit(pageTemperatureSpline);
        lineEditTemperatureSplineHeatTransferCoefficient->setObjectName(QString::fromUtf8("lineEditTemperatureSplineHeatTransferCoefficient"));

        gridLayout_5->addWidget(lineEditTemperatureSplineHeatTransferCoefficient, 1, 1, 1, 1);

        labelTemperatureSplineHeatTransferCoefficientUnit = new QLabel(pageTemperatureSpline);
        labelTemperatureSplineHeatTransferCoefficientUnit->setObjectName(QString::fromUtf8("labelTemperatureSplineHeatTransferCoefficientUnit"));

        gridLayout_5->addWidget(labelTemperatureSplineHeatTransferCoefficientUnit, 1, 2, 1, 1);

        comboBoxTemperatureSpline = new QComboBox(pageTemperatureSpline);
        comboBoxTemperatureSpline->setObjectName(QString::fromUtf8("comboBoxTemperatureSpline"));

        gridLayout_5->addWidget(comboBoxTemperatureSpline, 0, 1, 1, 2);

        labelTemperatureConstantHeatTransferCoefficient_3 = new QLabel(pageTemperatureSpline);
        labelTemperatureConstantHeatTransferCoefficient_3->setObjectName(QString::fromUtf8("labelTemperatureConstantHeatTransferCoefficient_3"));

        gridLayout_5->addWidget(labelTemperatureConstantHeatTransferCoefficient_3, 0, 0, 1, 1);

        checkBoxTemperatureSplineHeatTransferCoefficient = new QCheckBox(pageTemperatureSpline);
        checkBoxTemperatureSplineHeatTransferCoefficient->setObjectName(QString::fromUtf8("checkBoxTemperatureSplineHeatTransferCoefficient"));

        gridLayout_5->addWidget(checkBoxTemperatureSplineHeatTransferCoefficient, 1, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelTemperatureSplineHeatFilePath = new QLabel(pageTemperatureSpline);
        labelTemperatureSplineHeatFilePath->setObjectName(QString::fromUtf8("labelTemperatureSplineHeatFilePath"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTemperatureSplineHeatFilePath->sizePolicy().hasHeightForWidth());
        labelTemperatureSplineHeatFilePath->setSizePolicy(sizePolicy1);
        labelTemperatureSplineHeatFilePath->setMinimumSize(QSize(0, 0));
        labelTemperatureSplineHeatFilePath->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(labelTemperatureSplineHeatFilePath);

        widgetTemperatureSplineFilePathDataFile = new QtExt::BrowseFilenameWidget(pageTemperatureSpline);
        widgetTemperatureSplineFilePathDataFile->setObjectName(QString::fromUtf8("widgetTemperatureSplineFilePathDataFile"));
        sizePolicy1.setHeightForWidth(widgetTemperatureSplineFilePathDataFile->sizePolicy().hasHeightForWidth());
        widgetTemperatureSplineFilePathDataFile->setSizePolicy(sizePolicy1);
        widgetTemperatureSplineFilePathDataFile->setMinimumSize(QSize(0, 0));
        widgetTemperatureSplineFilePathDataFile->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(widgetTemperatureSplineFilePathDataFile);


        verticalLayout_3->addLayout(horizontalLayout);

        widgetTemperatureSplineSelectColumn = new QWidget(pageTemperatureSpline);
        widgetTemperatureSplineSelectColumn->setObjectName(QString::fromUtf8("widgetTemperatureSplineSelectColumn"));
        verticalLayout = new QVBoxLayout(widgetTemperatureSplineSelectColumn);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelTemperatureSplineSelectColumn = new QLabel(widgetTemperatureSplineSelectColumn);
        labelTemperatureSplineSelectColumn->setObjectName(QString::fromUtf8("labelTemperatureSplineSelectColumn"));

        verticalLayout->addWidget(labelTemperatureSplineSelectColumn);

        listWidgetTemperatureSplineSelectColumn = new QListWidget(widgetTemperatureSplineSelectColumn);
        listWidgetTemperatureSplineSelectColumn->setObjectName(QString::fromUtf8("listWidgetTemperatureSplineSelectColumn"));
        listWidgetTemperatureSplineSelectColumn->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(listWidgetTemperatureSplineSelectColumn);


        verticalLayout_3->addWidget(widgetTemperatureSplineSelectColumn);

        widgetPlotTemperatureSpline = new QwtPlot(pageTemperatureSpline);
        widgetPlotTemperatureSpline->setObjectName(QString::fromUtf8("widgetPlotTemperatureSpline"));
        sizePolicy1.setHeightForWidth(widgetPlotTemperatureSpline->sizePolicy().hasHeightForWidth());
        widgetPlotTemperatureSpline->setSizePolicy(sizePolicy1);
        widgetPlotTemperatureSpline->setMinimumSize(QSize(405, 201));
        widgetPlotTemperatureSpline->setMaximumSize(QSize(16777215, 500));
        widgetPlotTemperatureSpline->setFrameShape(QFrame::StyledPanel);
        widgetPlotTemperatureSpline->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(widgetPlotTemperatureSpline);

        verticalSpacerTemperatureSpline = new QSpacerItem(20, 1000, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacerTemperatureSpline);

        stackedWidgetHeatExchange->addWidget(pageTemperatureSpline);
        pageHeatLossConstant = new QWidget();
        pageHeatLossConstant->setObjectName(QString::fromUtf8("pageHeatLossConstant"));
        sizePolicy.setHeightForWidth(pageHeatLossConstant->sizePolicy().hasHeightForWidth());
        pageHeatLossConstant->setSizePolicy(sizePolicy);
        verticalLayoutPageHeatLossConstant = new QVBoxLayout(pageHeatLossConstant);
        verticalLayoutPageHeatLossConstant->setSpacing(10);
        verticalLayoutPageHeatLossConstant->setObjectName(QString::fromUtf8("verticalLayoutPageHeatLossConstant"));
        verticalLayoutPageHeatLossConstant->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayoutPageHeatLossConstant->addItem(verticalSpacer_4);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lineEditHeatLossConstantSupplyTemperature = new QtExt::ValidatingLineEdit(pageHeatLossConstant);
        lineEditHeatLossConstantSupplyTemperature->setObjectName(QString::fromUtf8("lineEditHeatLossConstantSupplyTemperature"));

        gridLayout_4->addWidget(lineEditHeatLossConstantSupplyTemperature, 1, 1, 1, 1);

        labelHeatLossConstantUserHeatFlux = new QLabel(pageHeatLossConstant);
        labelHeatLossConstantUserHeatFlux->setObjectName(QString::fromUtf8("labelHeatLossConstantUserHeatFlux"));

        gridLayout_4->addWidget(labelHeatLossConstantUserHeatFlux, 0, 0, 1, 1);

        lineEditHeatLossConstantUser = new QtExt::ValidatingLineEdit(pageHeatLossConstant);
        lineEditHeatLossConstantUser->setObjectName(QString::fromUtf8("lineEditHeatLossConstantUser"));

        gridLayout_4->addWidget(lineEditHeatLossConstantUser, 0, 1, 1, 1);

        labelHeatLossConstantSupplyTemperatureUnit = new QLabel(pageHeatLossConstant);
        labelHeatLossConstantSupplyTemperatureUnit->setObjectName(QString::fromUtf8("labelHeatLossConstantSupplyTemperatureUnit"));

        gridLayout_4->addWidget(labelHeatLossConstantSupplyTemperatureUnit, 1, 2, 1, 1);

        labelHeatLossConstantUserUnit = new QLabel(pageHeatLossConstant);
        labelHeatLossConstantUserUnit->setObjectName(QString::fromUtf8("labelHeatLossConstantUserUnit"));

        gridLayout_4->addWidget(labelHeatLossConstantUserUnit, 0, 2, 1, 1);

        labelHeatLossConstantSupplyTemperature = new QLabel(pageHeatLossConstant);
        labelHeatLossConstantSupplyTemperature->setObjectName(QString::fromUtf8("labelHeatLossConstantSupplyTemperature"));

        gridLayout_4->addWidget(labelHeatLossConstantSupplyTemperature, 1, 0, 1, 1);


        verticalLayoutPageHeatLossConstant->addLayout(gridLayout_4);

        verticalSpacerHeatLossConstant = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutPageHeatLossConstant->addItem(verticalSpacerHeatLossConstant);

        stackedWidgetHeatExchange->addWidget(pageHeatLossConstant);
        pageHeatLossSpline = new QWidget();
        pageHeatLossSpline->setObjectName(QString::fromUtf8("pageHeatLossSpline"));
        sizePolicy.setHeightForWidth(pageHeatLossSpline->sizePolicy().hasHeightForWidth());
        pageHeatLossSpline->setSizePolicy(sizePolicy);
        verticalLayout_8 = new QVBoxLayout(pageHeatLossSpline);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        widgetDefineHeatExchangeSpline = new QWidget(pageHeatLossSpline);
        widgetDefineHeatExchangeSpline->setObjectName(QString::fromUtf8("widgetDefineHeatExchangeSpline"));
        verticalLayout_2 = new QVBoxLayout(widgetDefineHeatExchangeSpline);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        toolButtonSetDefaultValues = new QToolButton(widgetDefineHeatExchangeSpline);
        toolButtonSetDefaultValues->setObjectName(QString::fromUtf8("toolButtonSetDefaultValues"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/arrow-source-grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonSetDefaultValues->setIcon(icon);
        toolButtonSetDefaultValues->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonSetDefaultValues->setArrowType(Qt::NoArrow);

        gridLayout_6->addWidget(toolButtonSetDefaultValues, 0, 2, 1, 1);

        labelHeatLossSplineUserBuildingType = new QLabel(widgetDefineHeatExchangeSpline);
        labelHeatLossSplineUserBuildingType->setObjectName(QString::fromUtf8("labelHeatLossSplineUserBuildingType"));
        labelHeatLossSplineUserBuildingType->setMaximumSize(QSize(109, 16777215));

        gridLayout_6->addWidget(labelHeatLossSplineUserBuildingType, 0, 0, 1, 1);

        comboBoxHeatLossSplineBuildingType = new QComboBox(widgetDefineHeatExchangeSpline);
        comboBoxHeatLossSplineBuildingType->setObjectName(QString::fromUtf8("comboBoxHeatLossSplineBuildingType"));

        gridLayout_6->addWidget(comboBoxHeatLossSplineBuildingType, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_6);

        stackedWidgetHeatLossSpline = new QStackedWidget(widgetDefineHeatExchangeSpline);
        stackedWidgetHeatLossSpline->setObjectName(QString::fromUtf8("stackedWidgetHeatLossSpline"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_10 = new QVBoxLayout(page);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 6, 0, 0);
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setUsesScrollButtons(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        widgetHeating = new QWidget(tab);
        widgetHeating->setObjectName(QString::fromUtf8("widgetHeating"));
        gridLayout = new QGridLayout(widgetHeating);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEditHeatLossSplineMaximumHeatingLoad = new QtExt::ValidatingLineEdit(widgetHeating);
        lineEditHeatLossSplineMaximumHeatingLoad->setObjectName(QString::fromUtf8("lineEditHeatLossSplineMaximumHeatingLoad"));
        lineEditHeatLossSplineMaximumHeatingLoad->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEditHeatLossSplineMaximumHeatingLoad, 0, 1, 1, 1);

        labelHeatLossSplineHeatingEnergyDemand = new QLabel(widgetHeating);
        labelHeatLossSplineHeatingEnergyDemand->setObjectName(QString::fromUtf8("labelHeatLossSplineHeatingEnergyDemand"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelHeatLossSplineHeatingEnergyDemand->sizePolicy().hasHeightForWidth());
        labelHeatLossSplineHeatingEnergyDemand->setSizePolicy(sizePolicy3);
        labelHeatLossSplineHeatingEnergyDemand->setMinimumSize(QSize(205, 0));
        labelHeatLossSplineHeatingEnergyDemand->setMaximumSize(QSize(16777215, 190));

        gridLayout->addWidget(labelHeatLossSplineHeatingEnergyDemand, 1, 0, 1, 1);

        labelHeatLossSplineMaximumHeatingLoadUnit = new QLabel(widgetHeating);
        labelHeatLossSplineMaximumHeatingLoadUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineMaximumHeatingLoadUnit"));

        gridLayout->addWidget(labelHeatLossSplineMaximumHeatingLoadUnit, 0, 2, 1, 1);

        labelHeatLossSplineHeatingSupplyTemp = new QLabel(widgetHeating);
        labelHeatLossSplineHeatingSupplyTemp->setObjectName(QString::fromUtf8("labelHeatLossSplineHeatingSupplyTemp"));
        sizePolicy3.setHeightForWidth(labelHeatLossSplineHeatingSupplyTemp->sizePolicy().hasHeightForWidth());
        labelHeatLossSplineHeatingSupplyTemp->setSizePolicy(sizePolicy3);
        labelHeatLossSplineHeatingSupplyTemp->setMinimumSize(QSize(205, 0));
        labelHeatLossSplineHeatingSupplyTemp->setMaximumSize(QSize(16777215, 190));

        gridLayout->addWidget(labelHeatLossSplineHeatingSupplyTemp, 2, 0, 1, 1);

        lineEditHeatLossSplineHeatingSupplyTemperature = new QtExt::ValidatingLineEdit(widgetHeating);
        lineEditHeatLossSplineHeatingSupplyTemperature->setObjectName(QString::fromUtf8("lineEditHeatLossSplineHeatingSupplyTemperature"));
        lineEditHeatLossSplineHeatingSupplyTemperature->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEditHeatLossSplineHeatingSupplyTemperature, 2, 1, 1, 1);

        labelHeatLossSplineMaximumHeatingLoad = new QLabel(widgetHeating);
        labelHeatLossSplineMaximumHeatingLoad->setObjectName(QString::fromUtf8("labelHeatLossSplineMaximumHeatingLoad"));
        sizePolicy3.setHeightForWidth(labelHeatLossSplineMaximumHeatingLoad->sizePolicy().hasHeightForWidth());
        labelHeatLossSplineMaximumHeatingLoad->setSizePolicy(sizePolicy3);
        labelHeatLossSplineMaximumHeatingLoad->setMinimumSize(QSize(205, 0));
        labelHeatLossSplineMaximumHeatingLoad->setMaximumSize(QSize(16777215, 190));

        gridLayout->addWidget(labelHeatLossSplineMaximumHeatingLoad, 0, 0, 1, 1);

        labelHeatLossSplineHeatingEnergyDemandUnit = new QLabel(widgetHeating);
        labelHeatLossSplineHeatingEnergyDemandUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineHeatingEnergyDemandUnit"));

        gridLayout->addWidget(labelHeatLossSplineHeatingEnergyDemandUnit, 1, 2, 1, 1);

        labelHeatLossSplineHeatingSupplyTempUnit = new QLabel(widgetHeating);
        labelHeatLossSplineHeatingSupplyTempUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineHeatingSupplyTempUnit"));

        gridLayout->addWidget(labelHeatLossSplineHeatingSupplyTempUnit, 2, 2, 1, 1);

        lineEditHeatLossSplineHeatingEnergyDemand = new QtExt::ValidatingLineEdit(widgetHeating);
        lineEditHeatLossSplineHeatingEnergyDemand->setObjectName(QString::fromUtf8("lineEditHeatLossSplineHeatingEnergyDemand"));
        lineEditHeatLossSplineHeatingEnergyDemand->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEditHeatLossSplineHeatingEnergyDemand, 1, 1, 1, 1);


        verticalLayout_7->addWidget(widgetHeating);

        checkBoxDHW = new QCheckBox(tab);
        checkBoxDHW->setObjectName(QString::fromUtf8("checkBoxDHW"));

        verticalLayout_7->addWidget(checkBoxDHW);

        widgetDHW = new QWidget(tab);
        widgetDHW->setObjectName(QString::fromUtf8("widgetDHW"));
        gridLayout_10 = new QGridLayout(widgetDHW);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        labelHeatLossSplineDomesticHotWaterDemandUnit = new QLabel(widgetDHW);
        labelHeatLossSplineDomesticHotWaterDemandUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineDomesticHotWaterDemandUnit"));

        gridLayout_10->addWidget(labelHeatLossSplineDomesticHotWaterDemandUnit, 0, 2, 1, 1);

        labelHeatLossSplineDomesticHotWaterDemandUnit_3 = new QLabel(widgetDHW);
        labelHeatLossSplineDomesticHotWaterDemandUnit_3->setObjectName(QString::fromUtf8("labelHeatLossSplineDomesticHotWaterDemandUnit_3"));

        gridLayout_10->addWidget(labelHeatLossSplineDomesticHotWaterDemandUnit_3, 2, 2, 1, 1);

        lineEditHeatLossSplineDomesticHotWaterDemand = new QtExt::ValidatingLineEdit(widgetDHW);
        lineEditHeatLossSplineDomesticHotWaterDemand->setObjectName(QString::fromUtf8("lineEditHeatLossSplineDomesticHotWaterDemand"));
        lineEditHeatLossSplineDomesticHotWaterDemand->setMaximumSize(QSize(300, 16777215));

        gridLayout_10->addWidget(lineEditHeatLossSplineDomesticHotWaterDemand, 0, 1, 1, 1);

        lineEditHeatLossSplineDomesticHotWaterShare = new QtExt::ValidatingLineEdit(widgetDHW);
        lineEditHeatLossSplineDomesticHotWaterShare->setObjectName(QString::fromUtf8("lineEditHeatLossSplineDomesticHotWaterShare"));
        lineEditHeatLossSplineDomesticHotWaterShare->setReadOnly(true);

        gridLayout_10->addWidget(lineEditHeatLossSplineDomesticHotWaterShare, 2, 1, 1, 1);

        labelHeatLossSplineDomesticHotWaterDemand = new QLabel(widgetDHW);
        labelHeatLossSplineDomesticHotWaterDemand->setObjectName(QString::fromUtf8("labelHeatLossSplineDomesticHotWaterDemand"));
        sizePolicy3.setHeightForWidth(labelHeatLossSplineDomesticHotWaterDemand->sizePolicy().hasHeightForWidth());
        labelHeatLossSplineDomesticHotWaterDemand->setSizePolicy(sizePolicy3);
        labelHeatLossSplineDomesticHotWaterDemand->setMinimumSize(QSize(205, 0));
        labelHeatLossSplineDomesticHotWaterDemand->setMaximumSize(QSize(16777215, 190));

        gridLayout_10->addWidget(labelHeatLossSplineDomesticHotWaterDemand, 0, 0, 1, 1);

        labelHeatLossSplineDomesticHotWaterDemand_2 = new QLabel(widgetDHW);
        labelHeatLossSplineDomesticHotWaterDemand_2->setObjectName(QString::fromUtf8("labelHeatLossSplineDomesticHotWaterDemand_2"));
        labelHeatLossSplineDomesticHotWaterDemand_2->setMinimumSize(QSize(205, 0));

        gridLayout_10->addWidget(labelHeatLossSplineDomesticHotWaterDemand_2, 2, 0, 1, 1);

        labelHeatLossSplineDHWSupplyTemp = new QLabel(widgetDHW);
        labelHeatLossSplineDHWSupplyTemp->setObjectName(QString::fromUtf8("labelHeatLossSplineDHWSupplyTemp"));
        sizePolicy3.setHeightForWidth(labelHeatLossSplineDHWSupplyTemp->sizePolicy().hasHeightForWidth());
        labelHeatLossSplineDHWSupplyTemp->setSizePolicy(sizePolicy3);
        labelHeatLossSplineDHWSupplyTemp->setMinimumSize(QSize(205, 0));
        labelHeatLossSplineDHWSupplyTemp->setMaximumSize(QSize(16777215, 190));

        gridLayout_10->addWidget(labelHeatLossSplineDHWSupplyTemp, 1, 0, 1, 1);

        lineEditHeatLossSplineDHWSupplyTemperature = new QtExt::ValidatingLineEdit(widgetDHW);
        lineEditHeatLossSplineDHWSupplyTemperature->setObjectName(QString::fromUtf8("lineEditHeatLossSplineDHWSupplyTemperature"));
        lineEditHeatLossSplineDHWSupplyTemperature->setMaximumSize(QSize(300, 16777215));

        gridLayout_10->addWidget(lineEditHeatLossSplineDHWSupplyTemperature, 1, 1, 1, 1);

        labelHeatLossSplineDHWSupplyTempUnit = new QLabel(widgetDHW);
        labelHeatLossSplineDHWSupplyTempUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineDHWSupplyTempUnit"));

        gridLayout_10->addWidget(labelHeatLossSplineDHWSupplyTempUnit, 1, 2, 1, 1);


        verticalLayout_7->addWidget(widgetDHW);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_5 = new QVBoxLayout(tab_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBoxCooling = new QCheckBox(tab_3);
        checkBoxCooling->setObjectName(QString::fromUtf8("checkBoxCooling"));

        verticalLayout_5->addWidget(checkBoxCooling);

        widgetCooling = new QWidget(tab_3);
        widgetCooling->setObjectName(QString::fromUtf8("widgetCooling"));
        gridLayout_3 = new QGridLayout(widgetCooling);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, 0);
        labelHeatLossSplineCoolingEnergyDemand = new QLabel(widgetCooling);
        labelHeatLossSplineCoolingEnergyDemand->setObjectName(QString::fromUtf8("labelHeatLossSplineCoolingEnergyDemand"));

        gridLayout_3->addWidget(labelHeatLossSplineCoolingEnergyDemand, 1, 0, 1, 1);

        labelHeatLossSplineMaximumCoolingLoad = new QLabel(widgetCooling);
        labelHeatLossSplineMaximumCoolingLoad->setObjectName(QString::fromUtf8("labelHeatLossSplineMaximumCoolingLoad"));

        gridLayout_3->addWidget(labelHeatLossSplineMaximumCoolingLoad, 0, 0, 1, 1);

        lineEditHeatLossSplineMaximumCoolingLoad = new QtExt::ValidatingLineEdit(widgetCooling);
        lineEditHeatLossSplineMaximumCoolingLoad->setObjectName(QString::fromUtf8("lineEditHeatLossSplineMaximumCoolingLoad"));

        gridLayout_3->addWidget(lineEditHeatLossSplineMaximumCoolingLoad, 0, 1, 1, 1);

        labelHeatLossSplineCoolingEnergyDemandUnit = new QLabel(widgetCooling);
        labelHeatLossSplineCoolingEnergyDemandUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineCoolingEnergyDemandUnit"));

        gridLayout_3->addWidget(labelHeatLossSplineCoolingEnergyDemandUnit, 1, 2, 1, 1);

        labelHeatLossSplineMaximumCoolingLoadUnit = new QLabel(widgetCooling);
        labelHeatLossSplineMaximumCoolingLoadUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineMaximumCoolingLoadUnit"));

        gridLayout_3->addWidget(labelHeatLossSplineMaximumCoolingLoadUnit, 0, 2, 1, 1);

        lineEditHeatLossSplineCoolingEnergyDemand = new QtExt::ValidatingLineEdit(widgetCooling);
        lineEditHeatLossSplineCoolingEnergyDemand->setObjectName(QString::fromUtf8("lineEditHeatLossSplineCoolingEnergyDemand"));

        gridLayout_3->addWidget(lineEditHeatLossSplineCoolingEnergyDemand, 1, 1, 1, 1);


        verticalLayout_5->addWidget(widgetCooling);

        verticalSpacer_6 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        tabWidget->addTab(tab_3, QString());

        verticalLayout_10->addWidget(tabWidget);

        horizontalLayoutHeatLossSplineFloorArea = new QHBoxLayout();
        horizontalLayoutHeatLossSplineFloorArea->setObjectName(QString::fromUtf8("horizontalLayoutHeatLossSplineFloorArea"));
        horizontalLayoutHeatLossSplineFloorArea->setContentsMargins(9, -1, 9, -1);
        checkBoxHeatLossSplineAreaRelatedValues = new QCheckBox(page);
        checkBoxHeatLossSplineAreaRelatedValues->setObjectName(QString::fromUtf8("checkBoxHeatLossSplineAreaRelatedValues"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(checkBoxHeatLossSplineAreaRelatedValues->sizePolicy().hasHeightForWidth());
        checkBoxHeatLossSplineAreaRelatedValues->setSizePolicy(sizePolicy4);
        checkBoxHeatLossSplineAreaRelatedValues->setMinimumSize(QSize(0, 0));
        checkBoxHeatLossSplineAreaRelatedValues->setMaximumSize(QSize(190, 16777215));

        horizontalLayoutHeatLossSplineFloorArea->addWidget(checkBoxHeatLossSplineAreaRelatedValues);

        lineEditHeatLossSplineFloorArea = new QtExt::ValidatingLineEdit(page);
        lineEditHeatLossSplineFloorArea->setObjectName(QString::fromUtf8("lineEditHeatLossSplineFloorArea"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEditHeatLossSplineFloorArea->sizePolicy().hasHeightForWidth());
        lineEditHeatLossSplineFloorArea->setSizePolicy(sizePolicy5);
        lineEditHeatLossSplineFloorArea->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayoutHeatLossSplineFloorArea->addWidget(lineEditHeatLossSplineFloorArea);

        labelHeatLossSplineFloorAreaUnit = new QLabel(page);
        labelHeatLossSplineFloorAreaUnit->setObjectName(QString::fromUtf8("labelHeatLossSplineFloorAreaUnit"));

        horizontalLayoutHeatLossSplineFloorArea->addWidget(labelHeatLossSplineFloorAreaUnit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutHeatLossSplineFloorArea->addItem(horizontalSpacer_2);


        verticalLayout_10->addLayout(horizontalLayoutHeatLossSplineFloorArea);

        stackedWidgetHeatLossSpline->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_9 = new QVBoxLayout(page_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 12, 0, -1);
        horizontalLayoutFilePath = new QHBoxLayout();
        horizontalLayoutFilePath->setObjectName(QString::fromUtf8("horizontalLayoutFilePath"));
        labelFilePath = new QLabel(page_2);
        labelFilePath->setObjectName(QString::fromUtf8("labelFilePath"));
        sizePolicy1.setHeightForWidth(labelFilePath->sizePolicy().hasHeightForWidth());
        labelFilePath->setSizePolicy(sizePolicy1);
        labelFilePath->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayoutFilePath->addWidget(labelFilePath);

        filepathDataFile = new QtExt::BrowseFilenameWidget(page_2);
        filepathDataFile->setObjectName(QString::fromUtf8("filepathDataFile"));
        sizePolicy4.setHeightForWidth(filepathDataFile->sizePolicy().hasHeightForWidth());
        filepathDataFile->setSizePolicy(sizePolicy4);
        filepathDataFile->setMaximumSize(QSize(16777215, 24));

        horizontalLayoutFilePath->addWidget(filepathDataFile);


        verticalLayout_9->addLayout(horizontalLayoutFilePath);

        labelHeatLossSplineSelectColumn = new QLabel(page_2);
        labelHeatLossSplineSelectColumn->setObjectName(QString::fromUtf8("labelHeatLossSplineSelectColumn"));

        verticalLayout_9->addWidget(labelHeatLossSplineSelectColumn);

        listWidgetHeatLossSplineSelectColumn = new QListWidget(page_2);
        listWidgetHeatLossSplineSelectColumn->setObjectName(QString::fromUtf8("listWidgetHeatLossSplineSelectColumn"));
        listWidgetHeatLossSplineSelectColumn->setMaximumSize(QSize(16777215, 100));

        verticalLayout_9->addWidget(listWidgetHeatLossSplineSelectColumn);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_3);

        stackedWidgetHeatLossSpline->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidgetHeatLossSpline);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        widgetPlotHeatLossSpline = new QwtPlot(widgetDefineHeatExchangeSpline);
        widgetPlotHeatLossSpline->setObjectName(QString::fromUtf8("widgetPlotHeatLossSpline"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(widgetPlotHeatLossSpline->sizePolicy().hasHeightForWidth());
        widgetPlotHeatLossSpline->setSizePolicy(sizePolicy6);
        widgetPlotHeatLossSpline->setMinimumSize(QSize(405, 201));
        widgetPlotHeatLossSpline->setFrameShape(QFrame::StyledPanel);
        widgetPlotHeatLossSpline->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(widgetPlotHeatLossSpline);


        verticalLayout_8->addWidget(widgetDefineHeatExchangeSpline);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButtonShowYear = new QRadioButton(pageHeatLossSpline);
        radioButtonShowYear->setObjectName(QString::fromUtf8("radioButtonShowYear"));

        horizontalLayout_2->addWidget(radioButtonShowYear);

        radioButtonShowDay = new QRadioButton(pageHeatLossSpline);
        radioButtonShowDay->setObjectName(QString::fromUtf8("radioButtonShowDay"));

        horizontalLayout_2->addWidget(radioButtonShowDay);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_8->addLayout(horizontalLayout_2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_7);

        stackedWidgetHeatExchange->addWidget(pageHeatLossSpline);
        pageNone = new QWidget();
        pageNone->setObjectName(QString::fromUtf8("pageNone"));
        sizePolicy.setHeightForWidth(pageNone->sizePolicy().hasHeightForWidth());
        pageNone->setSizePolicy(sizePolicy);
        verticalLayoutPageNone = new QVBoxLayout(pageNone);
        verticalLayoutPageNone->setSpacing(0);
        verticalLayoutPageNone->setObjectName(QString::fromUtf8("verticalLayoutPageNone"));
        verticalLayoutPageNone->setContentsMargins(0, 0, 0, 0);
        labelPageNone = new QLabel(pageNone);
        labelPageNone->setObjectName(QString::fromUtf8("labelPageNone"));

        verticalLayoutPageNone->addWidget(labelPageNone);

        verticalSpacerNone = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutPageNone->addItem(verticalSpacerNone);

        stackedWidgetHeatExchange->addWidget(pageNone);

        verticalLayout_4->addWidget(stackedWidgetHeatExchange);


        retranslateUi(SVNetworkComponentHeatExchangeEditWidget);

        stackedWidgetHeatExchange->setCurrentIndex(0);
        stackedWidgetHeatLossSpline->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVNetworkComponentHeatExchangeEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVNetworkComponentHeatExchangeEditWidget)
    {
        SVNetworkComponentHeatExchangeEditWidget->setWindowTitle(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Form", nullptr));
        checkBoxExternallyDefined->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "externally defined in network node", nullptr));
        labelTemperatureConstantTemperature->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Temperature:", nullptr));
        labelTemperatureConstantHeatTransferCoefficientUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "W/m\302\262K", nullptr));
        labelTemperatureConstantTemperatureUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "\302\260C", nullptr));
        checkBoxTemperatureConstantHeatTransferCoeff->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heat Transfer Coefficient:", nullptr));
        labelTemperatureSplineHeatTransferCoefficientUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "W/m\302\262K", nullptr));
        labelTemperatureConstantHeatTransferCoefficient_3->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Temperature", nullptr));
        checkBoxTemperatureSplineHeatTransferCoefficient->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heat Transfer Coefficient:", nullptr));
        labelTemperatureSplineHeatFilePath->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "File Path ", nullptr));
        labelTemperatureSplineSelectColumn->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Select Column In Data file", nullptr));
        labelHeatLossConstantUserHeatFlux->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heat Flux:", nullptr));
        labelHeatLossConstantSupplyTemperatureUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "C", nullptr));
        labelHeatLossConstantUserUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kW", nullptr));
        labelHeatLossConstantSupplyTemperature->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Supply Temperature:", nullptr));
        toolButtonSetDefaultValues->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Reset ", nullptr));
        labelHeatLossSplineUserBuildingType->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Building Type:", nullptr));
        labelHeatLossSplineHeatingEnergyDemand->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heating Energy Demand:", nullptr));
        labelHeatLossSplineMaximumHeatingLoadUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kW", nullptr));
        labelHeatLossSplineHeatingSupplyTemp->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heating Supply Temperature:", nullptr));
        labelHeatLossSplineMaximumHeatingLoad->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Maximum Heating Load:", nullptr));
        labelHeatLossSplineHeatingEnergyDemandUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kWh", nullptr));
        labelHeatLossSplineHeatingSupplyTempUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "C", nullptr));
        checkBoxDHW->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "use Domestic Hot Water (DHW)", nullptr));
        labelHeatLossSplineDomesticHotWaterDemandUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kWh", nullptr));
        labelHeatLossSplineDomesticHotWaterDemandUnit_3->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "%", nullptr));
        labelHeatLossSplineDomesticHotWaterDemand->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "DHW Energy Demand:", nullptr));
        labelHeatLossSplineDomesticHotWaterDemand_2->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Share of DHW:", nullptr));
        labelHeatLossSplineDHWSupplyTemp->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "DHW Supply Temperature:", nullptr));
        labelHeatLossSplineDHWSupplyTempUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "C", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Heating and DHW", nullptr));
        checkBoxCooling->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "use Cooling", nullptr));
        labelHeatLossSplineCoolingEnergyDemand->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Cooling Energy Demand:", nullptr));
        labelHeatLossSplineMaximumCoolingLoad->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Maximum Cooling Load:", nullptr));
        labelHeatLossSplineCoolingEnergyDemandUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kWh", nullptr));
        labelHeatLossSplineMaximumCoolingLoadUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "kW", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Cooling", nullptr));
        checkBoxHeatLossSplineAreaRelatedValues->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Related to floor area", nullptr));
        labelHeatLossSplineFloorAreaUnit->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "m\302\262", nullptr));
        labelFilePath->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Filepath", nullptr));
        labelHeatLossSplineSelectColumn->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "Select Column In Data file", nullptr));
        radioButtonShowYear->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "show year", nullptr));
        radioButtonShowDay->setText(QCoreApplication::translate("SVNetworkComponentHeatExchangeEditWidget", "show day", nullptr));
        labelPageNone->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SVNetworkComponentHeatExchangeEditWidget: public Ui_SVNetworkComponentHeatExchangeEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKCOMPONENTHEATEXCHANGEEDITWIDGET_H
