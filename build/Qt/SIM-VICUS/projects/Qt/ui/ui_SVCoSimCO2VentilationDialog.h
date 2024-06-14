/********************************************************************************
** Form generated from reading UI file 'SVCoSimCO2VentilationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVCOSIMCO2VENTILATIONDIALOG_H
#define UI_SVCOSIMCO2VENTILATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVCoSimCO2VentilationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelCheckSummary;
    QLabel *label;
    QPushButton *pushButtonGenerate;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButtonLaunchMasterSim;

    void setupUi(QDialog *SVCoSimCO2VentilationDialog)
    {
        if (SVCoSimCO2VentilationDialog->objectName().isEmpty())
            SVCoSimCO2VentilationDialog->setObjectName(QString::fromUtf8("SVCoSimCO2VentilationDialog"));
        SVCoSimCO2VentilationDialog->resize(1077, 294);
        verticalLayout = new QVBoxLayout(SVCoSimCO2VentilationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelCheckSummary = new QLabel(SVCoSimCO2VentilationDialog);
        labelCheckSummary->setObjectName(QString::fromUtf8("labelCheckSummary"));
        labelCheckSummary->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        labelCheckSummary->setWordWrap(true);

        verticalLayout->addWidget(labelCheckSummary);

        label = new QLabel(SVCoSimCO2VentilationDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        pushButtonGenerate = new QPushButton(SVCoSimCO2VentilationDialog);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));

        verticalLayout->addWidget(pushButtonGenerate);

        plainTextEdit = new QPlainTextEdit(SVCoSimCO2VentilationDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        pushButtonLaunchMasterSim = new QPushButton(SVCoSimCO2VentilationDialog);
        pushButtonLaunchMasterSim->setObjectName(QString::fromUtf8("pushButtonLaunchMasterSim"));

        verticalLayout->addWidget(pushButtonLaunchMasterSim);


        retranslateUi(SVCoSimCO2VentilationDialog);

        QMetaObject::connectSlotsByName(SVCoSimCO2VentilationDialog);
    } // setupUi

    void retranslateUi(QDialog *SVCoSimCO2VentilationDialog)
    {
        SVCoSimCO2VentilationDialog->setWindowTitle(QCoreApplication::translate("SVCoSimCO2VentilationDialog", "Co-Simulation with CO2 Balance and Ventilation", nullptr));
        labelCheckSummary->setText(QCoreApplication::translate("SVCoSimCO2VentilationDialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("SVCoSimCO2VentilationDialog", "The button below creates an FMU with the CO2 balances for each zone and the ventilation control algorithms according to the settings made in the zone templates. It also creates the matching NANDRAD FMU and the co-simulation project file for MASTERSIM.", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("SVCoSimCO2VentilationDialog", "Generate FMU and Co-Simulation project", nullptr));
        pushButtonLaunchMasterSim->setText(QCoreApplication::translate("SVCoSimCO2VentilationDialog", "Open Co-Simulation project in MasterSim...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVCoSimCO2VentilationDialog: public Ui_SVCoSimCO2VentilationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVCOSIMCO2VENTILATIONDIALOG_H
