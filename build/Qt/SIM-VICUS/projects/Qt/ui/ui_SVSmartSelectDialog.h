/********************************************************************************
** Form generated from reading UI file 'SVSmartSelectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSMARTSELECTDIALOG_H
#define UI_SVSMARTSELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSmartSelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidgetGroup;
    QWidget *tabBuildingObjects;
    QGridLayout *gridLayoutBuildings;
    QLabel *labelFilterInfo;
    QListWidget *listWidgetOptions;
    QHBoxLayout *horizontalLayoutBreadCrums;
    QToolButton *toolButtonReset;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout_3;
    QCheckBox *checkBoxFilterBoundaryCondition;
    QComboBox *comboBoxBoundaryCondition;
    QWidget *tabNetworkObjects;
    QVBoxLayout *verticalLayoutNetwork;
    QComboBox *comboBoxNetwork;
    QTabWidget *tabWidgetNetworkSelections;
    QWidget *tabNodes;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBoxNodeType;
    QCheckBox *checkBoxMaxHeatingDemandBelow;
    QtExt::ValidatingLineEdit *lineEditMaxHeatingDemandBelow;
    QLabel *label_2;
    QCheckBox *checkBoxMaxHeatingDemandAbove;
    QtExt::ValidatingLineEdit *lineEditMaxHeatingDemandAbove;
    QCheckBox *checkBoxMaxHeatingDemandEqualTo;
    QtExt::ValidatingLineEdit *lineEditMaxHeatingDemandEqualTo;
    QCheckBox *checkBoxNodeId;
    QtExt::ValidatingLineEdit *lineEditNodeId;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *tabEdges;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBoxLengthBelow;
    QtExt::ValidatingLineEdit *lineEditLengthBelow;
    QLabel *label_5;
    QCheckBox *checkBoxLengthAbove;
    QtExt::ValidatingLineEdit *lineEditLengthAbove;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxFilterName;
    QLineEdit *lineEditFilterName;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVSmartSelectDialog)
    {
        if (SVSmartSelectDialog->objectName().isEmpty())
            SVSmartSelectDialog->setObjectName(QString::fromUtf8("SVSmartSelectDialog"));
        SVSmartSelectDialog->resize(706, 586);
        verticalLayout = new QVBoxLayout(SVSmartSelectDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidgetGroup = new QTabWidget(SVSmartSelectDialog);
        tabWidgetGroup->setObjectName(QString::fromUtf8("tabWidgetGroup"));
        tabWidgetGroup->setDocumentMode(true);
        tabWidgetGroup->setTabBarAutoHide(true);
        tabBuildingObjects = new QWidget();
        tabBuildingObjects->setObjectName(QString::fromUtf8("tabBuildingObjects"));
        gridLayoutBuildings = new QGridLayout(tabBuildingObjects);
        gridLayoutBuildings->setObjectName(QString::fromUtf8("gridLayoutBuildings"));
        gridLayoutBuildings->setContentsMargins(0, -1, 0, -1);
        labelFilterInfo = new QLabel(tabBuildingObjects);
        labelFilterInfo->setObjectName(QString::fromUtf8("labelFilterInfo"));

        gridLayoutBuildings->addWidget(labelFilterInfo, 0, 0, 1, 1);

        listWidgetOptions = new QListWidget(tabBuildingObjects);
        listWidgetOptions->setObjectName(QString::fromUtf8("listWidgetOptions"));

        gridLayoutBuildings->addWidget(listWidgetOptions, 2, 0, 1, 3);

        horizontalLayoutBreadCrums = new QHBoxLayout();
        horizontalLayoutBreadCrums->setObjectName(QString::fromUtf8("horizontalLayoutBreadCrums"));
        toolButtonReset = new QToolButton(tabBuildingObjects);
        toolButtonReset->setObjectName(QString::fromUtf8("toolButtonReset"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/arrow-source-grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonReset->setIcon(icon);
        toolButtonReset->setIconSize(QSize(24, 24));

        horizontalLayoutBreadCrums->addWidget(toolButtonReset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayoutBreadCrums->addItem(horizontalSpacer);


        gridLayoutBuildings->addLayout(horizontalLayoutBreadCrums, 1, 0, 1, 3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        checkBoxFilterBoundaryCondition = new QCheckBox(tabBuildingObjects);
        checkBoxFilterBoundaryCondition->setObjectName(QString::fromUtf8("checkBoxFilterBoundaryCondition"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBoxFilterBoundaryCondition->sizePolicy().hasHeightForWidth());
        checkBoxFilterBoundaryCondition->setSizePolicy(sizePolicy);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, checkBoxFilterBoundaryCondition);

        comboBoxBoundaryCondition = new QComboBox(tabBuildingObjects);
        comboBoxBoundaryCondition->setObjectName(QString::fromUtf8("comboBoxBoundaryCondition"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, comboBoxBoundaryCondition);


        gridLayoutBuildings->addLayout(formLayout_3, 3, 0, 1, 1);

        tabWidgetGroup->addTab(tabBuildingObjects, QString());
        tabNetworkObjects = new QWidget();
        tabNetworkObjects->setObjectName(QString::fromUtf8("tabNetworkObjects"));
        verticalLayoutNetwork = new QVBoxLayout(tabNetworkObjects);
        verticalLayoutNetwork->setObjectName(QString::fromUtf8("verticalLayoutNetwork"));
        verticalLayoutNetwork->setContentsMargins(0, -1, 0, -1);
        comboBoxNetwork = new QComboBox(tabNetworkObjects);
        comboBoxNetwork->setObjectName(QString::fromUtf8("comboBoxNetwork"));

        verticalLayoutNetwork->addWidget(comboBoxNetwork);

        tabWidgetNetworkSelections = new QTabWidget(tabNetworkObjects);
        tabWidgetNetworkSelections->setObjectName(QString::fromUtf8("tabWidgetNetworkSelections"));
        tabWidgetNetworkSelections->setDocumentMode(true);
        tabNodes = new QWidget();
        tabNodes->setObjectName(QString::fromUtf8("tabNodes"));
        gridLayout = new QGridLayout(tabNodes);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tabNodes);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxNodeType = new QComboBox(tabNodes);
        comboBoxNodeType->setObjectName(QString::fromUtf8("comboBoxNodeType"));

        gridLayout->addWidget(comboBoxNodeType, 0, 1, 1, 1);

        checkBoxMaxHeatingDemandBelow = new QCheckBox(tabNodes);
        checkBoxMaxHeatingDemandBelow->setObjectName(QString::fromUtf8("checkBoxMaxHeatingDemandBelow"));

        gridLayout->addWidget(checkBoxMaxHeatingDemandBelow, 1, 0, 1, 1);

        lineEditMaxHeatingDemandBelow = new QtExt::ValidatingLineEdit(tabNodes);
        lineEditMaxHeatingDemandBelow->setObjectName(QString::fromUtf8("lineEditMaxHeatingDemandBelow"));

        gridLayout->addWidget(lineEditMaxHeatingDemandBelow, 1, 1, 1, 1);

        label_2 = new QLabel(tabNodes);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        checkBoxMaxHeatingDemandAbove = new QCheckBox(tabNodes);
        checkBoxMaxHeatingDemandAbove->setObjectName(QString::fromUtf8("checkBoxMaxHeatingDemandAbove"));

        gridLayout->addWidget(checkBoxMaxHeatingDemandAbove, 2, 0, 1, 1);

        lineEditMaxHeatingDemandAbove = new QtExt::ValidatingLineEdit(tabNodes);
        lineEditMaxHeatingDemandAbove->setObjectName(QString::fromUtf8("lineEditMaxHeatingDemandAbove"));

        gridLayout->addWidget(lineEditMaxHeatingDemandAbove, 2, 1, 1, 1);

        checkBoxMaxHeatingDemandEqualTo = new QCheckBox(tabNodes);
        checkBoxMaxHeatingDemandEqualTo->setObjectName(QString::fromUtf8("checkBoxMaxHeatingDemandEqualTo"));

        gridLayout->addWidget(checkBoxMaxHeatingDemandEqualTo, 3, 0, 1, 1);

        lineEditMaxHeatingDemandEqualTo = new QtExt::ValidatingLineEdit(tabNodes);
        lineEditMaxHeatingDemandEqualTo->setObjectName(QString::fromUtf8("lineEditMaxHeatingDemandEqualTo"));

        gridLayout->addWidget(lineEditMaxHeatingDemandEqualTo, 3, 1, 1, 1);

        checkBoxNodeId = new QCheckBox(tabNodes);
        checkBoxNodeId->setObjectName(QString::fromUtf8("checkBoxNodeId"));

        gridLayout->addWidget(checkBoxNodeId, 4, 0, 1, 1);

        lineEditNodeId = new QtExt::ValidatingLineEdit(tabNodes);
        lineEditNodeId->setObjectName(QString::fromUtf8("lineEditNodeId"));

        gridLayout->addWidget(lineEditNodeId, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        label_3 = new QLabel(tabNodes);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        label_4 = new QLabel(tabNodes);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 2, 1, 1);

        tabWidgetNetworkSelections->addTab(tabNodes, QString());
        tabEdges = new QWidget();
        tabEdges->setObjectName(QString::fromUtf8("tabEdges"));
        gridLayout_2 = new QGridLayout(tabEdges);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBoxLengthBelow = new QCheckBox(tabEdges);
        checkBoxLengthBelow->setObjectName(QString::fromUtf8("checkBoxLengthBelow"));

        gridLayout_2->addWidget(checkBoxLengthBelow, 0, 0, 1, 1);

        lineEditLengthBelow = new QtExt::ValidatingLineEdit(tabEdges);
        lineEditLengthBelow->setObjectName(QString::fromUtf8("lineEditLengthBelow"));

        gridLayout_2->addWidget(lineEditLengthBelow, 0, 1, 1, 1);

        label_5 = new QLabel(tabEdges);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        checkBoxLengthAbove = new QCheckBox(tabEdges);
        checkBoxLengthAbove->setObjectName(QString::fromUtf8("checkBoxLengthAbove"));

        gridLayout_2->addWidget(checkBoxLengthAbove, 1, 0, 1, 1);

        lineEditLengthAbove = new QtExt::ValidatingLineEdit(tabEdges);
        lineEditLengthAbove->setObjectName(QString::fromUtf8("lineEditLengthAbove"));

        gridLayout_2->addWidget(lineEditLengthAbove, 1, 1, 1, 1);

        label_6 = new QLabel(tabEdges);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 314, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

        tabWidgetNetworkSelections->addTab(tabEdges, QString());

        verticalLayoutNetwork->addWidget(tabWidgetNetworkSelections);

        tabWidgetGroup->addTab(tabNetworkObjects, QString());

        verticalLayout->addWidget(tabWidgetGroup);

        line = new QFrame(SVSmartSelectDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxFilterName = new QCheckBox(SVSmartSelectDialog);
        checkBoxFilterName->setObjectName(QString::fromUtf8("checkBoxFilterName"));

        horizontalLayout->addWidget(checkBoxFilterName);

        lineEditFilterName = new QLineEdit(SVSmartSelectDialog);
        lineEditFilterName->setObjectName(QString::fromUtf8("lineEditFilterName"));

        horizontalLayout->addWidget(lineEditFilterName);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SVSmartSelectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SVSmartSelectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVSmartSelectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVSmartSelectDialog, SLOT(reject()));

        tabWidgetGroup->setCurrentIndex(0);
        tabWidgetNetworkSelections->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SVSmartSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SVSmartSelectDialog)
    {
        SVSmartSelectDialog->setWindowTitle(QCoreApplication::translate("SVSmartSelectDialog", "Smart selection", nullptr));
        labelFilterInfo->setText(QCoreApplication::translate("SVSmartSelectDialog", "TextLabel", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonReset->setToolTip(QCoreApplication::translate("SVSmartSelectDialog", "Resets all filters.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonReset->setText(QString());
        checkBoxFilterBoundaryCondition->setText(QCoreApplication::translate("SVSmartSelectDialog", "boundary condition filter", nullptr));
        tabWidgetGroup->setTabText(tabWidgetGroup->indexOf(tabBuildingObjects), QCoreApplication::translate("SVSmartSelectDialog", "Building objects", nullptr));
        label->setText(QCoreApplication::translate("SVSmartSelectDialog", "Type:", nullptr));
        checkBoxMaxHeatingDemandBelow->setText(QCoreApplication::translate("SVSmartSelectDialog", "Max heating demand <", nullptr));
        label_2->setText(QCoreApplication::translate("SVSmartSelectDialog", "W", nullptr));
        checkBoxMaxHeatingDemandAbove->setText(QCoreApplication::translate("SVSmartSelectDialog", "Max heating demand >", nullptr));
        checkBoxMaxHeatingDemandEqualTo->setText(QCoreApplication::translate("SVSmartSelectDialog", "Max heating demand =", nullptr));
        checkBoxNodeId->setText(QCoreApplication::translate("SVSmartSelectDialog", "ID=", nullptr));
        label_3->setText(QCoreApplication::translate("SVSmartSelectDialog", "W", nullptr));
        label_4->setText(QCoreApplication::translate("SVSmartSelectDialog", "W", nullptr));
        tabWidgetNetworkSelections->setTabText(tabWidgetNetworkSelections->indexOf(tabNodes), QCoreApplication::translate("SVSmartSelectDialog", "Nodes", nullptr));
        checkBoxLengthBelow->setText(QCoreApplication::translate("SVSmartSelectDialog", "Length <", nullptr));
        label_5->setText(QCoreApplication::translate("SVSmartSelectDialog", "m", nullptr));
        checkBoxLengthAbove->setText(QCoreApplication::translate("SVSmartSelectDialog", "Length >", nullptr));
        label_6->setText(QCoreApplication::translate("SVSmartSelectDialog", "m", nullptr));
        tabWidgetNetworkSelections->setTabText(tabWidgetNetworkSelections->indexOf(tabEdges), QCoreApplication::translate("SVSmartSelectDialog", "Pipes", nullptr));
        tabWidgetGroup->setTabText(tabWidgetGroup->indexOf(tabNetworkObjects), QCoreApplication::translate("SVSmartSelectDialog", "Network objects", nullptr));
        checkBoxFilterName->setText(QCoreApplication::translate("SVSmartSelectDialog", "name filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSmartSelectDialog: public Ui_SVSmartSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSMARTSELECTDIALOG_H
