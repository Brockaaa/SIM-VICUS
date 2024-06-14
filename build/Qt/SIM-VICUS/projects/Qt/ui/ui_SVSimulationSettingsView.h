/********************************************************************************
** Form generated from reading UI file 'SVSimulationSettingsView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONSETTINGSVIEW_H
#define UI_SVSIMULATIONSETTINGSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationSettingsView
{
public:
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_0;
    QWidget *page1;
    QWidget *pageSimulation;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidgetSimulation;
    QWidget *tabSimulationStart;
    QWidget *tabSimulationOutputs;
    QWidget *tabSimulationModelOptions;
    QWidget *tabSimulationPerformanceOptions;
    QWidget *tabNetworkSettings;
    QWidget *page3;
    QWidget *page_4;

    void setupUi(QWidget *SVSimulationSettingsView)
    {
        if (SVSimulationSettingsView->objectName().isEmpty())
            SVSimulationSettingsView->setObjectName(QString::fromUtf8("SVSimulationSettingsView"));
        SVSimulationSettingsView->resize(1318, 839);
        horizontalLayout_2 = new QHBoxLayout(SVSimulationSettingsView);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listWidget = new QListWidget(SVSimulationSettingsView);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(220, 0));
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setFrameShape(QFrame::StyledPanel);
        listWidget->setFrameShadow(QFrame::Sunken);
        listWidget->setLineWidth(1);
        listWidget->setMidLineWidth(0);

        horizontalLayout_2->addWidget(listWidget);

        stackedWidget = new QStackedWidget(SVSimulationSettingsView);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_0 = new QWidget();
        page_0->setObjectName(QString::fromUtf8("page_0"));
        stackedWidget->addWidget(page_0);
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        stackedWidget->addWidget(page1);
        pageSimulation = new QWidget();
        pageSimulation->setObjectName(QString::fromUtf8("pageSimulation"));
        verticalLayout = new QVBoxLayout(pageSimulation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidgetSimulation = new QTabWidget(pageSimulation);
        tabWidgetSimulation->setObjectName(QString::fromUtf8("tabWidgetSimulation"));
        tabWidgetSimulation->setMinimumSize(QSize(200, 0));
        QFont font;
        font.setPointSize(9);
        tabWidgetSimulation->setFont(font);
        tabWidgetSimulation->setTabPosition(QTabWidget::North);
        tabSimulationStart = new QWidget();
        tabSimulationStart->setObjectName(QString::fromUtf8("tabSimulationStart"));
        QFont font1;
        font1.setPointSize(12);
        tabSimulationStart->setFont(font1);
        tabWidgetSimulation->addTab(tabSimulationStart, QString());
        tabSimulationOutputs = new QWidget();
        tabSimulationOutputs->setObjectName(QString::fromUtf8("tabSimulationOutputs"));
        tabWidgetSimulation->addTab(tabSimulationOutputs, QString());
        tabSimulationModelOptions = new QWidget();
        tabSimulationModelOptions->setObjectName(QString::fromUtf8("tabSimulationModelOptions"));
        tabWidgetSimulation->addTab(tabSimulationModelOptions, QString());
        tabSimulationPerformanceOptions = new QWidget();
        tabSimulationPerformanceOptions->setObjectName(QString::fromUtf8("tabSimulationPerformanceOptions"));
        tabWidgetSimulation->addTab(tabSimulationPerformanceOptions, QString());
        tabNetworkSettings = new QWidget();
        tabNetworkSettings->setObjectName(QString::fromUtf8("tabNetworkSettings"));
        tabWidgetSimulation->addTab(tabNetworkSettings, QString());

        verticalLayout->addWidget(tabWidgetSimulation);

        stackedWidget->addWidget(pageSimulation);
        page3 = new QWidget();
        page3->setObjectName(QString::fromUtf8("page3"));
        stackedWidget->addWidget(page3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        stackedWidget->addWidget(page_4);

        horizontalLayout_2->addWidget(stackedWidget);


        retranslateUi(SVSimulationSettingsView);

        stackedWidget->setCurrentIndex(4);
        tabWidgetSimulation->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVSimulationSettingsView);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationSettingsView)
    {
        SVSimulationSettingsView->setWindowTitle(QCoreApplication::translate("SVSimulationSettingsView", "Form", nullptr));
        tabWidgetSimulation->setTabText(tabWidgetSimulation->indexOf(tabSimulationStart), QCoreApplication::translate("SVSimulationSettingsView", "Start Simulation", nullptr));
        tabWidgetSimulation->setTabText(tabWidgetSimulation->indexOf(tabSimulationOutputs), QCoreApplication::translate("SVSimulationSettingsView", "Outputs", nullptr));
        tabWidgetSimulation->setTabText(tabWidgetSimulation->indexOf(tabSimulationModelOptions), QCoreApplication::translate("SVSimulationSettingsView", "Model settings", nullptr));
        tabWidgetSimulation->setTabText(tabWidgetSimulation->indexOf(tabSimulationPerformanceOptions), QCoreApplication::translate("SVSimulationSettingsView", "Performance options", nullptr));
        tabWidgetSimulation->setTabText(tabWidgetSimulation->indexOf(tabNetworkSettings), QCoreApplication::translate("SVSimulationSettingsView", "Network settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationSettingsView: public Ui_SVSimulationSettingsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONSETTINGSVIEW_H
