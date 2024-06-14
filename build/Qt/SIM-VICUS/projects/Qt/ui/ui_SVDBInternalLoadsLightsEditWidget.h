/********************************************************************************
** Form generated from reading UI file 'SVDBInternalLoadsLightsEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBINTERNALLOADSLIGHTSEDITWIDGET_H
#define UI_SVDBINTERNALLOADSLIGHTSEDITWIDGET_H

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

class Ui_SVDBInternalLoadsLightsEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QLabel *labelCategory_2;
    QToolButton *toolButtonRemovePowerManagementSchedule;
    QLabel *labelConvectiveFactor;
    QLabel *labelDisplayName;
    QLabel *labelDisplayName_2;
    QToolButton *toolButtonSelectSchedule;
    QtExt::ValidatingLineEdit *lineEditConvectiveFactor;
    QtExt::ValidatingLineEdit *lineEditPower;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelLightsInput;
    QComboBox *comboBoxMethod;
    QLineEdit *lineEditManagementScheduleName;
    QwtPlot *widgetPlot;
    QLabel *label;
    QLabel *labelLightsInputUnit;
    QLabel *labelConvectiveFactorUnit;
    QtExt::ColorButton *pushButtonColor;

    void setupUi(QWidget *SVDBInternalLoadsLightsEditWidget)
    {
        if (SVDBInternalLoadsLightsEditWidget->objectName().isEmpty())
            SVDBInternalLoadsLightsEditWidget->setObjectName(QString::fromUtf8("SVDBInternalLoadsLightsEditWidget"));
        SVDBInternalLoadsLightsEditWidget->resize(721, 270);
        gridLayoutMaster = new QGridLayout(SVDBInternalLoadsLightsEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        labelCategory_2 = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));

        gridLayoutMaster->addWidget(labelCategory_2, 1, 0, 1, 1);

        toolButtonRemovePowerManagementSchedule = new QToolButton(SVDBInternalLoadsLightsEditWidget);
        toolButtonRemovePowerManagementSchedule->setObjectName(QString::fromUtf8("toolButtonRemovePowerManagementSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemovePowerManagementSchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemovePowerManagementSchedule, 3, 5, 1, 1);

        labelConvectiveFactor = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelConvectiveFactor->setObjectName(QString::fromUtf8("labelConvectiveFactor"));

        gridLayoutMaster->addWidget(labelConvectiveFactor, 4, 0, 1, 1);

        labelDisplayName = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 1);

        labelDisplayName_2 = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelDisplayName_2->setObjectName(QString::fromUtf8("labelDisplayName_2"));

        gridLayoutMaster->addWidget(labelDisplayName_2, 3, 0, 1, 1);

        toolButtonSelectSchedule = new QToolButton(SVDBInternalLoadsLightsEditWidget);
        toolButtonSelectSchedule->setObjectName(QString::fromUtf8("toolButtonSelectSchedule"));

        gridLayoutMaster->addWidget(toolButtonSelectSchedule, 3, 4, 1, 1);

        lineEditConvectiveFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsLightsEditWidget);
        lineEditConvectiveFactor->setObjectName(QString::fromUtf8("lineEditConvectiveFactor"));
        lineEditConvectiveFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditConvectiveFactor, 4, 1, 1, 2);

        lineEditPower = new QtExt::ValidatingLineEdit(SVDBInternalLoadsLightsEditWidget);
        lineEditPower->setObjectName(QString::fromUtf8("lineEditPower"));
        lineEditPower->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditPower, 2, 1, 1, 2);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBInternalLoadsLightsEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 1, 1, 2);

        labelLightsInput = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelLightsInput->setObjectName(QString::fromUtf8("labelLightsInput"));

        gridLayoutMaster->addWidget(labelLightsInput, 2, 0, 1, 1);

        comboBoxMethod = new QComboBox(SVDBInternalLoadsLightsEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        gridLayoutMaster->addWidget(comboBoxMethod, 1, 1, 1, 2);

        lineEditManagementScheduleName = new QLineEdit(SVDBInternalLoadsLightsEditWidget);
        lineEditManagementScheduleName->setObjectName(QString::fromUtf8("lineEditManagementScheduleName"));
        lineEditManagementScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditManagementScheduleName, 3, 1, 1, 2);

        widgetPlot = new QwtPlot(SVDBInternalLoadsLightsEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 5, 0, 1, 6);

        label = new QLabel(SVDBInternalLoadsLightsEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayoutMaster->addWidget(label, 3, 3, 1, 1);

        labelLightsInputUnit = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelLightsInputUnit->setObjectName(QString::fromUtf8("labelLightsInputUnit"));

        gridLayoutMaster->addWidget(labelLightsInputUnit, 2, 3, 1, 3);

        labelConvectiveFactorUnit = new QLabel(SVDBInternalLoadsLightsEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit, 4, 3, 1, 3);

        pushButtonColor = new QtExt::ColorButton(SVDBInternalLoadsLightsEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 3, 1, 2);

        gridLayoutMaster->setColumnStretch(1, 1);

        retranslateUi(SVDBInternalLoadsLightsEditWidget);

        QMetaObject::connectSlotsByName(SVDBInternalLoadsLightsEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBInternalLoadsLightsEditWidget)
    {
        SVDBInternalLoadsLightsEditWidget->setWindowTitle(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Form", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Method:", nullptr));
        labelConvectiveFactor->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Convective Factor:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Name:", nullptr));
        labelDisplayName_2->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Power Management Schedule Name:", nullptr));
        toolButtonSelectSchedule->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "...", nullptr));
        labelLightsInput->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Power:", nullptr));
        label->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "W", nullptr));
        labelLightsInputUnit->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "Pers.", nullptr));
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBInternalLoadsLightsEditWidget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBInternalLoadsLightsEditWidget: public Ui_SVDBInternalLoadsLightsEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBINTERNALLOADSLIGHTSEDITWIDGET_H
