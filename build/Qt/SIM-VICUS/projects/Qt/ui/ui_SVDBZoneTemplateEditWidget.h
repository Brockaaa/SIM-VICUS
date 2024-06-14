/********************************************************************************
** Form generated from reading UI file 'SVDBZoneTemplateEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONETEMPLATEEDITWIDGET_H
#define UI_SVDBZONETEMPLATEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBZoneTemplateEditWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_4;
    QGroupBox *internalLoads;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonAddElectricLoad;
    QPushButton *pushButtonAddPersonLoad;
    QPushButton *pushButtonAddOtherLoad;
    QPushButton *pushButtonAddLightLoad;
    QGroupBox *infiltrationVentilation;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonAddInfiltration;
    QPushButton *pushButtonAddVentilationNatural;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *Controls;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonAddThermostat;
    QPushButton *pushButtonAddShading;
    QPushButton *pushButtonAddVentilationNaturalControl;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QPushButton *pushButtonAddIdealHeatingCooling;
    QWidget *widget;
    QVBoxLayout *verticalLayoutWidget;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSubTemplate;
    QLineEdit *lineEditSubComponent;
    QToolButton *toolButtonSelectSubComponent;
    QToolButton *toolButtonRemoveSubComponent;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBZoneTemplateEditWidget)
    {
        if (SVDBZoneTemplateEditWidget->objectName().isEmpty())
            SVDBZoneTemplateEditWidget->setObjectName(QString::fromUtf8("SVDBZoneTemplateEditWidget"));
        SVDBZoneTemplateEditWidget->resize(747, 728);
        SVDBZoneTemplateEditWidget->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(SVDBZoneTemplateEditWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelDisplayName = new QLabel(SVDBZoneTemplateEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBZoneTemplateEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout_2->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBZoneTemplateEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButtonColor);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        internalLoads = new QGroupBox(SVDBZoneTemplateEditWidget);
        internalLoads->setObjectName(QString::fromUtf8("internalLoads"));
        verticalLayout_3 = new QVBoxLayout(internalLoads);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButtonAddElectricLoad = new QPushButton(internalLoads);
        pushButtonAddElectricLoad->setObjectName(QString::fromUtf8("pushButtonAddElectricLoad"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddElectricLoad->setIcon(icon);
        pushButtonAddElectricLoad->setCheckable(true);

        verticalLayout_3->addWidget(pushButtonAddElectricLoad);

        pushButtonAddPersonLoad = new QPushButton(internalLoads);
        pushButtonAddPersonLoad->setObjectName(QString::fromUtf8("pushButtonAddPersonLoad"));
        pushButtonAddPersonLoad->setIcon(icon);
        pushButtonAddPersonLoad->setCheckable(true);

        verticalLayout_3->addWidget(pushButtonAddPersonLoad);

        pushButtonAddOtherLoad = new QPushButton(internalLoads);
        pushButtonAddOtherLoad->setObjectName(QString::fromUtf8("pushButtonAddOtherLoad"));
        pushButtonAddOtherLoad->setEnabled(false);
        pushButtonAddOtherLoad->setIcon(icon);
        pushButtonAddOtherLoad->setCheckable(true);

        verticalLayout_3->addWidget(pushButtonAddOtherLoad);

        pushButtonAddLightLoad = new QPushButton(internalLoads);
        pushButtonAddLightLoad->setObjectName(QString::fromUtf8("pushButtonAddLightLoad"));
        pushButtonAddLightLoad->setIcon(icon);
        pushButtonAddLightLoad->setCheckable(true);

        verticalLayout_3->addWidget(pushButtonAddLightLoad);


        gridLayout_4->addWidget(internalLoads, 0, 1, 1, 1);

        infiltrationVentilation = new QGroupBox(SVDBZoneTemplateEditWidget);
        infiltrationVentilation->setObjectName(QString::fromUtf8("infiltrationVentilation"));
        verticalLayout_2 = new QVBoxLayout(infiltrationVentilation);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButtonAddInfiltration = new QPushButton(infiltrationVentilation);
        pushButtonAddInfiltration->setObjectName(QString::fromUtf8("pushButtonAddInfiltration"));
        pushButtonAddInfiltration->setIcon(icon);
        pushButtonAddInfiltration->setCheckable(true);

        verticalLayout_2->addWidget(pushButtonAddInfiltration);

        pushButtonAddVentilationNatural = new QPushButton(infiltrationVentilation);
        pushButtonAddVentilationNatural->setObjectName(QString::fromUtf8("pushButtonAddVentilationNatural"));
        pushButtonAddVentilationNatural->setIcon(icon);
        pushButtonAddVentilationNatural->setCheckable(true);

        verticalLayout_2->addWidget(pushButtonAddVentilationNatural);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        gridLayout_4->addWidget(infiltrationVentilation, 0, 2, 1, 1);

        Controls = new QGroupBox(SVDBZoneTemplateEditWidget);
        Controls->setObjectName(QString::fromUtf8("Controls"));
        verticalLayout = new QVBoxLayout(Controls);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonAddThermostat = new QPushButton(Controls);
        pushButtonAddThermostat->setObjectName(QString::fromUtf8("pushButtonAddThermostat"));
        pushButtonAddThermostat->setIcon(icon);
        pushButtonAddThermostat->setCheckable(true);

        verticalLayout->addWidget(pushButtonAddThermostat);

        pushButtonAddShading = new QPushButton(Controls);
        pushButtonAddShading->setObjectName(QString::fromUtf8("pushButtonAddShading"));
        pushButtonAddShading->setIcon(icon);
        pushButtonAddShading->setCheckable(true);
        pushButtonAddShading->setChecked(false);

        verticalLayout->addWidget(pushButtonAddShading);

        pushButtonAddVentilationNaturalControl = new QPushButton(Controls);
        pushButtonAddVentilationNaturalControl->setObjectName(QString::fromUtf8("pushButtonAddVentilationNaturalControl"));
        pushButtonAddVentilationNaturalControl->setIcon(icon);
        pushButtonAddVentilationNaturalControl->setCheckable(true);

        verticalLayout->addWidget(pushButtonAddVentilationNaturalControl);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        gridLayout_4->addWidget(Controls, 0, 3, 1, 1);

        groupBox = new QGroupBox(SVDBZoneTemplateEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButtonAddIdealHeatingCooling = new QPushButton(groupBox);
        pushButtonAddIdealHeatingCooling->setObjectName(QString::fromUtf8("pushButtonAddIdealHeatingCooling"));
        pushButtonAddIdealHeatingCooling->setIcon(icon);
        pushButtonAddIdealHeatingCooling->setCheckable(true);

        gridLayout_5->addWidget(pushButtonAddIdealHeatingCooling, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 1, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);

        widget = new QWidget(SVDBZoneTemplateEditWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayoutWidget = new QVBoxLayout(widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayoutWidget->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSubTemplate = new QLabel(widget);
        labelSubTemplate->setObjectName(QString::fromUtf8("labelSubTemplate"));

        horizontalLayout->addWidget(labelSubTemplate);

        lineEditSubComponent = new QLineEdit(widget);
        lineEditSubComponent->setObjectName(QString::fromUtf8("lineEditSubComponent"));
        lineEditSubComponent->setReadOnly(true);

        horizontalLayout->addWidget(lineEditSubComponent);

        toolButtonSelectSubComponent = new QToolButton(widget);
        toolButtonSelectSubComponent->setObjectName(QString::fromUtf8("toolButtonSelectSubComponent"));

        horizontalLayout->addWidget(toolButtonSelectSubComponent);

        toolButtonRemoveSubComponent = new QToolButton(widget);
        toolButtonRemoveSubComponent->setObjectName(QString::fromUtf8("toolButtonRemoveSubComponent"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveSubComponent->setIcon(icon1);

        horizontalLayout->addWidget(toolButtonRemoveSubComponent);


        verticalLayoutWidget->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 283, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalLayout_4->setStretch(4, 1);

        retranslateUi(SVDBZoneTemplateEditWidget);

        QMetaObject::connectSlotsByName(SVDBZoneTemplateEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBZoneTemplateEditWidget)
    {
        SVDBZoneTemplateEditWidget->setWindowTitle(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Name:", nullptr));
        internalLoads->setTitle(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Internal loads", nullptr));
        pushButtonAddElectricLoad->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Electric Equipment", nullptr));
        pushButtonAddPersonLoad->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Person", nullptr));
        pushButtonAddOtherLoad->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Other", nullptr));
        pushButtonAddLightLoad->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Lights", nullptr));
        infiltrationVentilation->setTitle(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Infiltration/Ventilation", nullptr));
        pushButtonAddInfiltration->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Infiltration", nullptr));
        pushButtonAddVentilationNatural->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Natural Ventilation", nullptr));
        Controls->setTitle(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Controls", nullptr));
        pushButtonAddThermostat->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Thermostat", nullptr));
        pushButtonAddShading->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Shading", nullptr));
        pushButtonAddVentilationNaturalControl->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Natural Ventilation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "HVAC", nullptr));
        pushButtonAddIdealHeatingCooling->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "Ideal Heating/Cooling", nullptr));
        labelSubTemplate->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "TextLabel", nullptr));
        toolButtonSelectSubComponent->setText(QCoreApplication::translate("SVDBZoneTemplateEditWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneTemplateEditWidget: public Ui_SVDBZoneTemplateEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONETEMPLATEEDITWIDGET_H
