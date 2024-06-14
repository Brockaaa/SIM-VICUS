/********************************************************************************
** Form generated from reading UI file 'SVNetworkImportDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKIMPORTDIALOG_H
#define UI_SVNETWORKIMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVNetworkImportDialog
{
public:
    QGridLayout *gridLayout_6;
    QGroupBox *groupBoxSelectNetwork;
    QGridLayout *gridLayout_2;
    QtExt::ValidatingLineEdit *lineEditOriginY;
    QtExt::ValidatingLineEdit *lineEditOriginZ;
    QLineEdit *lineEditNetworkName;
    QRadioButton *radioButtonAddToExistingNetwork;
    QComboBox *comboBoxNetworkSelectionBox;
    QtExt::ValidatingLineEdit *lineEditOriginX;
    QLabel *label_3;
    QRadioButton *radioButtonNewNetwork;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tabImportPipes;
    QGridLayout *gridLayout_4;
    QLabel *label_9;
    QLabel *label_7;
    QPushButton *pushButtonSelectDefaultPipe;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QPushButton *pushButtonSelectAvailablePipes;
    QtExt::BrowseFilenameWidget *lineEditPipelineFileName;
    QLabel *labelDefaulPipeName;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabImportSubStations;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QLabel *label_11;
    QLabel *label_5;
    QtExt::BrowseFilenameWidget *lineEditSubStationFileName;
    QLabel *label_4;
    QLabel *label_14;
    QLabel *label_12;
    QLineEdit *lineEditSubStationName;
    QtExt::ValidatingLineEdit *lineEditMaxHeatingDemand;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBoxUTM;
    QFormLayout *formLayout;
    QLabel *label_2;
    QComboBox *comboBoxUTMZone;

    void setupUi(QDialog *SVNetworkImportDialog)
    {
        if (SVNetworkImportDialog->objectName().isEmpty())
            SVNetworkImportDialog->setObjectName(QString::fromUtf8("SVNetworkImportDialog"));
        SVNetworkImportDialog->resize(756, 511);
        gridLayout_6 = new QGridLayout(SVNetworkImportDialog);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBoxSelectNetwork = new QGroupBox(SVNetworkImportDialog);
        groupBoxSelectNetwork->setObjectName(QString::fromUtf8("groupBoxSelectNetwork"));
        gridLayout_2 = new QGridLayout(groupBoxSelectNetwork);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditOriginY = new QtExt::ValidatingLineEdit(groupBoxSelectNetwork);
        lineEditOriginY->setObjectName(QString::fromUtf8("lineEditOriginY"));
        lineEditOriginY->setReadOnly(true);

        gridLayout_2->addWidget(lineEditOriginY, 2, 3, 1, 1);

        lineEditOriginZ = new QtExt::ValidatingLineEdit(groupBoxSelectNetwork);
        lineEditOriginZ->setObjectName(QString::fromUtf8("lineEditOriginZ"));
        lineEditOriginZ->setReadOnly(true);

        gridLayout_2->addWidget(lineEditOriginZ, 2, 4, 1, 1);

        lineEditNetworkName = new QLineEdit(groupBoxSelectNetwork);
        lineEditNetworkName->setObjectName(QString::fromUtf8("lineEditNetworkName"));

        gridLayout_2->addWidget(lineEditNetworkName, 0, 2, 1, 3);

        radioButtonAddToExistingNetwork = new QRadioButton(groupBoxSelectNetwork);
        radioButtonAddToExistingNetwork->setObjectName(QString::fromUtf8("radioButtonAddToExistingNetwork"));
        radioButtonAddToExistingNetwork->setEnabled(false);

        gridLayout_2->addWidget(radioButtonAddToExistingNetwork, 1, 0, 1, 1);

        comboBoxNetworkSelectionBox = new QComboBox(groupBoxSelectNetwork);
        comboBoxNetworkSelectionBox->setObjectName(QString::fromUtf8("comboBoxNetworkSelectionBox"));

        gridLayout_2->addWidget(comboBoxNetworkSelectionBox, 1, 2, 1, 3);

        lineEditOriginX = new QtExt::ValidatingLineEdit(groupBoxSelectNetwork);
        lineEditOriginX->setObjectName(QString::fromUtf8("lineEditOriginX"));
        lineEditOriginX->setReadOnly(true);

        gridLayout_2->addWidget(lineEditOriginX, 2, 2, 1, 1);

        label_3 = new QLabel(groupBoxSelectNetwork);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        radioButtonNewNetwork = new QRadioButton(groupBoxSelectNetwork);
        radioButtonNewNetwork->setObjectName(QString::fromUtf8("radioButtonNewNetwork"));
        radioButtonNewNetwork->setChecked(true);

        gridLayout_2->addWidget(radioButtonNewNetwork, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBoxSelectNetwork, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SVNetworkImportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_6->addWidget(buttonBox, 4, 0, 1, 1);

        tabWidget = new QTabWidget(SVNetworkImportDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabImportPipes = new QWidget();
        tabImportPipes->setObjectName(QString::fromUtf8("tabImportPipes"));
        gridLayout_4 = new QGridLayout(tabImportPipes);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_9 = new QLabel(tabImportPipes);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 3, 0, 1, 1);

        label_7 = new QLabel(tabImportPipes);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        pushButtonSelectDefaultPipe = new QPushButton(tabImportPipes);
        pushButtonSelectDefaultPipe->setObjectName(QString::fromUtf8("pushButtonSelectDefaultPipe"));

        gridLayout_4->addWidget(pushButtonSelectDefaultPipe, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 7, 1, 1, 1);

        label = new QLabel(tabImportPipes);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:rgb(119, 118, 123)"));
        label->setWordWrap(true);

        gridLayout_4->addWidget(label, 5, 0, 1, 3);

        pushButtonSelectAvailablePipes = new QPushButton(tabImportPipes);
        pushButtonSelectAvailablePipes->setObjectName(QString::fromUtf8("pushButtonSelectAvailablePipes"));

        gridLayout_4->addWidget(pushButtonSelectAvailablePipes, 6, 0, 1, 1);

        lineEditPipelineFileName = new QtExt::BrowseFilenameWidget(tabImportPipes);
        lineEditPipelineFileName->setObjectName(QString::fromUtf8("lineEditPipelineFileName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditPipelineFileName->sizePolicy().hasHeightForWidth());
        lineEditPipelineFileName->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(lineEditPipelineFileName, 0, 1, 1, 2);

        labelDefaulPipeName = new QLabel(tabImportPipes);
        labelDefaulPipeName->setObjectName(QString::fromUtf8("labelDefaulPipeName"));

        gridLayout_4->addWidget(labelDefaulPipeName, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_4->addItem(verticalSpacer_2, 4, 1, 1, 1);

        tabWidget->addTab(tabImportPipes, QString());
        tabImportSubStations = new QWidget();
        tabImportSubStations->setObjectName(QString::fromUtf8("tabImportSubStations"));
        gridLayout_5 = new QGridLayout(tabImportSubStations);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox_3 = new QGroupBox(tabImportSubStations);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 1, 0, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color:rgb(119, 118, 123)"));
        label_5->setWordWrap(true);

        gridLayout->addWidget(label_5, 2, 0, 1, 2);

        lineEditSubStationFileName = new QtExt::BrowseFilenameWidget(groupBox_3);
        lineEditSubStationFileName->setObjectName(QString::fromUtf8("lineEditSubStationFileName"));

        gridLayout->addWidget(lineEditSubStationFileName, 0, 1, 1, 2);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color:rgb(119, 118, 123)"));
        label_4->setWordWrap(true);

        gridLayout->addWidget(label_4, 4, 0, 1, 2);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 3, 2, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 3, 0, 1, 1);

        lineEditSubStationName = new QLineEdit(groupBox_3);
        lineEditSubStationName->setObjectName(QString::fromUtf8("lineEditSubStationName"));

        gridLayout->addWidget(lineEditSubStationName, 1, 1, 1, 1);

        lineEditMaxHeatingDemand = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditMaxHeatingDemand->setObjectName(QString::fromUtf8("lineEditMaxHeatingDemand"));
        lineEditMaxHeatingDemand->setLayoutDirection(Qt::LeftToRight);
        lineEditMaxHeatingDemand->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lineEditMaxHeatingDemand, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 0, 0, 1, 1);

        tabWidget->addTab(tabImportSubStations, QString());

        gridLayout_6->addWidget(tabWidget, 3, 0, 1, 1);

        groupBoxUTM = new QGroupBox(SVNetworkImportDialog);
        groupBoxUTM->setObjectName(QString::fromUtf8("groupBoxUTM"));
        groupBoxUTM->setCheckable(true);
        formLayout = new QFormLayout(groupBoxUTM);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(groupBoxUTM);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        comboBoxUTMZone = new QComboBox(groupBoxUTM);
        comboBoxUTMZone->setObjectName(QString::fromUtf8("comboBoxUTMZone"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxUTMZone);


        gridLayout_6->addWidget(groupBoxUTM, 1, 0, 1, 1);


        retranslateUi(SVNetworkImportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVNetworkImportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVNetworkImportDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVNetworkImportDialog);
    } // setupUi

    void retranslateUi(QDialog *SVNetworkImportDialog)
    {
        SVNetworkImportDialog->setWindowTitle(QCoreApplication::translate("SVNetworkImportDialog", "Import Pipe Network", nullptr));
        groupBoxSelectNetwork->setTitle(QCoreApplication::translate("SVNetworkImportDialog", "Select network", nullptr));
        lineEditNetworkName->setText(QCoreApplication::translate("SVNetworkImportDialog", "unnamed", nullptr));
        radioButtonAddToExistingNetwork->setText(QCoreApplication::translate("SVNetworkImportDialog", "Add to existing network", nullptr));
        label_3->setText(QCoreApplication::translate("SVNetworkImportDialog", "Origin", nullptr));
        radioButtonNewNetwork->setText(QCoreApplication::translate("SVNetworkImportDialog", "New network", nullptr));
        label_9->setText(QCoreApplication::translate("SVNetworkImportDialog", "Default pipe", nullptr));
        label_7->setText(QCoreApplication::translate("SVNetworkImportDialog", "File name", nullptr));
        pushButtonSelectDefaultPipe->setText(QCoreApplication::translate("SVNetworkImportDialog", "...", nullptr));
        label->setText(QCoreApplication::translate("SVNetworkImportDialog", "For geojson files: If the pipe diamater is specified with property attribute \"da\", selected pipe properties from the database can be assigned automatically. If no pipe property with  appropriate outer diameter can be found, given default property is used.  ", nullptr));
        pushButtonSelectAvailablePipes->setText(QCoreApplication::translate("SVNetworkImportDialog", "Select available pipes ...", nullptr));
        labelDefaulPipeName->setText(QCoreApplication::translate("SVNetworkImportDialog", "No pipe selected", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabImportPipes), QCoreApplication::translate("SVNetworkImportDialog", "Import Pipeline", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVNetworkImportDialog", "Sub station import", nullptr));
        label_13->setText(QCoreApplication::translate("SVNetworkImportDialog", "Sub Station Name:", nullptr));
        label_11->setText(QCoreApplication::translate("SVNetworkImportDialog", "File", nullptr));
        label_5->setText(QCoreApplication::translate("SVNetworkImportDialog", "For geojson files: Sub Station Name can be imported with attribute \"Name\"", nullptr));
        label_4->setText(QCoreApplication::translate("SVNetworkImportDialog", "For geojson files: Installed power can be imported with attribute \"MaxHeatingDemand\" or \"Qmax\" in kW", nullptr));
        label_14->setText(QCoreApplication::translate("SVNetworkImportDialog", "kW", nullptr));
        label_12->setText(QCoreApplication::translate("SVNetworkImportDialog", "Installed power (maximum load):", nullptr));
#if QT_CONFIG(tooltip)
        lineEditMaxHeatingDemand->setToolTip(QCoreApplication::translate("SVNetworkImportDialog", "This is the maximum power of this sub station, used for pipe dimensioning", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEditMaxHeatingDemand->setText(QCoreApplication::translate("SVNetworkImportDialog", "5", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabImportSubStations), QCoreApplication::translate("SVNetworkImportDialog", "Import Sub Stations", nullptr));
        groupBoxUTM->setTitle(QCoreApplication::translate("SVNetworkImportDialog", "convert to UTM when import geojson", nullptr));
        label_2->setText(QCoreApplication::translate("SVNetworkImportDialog", "UTM Zone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkImportDialog: public Ui_SVNetworkImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKIMPORTDIALOG_H
