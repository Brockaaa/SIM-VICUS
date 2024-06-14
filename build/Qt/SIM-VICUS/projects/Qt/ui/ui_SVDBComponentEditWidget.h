/********************************************************************************
** Form generated from reading UI file 'SVDBComponentEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBCOMPONENTEDITWIDGET_H
#define UI_SVDBCOMPONENTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_ConstructionViewHoverToSelect.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_ValidatingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_SVDBComponentEditWidget
{
public:
    QVBoxLayout *masterLayout;
    QGridLayout *gridLayout_4;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelComponentType;
    QComboBox *comboBoxComponentType;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEditConstructionName;
    QToolButton *toolButtonSelectConstruction;
    QToolButton *toolButtonRemoveConstruction;
    QtExt::ConstructionViewHoverToSelect *graphicsViewConstruction;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSurfaceHeatingIndex;
    QSpinBox *spinBoxActiveLayerIndex;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxActiveLayerEnabled;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidgetProperties;
    QWidget *tabConstructionType;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEditBoundaryConditionSideBName;
    QToolButton *toolButtonSelectBoundaryConditionSideBName;
    QToolButton *toolButtonRemoveBoundaryConditionSideB;
    QTextBrowser *textBrowserBCSideB;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowserBCSideA;
    QToolButton *toolButtonSelectBoundaryConditionSideAName;
    QLineEdit *lineEditBoundaryConditionSideAName;
    QToolButton *toolButtonRemoveBoundaryConditionSideA;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelUValue;
    QLineEdit *lineEditUValue;
    QLabel *labelUValue_2;
    QWidget *tabLCA;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetLca;
    QWidget *tabSurface;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditDaylightName;
    QPushButton *pushButtonDaylight;
    QFormLayout *formLayout;
    QLabel *labelDaylight;
    QtExt::ColorButton *pushButtonDaylightColor;
    QLabel *labelDaylight_2;
    QtExt::ValidatingLineEdit *lineEditRoughness;
    QLabel *labelDaylight_3;
    QtExt::ValidatingLineEdit *lineEditSpecularity;
    QSpacerItem *verticalSpacer;
    QWidget *tabAcoustic;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QtExt::ValidatingLineEdit *lineEditImpactSound;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QtExt::ValidatingLineEdit *lineEditAirSoundRes;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QTextBrowser *textBrowserAcousticBCSideA;
    QToolButton *toolButtonSelectAcousticBoundaryConditionSideAName;
    QLineEdit *lineEditAcousticBoundaryConditionSideAName;
    QToolButton *toolButtonRemoveAcousticBoundaryConditionSideA;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEditAcousticBoundaryConditionSideBName;
    QToolButton *toolButtonSelectAcousticBoundaryConditionSideBName;
    QToolButton *toolButtonRemoveAcousticBoundaryConditionSideB;
    QTextBrowser *textBrowserAcousticBCSideB;

    void setupUi(QWidget *SVDBComponentEditWidget)
    {
        if (SVDBComponentEditWidget->objectName().isEmpty())
            SVDBComponentEditWidget->setObjectName(QString::fromUtf8("SVDBComponentEditWidget"));
        SVDBComponentEditWidget->resize(1458, 1120);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVDBComponentEditWidget->sizePolicy().hasHeightForWidth());
        SVDBComponentEditWidget->setSizePolicy(sizePolicy);
        masterLayout = new QVBoxLayout(SVDBComponentEditWidget);
        masterLayout->setObjectName(QString::fromUtf8("masterLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        labelDisplayName = new QLabel(SVDBComponentEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayout_4->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBComponentEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout_4->addWidget(lineEditName, 0, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBComponentEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(pushButtonColor, 0, 2, 1, 1);

        labelComponentType = new QLabel(SVDBComponentEditWidget);
        labelComponentType->setObjectName(QString::fromUtf8("labelComponentType"));

        gridLayout_4->addWidget(labelComponentType, 1, 0, 1, 1);

        comboBoxComponentType = new QComboBox(SVDBComponentEditWidget);
        comboBoxComponentType->setObjectName(QString::fromUtf8("comboBoxComponentType"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBoxComponentType->sizePolicy().hasHeightForWidth());
        comboBoxComponentType->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(comboBoxComponentType, 1, 1, 1, 1);


        masterLayout->addLayout(gridLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        lineEditConstructionName = new QLineEdit(SVDBComponentEditWidget);
        lineEditConstructionName->setObjectName(QString::fromUtf8("lineEditConstructionName"));
        lineEditConstructionName->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEditConstructionName);

        toolButtonSelectConstruction = new QToolButton(SVDBComponentEditWidget);
        toolButtonSelectConstruction->setObjectName(QString::fromUtf8("toolButtonSelectConstruction"));

        horizontalLayout_5->addWidget(toolButtonSelectConstruction);

        toolButtonRemoveConstruction = new QToolButton(SVDBComponentEditWidget);
        toolButtonRemoveConstruction->setObjectName(QString::fromUtf8("toolButtonRemoveConstruction"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveConstruction->setIcon(icon);

        horizontalLayout_5->addWidget(toolButtonRemoveConstruction);


        masterLayout->addLayout(horizontalLayout_5);

        graphicsViewConstruction = new QtExt::ConstructionViewHoverToSelect(SVDBComponentEditWidget);
        graphicsViewConstruction->setObjectName(QString::fromUtf8("graphicsViewConstruction"));

        masterLayout->addWidget(graphicsViewConstruction);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSurfaceHeatingIndex = new QLabel(SVDBComponentEditWidget);
        labelSurfaceHeatingIndex->setObjectName(QString::fromUtf8("labelSurfaceHeatingIndex"));

        horizontalLayout->addWidget(labelSurfaceHeatingIndex);

        spinBoxActiveLayerIndex = new QSpinBox(SVDBComponentEditWidget);
        spinBoxActiveLayerIndex->setObjectName(QString::fromUtf8("spinBoxActiveLayerIndex"));
        spinBoxActiveLayerIndex->setMinimum(1);

        horizontalLayout->addWidget(spinBoxActiveLayerIndex);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        masterLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBoxActiveLayerEnabled = new QCheckBox(SVDBComponentEditWidget);
        checkBoxActiveLayerEnabled->setObjectName(QString::fromUtf8("checkBoxActiveLayerEnabled"));
        checkBoxActiveLayerEnabled->setMaximumSize(QSize(16777215, 16777215));
        checkBoxActiveLayerEnabled->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(checkBoxActiveLayerEnabled);

        horizontalSpacer = new QSpacerItem(75, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        masterLayout->addLayout(horizontalLayout_2);

        tabWidgetProperties = new QTabWidget(SVDBComponentEditWidget);
        tabWidgetProperties->setObjectName(QString::fromUtf8("tabWidgetProperties"));
        tabWidgetProperties->setEnabled(true);
        tabWidgetProperties->setTabShape(QTabWidget::Rounded);
        tabConstructionType = new QWidget();
        tabConstructionType->setObjectName(QString::fromUtf8("tabConstructionType"));
        gridLayout = new QGridLayout(tabConstructionType);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(tabConstructionType);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEditBoundaryConditionSideBName = new QLineEdit(groupBox_3);
        lineEditBoundaryConditionSideBName->setObjectName(QString::fromUtf8("lineEditBoundaryConditionSideBName"));
        lineEditBoundaryConditionSideBName->setReadOnly(true);

        gridLayout_3->addWidget(lineEditBoundaryConditionSideBName, 0, 0, 1, 1);

        toolButtonSelectBoundaryConditionSideBName = new QToolButton(groupBox_3);
        toolButtonSelectBoundaryConditionSideBName->setObjectName(QString::fromUtf8("toolButtonSelectBoundaryConditionSideBName"));

        gridLayout_3->addWidget(toolButtonSelectBoundaryConditionSideBName, 0, 1, 1, 1);

        toolButtonRemoveBoundaryConditionSideB = new QToolButton(groupBox_3);
        toolButtonRemoveBoundaryConditionSideB->setObjectName(QString::fromUtf8("toolButtonRemoveBoundaryConditionSideB"));
        toolButtonRemoveBoundaryConditionSideB->setIcon(icon);

        gridLayout_3->addWidget(toolButtonRemoveBoundaryConditionSideB, 0, 2, 1, 1);

        textBrowserBCSideB = new QTextBrowser(groupBox_3);
        textBrowserBCSideB->setObjectName(QString::fromUtf8("textBrowserBCSideB"));

        gridLayout_3->addWidget(textBrowserBCSideB, 1, 0, 1, 3);


        gridLayout->addWidget(groupBox_3, 1, 2, 1, 1);

        groupBox_2 = new QGroupBox(tabConstructionType);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textBrowserBCSideA = new QTextBrowser(groupBox_2);
        textBrowserBCSideA->setObjectName(QString::fromUtf8("textBrowserBCSideA"));

        gridLayout_2->addWidget(textBrowserBCSideA, 1, 0, 1, 3);

        toolButtonSelectBoundaryConditionSideAName = new QToolButton(groupBox_2);
        toolButtonSelectBoundaryConditionSideAName->setObjectName(QString::fromUtf8("toolButtonSelectBoundaryConditionSideAName"));

        gridLayout_2->addWidget(toolButtonSelectBoundaryConditionSideAName, 0, 1, 1, 1);

        lineEditBoundaryConditionSideAName = new QLineEdit(groupBox_2);
        lineEditBoundaryConditionSideAName->setObjectName(QString::fromUtf8("lineEditBoundaryConditionSideAName"));
        lineEditBoundaryConditionSideAName->setReadOnly(true);

        gridLayout_2->addWidget(lineEditBoundaryConditionSideAName, 0, 0, 1, 1);

        toolButtonRemoveBoundaryConditionSideA = new QToolButton(groupBox_2);
        toolButtonRemoveBoundaryConditionSideA->setObjectName(QString::fromUtf8("toolButtonRemoveBoundaryConditionSideA"));
        toolButtonRemoveBoundaryConditionSideA->setIcon(icon);

        gridLayout_2->addWidget(toolButtonRemoveBoundaryConditionSideA, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelUValue = new QLabel(tabConstructionType);
        labelUValue->setObjectName(QString::fromUtf8("labelUValue"));

        horizontalLayout_3->addWidget(labelUValue);

        lineEditUValue = new QLineEdit(tabConstructionType);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));
        lineEditUValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditUValue->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEditUValue);

        labelUValue_2 = new QLabel(tabConstructionType);
        labelUValue_2->setObjectName(QString::fromUtf8("labelUValue_2"));

        horizontalLayout_3->addWidget(labelUValue_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 2);

        tabWidgetProperties->addTab(tabConstructionType, QString());
        tabLCA = new QWidget();
        tabLCA->setObjectName(QString::fromUtf8("tabLCA"));
        tabLCA->setEnabled(false);
        verticalLayout_2 = new QVBoxLayout(tabLCA);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidgetLca = new QTableWidget(tabLCA);
        tableWidgetLca->setObjectName(QString::fromUtf8("tableWidgetLca"));

        verticalLayout_2->addWidget(tableWidgetLca);

        tabWidgetProperties->addTab(tabLCA, QString());
        tabSurface = new QWidget();
        tabSurface->setObjectName(QString::fromUtf8("tabSurface"));
        tabSurface->setEnabled(false);
        verticalLayout = new QVBoxLayout(tabSurface);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEditDaylightName = new QLineEdit(tabSurface);
        lineEditDaylightName->setObjectName(QString::fromUtf8("lineEditDaylightName"));

        horizontalLayout_4->addWidget(lineEditDaylightName);

        pushButtonDaylight = new QPushButton(tabSurface);
        pushButtonDaylight->setObjectName(QString::fromUtf8("pushButtonDaylight"));

        horizontalLayout_4->addWidget(pushButtonDaylight);


        verticalLayout->addLayout(horizontalLayout_4);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelDaylight = new QLabel(tabSurface);
        labelDaylight->setObjectName(QString::fromUtf8("labelDaylight"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelDaylight);

        pushButtonDaylightColor = new QtExt::ColorButton(tabSurface);
        pushButtonDaylightColor->setObjectName(QString::fromUtf8("pushButtonDaylightColor"));
        sizePolicy1.setHeightForWidth(pushButtonDaylightColor->sizePolicy().hasHeightForWidth());
        pushButtonDaylightColor->setSizePolicy(sizePolicy1);

        formLayout->setWidget(0, QFormLayout::FieldRole, pushButtonDaylightColor);

        labelDaylight_2 = new QLabel(tabSurface);
        labelDaylight_2->setObjectName(QString::fromUtf8("labelDaylight_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelDaylight_2);

        lineEditRoughness = new QtExt::ValidatingLineEdit(tabSurface);
        lineEditRoughness->setObjectName(QString::fromUtf8("lineEditRoughness"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditRoughness);

        labelDaylight_3 = new QLabel(tabSurface);
        labelDaylight_3->setObjectName(QString::fromUtf8("labelDaylight_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelDaylight_3);

        lineEditSpecularity = new QtExt::ValidatingLineEdit(tabSurface);
        lineEditSpecularity->setObjectName(QString::fromUtf8("lineEditSpecularity"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditSpecularity);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidgetProperties->addTab(tabSurface, QString());
        tabAcoustic = new QWidget();
        tabAcoustic->setObjectName(QString::fromUtf8("tabAcoustic"));
        tabAcoustic->setEnabled(false);
        gridLayout_7 = new QGridLayout(tabAcoustic);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(tabAcoustic);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(170, 0));

        horizontalLayout_6->addWidget(label_7);

        lineEditImpactSound = new QtExt::ValidatingLineEdit(tabAcoustic);
        lineEditImpactSound->setObjectName(QString::fromUtf8("lineEditImpactSound"));

        horizontalLayout_6->addWidget(lineEditImpactSound);

        label_10 = new QLabel(tabAcoustic);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_6->addWidget(label_10);


        gridLayout_7->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(tabAcoustic);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(170, 0));

        horizontalLayout_7->addWidget(label_8);

        lineEditAirSoundRes = new QtExt::ValidatingLineEdit(tabAcoustic);
        lineEditAirSoundRes->setObjectName(QString::fromUtf8("lineEditAirSoundRes"));

        horizontalLayout_7->addWidget(lineEditAirSoundRes);

        label_9 = new QLabel(tabAcoustic);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_7->addWidget(label_9);


        gridLayout_7->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_4 = new QGroupBox(tabAcoustic);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        textBrowserAcousticBCSideA = new QTextBrowser(groupBox_4);
        textBrowserAcousticBCSideA->setObjectName(QString::fromUtf8("textBrowserAcousticBCSideA"));

        gridLayout_5->addWidget(textBrowserAcousticBCSideA, 1, 0, 1, 3);

        toolButtonSelectAcousticBoundaryConditionSideAName = new QToolButton(groupBox_4);
        toolButtonSelectAcousticBoundaryConditionSideAName->setObjectName(QString::fromUtf8("toolButtonSelectAcousticBoundaryConditionSideAName"));

        gridLayout_5->addWidget(toolButtonSelectAcousticBoundaryConditionSideAName, 0, 1, 1, 1);

        lineEditAcousticBoundaryConditionSideAName = new QLineEdit(groupBox_4);
        lineEditAcousticBoundaryConditionSideAName->setObjectName(QString::fromUtf8("lineEditAcousticBoundaryConditionSideAName"));
        lineEditAcousticBoundaryConditionSideAName->setReadOnly(true);

        gridLayout_5->addWidget(lineEditAcousticBoundaryConditionSideAName, 0, 0, 1, 1);

        toolButtonRemoveAcousticBoundaryConditionSideA = new QToolButton(groupBox_4);
        toolButtonRemoveAcousticBoundaryConditionSideA->setObjectName(QString::fromUtf8("toolButtonRemoveAcousticBoundaryConditionSideA"));
        toolButtonRemoveAcousticBoundaryConditionSideA->setIcon(icon);

        gridLayout_5->addWidget(toolButtonRemoveAcousticBoundaryConditionSideA, 0, 2, 1, 1);


        horizontalLayout_8->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(tabAcoustic);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        lineEditAcousticBoundaryConditionSideBName = new QLineEdit(groupBox_5);
        lineEditAcousticBoundaryConditionSideBName->setObjectName(QString::fromUtf8("lineEditAcousticBoundaryConditionSideBName"));
        lineEditAcousticBoundaryConditionSideBName->setReadOnly(true);

        gridLayout_6->addWidget(lineEditAcousticBoundaryConditionSideBName, 0, 0, 1, 1);

        toolButtonSelectAcousticBoundaryConditionSideBName = new QToolButton(groupBox_5);
        toolButtonSelectAcousticBoundaryConditionSideBName->setObjectName(QString::fromUtf8("toolButtonSelectAcousticBoundaryConditionSideBName"));

        gridLayout_6->addWidget(toolButtonSelectAcousticBoundaryConditionSideBName, 0, 1, 1, 1);

        toolButtonRemoveAcousticBoundaryConditionSideB = new QToolButton(groupBox_5);
        toolButtonRemoveAcousticBoundaryConditionSideB->setObjectName(QString::fromUtf8("toolButtonRemoveAcousticBoundaryConditionSideB"));
        toolButtonRemoveAcousticBoundaryConditionSideB->setIcon(icon);

        gridLayout_6->addWidget(toolButtonRemoveAcousticBoundaryConditionSideB, 0, 2, 1, 1);

        textBrowserAcousticBCSideB = new QTextBrowser(groupBox_5);
        textBrowserAcousticBCSideB->setObjectName(QString::fromUtf8("textBrowserAcousticBCSideB"));

        gridLayout_6->addWidget(textBrowserAcousticBCSideB, 1, 0, 1, 3);


        horizontalLayout_8->addWidget(groupBox_5);


        gridLayout_7->addLayout(horizontalLayout_8, 2, 0, 1, 1);

        tabWidgetProperties->addTab(tabAcoustic, QString());

        masterLayout->addWidget(tabWidgetProperties);


        retranslateUi(SVDBComponentEditWidget);

        tabWidgetProperties->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SVDBComponentEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBComponentEditWidget)
    {
        labelDisplayName->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Name:", nullptr));
        labelComponentType->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Type:", nullptr));
        toolButtonSelectConstruction->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        labelSurfaceHeatingIndex->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Index of heated construction layer (counting from side A):", nullptr));
        checkBoxActiveLayerEnabled->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Construction has active layer (surface heating/cooling)", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVDBComponentEditWidget", "Boundary Condition Side B", nullptr));
        toolButtonSelectBoundaryConditionSideBName->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVDBComponentEditWidget", "Boundary Condition Side A", nullptr));
        toolButtonSelectBoundaryConditionSideAName->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        labelUValue->setText(QCoreApplication::translate("SVDBComponentEditWidget", "UValue (using assigned BC properties):", nullptr));
#if QT_CONFIG(tooltip)
        lineEditUValue->setToolTip(QCoreApplication::translate("SVDBComponentEditWidget", "U-value is being calculated using the heat conduction values from the assigned boundary conditions.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelUValue_2->setText(QCoreApplication::translate("SVDBComponentEditWidget", "W/m2K", nullptr));
        tabWidgetProperties->setTabText(tabWidgetProperties->indexOf(tabConstructionType), QCoreApplication::translate("SVDBComponentEditWidget", "Thermal properties", nullptr));
        tabWidgetProperties->setTabText(tabWidgetProperties->indexOf(tabLCA), QCoreApplication::translate("SVDBComponentEditWidget", "LCA properties", nullptr));
        pushButtonDaylight->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        labelDaylight->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Color:", nullptr));
        labelDaylight_2->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Roughness:", nullptr));
        labelDaylight_3->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Specularity:", nullptr));
        tabWidgetProperties->setTabText(tabWidgetProperties->indexOf(tabSurface), QCoreApplication::translate("SVDBComponentEditWidget", "Radiance properties", nullptr));
        label_7->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Impact sound value:", nullptr));
        label_10->setText(QCoreApplication::translate("SVDBComponentEditWidget", "dB", nullptr));
        label_8->setText(QCoreApplication::translate("SVDBComponentEditWidget", "Air sound resistance:", nullptr));
        label_9->setText(QCoreApplication::translate("SVDBComponentEditWidget", "dB", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SVDBComponentEditWidget", "Boundary Condition Side A", nullptr));
        toolButtonSelectAcousticBoundaryConditionSideAName->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("SVDBComponentEditWidget", "Boundary Condition Side B", nullptr));
        toolButtonSelectAcousticBoundaryConditionSideBName->setText(QCoreApplication::translate("SVDBComponentEditWidget", "...", nullptr));
        tabWidgetProperties->setTabText(tabWidgetProperties->indexOf(tabAcoustic), QCoreApplication::translate("SVDBComponentEditWidget", "Acoustic properties", nullptr));
        (void)SVDBComponentEditWidget;
    } // retranslateUi

};

namespace Ui {
    class SVDBComponentEditWidget: public Ui_SVDBComponentEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBCOMPONENTEDITWIDGET_H
