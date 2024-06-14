/********************************************************************************
** Form generated from reading UI file 'SVDBSurfaceHeatingEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSURFACEHEATINGEDITWIDGET_H
#define UI_SVDBSURFACEHEATINGEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBSurfaceHeatingEditWidget
{
public:
    QVBoxLayout *masterLayout;
    QGridLayout *gridLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelAirChangeRate;
    QtExt::ValidatingLineEdit *lineEditHeatingLimit;
    QLabel *labelAirChangeRateUnit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelShieldCoefficient;
    QtExt::ValidatingLineEdit *lineEditCoolingLimit;
    QLabel *labelShieldCoefficientUnit;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSubTemplate;
    QLineEdit *lineEditPipeName;
    QToolButton *toolButtonSelectPipes;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *labelShieldCoefficient_4;
    QtExt::ValidatingLineEdit *lineEditTemperaturDifference;
    QtExt::ValidatingLineEdit *lineEditFluidVelocity;
    QLabel *labelShieldCoefficient_3;
    QtExt::ValidatingLineEdit *lineEditPipeSpacing;
    QLabel *labelShieldCoefficient_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidgetCooling;
    QTableWidget *tableWidgetHeating;
    QwtPlot *widgetPlotHeatingCurve;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBSurfaceHeatingEditWidget)
    {
        if (SVDBSurfaceHeatingEditWidget->objectName().isEmpty())
            SVDBSurfaceHeatingEditWidget->setObjectName(QString::fromUtf8("SVDBSurfaceHeatingEditWidget"));
        SVDBSurfaceHeatingEditWidget->resize(846, 426);
        masterLayout = new QVBoxLayout(SVDBSurfaceHeatingEditWidget);
        masterLayout->setObjectName(QString::fromUtf8("masterLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelDisplayName = new QLabel(SVDBSurfaceHeatingEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBSurfaceHeatingEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 0, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBSurfaceHeatingEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonColor, 0, 2, 1, 1);

        labelType = new QLabel(SVDBSurfaceHeatingEditWidget);
        labelType->setObjectName(QString::fromUtf8("labelType"));

        gridLayout->addWidget(labelType, 1, 0, 1, 1);

        comboBoxType = new QComboBox(SVDBSurfaceHeatingEditWidget);
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));

        gridLayout->addWidget(comboBoxType, 1, 1, 1, 1);


        masterLayout->addLayout(gridLayout);

        stackedWidget = new QStackedWidget(SVDBSurfaceHeatingEditWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelAirChangeRate = new QLabel(page);
        labelAirChangeRate->setObjectName(QString::fromUtf8("labelAirChangeRate"));

        horizontalLayout_2->addWidget(labelAirChangeRate);

        lineEditHeatingLimit = new QtExt::ValidatingLineEdit(page);
        lineEditHeatingLimit->setObjectName(QString::fromUtf8("lineEditHeatingLimit"));
        lineEditHeatingLimit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(lineEditHeatingLimit);

        labelAirChangeRateUnit = new QLabel(page);
        labelAirChangeRateUnit->setObjectName(QString::fromUtf8("labelAirChangeRateUnit"));

        horizontalLayout_2->addWidget(labelAirChangeRateUnit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelShieldCoefficient = new QLabel(page);
        labelShieldCoefficient->setObjectName(QString::fromUtf8("labelShieldCoefficient"));

        horizontalLayout_3->addWidget(labelShieldCoefficient);

        lineEditCoolingLimit = new QtExt::ValidatingLineEdit(page);
        lineEditCoolingLimit->setObjectName(QString::fromUtf8("lineEditCoolingLimit"));
        lineEditCoolingLimit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(lineEditCoolingLimit);

        labelShieldCoefficientUnit = new QLabel(page);
        labelShieldCoefficientUnit->setObjectName(QString::fromUtf8("labelShieldCoefficientUnit"));

        horizontalLayout_3->addWidget(labelShieldCoefficientUnit);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSubTemplate = new QLabel(page_2);
        labelSubTemplate->setObjectName(QString::fromUtf8("labelSubTemplate"));

        horizontalLayout->addWidget(labelSubTemplate);

        lineEditPipeName = new QLineEdit(page_2);
        lineEditPipeName->setObjectName(QString::fromUtf8("lineEditPipeName"));
        lineEditPipeName->setReadOnly(true);

        horizontalLayout->addWidget(lineEditPipeName);

        toolButtonSelectPipes = new QToolButton(page_2);
        toolButtonSelectPipes->setObjectName(QString::fromUtf8("toolButtonSelectPipes"));

        horizontalLayout->addWidget(toolButtonSelectPipes);


        verticalLayout_3->addLayout(horizontalLayout);

        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        labelShieldCoefficient_4 = new QLabel(groupBox_2);
        labelShieldCoefficient_4->setObjectName(QString::fromUtf8("labelShieldCoefficient_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, labelShieldCoefficient_4);

        lineEditTemperaturDifference = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditTemperaturDifference->setObjectName(QString::fromUtf8("lineEditTemperaturDifference"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditTemperaturDifference->sizePolicy().hasHeightForWidth());
        lineEditTemperaturDifference->setSizePolicy(sizePolicy1);
        lineEditTemperaturDifference->setMaximumSize(QSize(16777215, 16777215));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEditTemperaturDifference);

        lineEditFluidVelocity = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditFluidVelocity->setObjectName(QString::fromUtf8("lineEditFluidVelocity"));
        sizePolicy1.setHeightForWidth(lineEditFluidVelocity->sizePolicy().hasHeightForWidth());
        lineEditFluidVelocity->setSizePolicy(sizePolicy1);
        lineEditFluidVelocity->setMaximumSize(QSize(16777215, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEditFluidVelocity);

        labelShieldCoefficient_3 = new QLabel(groupBox_2);
        labelShieldCoefficient_3->setObjectName(QString::fromUtf8("labelShieldCoefficient_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelShieldCoefficient_3);

        lineEditPipeSpacing = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditPipeSpacing->setObjectName(QString::fromUtf8("lineEditPipeSpacing"));
        sizePolicy1.setHeightForWidth(lineEditPipeSpacing->sizePolicy().hasHeightForWidth());
        lineEditPipeSpacing->setSizePolicy(sizePolicy1);
        lineEditPipeSpacing->setMaximumSize(QSize(16777215, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditPipeSpacing);

        labelShieldCoefficient_2 = new QLabel(groupBox_2);
        labelShieldCoefficient_2->setObjectName(QString::fromUtf8("labelShieldCoefficient_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelShieldCoefficient_2);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidgetCooling = new QTableWidget(groupBox);
        tableWidgetCooling->setObjectName(QString::fromUtf8("tableWidgetCooling"));
        tableWidgetCooling->setMinimumSize(QSize(400, 0));

        gridLayout_2->addWidget(tableWidgetCooling, 3, 0, 1, 1);

        tableWidgetHeating = new QTableWidget(groupBox);
        tableWidgetHeating->setObjectName(QString::fromUtf8("tableWidgetHeating"));
        tableWidgetHeating->setMinimumSize(QSize(400, 0));

        gridLayout_2->addWidget(tableWidgetHeating, 1, 0, 1, 1);

        widgetPlotHeatingCurve = new QwtPlot(groupBox);
        widgetPlotHeatingCurve->setObjectName(QString::fromUtf8("widgetPlotHeatingCurve"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetPlotHeatingCurve->sizePolicy().hasHeightForWidth());
        widgetPlotHeatingCurve->setSizePolicy(sizePolicy2);
        widgetPlotHeatingCurve->setMinimumSize(QSize(400, 0));

        gridLayout_2->addWidget(widgetPlotHeatingCurve, 1, 2, 3, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        stackedWidget->addWidget(page_2);

        masterLayout->addWidget(stackedWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        masterLayout->addItem(verticalSpacer);


        retranslateUi(SVDBSurfaceHeatingEditWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVDBSurfaceHeatingEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBSurfaceHeatingEditWidget)
    {
        SVDBSurfaceHeatingEditWidget->setWindowTitle(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Name:", nullptr));
        labelType->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Type:", nullptr));
        labelAirChangeRate->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Max. heating limit:", nullptr));
        labelAirChangeRateUnit->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "W/m2", nullptr));
        labelShieldCoefficient->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Max. cooling limit:", nullptr));
        labelShieldCoefficientUnit->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "W/m2", nullptr));
        labelSubTemplate->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Pipe:", nullptr));
        toolButtonSelectPipes->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "System parameter", nullptr));
        labelShieldCoefficient_4->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Temperature difference between supply and return [K]:", nullptr));
        labelShieldCoefficient_3->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Maximum fluid velocity [m/s]:", nullptr));
        labelShieldCoefficient_2->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Pipe spacing [m]:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Curves", nullptr));
        label->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Heating", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBSurfaceHeatingEditWidget", "Cooling", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBSurfaceHeatingEditWidget: public Ui_SVDBSurfaceHeatingEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSURFACEHEATINGEDITWIDGET_H
