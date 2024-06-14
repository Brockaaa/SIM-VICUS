/********************************************************************************
** Form generated from reading UI file 'SVDBInternalLoadsOtherEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBINTERNALLOADSOTHEREDITWIDGET_H
#define UI_SVDBINTERNALLOADSOTHEREDITWIDGET_H

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

class Ui_SVDBInternalLoadsOtherEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QLabel *labelOtherInput;
    QToolButton *toolButtonSelectSchedule;
    QComboBox *comboBoxMethod;
    QtExt::ValidatingLineEdit *lineEditConvectiveFactor;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelConvectiveFactor;
    QLabel *labelDisplayName_2;
    QtExt::ValidatingLineEdit *lineEditPower;
    QToolButton *toolButtonRemovePowerManagementSchedule;
    QwtPlot *widgetPlot;
    QLabel *labelCategory_2;
    QLabel *labelDisplayName;
    QLineEdit *lineEditManagementScheduleName;
    QLabel *labelOtherSchedInputUnit;
    QLabel *labelConvectiveFactorUnit;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelOtherInputUnit;

    void setupUi(QWidget *SVDBInternalLoadsOtherEditWidget)
    {
        if (SVDBInternalLoadsOtherEditWidget->objectName().isEmpty())
            SVDBInternalLoadsOtherEditWidget->setObjectName(QString::fromUtf8("SVDBInternalLoadsOtherEditWidget"));
        SVDBInternalLoadsOtherEditWidget->resize(989, 324);
        gridLayoutMaster = new QGridLayout(SVDBInternalLoadsOtherEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        labelOtherInput = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelOtherInput->setObjectName(QString::fromUtf8("labelOtherInput"));

        gridLayoutMaster->addWidget(labelOtherInput, 2, 0, 1, 2);

        toolButtonSelectSchedule = new QToolButton(SVDBInternalLoadsOtherEditWidget);
        toolButtonSelectSchedule->setObjectName(QString::fromUtf8("toolButtonSelectSchedule"));

        gridLayoutMaster->addWidget(toolButtonSelectSchedule, 3, 5, 1, 1);

        comboBoxMethod = new QComboBox(SVDBInternalLoadsOtherEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        gridLayoutMaster->addWidget(comboBoxMethod, 1, 2, 1, 2);

        lineEditConvectiveFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsOtherEditWidget);
        lineEditConvectiveFactor->setObjectName(QString::fromUtf8("lineEditConvectiveFactor"));
        lineEditConvectiveFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditConvectiveFactor, 4, 2, 1, 2);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBInternalLoadsOtherEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 2, 1, 2);

        labelConvectiveFactor = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelConvectiveFactor->setObjectName(QString::fromUtf8("labelConvectiveFactor"));

        gridLayoutMaster->addWidget(labelConvectiveFactor, 4, 0, 1, 2);

        labelDisplayName_2 = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelDisplayName_2->setObjectName(QString::fromUtf8("labelDisplayName_2"));
        labelDisplayName_2->setMinimumSize(QSize(0, 0));

        gridLayoutMaster->addWidget(labelDisplayName_2, 3, 0, 1, 2);

        lineEditPower = new QtExt::ValidatingLineEdit(SVDBInternalLoadsOtherEditWidget);
        lineEditPower->setObjectName(QString::fromUtf8("lineEditPower"));
        lineEditPower->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditPower, 2, 2, 1, 2);

        toolButtonRemovePowerManagementSchedule = new QToolButton(SVDBInternalLoadsOtherEditWidget);
        toolButtonRemovePowerManagementSchedule->setObjectName(QString::fromUtf8("toolButtonRemovePowerManagementSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemovePowerManagementSchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemovePowerManagementSchedule, 3, 6, 1, 1);

        widgetPlot = new QwtPlot(SVDBInternalLoadsOtherEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 5, 0, 1, 7);

        labelCategory_2 = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));
        labelCategory_2->setMinimumSize(QSize(0, 0));

        gridLayoutMaster->addWidget(labelCategory_2, 1, 0, 1, 2);

        labelDisplayName = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(0, 0));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 2);

        lineEditManagementScheduleName = new QLineEdit(SVDBInternalLoadsOtherEditWidget);
        lineEditManagementScheduleName->setObjectName(QString::fromUtf8("lineEditManagementScheduleName"));
        lineEditManagementScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditManagementScheduleName, 3, 2, 1, 2);

        labelOtherSchedInputUnit = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelOtherSchedInputUnit->setObjectName(QString::fromUtf8("labelOtherSchedInputUnit"));

        gridLayoutMaster->addWidget(labelOtherSchedInputUnit, 3, 4, 1, 1);

        labelConvectiveFactorUnit = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit, 4, 4, 1, 3);

        pushButtonColor = new QtExt::ColorButton(SVDBInternalLoadsOtherEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 4, 1, 3);

        labelOtherInputUnit = new QLabel(SVDBInternalLoadsOtherEditWidget);
        labelOtherInputUnit->setObjectName(QString::fromUtf8("labelOtherInputUnit"));

        gridLayoutMaster->addWidget(labelOtherInputUnit, 2, 4, 1, 2);

        gridLayoutMaster->setColumnStretch(2, 1);

        retranslateUi(SVDBInternalLoadsOtherEditWidget);

        QMetaObject::connectSlotsByName(SVDBInternalLoadsOtherEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBInternalLoadsOtherEditWidget)
    {
        SVDBInternalLoadsOtherEditWidget->setWindowTitle(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Form", nullptr));
        labelOtherInput->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Power:", nullptr));
        toolButtonSelectSchedule->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "...", nullptr));
        labelConvectiveFactor->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Convective Factor:", nullptr));
        labelDisplayName_2->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Power Management Schedule Name:", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Method:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "Name:", nullptr));
        labelOtherSchedInputUnit->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "W", nullptr));
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "-", nullptr));
        labelOtherInputUnit->setText(QCoreApplication::translate("SVDBInternalLoadsOtherEditWidget", "W/m2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBInternalLoadsOtherEditWidget: public Ui_SVDBInternalLoadsOtherEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBINTERNALLOADSOTHEREDITWIDGET_H
