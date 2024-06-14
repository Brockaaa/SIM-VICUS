/********************************************************************************
** Form generated from reading UI file 'SVDBInternalLoadsElectricEquipmentEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBINTERNALLOADSELECTRICEQUIPMENTEDITWIDGET_H
#define UI_SVDBINTERNALLOADSELECTRICEQUIPMENTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBInternalLoadsElectricEquipmentEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QwtPlot *widgetPlot;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ValidatingLineEdit *lineEditLossFactor;
    QToolButton *toolButtonRemovePowerManagementSchedule;
    QLabel *labelLossFactor;
    QLabel *labelCategory_2;
    QLineEdit *lineEditManagementScheduleName;
    QLabel *labelDisplayName_2;
    QtExt::ValidatingLineEdit *lineEditPower;
    QLabel *labelDisplayName;
    QLabel *labelElectricEquipmentInput;
    QToolButton *toolButtonSelectSchedule;
    QComboBox *comboBoxMethod;
    QtExt::ValidatingLineEdit *lineEditLatentFactor;
    QLabel *labelConvectiveFactor;
    QLabel *labelLatentFactor;
    QtExt::ValidatingLineEdit *lineEditConvectiveFactor;
    QLabel *label1;
    QLabel *labelElectricEquipmentInputUnit;
    QLabel *labelConvectiveFactorUnit;
    QLabel *labelConvectiveFactorUnit_2;
    QLabel *labelConvectiveFactorUnit_3;
    QtExt::ColorButton *pushButtonColor;

    void setupUi(QWidget *SVDBInternalLoadsElectricEquipmentEditWidget)
    {
        if (SVDBInternalLoadsElectricEquipmentEditWidget->objectName().isEmpty())
            SVDBInternalLoadsElectricEquipmentEditWidget->setObjectName(QString::fromUtf8("SVDBInternalLoadsElectricEquipmentEditWidget"));
        SVDBInternalLoadsElectricEquipmentEditWidget->resize(508, 330);
        gridLayoutMaster = new QGridLayout(SVDBInternalLoadsElectricEquipmentEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        widgetPlot = new QwtPlot(SVDBInternalLoadsElectricEquipmentEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 7, 0, 1, 6);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 1, 1, 2);

        lineEditLossFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditLossFactor->setObjectName(QString::fromUtf8("lineEditLossFactor"));
        lineEditLossFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditLossFactor, 6, 1, 1, 2);

        toolButtonRemovePowerManagementSchedule = new QToolButton(SVDBInternalLoadsElectricEquipmentEditWidget);
        toolButtonRemovePowerManagementSchedule->setObjectName(QString::fromUtf8("toolButtonRemovePowerManagementSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemovePowerManagementSchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemovePowerManagementSchedule, 3, 5, 1, 1);

        labelLossFactor = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelLossFactor->setObjectName(QString::fromUtf8("labelLossFactor"));

        gridLayoutMaster->addWidget(labelLossFactor, 6, 0, 1, 1);

        labelCategory_2 = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));

        gridLayoutMaster->addWidget(labelCategory_2, 1, 0, 1, 1);

        lineEditManagementScheduleName = new QLineEdit(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditManagementScheduleName->setObjectName(QString::fromUtf8("lineEditManagementScheduleName"));
        lineEditManagementScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditManagementScheduleName, 3, 1, 1, 2);

        labelDisplayName_2 = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelDisplayName_2->setObjectName(QString::fromUtf8("labelDisplayName_2"));

        gridLayoutMaster->addWidget(labelDisplayName_2, 3, 0, 1, 1);

        lineEditPower = new QtExt::ValidatingLineEdit(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditPower->setObjectName(QString::fromUtf8("lineEditPower"));
        lineEditPower->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditPower, 2, 1, 1, 2);

        labelDisplayName = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 1);

        labelElectricEquipmentInput = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelElectricEquipmentInput->setObjectName(QString::fromUtf8("labelElectricEquipmentInput"));

        gridLayoutMaster->addWidget(labelElectricEquipmentInput, 2, 0, 1, 1);

        toolButtonSelectSchedule = new QToolButton(SVDBInternalLoadsElectricEquipmentEditWidget);
        toolButtonSelectSchedule->setObjectName(QString::fromUtf8("toolButtonSelectSchedule"));

        gridLayoutMaster->addWidget(toolButtonSelectSchedule, 3, 4, 1, 1);

        comboBoxMethod = new QComboBox(SVDBInternalLoadsElectricEquipmentEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        gridLayoutMaster->addWidget(comboBoxMethod, 1, 1, 1, 2);

        lineEditLatentFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditLatentFactor->setObjectName(QString::fromUtf8("lineEditLatentFactor"));
        lineEditLatentFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditLatentFactor, 5, 1, 1, 2);

        labelConvectiveFactor = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelConvectiveFactor->setObjectName(QString::fromUtf8("labelConvectiveFactor"));

        gridLayoutMaster->addWidget(labelConvectiveFactor, 4, 0, 1, 1);

        labelLatentFactor = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelLatentFactor->setObjectName(QString::fromUtf8("labelLatentFactor"));

        gridLayoutMaster->addWidget(labelLatentFactor, 5, 0, 1, 1);

        lineEditConvectiveFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsElectricEquipmentEditWidget);
        lineEditConvectiveFactor->setObjectName(QString::fromUtf8("lineEditConvectiveFactor"));
        lineEditConvectiveFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditConvectiveFactor, 4, 1, 1, 2);

        label1 = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayoutMaster->addWidget(label1, 3, 3, 1, 1);

        labelElectricEquipmentInputUnit = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelElectricEquipmentInputUnit->setObjectName(QString::fromUtf8("labelElectricEquipmentInputUnit"));

        gridLayoutMaster->addWidget(labelElectricEquipmentInputUnit, 2, 3, 1, 3);

        labelConvectiveFactorUnit = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit, 4, 3, 1, 3);

        labelConvectiveFactorUnit_2 = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelConvectiveFactorUnit_2->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_2"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_2, 5, 3, 1, 3);

        labelConvectiveFactorUnit_3 = new QLabel(SVDBInternalLoadsElectricEquipmentEditWidget);
        labelConvectiveFactorUnit_3->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_3"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_3, 6, 3, 1, 3);

        pushButtonColor = new QtExt::ColorButton(SVDBInternalLoadsElectricEquipmentEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 3, 1, 2);

        gridLayoutMaster->setColumnStretch(1, 1);

        retranslateUi(SVDBInternalLoadsElectricEquipmentEditWidget);

        QMetaObject::connectSlotsByName(SVDBInternalLoadsElectricEquipmentEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBInternalLoadsElectricEquipmentEditWidget)
    {
        SVDBInternalLoadsElectricEquipmentEditWidget->setWindowTitle(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Form", nullptr));
        labelLossFactor->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Loss Factor:", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Method:", nullptr));
        labelDisplayName_2->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Power Management Schedule Name:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Name:", nullptr));
        labelElectricEquipmentInput->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Power:", nullptr));
        toolButtonSelectSchedule->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "...", nullptr));
        labelConvectiveFactor->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Convective Factor:", nullptr));
        labelLatentFactor->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Latent Factor:", nullptr));
        label1->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "W", nullptr));
        labelElectricEquipmentInputUnit->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "Pers.", nullptr));
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "-", nullptr));
        labelConvectiveFactorUnit_2->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "-", nullptr));
        labelConvectiveFactorUnit_3->setText(QCoreApplication::translate("SVDBInternalLoadsElectricEquipmentEditWidget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBInternalLoadsElectricEquipmentEditWidget: public Ui_SVDBInternalLoadsElectricEquipmentEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBINTERNALLOADSELECTRICEQUIPMENTEDITWIDGET_H
