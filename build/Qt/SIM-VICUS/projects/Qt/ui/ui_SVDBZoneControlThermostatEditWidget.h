/********************************************************************************
** Form generated from reading UI file 'SVDBZoneControlThermostatEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONECONTROLTHERMOSTATEDITWIDGET_H
#define UI_SVDBZONECONTROLTHERMOSTATEDITWIDGET_H

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

class Ui_SVDBZoneControlThermostatEditWidget
{
public:
    QGridLayout *gridLayout;
    QToolButton *toolButtonRemoveHeatingSetpointSchedule;
    QtExt::ValidatingLineEdit *lineEditTolerance;
    QLabel *labelScheduleCooling;
    QComboBox *comboBoxMethod;
    QLabel *labelTolerance;
    QComboBox *comboBoxControllerType;
    QLineEdit *lineEditHeatingScheduleName;
    QLabel *labelScheduleHeating;
    QToolButton *toolButtonSelectCoolingSchedule;
    QLineEdit *lineEditCoolingScheduleName;
    QLabel *labelControllerType;
    QwtPlot *widgetPlot;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelCategory_2;
    QLabel *labelDisplayName;
    QToolButton *toolButtonRemoveCoolingSetpointSchedule;
    QToolButton *toolButtonSelectHeatingSchedule;
    QLabel *label;
    QLabel *label_2;
    QLabel *labelTolerance_2;
    QtExt::ColorButton *pushButtonColor;

    void setupUi(QWidget *SVDBZoneControlThermostatEditWidget)
    {
        if (SVDBZoneControlThermostatEditWidget->objectName().isEmpty())
            SVDBZoneControlThermostatEditWidget->setObjectName(QString::fromUtf8("SVDBZoneControlThermostatEditWidget"));
        SVDBZoneControlThermostatEditWidget->resize(463, 393);
        gridLayout = new QGridLayout(SVDBZoneControlThermostatEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButtonRemoveHeatingSetpointSchedule = new QToolButton(SVDBZoneControlThermostatEditWidget);
        toolButtonRemoveHeatingSetpointSchedule->setObjectName(QString::fromUtf8("toolButtonRemoveHeatingSetpointSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveHeatingSetpointSchedule->setIcon(icon);

        gridLayout->addWidget(toolButtonRemoveHeatingSetpointSchedule, 3, 5, 1, 1);

        lineEditTolerance = new QtExt::ValidatingLineEdit(SVDBZoneControlThermostatEditWidget);
        lineEditTolerance->setObjectName(QString::fromUtf8("lineEditTolerance"));
        lineEditTolerance->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(lineEditTolerance, 5, 2, 1, 1);

        labelScheduleCooling = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelScheduleCooling->setObjectName(QString::fromUtf8("labelScheduleCooling"));

        gridLayout->addWidget(labelScheduleCooling, 4, 0, 1, 2);

        comboBoxMethod = new QComboBox(SVDBZoneControlThermostatEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        gridLayout->addWidget(comboBoxMethod, 1, 2, 1, 1);

        labelTolerance = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelTolerance->setObjectName(QString::fromUtf8("labelTolerance"));

        gridLayout->addWidget(labelTolerance, 5, 0, 1, 1);

        comboBoxControllerType = new QComboBox(SVDBZoneControlThermostatEditWidget);
        comboBoxControllerType->setObjectName(QString::fromUtf8("comboBoxControllerType"));

        gridLayout->addWidget(comboBoxControllerType, 2, 2, 1, 1);

        lineEditHeatingScheduleName = new QLineEdit(SVDBZoneControlThermostatEditWidget);
        lineEditHeatingScheduleName->setObjectName(QString::fromUtf8("lineEditHeatingScheduleName"));
        lineEditHeatingScheduleName->setReadOnly(true);

        gridLayout->addWidget(lineEditHeatingScheduleName, 3, 2, 1, 1);

        labelScheduleHeating = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelScheduleHeating->setObjectName(QString::fromUtf8("labelScheduleHeating"));

        gridLayout->addWidget(labelScheduleHeating, 3, 0, 1, 2);

        toolButtonSelectCoolingSchedule = new QToolButton(SVDBZoneControlThermostatEditWidget);
        toolButtonSelectCoolingSchedule->setObjectName(QString::fromUtf8("toolButtonSelectCoolingSchedule"));

        gridLayout->addWidget(toolButtonSelectCoolingSchedule, 4, 4, 1, 1);

        lineEditCoolingScheduleName = new QLineEdit(SVDBZoneControlThermostatEditWidget);
        lineEditCoolingScheduleName->setObjectName(QString::fromUtf8("lineEditCoolingScheduleName"));
        lineEditCoolingScheduleName->setReadOnly(true);

        gridLayout->addWidget(lineEditCoolingScheduleName, 4, 2, 1, 1);

        labelControllerType = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelControllerType->setObjectName(QString::fromUtf8("labelControllerType"));

        gridLayout->addWidget(labelControllerType, 2, 0, 1, 1);

        widgetPlot = new QwtPlot(SVDBZoneControlThermostatEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayout->addWidget(widgetPlot, 6, 0, 1, 7);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBZoneControlThermostatEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 0, 2, 1, 1);

        labelCategory_2 = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));

        gridLayout->addWidget(labelCategory_2, 1, 0, 1, 1);

        labelDisplayName = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        toolButtonRemoveCoolingSetpointSchedule = new QToolButton(SVDBZoneControlThermostatEditWidget);
        toolButtonRemoveCoolingSetpointSchedule->setObjectName(QString::fromUtf8("toolButtonRemoveCoolingSetpointSchedule"));
        toolButtonRemoveCoolingSetpointSchedule->setIcon(icon);

        gridLayout->addWidget(toolButtonRemoveCoolingSetpointSchedule, 4, 5, 1, 1);

        toolButtonSelectHeatingSchedule = new QToolButton(SVDBZoneControlThermostatEditWidget);
        toolButtonSelectHeatingSchedule->setObjectName(QString::fromUtf8("toolButtonSelectHeatingSchedule"));

        gridLayout->addWidget(toolButtonSelectHeatingSchedule, 3, 4, 1, 1);

        label = new QLabel(SVDBZoneControlThermostatEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 3, 1, 1);

        label_2 = new QLabel(SVDBZoneControlThermostatEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 3, 1, 1);

        labelTolerance_2 = new QLabel(SVDBZoneControlThermostatEditWidget);
        labelTolerance_2->setObjectName(QString::fromUtf8("labelTolerance_2"));

        gridLayout->addWidget(labelTolerance_2, 5, 3, 1, 3);

        pushButtonColor = new QtExt::ColorButton(SVDBZoneControlThermostatEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonColor, 0, 3, 1, 2);


        retranslateUi(SVDBZoneControlThermostatEditWidget);

        QMetaObject::connectSlotsByName(SVDBZoneControlThermostatEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBZoneControlThermostatEditWidget)
    {
        SVDBZoneControlThermostatEditWidget->setWindowTitle(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Form", nullptr));
        labelScheduleCooling->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Cooling Setpoint Schedule:", nullptr));
        labelTolerance->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Tolerance:", nullptr));
        labelScheduleHeating->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Heating Setpoint Schedule:", nullptr));
        toolButtonSelectCoolingSchedule->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "...", nullptr));
        labelControllerType->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Controller Type:", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Method:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "Name:", nullptr));
        toolButtonSelectHeatingSchedule->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "...", nullptr));
        label->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "\302\260C", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "\302\260C", nullptr));
        labelTolerance_2->setText(QCoreApplication::translate("SVDBZoneControlThermostatEditWidget", "K", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneControlThermostatEditWidget: public Ui_SVDBZoneControlThermostatEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONECONTROLTHERMOSTATEDITWIDGET_H
