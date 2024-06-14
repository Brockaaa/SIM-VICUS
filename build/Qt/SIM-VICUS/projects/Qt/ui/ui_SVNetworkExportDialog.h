/********************************************************************************
** Form generated from reading UI file 'SVNetworkExportDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKEXPORTDIALOG_H
#define UI_SVNETWORKEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVNetworkExportDialog
{
public:
    QGridLayout *gridLayout_3;
    QComboBox *comboBoxNetworkSelection;
    QCheckBox *checkBoxExportSubStation;
    QtExt::BrowseFilenameWidget *lineEditExportFileName;
    QCheckBox *checkBoxExportPipeline;
    QLabel *label_2;
    QLabel *label;
    QGroupBox *groupBoxToUTM;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonSouthern;
    QRadioButton *radioButtonNorthern;
    QLabel *label_4;
    QComboBox *comboBoxUTMZone;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVNetworkExportDialog)
    {
        if (SVNetworkExportDialog->objectName().isEmpty())
            SVNetworkExportDialog->setObjectName(QString::fromUtf8("SVNetworkExportDialog"));
        SVNetworkExportDialog->resize(561, 229);
        gridLayout_3 = new QGridLayout(SVNetworkExportDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        comboBoxNetworkSelection = new QComboBox(SVNetworkExportDialog);
        comboBoxNetworkSelection->setObjectName(QString::fromUtf8("comboBoxNetworkSelection"));

        gridLayout_3->addWidget(comboBoxNetworkSelection, 0, 1, 1, 2);

        checkBoxExportSubStation = new QCheckBox(SVNetworkExportDialog);
        checkBoxExportSubStation->setObjectName(QString::fromUtf8("checkBoxExportSubStation"));

        gridLayout_3->addWidget(checkBoxExportSubStation, 1, 2, 1, 1);

        lineEditExportFileName = new QtExt::BrowseFilenameWidget(SVNetworkExportDialog);
        lineEditExportFileName->setObjectName(QString::fromUtf8("lineEditExportFileName"));

        gridLayout_3->addWidget(lineEditExportFileName, 2, 1, 1, 2);

        checkBoxExportPipeline = new QCheckBox(SVNetworkExportDialog);
        checkBoxExportPipeline->setObjectName(QString::fromUtf8("checkBoxExportPipeline"));

        gridLayout_3->addWidget(checkBoxExportPipeline, 1, 1, 1, 1);

        label_2 = new QLabel(SVNetworkExportDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(SVNetworkExportDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 2, 0, 1, 1);

        groupBoxToUTM = new QGroupBox(SVNetworkExportDialog);
        groupBoxToUTM->setObjectName(QString::fromUtf8("groupBoxToUTM"));
        groupBoxToUTM->setCheckable(true);
        groupBoxToUTM->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxToUTM);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonSouthern = new QRadioButton(groupBoxToUTM);
        radioButtonSouthern->setObjectName(QString::fromUtf8("radioButtonSouthern"));

        gridLayout_2->addWidget(radioButtonSouthern, 1, 2, 1, 1);

        radioButtonNorthern = new QRadioButton(groupBoxToUTM);
        radioButtonNorthern->setObjectName(QString::fromUtf8("radioButtonNorthern"));

        gridLayout_2->addWidget(radioButtonNorthern, 1, 1, 1, 1);

        label_4 = new QLabel(groupBoxToUTM);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        comboBoxUTMZone = new QComboBox(groupBoxToUTM);
        comboBoxUTMZone->setObjectName(QString::fromUtf8("comboBoxUTMZone"));

        gridLayout_2->addWidget(comboBoxUTMZone, 0, 1, 1, 2);

        label_3 = new QLabel(groupBoxToUTM);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBoxToUTM, 3, 0, 1, 3);

        buttonBox = new QDialogButtonBox(SVNetworkExportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 4, 2, 1, 1);


        retranslateUi(SVNetworkExportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVNetworkExportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVNetworkExportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVNetworkExportDialog);
    } // setupUi

    void retranslateUi(QDialog *SVNetworkExportDialog)
    {
        SVNetworkExportDialog->setWindowTitle(QCoreApplication::translate("SVNetworkExportDialog", "Dialog", nullptr));
        checkBoxExportSubStation->setText(QCoreApplication::translate("SVNetworkExportDialog", "Export substation", nullptr));
        checkBoxExportPipeline->setText(QCoreApplication::translate("SVNetworkExportDialog", "Export pipeline", nullptr));
        label_2->setText(QCoreApplication::translate("SVNetworkExportDialog", "Select Network", nullptr));
        label->setText(QCoreApplication::translate("SVNetworkExportDialog", "Export file name:", nullptr));
        groupBoxToUTM->setTitle(QCoreApplication::translate("SVNetworkExportDialog", "Convert to UTM", nullptr));
        radioButtonSouthern->setText(QCoreApplication::translate("SVNetworkExportDialog", "Southern", nullptr));
        radioButtonNorthern->setText(QCoreApplication::translate("SVNetworkExportDialog", "Northern", nullptr));
        label_4->setText(QCoreApplication::translate("SVNetworkExportDialog", "Hemisphere", nullptr));
        label_3->setText(QCoreApplication::translate("SVNetworkExportDialog", "UTM Zone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkExportDialog: public Ui_SVNetworkExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKEXPORTDIALOG_H
