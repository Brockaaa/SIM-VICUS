/********************************************************************************
** Form generated from reading UI file 'SVOutputGridEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVOUTPUTGRIDEDITDIALOG_H
#define UI_SVOUTPUTGRIDEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVOutputGridEditDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxSpecification;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEditName;
    QLabel *labelName;
    QSpinBox *spinBoxIntervalCount;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVOutputGridEditDialog)
    {
        if (SVOutputGridEditDialog->objectName().isEmpty())
            SVOutputGridEditDialog->setObjectName(QString::fromUtf8("SVOutputGridEditDialog"));
        SVOutputGridEditDialog->resize(847, 542);
        verticalLayout_2 = new QVBoxLayout(SVOutputGridEditDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBoxSpecification = new QGroupBox(SVOutputGridEditDialog);
        groupBoxSpecification->setObjectName(QString::fromUtf8("groupBoxSpecification"));
        gridLayout = new QGridLayout(groupBoxSpecification);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(813, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        lineEditName = new QLineEdit(groupBoxSpecification);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 0, 1, 1, 2);

        labelName = new QLabel(groupBoxSpecification);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        spinBoxIntervalCount = new QSpinBox(groupBoxSpecification);
        spinBoxIntervalCount->setObjectName(QString::fromUtf8("spinBoxIntervalCount"));
        spinBoxIntervalCount->setMinimum(1);

        gridLayout->addWidget(spinBoxIntervalCount, 1, 1, 1, 1);

        label = new QLabel(groupBoxSpecification);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBoxSpecification);

        groupBox = new QGroupBox(SVOutputGridEditDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(tableWidget);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);


        verticalLayout_2->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(SVOutputGridEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SVOutputGridEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVOutputGridEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVOutputGridEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVOutputGridEditDialog);
    } // setupUi

    void retranslateUi(QDialog *SVOutputGridEditDialog)
    {
        SVOutputGridEditDialog->setWindowTitle(QCoreApplication::translate("SVOutputGridEditDialog", "Output Grid Editor", nullptr));
        groupBoxSpecification->setTitle(QCoreApplication::translate("SVOutputGridEditDialog", "Output grid details", nullptr));
        labelName->setText(QCoreApplication::translate("SVOutputGridEditDialog", "Name:", nullptr));
        label->setText(QCoreApplication::translate("SVOutputGridEditDialog", "Number of intervals:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVOutputGridEditDialog", "Output time intervals and their associated output step sizes", nullptr));
        label_3->setText(QCoreApplication::translate("SVOutputGridEditDialog", "Format: Enter time offsets with respect to simulation start as \"<value> <unit>\" strings.", nullptr));
        label_2->setText(QCoreApplication::translate("SVOutputGridEditDialog", "Missing end time points of intervals are set automatically based on next interval's start time or in case of the last interval as end point of simulation.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVOutputGridEditDialog: public Ui_SVOutputGridEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVOUTPUTGRIDEDITDIALOG_H
