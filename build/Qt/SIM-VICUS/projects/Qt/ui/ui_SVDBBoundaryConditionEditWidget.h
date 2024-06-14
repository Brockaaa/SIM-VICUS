/********************************************************************************
** Form generated from reading UI file 'SVDBBoundaryConditionEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBBOUNDARYCONDITIONEDITWIDGET_H
#define UI_SVDBBOUNDARYCONDITIONEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBBoundaryConditionEditWidget
{
public:
    QVBoxLayout *verticalLayoutMaster;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QGroupBox *groupBoxHeatTransfer;
    QGridLayout *gridLayout_4;
    QtExt::ValidatingLineEdit *lineEditHeatTransferCoefficient;
    QLabel *labelHeatTransferCoeffModelType;
    QLabel *labelHeatTransferCoefficient_2;
    QLabel *labelConnectedZoneType;
    QLabel *labelHeatTransferCoefficient;
    QtExt::ValidatingLineEdit *lineEditZoneConstTemperature;
    QLabel *labelZoneConstTemperature;
    QLabel *labelZoneConstTemperature_2;
    QComboBox *comboBoxConnectedZoneType;
    QComboBox *comboBoxHeatTransferCoeffModelType;
    QGridLayout *gridLayout;
    QLabel *labelScheduleZoneTemperature;
    QLineEdit *lineEditTemperatureScheduleName;
    QToolButton *toolButtonSelectTemperatureSchedule;
    QToolButton *toolButtonRemoveTemperatureSchedule;
    QGroupBox *groupBoxLongWaveExchange;
    QGridLayout *gridLayout_2;
    QLabel *labelLongWaveEmissivity;
    QtExt::ValidatingLineEdit *lineEditLongWaveEmissivity;
    QLabel *labelLongWaveEmissivity_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelLWModelType;
    QComboBox *comboBoxLWModelType;
    QGroupBox *groupBoxShortWaveRad;
    QGridLayout *gridLayout_3;
    QtExt::ValidatingLineEdit *lineEditSolarAbsorptionCoefficient;
    QLabel *labelSolarAbsorptionCoefficient;
    QLabel *labelSolarAbsorptionCoefficient_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelSWModelType;
    QComboBox *comboBoxSWModelType;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBBoundaryConditionEditWidget)
    {
        if (SVDBBoundaryConditionEditWidget->objectName().isEmpty())
            SVDBBoundaryConditionEditWidget->setObjectName(QString::fromUtf8("SVDBBoundaryConditionEditWidget"));
        SVDBBoundaryConditionEditWidget->resize(474, 518);
        verticalLayoutMaster = new QVBoxLayout(SVDBBoundaryConditionEditWidget);
        verticalLayoutMaster->setObjectName(QString::fromUtf8("verticalLayoutMaster"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBBoundaryConditionEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBBoundaryConditionEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBBoundaryConditionEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);
        pushButtonColor->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(pushButtonColor);


        verticalLayoutMaster->addLayout(horizontalLayout);

        groupBoxHeatTransfer = new QGroupBox(SVDBBoundaryConditionEditWidget);
        groupBoxHeatTransfer->setObjectName(QString::fromUtf8("groupBoxHeatTransfer"));
        gridLayout_4 = new QGridLayout(groupBoxHeatTransfer);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lineEditHeatTransferCoefficient = new QtExt::ValidatingLineEdit(groupBoxHeatTransfer);
        lineEditHeatTransferCoefficient->setObjectName(QString::fromUtf8("lineEditHeatTransferCoefficient"));

        gridLayout_4->addWidget(lineEditHeatTransferCoefficient, 2, 2, 1, 1);

        labelHeatTransferCoeffModelType = new QLabel(groupBoxHeatTransfer);
        labelHeatTransferCoeffModelType->setObjectName(QString::fromUtf8("labelHeatTransferCoeffModelType"));

        gridLayout_4->addWidget(labelHeatTransferCoeffModelType, 0, 0, 1, 1);

        labelHeatTransferCoefficient_2 = new QLabel(groupBoxHeatTransfer);
        labelHeatTransferCoefficient_2->setObjectName(QString::fromUtf8("labelHeatTransferCoefficient_2"));

        gridLayout_4->addWidget(labelHeatTransferCoefficient_2, 2, 3, 1, 1);

        labelConnectedZoneType = new QLabel(groupBoxHeatTransfer);
        labelConnectedZoneType->setObjectName(QString::fromUtf8("labelConnectedZoneType"));

        gridLayout_4->addWidget(labelConnectedZoneType, 1, 0, 1, 1);

        labelHeatTransferCoefficient = new QLabel(groupBoxHeatTransfer);
        labelHeatTransferCoefficient->setObjectName(QString::fromUtf8("labelHeatTransferCoefficient"));

        gridLayout_4->addWidget(labelHeatTransferCoefficient, 2, 0, 1, 2);

        lineEditZoneConstTemperature = new QtExt::ValidatingLineEdit(groupBoxHeatTransfer);
        lineEditZoneConstTemperature->setObjectName(QString::fromUtf8("lineEditZoneConstTemperature"));

        gridLayout_4->addWidget(lineEditZoneConstTemperature, 3, 2, 1, 1);

        labelZoneConstTemperature = new QLabel(groupBoxHeatTransfer);
        labelZoneConstTemperature->setObjectName(QString::fromUtf8("labelZoneConstTemperature"));

        gridLayout_4->addWidget(labelZoneConstTemperature, 3, 0, 1, 2);

        labelZoneConstTemperature_2 = new QLabel(groupBoxHeatTransfer);
        labelZoneConstTemperature_2->setObjectName(QString::fromUtf8("labelZoneConstTemperature_2"));

        gridLayout_4->addWidget(labelZoneConstTemperature_2, 3, 3, 1, 1);

        comboBoxConnectedZoneType = new QComboBox(groupBoxHeatTransfer);
        comboBoxConnectedZoneType->setObjectName(QString::fromUtf8("comboBoxConnectedZoneType"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxConnectedZoneType->sizePolicy().hasHeightForWidth());
        comboBoxConnectedZoneType->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(comboBoxConnectedZoneType, 1, 1, 1, 3);

        comboBoxHeatTransferCoeffModelType = new QComboBox(groupBoxHeatTransfer);
        comboBoxHeatTransferCoeffModelType->setObjectName(QString::fromUtf8("comboBoxHeatTransferCoeffModelType"));
        sizePolicy1.setHeightForWidth(comboBoxHeatTransferCoeffModelType->sizePolicy().hasHeightForWidth());
        comboBoxHeatTransferCoeffModelType->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(comboBoxHeatTransferCoeffModelType, 0, 1, 1, 3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelScheduleZoneTemperature = new QLabel(groupBoxHeatTransfer);
        labelScheduleZoneTemperature->setObjectName(QString::fromUtf8("labelScheduleZoneTemperature"));

        gridLayout->addWidget(labelScheduleZoneTemperature, 0, 0, 1, 1);

        lineEditTemperatureScheduleName = new QLineEdit(groupBoxHeatTransfer);
        lineEditTemperatureScheduleName->setObjectName(QString::fromUtf8("lineEditTemperatureScheduleName"));
        lineEditTemperatureScheduleName->setReadOnly(true);

        gridLayout->addWidget(lineEditTemperatureScheduleName, 0, 1, 1, 1);

        toolButtonSelectTemperatureSchedule = new QToolButton(groupBoxHeatTransfer);
        toolButtonSelectTemperatureSchedule->setObjectName(QString::fromUtf8("toolButtonSelectTemperatureSchedule"));

        gridLayout->addWidget(toolButtonSelectTemperatureSchedule, 0, 2, 1, 1);

        toolButtonRemoveTemperatureSchedule = new QToolButton(groupBoxHeatTransfer);
        toolButtonRemoveTemperatureSchedule->setObjectName(QString::fromUtf8("toolButtonRemoveTemperatureSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveTemperatureSchedule->setIcon(icon);

        gridLayout->addWidget(toolButtonRemoveTemperatureSchedule, 0, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 4, 0, 1, 4);


        verticalLayoutMaster->addWidget(groupBoxHeatTransfer);

        groupBoxLongWaveExchange = new QGroupBox(SVDBBoundaryConditionEditWidget);
        groupBoxLongWaveExchange->setObjectName(QString::fromUtf8("groupBoxLongWaveExchange"));
        gridLayout_2 = new QGridLayout(groupBoxLongWaveExchange);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelLongWaveEmissivity = new QLabel(groupBoxLongWaveExchange);
        labelLongWaveEmissivity->setObjectName(QString::fromUtf8("labelLongWaveEmissivity"));

        gridLayout_2->addWidget(labelLongWaveEmissivity, 1, 0, 1, 1);

        lineEditLongWaveEmissivity = new QtExt::ValidatingLineEdit(groupBoxLongWaveExchange);
        lineEditLongWaveEmissivity->setObjectName(QString::fromUtf8("lineEditLongWaveEmissivity"));

        gridLayout_2->addWidget(lineEditLongWaveEmissivity, 1, 1, 1, 1);

        labelLongWaveEmissivity_2 = new QLabel(groupBoxLongWaveExchange);
        labelLongWaveEmissivity_2->setObjectName(QString::fromUtf8("labelLongWaveEmissivity_2"));

        gridLayout_2->addWidget(labelLongWaveEmissivity_2, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelLWModelType = new QLabel(groupBoxLongWaveExchange);
        labelLWModelType->setObjectName(QString::fromUtf8("labelLWModelType"));

        horizontalLayout_2->addWidget(labelLWModelType);

        comboBoxLWModelType = new QComboBox(groupBoxLongWaveExchange);
        comboBoxLWModelType->setObjectName(QString::fromUtf8("comboBoxLWModelType"));
        sizePolicy1.setHeightForWidth(comboBoxLWModelType->sizePolicy().hasHeightForWidth());
        comboBoxLWModelType->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(comboBoxLWModelType);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 3);


        verticalLayoutMaster->addWidget(groupBoxLongWaveExchange);

        groupBoxShortWaveRad = new QGroupBox(SVDBBoundaryConditionEditWidget);
        groupBoxShortWaveRad->setObjectName(QString::fromUtf8("groupBoxShortWaveRad"));
        gridLayout_3 = new QGridLayout(groupBoxShortWaveRad);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEditSolarAbsorptionCoefficient = new QtExt::ValidatingLineEdit(groupBoxShortWaveRad);
        lineEditSolarAbsorptionCoefficient->setObjectName(QString::fromUtf8("lineEditSolarAbsorptionCoefficient"));

        gridLayout_3->addWidget(lineEditSolarAbsorptionCoefficient, 1, 2, 1, 1);

        labelSolarAbsorptionCoefficient = new QLabel(groupBoxShortWaveRad);
        labelSolarAbsorptionCoefficient->setObjectName(QString::fromUtf8("labelSolarAbsorptionCoefficient"));

        gridLayout_3->addWidget(labelSolarAbsorptionCoefficient, 1, 1, 1, 1);

        labelSolarAbsorptionCoefficient_2 = new QLabel(groupBoxShortWaveRad);
        labelSolarAbsorptionCoefficient_2->setObjectName(QString::fromUtf8("labelSolarAbsorptionCoefficient_2"));

        gridLayout_3->addWidget(labelSolarAbsorptionCoefficient_2, 1, 3, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelSWModelType = new QLabel(groupBoxShortWaveRad);
        labelSWModelType->setObjectName(QString::fromUtf8("labelSWModelType"));

        horizontalLayout_3->addWidget(labelSWModelType);

        comboBoxSWModelType = new QComboBox(groupBoxShortWaveRad);
        comboBoxSWModelType->setObjectName(QString::fromUtf8("comboBoxSWModelType"));
        sizePolicy1.setHeightForWidth(comboBoxSWModelType->sizePolicy().hasHeightForWidth());
        comboBoxSWModelType->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(comboBoxSWModelType);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 4);


        verticalLayoutMaster->addWidget(groupBoxShortWaveRad);

        verticalSpacer = new QSpacerItem(20, 151, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutMaster->addItem(verticalSpacer);


        retranslateUi(SVDBBoundaryConditionEditWidget);

        QMetaObject::connectSlotsByName(SVDBBoundaryConditionEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBBoundaryConditionEditWidget)
    {
        SVDBBoundaryConditionEditWidget->setWindowTitle(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Name:", nullptr));
        groupBoxHeatTransfer->setTitle(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Heat Transfer Model", nullptr));
        labelHeatTransferCoeffModelType->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Type:", nullptr));
        labelHeatTransferCoefficient_2->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "W/m2K", nullptr));
        labelConnectedZoneType->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Connected zone:", nullptr));
        labelHeatTransferCoefficient->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Coefficient:", nullptr));
        labelZoneConstTemperature->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Zone temperature:", nullptr));
        labelZoneConstTemperature_2->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "C", nullptr));
        labelScheduleZoneTemperature->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Temperature schedule:", nullptr));
        toolButtonSelectTemperatureSchedule->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "...", nullptr));
        groupBoxLongWaveExchange->setTitle(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Long Wave Model", nullptr));
        labelLongWaveEmissivity->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Emissivity:", nullptr));
        labelLongWaveEmissivity_2->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "---", nullptr));
        labelLWModelType->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Type:", nullptr));
        groupBoxShortWaveRad->setTitle(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Short Wave Model", nullptr));
        labelSolarAbsorptionCoefficient->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Absorption coefficient:", nullptr));
        labelSolarAbsorptionCoefficient_2->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "---", nullptr));
        labelSWModelType->setText(QCoreApplication::translate("SVDBBoundaryConditionEditWidget", "Type:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBBoundaryConditionEditWidget: public Ui_SVDBBoundaryConditionEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBBOUNDARYCONDITIONEDITWIDGET_H
