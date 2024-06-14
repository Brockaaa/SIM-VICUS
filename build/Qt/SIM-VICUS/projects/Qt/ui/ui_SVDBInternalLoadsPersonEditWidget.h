/********************************************************************************
** Form generated from reading UI file 'SVDBInternalLoadsPersonEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBINTERNALLOADSPERSONEDITWIDGET_H
#define UI_SVDBINTERNALLOADSPERSONEDITWIDGET_H

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

class Ui_SVDBInternalLoadsPersonEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QToolButton *toolButtonRemoveMoistureRateSchedule;
    QLabel *labelPersonCount;
    QLabel *labelDisplayName;
    QLabel *labelCategory_2;
    QToolButton *toolButtonSelectOccupancy;
    QToolButton *toolButtonSelectMoistureRate;
    QToolButton *toolButtonRemoveOccupancySchedule;
    QLabel *labelDisplayName_2;
    QLineEdit *lineEditOccupancyScheduleName;
    QToolButton *toolButtonRemoveActivitySchedule;
    QLineEdit *lineEditMoistureRateScheduleName;
    QtExt::ValidatingLineEdit *lineEditPersonCount;
    QwtPlot *widgetPlot;
    QToolButton *toolButtonSelectActivity;
    QLabel *labelMoistProd;
    QLabel *labelConvectiveFactor;
    QtExt::ValidatingLineEdit *lineEditConvectiveFactor;
    QComboBox *comboBoxPersonMethod;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelDisplayName_3;
    QLineEdit *lineEditActivityScheduleName;
    QLabel *label;
    QLabel *labelPersonCountUnit;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelConvectiveFactor_2;
    QtExt::ColorButton *pushButtonColor;

    void setupUi(QWidget *SVDBInternalLoadsPersonEditWidget)
    {
        if (SVDBInternalLoadsPersonEditWidget->objectName().isEmpty())
            SVDBInternalLoadsPersonEditWidget->setObjectName(QString::fromUtf8("SVDBInternalLoadsPersonEditWidget"));
        SVDBInternalLoadsPersonEditWidget->resize(761, 322);
        SVDBInternalLoadsPersonEditWidget->setMinimumSize(QSize(500, 0));
        gridLayoutMaster = new QGridLayout(SVDBInternalLoadsPersonEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        toolButtonRemoveMoistureRateSchedule = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonRemoveMoistureRateSchedule->setObjectName(QString::fromUtf8("toolButtonRemoveMoistureRateSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveMoistureRateSchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemoveMoistureRateSchedule, 5, 4, 1, 1);

        labelPersonCount = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelPersonCount->setObjectName(QString::fromUtf8("labelPersonCount"));

        gridLayoutMaster->addWidget(labelPersonCount, 2, 0, 1, 1);

        labelDisplayName = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 1);

        labelCategory_2 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));
        labelCategory_2->setMinimumSize(QSize(60, 0));

        gridLayoutMaster->addWidget(labelCategory_2, 1, 0, 1, 1);

        toolButtonSelectOccupancy = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonSelectOccupancy->setObjectName(QString::fromUtf8("toolButtonSelectOccupancy"));

        gridLayoutMaster->addWidget(toolButtonSelectOccupancy, 3, 3, 1, 1);

        toolButtonSelectMoistureRate = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonSelectMoistureRate->setObjectName(QString::fromUtf8("toolButtonSelectMoistureRate"));

        gridLayoutMaster->addWidget(toolButtonSelectMoistureRate, 5, 3, 1, 1);

        toolButtonRemoveOccupancySchedule = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonRemoveOccupancySchedule->setObjectName(QString::fromUtf8("toolButtonRemoveOccupancySchedule"));
        toolButtonRemoveOccupancySchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemoveOccupancySchedule, 3, 4, 1, 1);

        labelDisplayName_2 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelDisplayName_2->setObjectName(QString::fromUtf8("labelDisplayName_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelDisplayName_2->sizePolicy().hasHeightForWidth());
        labelDisplayName_2->setSizePolicy(sizePolicy);
        labelDisplayName_2->setMinimumSize(QSize(60, 0));

        gridLayoutMaster->addWidget(labelDisplayName_2, 3, 0, 1, 1);

        lineEditOccupancyScheduleName = new QLineEdit(SVDBInternalLoadsPersonEditWidget);
        lineEditOccupancyScheduleName->setObjectName(QString::fromUtf8("lineEditOccupancyScheduleName"));
        lineEditOccupancyScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditOccupancyScheduleName, 3, 1, 1, 1);

        toolButtonRemoveActivitySchedule = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonRemoveActivitySchedule->setObjectName(QString::fromUtf8("toolButtonRemoveActivitySchedule"));
        toolButtonRemoveActivitySchedule->setIcon(icon);

        gridLayoutMaster->addWidget(toolButtonRemoveActivitySchedule, 4, 4, 1, 1);

        lineEditMoistureRateScheduleName = new QLineEdit(SVDBInternalLoadsPersonEditWidget);
        lineEditMoistureRateScheduleName->setObjectName(QString::fromUtf8("lineEditMoistureRateScheduleName"));
        lineEditMoistureRateScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditMoistureRateScheduleName, 5, 1, 1, 1);

        lineEditPersonCount = new QtExt::ValidatingLineEdit(SVDBInternalLoadsPersonEditWidget);
        lineEditPersonCount->setObjectName(QString::fromUtf8("lineEditPersonCount"));

        gridLayoutMaster->addWidget(lineEditPersonCount, 2, 1, 1, 1);

        widgetPlot = new QwtPlot(SVDBInternalLoadsPersonEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 7, 0, 1, 5);

        toolButtonSelectActivity = new QToolButton(SVDBInternalLoadsPersonEditWidget);
        toolButtonSelectActivity->setObjectName(QString::fromUtf8("toolButtonSelectActivity"));

        gridLayoutMaster->addWidget(toolButtonSelectActivity, 4, 3, 1, 1);

        labelMoistProd = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelMoistProd->setObjectName(QString::fromUtf8("labelMoistProd"));
        labelMoistProd->setMinimumSize(QSize(60, 0));

        gridLayoutMaster->addWidget(labelMoistProd, 5, 0, 1, 1);

        labelConvectiveFactor = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelConvectiveFactor->setObjectName(QString::fromUtf8("labelConvectiveFactor"));

        gridLayoutMaster->addWidget(labelConvectiveFactor, 6, 0, 1, 1);

        lineEditConvectiveFactor = new QtExt::ValidatingLineEdit(SVDBInternalLoadsPersonEditWidget);
        lineEditConvectiveFactor->setObjectName(QString::fromUtf8("lineEditConvectiveFactor"));
        lineEditConvectiveFactor->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditConvectiveFactor, 6, 1, 1, 1);

        comboBoxPersonMethod = new QComboBox(SVDBInternalLoadsPersonEditWidget);
        comboBoxPersonMethod->setObjectName(QString::fromUtf8("comboBoxPersonMethod"));

        gridLayoutMaster->addWidget(comboBoxPersonMethod, 1, 1, 1, 4);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBInternalLoadsPersonEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 1, 1, 1);

        labelDisplayName_3 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelDisplayName_3->setObjectName(QString::fromUtf8("labelDisplayName_3"));
        labelDisplayName_3->setMinimumSize(QSize(60, 0));

        gridLayoutMaster->addWidget(labelDisplayName_3, 4, 0, 1, 1);

        lineEditActivityScheduleName = new QLineEdit(SVDBInternalLoadsPersonEditWidget);
        lineEditActivityScheduleName->setObjectName(QString::fromUtf8("lineEditActivityScheduleName"));
        lineEditActivityScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditActivityScheduleName, 4, 1, 1, 1);

        label = new QLabel(SVDBInternalLoadsPersonEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayoutMaster->addWidget(label, 3, 2, 1, 1);

        labelPersonCountUnit = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelPersonCountUnit->setObjectName(QString::fromUtf8("labelPersonCountUnit"));

        gridLayoutMaster->addWidget(labelPersonCountUnit, 2, 2, 1, 3);

        label_2 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayoutMaster->addWidget(label_2, 4, 2, 1, 1);

        label_3 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayoutMaster->addWidget(label_3, 5, 2, 1, 1);

        labelConvectiveFactor_2 = new QLabel(SVDBInternalLoadsPersonEditWidget);
        labelConvectiveFactor_2->setObjectName(QString::fromUtf8("labelConvectiveFactor_2"));

        gridLayoutMaster->addWidget(labelConvectiveFactor_2, 6, 2, 1, 3);

        pushButtonColor = new QtExt::ColorButton(SVDBInternalLoadsPersonEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy1);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 2, 1, 1);

        gridLayoutMaster->setColumnStretch(1, 1);

        retranslateUi(SVDBInternalLoadsPersonEditWidget);

        QMetaObject::connectSlotsByName(SVDBInternalLoadsPersonEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBInternalLoadsPersonEditWidget)
    {
        SVDBInternalLoadsPersonEditWidget->setWindowTitle(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Form", nullptr));
        labelPersonCount->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Max. person count:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Name:", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Person count method:", nullptr));
        toolButtonSelectOccupancy->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "...", nullptr));
        toolButtonSelectMoistureRate->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "...", nullptr));
        labelDisplayName_2->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Occupancy schedule:", nullptr));
        toolButtonSelectActivity->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "...", nullptr));
        labelMoistProd->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Moisture production rate schedule:", nullptr));
        labelConvectiveFactor->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Convective Factor:", nullptr));
        labelDisplayName_3->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Activity schedule:", nullptr));
        label->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "-", nullptr));
        labelPersonCountUnit->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "Pers.", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "W/Pers.", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "kg/Pers.", nullptr));
        labelConvectiveFactor_2->setText(QCoreApplication::translate("SVDBInternalLoadsPersonEditWidget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBInternalLoadsPersonEditWidget: public Ui_SVDBInternalLoadsPersonEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBINTERNALLOADSPERSONEDITWIDGET_H
