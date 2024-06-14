/********************************************************************************
** Form generated from reading UI file 'SVSimulationOutputOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONOUTPUTOPTIONS_H
#define UI_SVSIMULATIONOUTPUTOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationOutputOptions
{
public:
    QVBoxLayout *verticalLayoutOutputs;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_4;
    QWidget *widgetOutputDefs;
    QGridLayout *gridLayout_2;
    QToolButton *toolButtonRemoveDefinition;
    QCheckBox *checkBoxDefaultNetworkOutputs;
    QCheckBox *checkBoxDefaultNetworkSummationModels;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *checkBoxDefaultBuildingOutputs;
    QTableWidget *tableWidgetOutputDefinitions;
    QLabel *label_7;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_4;
    QFrame *line;
    QWidget *widgetFormat;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QFrame *line_2;
    QCheckBox *checkBoxBinaryFormat;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidgetOutputGrids;
    QToolButton *toolButtonRemoveGrid;
    QLabel *label_8;
    QToolButton *toolButtonEditGrid;
    QToolButton *toolButtonAddGrid;
    QSpacerItem *verticalSpacer;
    QFrame *line_3;
    QWidget *widgetAvailableOutputs;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditReferenceType;
    QLabel *label_3;
    QLineEdit *lineEditQuantity;
    QCheckBox *checkBoxEnableSelectVectorIndices;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widgetObjects;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QListWidget *listWidgetObjectIDs;
    QWidget *widgetVectorIDs;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelVectorIndexes;
    QListWidget *listWidgetVectorIndexes;
    QFrame *line_4;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonUpdateOutputList;
    QLabel *labelOutputUpdateNeeded;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonAddDefinition;
    QVBoxLayout *verticalLayout_4;
    QTableView *tableViewAvailableOutputs;

    void setupUi(QWidget *SVSimulationOutputOptions)
    {
        if (SVSimulationOutputOptions->objectName().isEmpty())
            SVSimulationOutputOptions->setObjectName(QString::fromUtf8("SVSimulationOutputOptions"));
        SVSimulationOutputOptions->resize(1216, 815);
        verticalLayoutOutputs = new QVBoxLayout(SVSimulationOutputOptions);
        verticalLayoutOutputs->setObjectName(QString::fromUtf8("verticalLayoutOutputs"));
        splitter = new QSplitter(SVSimulationOutputOptions);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout_4 = new QGridLayout(layoutWidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widgetOutputDefs = new QWidget(layoutWidget);
        widgetOutputDefs->setObjectName(QString::fromUtf8("widgetOutputDefs"));
        gridLayout_2 = new QGridLayout(widgetOutputDefs);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        toolButtonRemoveDefinition = new QToolButton(widgetOutputDefs);
        toolButtonRemoveDefinition->setObjectName(QString::fromUtf8("toolButtonRemoveDefinition"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveDefinition->setIcon(icon);
        toolButtonRemoveDefinition->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(toolButtonRemoveDefinition, 8, 1, 1, 1);

        checkBoxDefaultNetworkOutputs = new QCheckBox(widgetOutputDefs);
        checkBoxDefaultNetworkOutputs->setObjectName(QString::fromUtf8("checkBoxDefaultNetworkOutputs"));

        gridLayout_2->addWidget(checkBoxDefaultNetworkOutputs, 3, 0, 1, 1);

        checkBoxDefaultNetworkSummationModels = new QCheckBox(widgetOutputDefs);
        checkBoxDefaultNetworkSummationModels->setObjectName(QString::fromUtf8("checkBoxDefaultNetworkSummationModels"));

        gridLayout_2->addWidget(checkBoxDefaultNetworkSummationModels, 4, 0, 1, 1);

        label_6 = new QLabel(widgetOutputDefs);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setBold(true);
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 7, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 458, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_2, 9, 1, 1, 1);

        checkBoxDefaultBuildingOutputs = new QCheckBox(widgetOutputDefs);
        checkBoxDefaultBuildingOutputs->setObjectName(QString::fromUtf8("checkBoxDefaultBuildingOutputs"));

        gridLayout_2->addWidget(checkBoxDefaultBuildingOutputs, 2, 0, 1, 1);

        tableWidgetOutputDefinitions = new QTableWidget(widgetOutputDefs);
        tableWidgetOutputDefinitions->setObjectName(QString::fromUtf8("tableWidgetOutputDefinitions"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetOutputDefinitions->sizePolicy().hasHeightForWidth());
        tableWidgetOutputDefinitions->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(tableWidgetOutputDefinitions, 8, 0, 2, 1);

        label_7 = new QLabel(widgetOutputDefs);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font1;
        font1.setItalic(true);
        label_7->setFont(font1);

        gridLayout_2->addWidget(label_7, 5, 0, 1, 1);

        label_2 = new QLabel(widgetOutputDefs);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 6, 0, 1, 1);

        line = new QFrame(widgetOutputDefs);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 1, 0, 1, 2);


        gridLayout_4->addWidget(widgetOutputDefs, 0, 0, 2, 1);

        widgetFormat = new QWidget(layoutWidget);
        widgetFormat->setObjectName(QString::fromUtf8("widgetFormat"));
        verticalLayout_6 = new QVBoxLayout(widgetFormat);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 0, -1, -1);
        label_5 = new QLabel(widgetFormat);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        line_2 = new QFrame(widgetFormat);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        checkBoxBinaryFormat = new QCheckBox(widgetFormat);
        checkBoxBinaryFormat->setObjectName(QString::fromUtf8("checkBoxBinaryFormat"));

        verticalLayout_6->addWidget(checkBoxBinaryFormat);


        gridLayout_4->addWidget(widgetFormat, 0, 1, 1, 1);

        widget = new QWidget(layoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidgetOutputGrids = new QTableWidget(widget);
        tableWidgetOutputGrids->setObjectName(QString::fromUtf8("tableWidgetOutputGrids"));
        sizePolicy.setHeightForWidth(tableWidgetOutputGrids->sizePolicy().hasHeightForWidth());
        tableWidgetOutputGrids->setSizePolicy(sizePolicy);
        tableWidgetOutputGrids->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidgetOutputGrids, 2, 0, 4, 1);

        toolButtonRemoveGrid = new QToolButton(widget);
        toolButtonRemoveGrid->setObjectName(QString::fromUtf8("toolButtonRemoveGrid"));
        toolButtonRemoveGrid->setIcon(icon);
        toolButtonRemoveGrid->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonRemoveGrid, 4, 1, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        toolButtonEditGrid = new QToolButton(widget);
        toolButtonEditGrid->setObjectName(QString::fromUtf8("toolButtonEditGrid"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonEditGrid->setIcon(icon1);
        toolButtonEditGrid->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonEditGrid, 3, 1, 1, 1);

        toolButtonAddGrid = new QToolButton(widget);
        toolButtonAddGrid->setObjectName(QString::fromUtf8("toolButtonAddGrid"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddGrid->setIcon(icon2);
        toolButtonAddGrid->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonAddGrid, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 518, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        line_3 = new QFrame(widget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 0, 1, 1);


        gridLayout_4->addWidget(widget, 1, 1, 1, 1);

        splitter->addWidget(layoutWidget);
        widgetAvailableOutputs = new QWidget(splitter);
        widgetAvailableOutputs->setObjectName(QString::fromUtf8("widgetAvailableOutputs"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(widgetAvailableOutputs->sizePolicy().hasHeightForWidth());
        widgetAvailableOutputs->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(widgetAvailableOutputs);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 20, -1, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widgetAvailableOutputs);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditReferenceType = new QLineEdit(widgetAvailableOutputs);
        lineEditReferenceType->setObjectName(QString::fromUtf8("lineEditReferenceType"));

        horizontalLayout_2->addWidget(lineEditReferenceType);

        label_3 = new QLabel(widgetAvailableOutputs);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditQuantity = new QLineEdit(widgetAvailableOutputs);
        lineEditQuantity->setObjectName(QString::fromUtf8("lineEditQuantity"));

        horizontalLayout_2->addWidget(lineEditQuantity);

        checkBoxEnableSelectVectorIndices = new QCheckBox(widgetAvailableOutputs);
        checkBoxEnableSelectVectorIndices->setObjectName(QString::fromUtf8("checkBoxEnableSelectVectorIndices"));

        horizontalLayout_2->addWidget(checkBoxEnableSelectVectorIndices);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout_2, 8, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widgetObjects = new QWidget(widgetAvailableOutputs);
        widgetObjects->setObjectName(QString::fromUtf8("widgetObjects"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetObjects->sizePolicy().hasHeightForWidth());
        widgetObjects->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(widgetObjects);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        label_4 = new QLabel(widgetObjects);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        listWidgetObjectIDs = new QListWidget(widgetObjects);
        listWidgetObjectIDs->setObjectName(QString::fromUtf8("listWidgetObjectIDs"));
        listWidgetObjectIDs->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetObjectIDs);


        verticalLayout_2->addWidget(widgetObjects);

        widgetVectorIDs = new QWidget(widgetAvailableOutputs);
        widgetVectorIDs->setObjectName(QString::fromUtf8("widgetVectorIDs"));
        sizePolicy2.setHeightForWidth(widgetVectorIDs->sizePolicy().hasHeightForWidth());
        widgetVectorIDs->setSizePolicy(sizePolicy2);
        verticalLayout_5 = new QVBoxLayout(widgetVectorIDs);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 0, -1, 0);
        labelVectorIndexes = new QLabel(widgetVectorIDs);
        labelVectorIndexes->setObjectName(QString::fromUtf8("labelVectorIndexes"));

        verticalLayout_5->addWidget(labelVectorIndexes);

        listWidgetVectorIndexes = new QListWidget(widgetVectorIDs);
        listWidgetVectorIndexes->setObjectName(QString::fromUtf8("listWidgetVectorIndexes"));
        listWidgetVectorIndexes->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_5->addWidget(listWidgetVectorIndexes);


        verticalLayout_2->addWidget(widgetVectorIDs);


        gridLayout_3->addLayout(verticalLayout_2, 4, 1, 1, 1);

        line_4 = new QFrame(widgetAvailableOutputs);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_4, 1, 0, 1, 2);

        label_9 = new QLabel(widgetAvailableOutputs);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonUpdateOutputList = new QPushButton(widgetAvailableOutputs);
        pushButtonUpdateOutputList->setObjectName(QString::fromUtf8("pushButtonUpdateOutputList"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/24x24/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUpdateOutputList->setIcon(icon3);

        horizontalLayout->addWidget(pushButtonUpdateOutputList);

        labelOutputUpdateNeeded = new QLabel(widgetAvailableOutputs);
        labelOutputUpdateNeeded->setObjectName(QString::fromUtf8("labelOutputUpdateNeeded"));
        sizePolicy.setHeightForWidth(labelOutputUpdateNeeded->sizePolicy().hasHeightForWidth());
        labelOutputUpdateNeeded->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(239, 41, 41, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(190, 190, 190, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        labelOutputUpdateNeeded->setPalette(palette);

        horizontalLayout->addWidget(labelOutputUpdateNeeded);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 2);

        toolButtonAddDefinition = new QToolButton(widgetAvailableOutputs);
        toolButtonAddDefinition->setObjectName(QString::fromUtf8("toolButtonAddDefinition"));
        toolButtonAddDefinition->setIcon(icon2);
        toolButtonAddDefinition->setIconSize(QSize(24, 24));

        gridLayout_3->addWidget(toolButtonAddDefinition, 9, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableViewAvailableOutputs = new QTableView(widgetAvailableOutputs);
        tableViewAvailableOutputs->setObjectName(QString::fromUtf8("tableViewAvailableOutputs"));
        tableViewAvailableOutputs->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewAvailableOutputs->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_4->addWidget(tableViewAvailableOutputs);


        gridLayout_3->addLayout(verticalLayout_4, 4, 0, 1, 1);

        splitter->addWidget(widgetAvailableOutputs);

        verticalLayoutOutputs->addWidget(splitter);


        retranslateUi(SVSimulationOutputOptions);

        QMetaObject::connectSlotsByName(SVSimulationOutputOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationOutputOptions)
    {
        SVSimulationOutputOptions->setWindowTitle(QCoreApplication::translate("SVSimulationOutputOptions", "Form", nullptr));
        toolButtonRemoveDefinition->setText(QCoreApplication::translate("SVSimulationOutputOptions", "...", nullptr));
        checkBoxDefaultNetworkOutputs->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Generate default network-related outputs", nullptr));
        checkBoxDefaultNetworkSummationModels->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Generate default network-related summation models and according outputs", nullptr));
        label_6->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Custom simulation outputs", nullptr));
        checkBoxDefaultBuildingOutputs->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Generate default building-related outputs", nullptr));
        label_7->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Note: Auto-generated outputs always use the first output grid in the list.", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Output definitions", nullptr));
        label_5->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Output format", nullptr));
        checkBoxBinaryFormat->setText(QCoreApplication::translate("SVSimulationOutputOptions", "write in binary format", nullptr));
        toolButtonRemoveGrid->setText(QCoreApplication::translate("SVSimulationOutputOptions", "...", nullptr));
        label_8->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Output grids", nullptr));
        toolButtonEditGrid->setText(QCoreApplication::translate("SVSimulationOutputOptions", "...", nullptr));
        toolButtonAddGrid->setText(QCoreApplication::translate("SVSimulationOutputOptions", "...", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Name filter:", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Quantity filter:", nullptr));
        checkBoxEnableSelectVectorIndices->setText(QCoreApplication::translate("SVSimulationOutputOptions", "enable selection of vector indices for all objects", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Objects", nullptr));
        labelVectorIndexes->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Vector indeces", nullptr));
        label_9->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Available outputs", nullptr));
        pushButtonUpdateOutputList->setText(QCoreApplication::translate("SVSimulationOutputOptions", "Update output list", nullptr));
        labelOutputUpdateNeeded->setText(QCoreApplication::translate("SVSimulationOutputOptions", "The output definition list is outdated, you should update the output list.", nullptr));
        toolButtonAddDefinition->setText(QCoreApplication::translate("SVSimulationOutputOptions", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationOutputOptions: public Ui_SVSimulationOutputOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONOUTPUTOPTIONS_H
