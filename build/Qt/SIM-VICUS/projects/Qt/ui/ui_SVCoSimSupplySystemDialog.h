/********************************************************************************
** Form generated from reading UI file 'SVCoSimSupplySystemDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVCOSIMSUPPLYSYSTEMDIALOG_H
#define UI_SVCOSIMSUPPLYSYSTEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVCoSimSupplySystemDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelCheckSummary;
    QLabel *label;
    QPushButton *pushButtonGenerate;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButtonLaunchMasterSim;

    void setupUi(QDialog *SVCoSimSupplySystemDialog)
    {
        if (SVCoSimSupplySystemDialog->objectName().isEmpty())
            SVCoSimSupplySystemDialog->setObjectName(QString::fromUtf8("SVCoSimSupplySystemDialog"));
        SVCoSimSupplySystemDialog->resize(1077, 294);
        verticalLayout = new QVBoxLayout(SVCoSimSupplySystemDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelCheckSummary = new QLabel(SVCoSimSupplySystemDialog);
        labelCheckSummary->setObjectName(QString::fromUtf8("labelCheckSummary"));
        labelCheckSummary->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        labelCheckSummary->setWordWrap(true);

        verticalLayout->addWidget(labelCheckSummary);

        label = new QLabel(SVCoSimSupplySystemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        pushButtonGenerate = new QPushButton(SVCoSimSupplySystemDialog);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));

        verticalLayout->addWidget(pushButtonGenerate);

        plainTextEdit = new QPlainTextEdit(SVCoSimSupplySystemDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        pushButtonLaunchMasterSim = new QPushButton(SVCoSimSupplySystemDialog);
        pushButtonLaunchMasterSim->setObjectName(QString::fromUtf8("pushButtonLaunchMasterSim"));

        verticalLayout->addWidget(pushButtonLaunchMasterSim);


        retranslateUi(SVCoSimSupplySystemDialog);

        QMetaObject::connectSlotsByName(SVCoSimSupplySystemDialog);
    } // setupUi

    void retranslateUi(QDialog *SVCoSimSupplySystemDialog)
    {
        SVCoSimSupplySystemDialog->setWindowTitle(QCoreApplication::translate("SVCoSimSupplySystemDialog", "Co-Simulation with CO2 Balance and Ventilation", nullptr));
        labelCheckSummary->setText(QCoreApplication::translate("SVCoSimSupplySystemDialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("SVCoSimSupplySystemDialog", "The button below creates an FMU connects to an external supply model FMU targeted in the Supply system dialog. It also creates the matching co-simulation project file for MASTERSIM.", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("SVCoSimSupplySystemDialog", "Generate FMU and Co-Simulation project", nullptr));
        pushButtonLaunchMasterSim->setText(QCoreApplication::translate("SVCoSimSupplySystemDialog", "Open Co-Simulation project in MasterSim...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVCoSimSupplySystemDialog: public Ui_SVCoSimSupplySystemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVCOSIMSUPPLYSYSTEMDIALOG_H
