/********************************************************************************
** Form generated from reading UI file 'SVNetworkComponentEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKCOMPONENTEDITWIDGET_H
#define UI_SVNETWORKCOMPONENTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_SVNetworkComponentEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabComponent;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonComponentDBDialogOpen;
    QTableWidget *tableWidgetParameters;
    QWidget *widgetPolynom;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QTableWidget *tableWidgetPolynomCoefficients;
    QTabWidget *tabWidgetPlots;
    QWidget *plotTab1;
    QVBoxLayout *verticalLayout_5;
    QwtPlot *widgetPlot1;
    QWidget *plotTab2;
    QVBoxLayout *verticalLayout_4;
    QwtPlot *widgetPlot2;
    QWidget *widgetController;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelController;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEditController;
    QToolButton *toolButtonControllerSet;
    QToolButton *toolButtonControllerRemove;
    QWidget *widgetSchedules;
    QGridLayout *gridLayout_2;
    QToolButton *toolButtonSchedule1;
    QLineEdit *lineEditSchedule1;
    QToolButton *toolButtonSchedule2;
    QLineEdit *lineEditSchedule2;
    QLabel *labelSchedule1;
    QLabel *labelSchedule2;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *widgetPipeProperties;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditPipeProperties;
    QToolButton *toolButtonPipeProperties;
    QSpacerItem *verticalSpacerComponent;
    QWidget *tabHeatExchange;
    QVBoxLayout *verticalLayoutTabHeatExchange;

    void setupUi(QWidget *SVNetworkComponentEditWidget)
    {
        if (SVNetworkComponentEditWidget->objectName().isEmpty())
            SVNetworkComponentEditWidget->setObjectName(QString::fromUtf8("SVNetworkComponentEditWidget"));
        SVNetworkComponentEditWidget->resize(1044, 2254);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(SVNetworkComponentEditWidget->sizePolicy().hasHeightForWidth());
        SVNetworkComponentEditWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SVNetworkComponentEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SVNetworkComponentEditWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setTabBarAutoHide(true);
        tabComponent = new QWidget();
        tabComponent->setObjectName(QString::fromUtf8("tabComponent"));
        sizePolicy.setHeightForWidth(tabComponent->sizePolicy().hasHeightForWidth());
        tabComponent->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(tabComponent);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(tabComponent);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonComponentDBDialogOpen = new QPushButton(tabComponent);
        pushButtonComponentDBDialogOpen->setObjectName(QString::fromUtf8("pushButtonComponentDBDialogOpen"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonComponentDBDialogOpen->sizePolicy().hasHeightForWidth());
        pushButtonComponentDBDialogOpen->setSizePolicy(sizePolicy1);
        pushButtonComponentDBDialogOpen->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(pushButtonComponentDBDialogOpen);


        verticalLayout_6->addLayout(horizontalLayout_2);

        tableWidgetParameters = new QTableWidget(tabComponent);
        tableWidgetParameters->setObjectName(QString::fromUtf8("tableWidgetParameters"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidgetParameters->sizePolicy().hasHeightForWidth());
        tableWidgetParameters->setSizePolicy(sizePolicy2);
        tableWidgetParameters->setMaximumSize(QSize(16777215, 16777215));
        tableWidgetParameters->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetParameters->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidgetParameters->setAutoScroll(true);
        tableWidgetParameters->setShowGrid(true);

        verticalLayout_6->addWidget(tableWidgetParameters);

        widgetPolynom = new QWidget(tabComponent);
        widgetPolynom->setObjectName(QString::fromUtf8("widgetPolynom"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widgetPolynom->sizePolicy().hasHeightForWidth());
        widgetPolynom->setSizePolicy(sizePolicy3);
        verticalLayout_2 = new QVBoxLayout(widgetPolynom);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        label_2 = new QLabel(widgetPolynom);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        tableWidgetPolynomCoefficients = new QTableWidget(widgetPolynom);
        tableWidgetPolynomCoefficients->setObjectName(QString::fromUtf8("tableWidgetPolynomCoefficients"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tableWidgetPolynomCoefficients->sizePolicy().hasHeightForWidth());
        tableWidgetPolynomCoefficients->setSizePolicy(sizePolicy4);
        tableWidgetPolynomCoefficients->setMinimumSize(QSize(0, 0));
        tableWidgetPolynomCoefficients->setMaximumSize(QSize(16777215, 150));
        tableWidgetPolynomCoefficients->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidgetPolynomCoefficients->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidgetPolynomCoefficients->setShowGrid(true);

        verticalLayout_2->addWidget(tableWidgetPolynomCoefficients);

        tabWidgetPlots = new QTabWidget(widgetPolynom);
        tabWidgetPlots->setObjectName(QString::fromUtf8("tabWidgetPlots"));
        sizePolicy.setHeightForWidth(tabWidgetPlots->sizePolicy().hasHeightForWidth());
        tabWidgetPlots->setSizePolicy(sizePolicy);
        tabWidgetPlots->setMinimumSize(QSize(0, 250));
        tabWidgetPlots->setMaximumSize(QSize(16777215, 250));
        tabWidgetPlots->setTabPosition(QTabWidget::North);
        plotTab1 = new QWidget();
        plotTab1->setObjectName(QString::fromUtf8("plotTab1"));
        sizePolicy.setHeightForWidth(plotTab1->sizePolicy().hasHeightForWidth());
        plotTab1->setSizePolicy(sizePolicy);
        plotTab1->setMinimumSize(QSize(0, 0));
        plotTab1->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(plotTab1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widgetPlot1 = new QwtPlot(plotTab1);
        widgetPlot1->setObjectName(QString::fromUtf8("widgetPlot1"));
        sizePolicy.setHeightForWidth(widgetPlot1->sizePolicy().hasHeightForWidth());
        widgetPlot1->setSizePolicy(sizePolicy);
        widgetPlot1->setMinimumSize(QSize(0, 0));
        widgetPlot1->setMaximumSize(QSize(16777215, 220));

        verticalLayout_5->addWidget(widgetPlot1);

        tabWidgetPlots->addTab(plotTab1, QString());
        plotTab2 = new QWidget();
        plotTab2->setObjectName(QString::fromUtf8("plotTab2"));
        sizePolicy.setHeightForWidth(plotTab2->sizePolicy().hasHeightForWidth());
        plotTab2->setSizePolicy(sizePolicy);
        plotTab2->setMinimumSize(QSize(0, 0));
        plotTab2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_4 = new QVBoxLayout(plotTab2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widgetPlot2 = new QwtPlot(plotTab2);
        widgetPlot2->setObjectName(QString::fromUtf8("widgetPlot2"));
        sizePolicy.setHeightForWidth(widgetPlot2->sizePolicy().hasHeightForWidth());
        widgetPlot2->setSizePolicy(sizePolicy);
        widgetPlot2->setMinimumSize(QSize(0, 0));
        widgetPlot2->setMaximumSize(QSize(16777215, 220));

        verticalLayout_4->addWidget(widgetPlot2);

        tabWidgetPlots->addTab(plotTab2, QString());

        verticalLayout_2->addWidget(tabWidgetPlots);


        verticalLayout_6->addWidget(widgetPolynom);

        widgetController = new QWidget(tabComponent);
        widgetController->setObjectName(QString::fromUtf8("widgetController"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(widgetController->sizePolicy().hasHeightForWidth());
        widgetController->setSizePolicy(sizePolicy5);
        verticalLayout_3 = new QVBoxLayout(widgetController);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        labelController = new QLabel(widgetController);
        labelController->setObjectName(QString::fromUtf8("labelController"));
        labelController->setFont(font);

        verticalLayout_3->addWidget(labelController);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEditController = new QLineEdit(widgetController);
        lineEditController->setObjectName(QString::fromUtf8("lineEditController"));
        lineEditController->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEditController);

        toolButtonControllerSet = new QToolButton(widgetController);
        toolButtonControllerSet->setObjectName(QString::fromUtf8("toolButtonControllerSet"));

        horizontalLayout_3->addWidget(toolButtonControllerSet);

        toolButtonControllerRemove = new QToolButton(widgetController);
        toolButtonControllerRemove->setObjectName(QString::fromUtf8("toolButtonControllerRemove"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonControllerRemove->setIcon(icon);

        horizontalLayout_3->addWidget(toolButtonControllerRemove);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_6->addWidget(widgetController);

        widgetSchedules = new QWidget(tabComponent);
        widgetSchedules->setObjectName(QString::fromUtf8("widgetSchedules"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(widgetSchedules->sizePolicy().hasHeightForWidth());
        widgetSchedules->setSizePolicy(sizePolicy6);
        gridLayout_2 = new QGridLayout(widgetSchedules);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButtonSchedule1 = new QToolButton(widgetSchedules);
        toolButtonSchedule1->setObjectName(QString::fromUtf8("toolButtonSchedule1"));

        gridLayout_2->addWidget(toolButtonSchedule1, 2, 2, 1, 1);

        lineEditSchedule1 = new QLineEdit(widgetSchedules);
        lineEditSchedule1->setObjectName(QString::fromUtf8("lineEditSchedule1"));
        lineEditSchedule1->setReadOnly(true);

        gridLayout_2->addWidget(lineEditSchedule1, 2, 1, 1, 1);

        toolButtonSchedule2 = new QToolButton(widgetSchedules);
        toolButtonSchedule2->setObjectName(QString::fromUtf8("toolButtonSchedule2"));

        gridLayout_2->addWidget(toolButtonSchedule2, 3, 2, 1, 1);

        lineEditSchedule2 = new QLineEdit(widgetSchedules);
        lineEditSchedule2->setObjectName(QString::fromUtf8("lineEditSchedule2"));
        lineEditSchedule2->setReadOnly(true);

        gridLayout_2->addWidget(lineEditSchedule2, 3, 1, 1, 1);

        labelSchedule1 = new QLabel(widgetSchedules);
        labelSchedule1->setObjectName(QString::fromUtf8("labelSchedule1"));

        gridLayout_2->addWidget(labelSchedule1, 2, 0, 1, 1);

        labelSchedule2 = new QLabel(widgetSchedules);
        labelSchedule2->setObjectName(QString::fromUtf8("labelSchedule2"));

        gridLayout_2->addWidget(labelSchedule2, 3, 0, 1, 1);

        label_4 = new QLabel(widgetSchedules);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 3);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_5, 0, 0, 1, 1);


        verticalLayout_6->addWidget(widgetSchedules);

        widgetPipeProperties = new QWidget(tabComponent);
        widgetPipeProperties->setObjectName(QString::fromUtf8("widgetPipeProperties"));
        verticalLayout_7 = new QVBoxLayout(widgetPipeProperties);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_7->addItem(verticalSpacer_6);

        label_5 = new QLabel(widgetPipeProperties);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout_7->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditPipeProperties = new QLineEdit(widgetPipeProperties);
        lineEditPipeProperties->setObjectName(QString::fromUtf8("lineEditPipeProperties"));
        lineEditPipeProperties->setReadOnly(true);

        horizontalLayout->addWidget(lineEditPipeProperties);

        toolButtonPipeProperties = new QToolButton(widgetPipeProperties);
        toolButtonPipeProperties->setObjectName(QString::fromUtf8("toolButtonPipeProperties"));
        sizePolicy1.setHeightForWidth(toolButtonPipeProperties->sizePolicy().hasHeightForWidth());
        toolButtonPipeProperties->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(toolButtonPipeProperties);


        verticalLayout_7->addLayout(horizontalLayout);


        verticalLayout_6->addWidget(widgetPipeProperties);

        verticalSpacerComponent = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacerComponent);

        tabWidget->addTab(tabComponent, QString());
        tabHeatExchange = new QWidget();
        tabHeatExchange->setObjectName(QString::fromUtf8("tabHeatExchange"));
        sizePolicy.setHeightForWidth(tabHeatExchange->sizePolicy().hasHeightForWidth());
        tabHeatExchange->setSizePolicy(sizePolicy);
        verticalLayoutTabHeatExchange = new QVBoxLayout(tabHeatExchange);
        verticalLayoutTabHeatExchange->setSpacing(0);
        verticalLayoutTabHeatExchange->setObjectName(QString::fromUtf8("verticalLayoutTabHeatExchange"));
        verticalLayoutTabHeatExchange->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tabHeatExchange, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SVNetworkComponentEditWidget);

        tabWidget->setCurrentIndex(0);
        tabWidgetPlots->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SVNetworkComponentEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVNetworkComponentEditWidget)
    {
        SVNetworkComponentEditWidget->setWindowTitle(QCoreApplication::translate("SVNetworkComponentEditWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Model parameters", nullptr));
        pushButtonComponentDBDialogOpen->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "DB ...", nullptr));
        label_2->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Polynom ", nullptr));
        tabWidgetPlots->setTabText(tabWidgetPlots->indexOf(plotTab1), QString());
        tabWidgetPlots->setTabText(tabWidgetPlots->indexOf(plotTab2), QString());
        labelController->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Controller ", nullptr));
        toolButtonControllerSet->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "...", nullptr));
        toolButtonControllerRemove->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "...", nullptr));
        toolButtonSchedule1->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "...", nullptr));
        toolButtonSchedule2->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "...", nullptr));
        labelSchedule1->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Schedule 1", nullptr));
        labelSchedule2->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Schedule 2", nullptr));
        label_4->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Schedules", nullptr));
        label_5->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "Pipe properties", nullptr));
        toolButtonPipeProperties->setText(QCoreApplication::translate("SVNetworkComponentEditWidget", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabComponent), QCoreApplication::translate("SVNetworkComponentEditWidget", "Component", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabHeatExchange), QCoreApplication::translate("SVNetworkComponentEditWidget", "Heat Exchange", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkComponentEditWidget: public Ui_SVNetworkComponentEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKCOMPONENTEDITWIDGET_H
