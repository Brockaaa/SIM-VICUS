/********************************************************************************
** Form generated from reading UI file 'SVDBSubSurfaceComponentEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSUBSURFACECOMPONENTEDITWIDGET_H
#define UI_SVDBSUBSURFACECOMPONENTEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBSubSurfaceComponentEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *masterL;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QComboBox *comboBoxSubSurfaceType;
    QtExt::ColorButton *pushButtonColor;
    QLineEdit *lineEditUValue;
    QLabel *labelComponentType;
    QLabel *labelDisplayName;
    QLabel *labelDisplayName_3;
    QLabel *labelDisplayName_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QTabWidget *tabWidgetShading;
    QWidget *tabWindow;
    QGridLayout *gridLayout_4;
    QToolButton *toolButtonSelectWindow;
    QLabel *labelDisplayName_6;
    QLineEdit *lineEditSHGCValue;
    QLabel *labelDisplayName_4;
    QLineEdit *lineEditWindowName;
    QwtPlot *shgcPlot;
    QWidget *Shading;
    QGridLayout *gridLayout_5;
    QtExt::ValidatingLineEdit *lineEditReductionFactor;
    QLabel *labelDisplayName_5;
    QLabel *labelDisplayName_7;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditBoundaryConditionSideAName;
    QToolButton *toolButtonSelectBoundaryConditionSideAName;
    QToolButton *toolButtonRemoveBoundaryConditionSideA;
    QTextBrowser *textBrowserBCSideA;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEditBoundaryConditionSideBName;
    QToolButton *toolButtonSelectBoundaryConditionSideBName;
    QToolButton *toolButtonRemoveBoundaryConditionSideB;
    QTextBrowser *textBrowserBCSideB;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVDBSubSurfaceComponentEditWidget)
    {
        if (SVDBSubSurfaceComponentEditWidget->objectName().isEmpty())
            SVDBSubSurfaceComponentEditWidget->setObjectName(QString::fromUtf8("SVDBSubSurfaceComponentEditWidget"));
        SVDBSubSurfaceComponentEditWidget->resize(619, 708);
        verticalLayout = new QVBoxLayout(SVDBSubSurfaceComponentEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        masterL = new QGridLayout();
        masterL->setObjectName(QString::fromUtf8("masterL"));
        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBSubSurfaceComponentEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        masterL->addWidget(lineEditName, 0, 1, 1, 1);

        comboBoxSubSurfaceType = new QComboBox(SVDBSubSurfaceComponentEditWidget);
        comboBoxSubSurfaceType->setObjectName(QString::fromUtf8("comboBoxSubSurfaceType"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxSubSurfaceType->sizePolicy().hasHeightForWidth());
        comboBoxSubSurfaceType->setSizePolicy(sizePolicy);

        masterL->addWidget(comboBoxSubSurfaceType, 1, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBSubSurfaceComponentEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy1);

        masterL->addWidget(pushButtonColor, 0, 2, 1, 1);

        lineEditUValue = new QLineEdit(SVDBSubSurfaceComponentEditWidget);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));
        lineEditUValue->setReadOnly(true);

        masterL->addWidget(lineEditUValue, 3, 1, 1, 1);

        labelComponentType = new QLabel(SVDBSubSurfaceComponentEditWidget);
        labelComponentType->setObjectName(QString::fromUtf8("labelComponentType"));

        masterL->addWidget(labelComponentType, 1, 0, 1, 1);

        labelDisplayName = new QLabel(SVDBSubSurfaceComponentEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        masterL->addWidget(labelDisplayName, 0, 0, 1, 1);

        labelDisplayName_3 = new QLabel(SVDBSubSurfaceComponentEditWidget);
        labelDisplayName_3->setObjectName(QString::fromUtf8("labelDisplayName_3"));

        masterL->addWidget(labelDisplayName_3, 3, 2, 1, 1);

        labelDisplayName_2 = new QLabel(SVDBSubSurfaceComponentEditWidget);
        labelDisplayName_2->setObjectName(QString::fromUtf8("labelDisplayName_2"));
        labelDisplayName_2->setMinimumSize(QSize(60, 0));

        masterL->addWidget(labelDisplayName_2, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        masterL->addItem(verticalSpacer_3, 2, 1, 1, 1);


        verticalLayout->addLayout(masterL);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        tabWidgetShading = new QTabWidget(SVDBSubSurfaceComponentEditWidget);
        tabWidgetShading->setObjectName(QString::fromUtf8("tabWidgetShading"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidgetShading->sizePolicy().hasHeightForWidth());
        tabWidgetShading->setSizePolicy(sizePolicy2);
        tabWindow = new QWidget();
        tabWindow->setObjectName(QString::fromUtf8("tabWindow"));
        gridLayout_4 = new QGridLayout(tabWindow);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        toolButtonSelectWindow = new QToolButton(tabWindow);
        toolButtonSelectWindow->setObjectName(QString::fromUtf8("toolButtonSelectWindow"));

        gridLayout_4->addWidget(toolButtonSelectWindow, 0, 2, 1, 1);

        labelDisplayName_6 = new QLabel(tabWindow);
        labelDisplayName_6->setObjectName(QString::fromUtf8("labelDisplayName_6"));

        gridLayout_4->addWidget(labelDisplayName_6, 1, 2, 1, 1);

        lineEditSHGCValue = new QLineEdit(tabWindow);
        lineEditSHGCValue->setObjectName(QString::fromUtf8("lineEditSHGCValue"));
        lineEditSHGCValue->setToolTipDuration(9);
        lineEditSHGCValue->setReadOnly(true);

        gridLayout_4->addWidget(lineEditSHGCValue, 1, 1, 1, 1);

        labelDisplayName_4 = new QLabel(tabWindow);
        labelDisplayName_4->setObjectName(QString::fromUtf8("labelDisplayName_4"));
        labelDisplayName_4->setMinimumSize(QSize(60, 0));

        gridLayout_4->addWidget(labelDisplayName_4, 1, 0, 1, 1);

        lineEditWindowName = new QLineEdit(tabWindow);
        lineEditWindowName->setObjectName(QString::fromUtf8("lineEditWindowName"));
        lineEditWindowName->setReadOnly(true);

        gridLayout_4->addWidget(lineEditWindowName, 0, 0, 1, 2);

        shgcPlot = new QwtPlot(tabWindow);
        shgcPlot->setObjectName(QString::fromUtf8("shgcPlot"));
        sizePolicy2.setHeightForWidth(shgcPlot->sizePolicy().hasHeightForWidth());
        shgcPlot->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(shgcPlot, 2, 0, 1, 3);

        tabWidgetShading->addTab(tabWindow, QString());
        Shading = new QWidget();
        Shading->setObjectName(QString::fromUtf8("Shading"));
        gridLayout_5 = new QGridLayout(Shading);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lineEditReductionFactor = new QtExt::ValidatingLineEdit(Shading);
        lineEditReductionFactor->setObjectName(QString::fromUtf8("lineEditReductionFactor"));
        lineEditReductionFactor->setToolTipDuration(9);
        lineEditReductionFactor->setReadOnly(false);

        gridLayout_5->addWidget(lineEditReductionFactor, 0, 1, 1, 1);

        labelDisplayName_5 = new QLabel(Shading);
        labelDisplayName_5->setObjectName(QString::fromUtf8("labelDisplayName_5"));
        labelDisplayName_5->setMinimumSize(QSize(60, 0));

        gridLayout_5->addWidget(labelDisplayName_5, 0, 0, 1, 1);

        labelDisplayName_7 = new QLabel(Shading);
        labelDisplayName_7->setObjectName(QString::fromUtf8("labelDisplayName_7"));

        gridLayout_5->addWidget(labelDisplayName_7, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 2, 1, 1, 1);

        label_5 = new QLabel(Shading);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setItalic(true);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color:rgb(119, 118, 123)"));
        label_5->setWordWrap(true);

        gridLayout_5->addWidget(label_5, 1, 0, 1, 3);

        tabWidgetShading->addTab(Shading, QString());

        verticalLayout->addWidget(tabWidgetShading);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_2 = new QGroupBox(SVDBSubSurfaceComponentEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditBoundaryConditionSideAName = new QLineEdit(groupBox_2);
        lineEditBoundaryConditionSideAName->setObjectName(QString::fromUtf8("lineEditBoundaryConditionSideAName"));

        gridLayout_2->addWidget(lineEditBoundaryConditionSideAName, 0, 0, 1, 1);

        toolButtonSelectBoundaryConditionSideAName = new QToolButton(groupBox_2);
        toolButtonSelectBoundaryConditionSideAName->setObjectName(QString::fromUtf8("toolButtonSelectBoundaryConditionSideAName"));

        gridLayout_2->addWidget(toolButtonSelectBoundaryConditionSideAName, 0, 1, 1, 1);

        toolButtonRemoveBoundaryConditionSideA = new QToolButton(groupBox_2);
        toolButtonRemoveBoundaryConditionSideA->setObjectName(QString::fromUtf8("toolButtonRemoveBoundaryConditionSideA"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveBoundaryConditionSideA->setIcon(icon);

        gridLayout_2->addWidget(toolButtonRemoveBoundaryConditionSideA, 0, 2, 1, 1);

        textBrowserBCSideA = new QTextBrowser(groupBox_2);
        textBrowserBCSideA->setObjectName(QString::fromUtf8("textBrowserBCSideA"));

        gridLayout_2->addWidget(textBrowserBCSideA, 1, 0, 1, 3);


        horizontalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(SVDBSubSurfaceComponentEditWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEditBoundaryConditionSideBName = new QLineEdit(groupBox_3);
        lineEditBoundaryConditionSideBName->setObjectName(QString::fromUtf8("lineEditBoundaryConditionSideBName"));

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


        horizontalLayout_2->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(SVDBSubSurfaceComponentEditWidget);

        tabWidgetShading->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVDBSubSurfaceComponentEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBSubSurfaceComponentEditWidget)
    {
        SVDBSubSurfaceComponentEditWidget->setWindowTitle(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        lineEditUValue->setToolTip(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "U-value is being calculated using the heat conduction values from the assigned boundary conditions.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelComponentType->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Type:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Name:", nullptr));
        labelDisplayName_3->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "W/m2K", nullptr));
        labelDisplayName_2->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "UValue (using assigned BC properties):", nullptr));
        toolButtonSelectWindow->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "...", nullptr));
        labelDisplayName_6->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "-", nullptr));
        labelDisplayName_4->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "SHGC:", nullptr));
        tabWidgetShading->setTabText(tabWidgetShading->indexOf(tabWindow), QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Window properties", nullptr));
        lineEditReductionFactor->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "1", nullptr));
        labelDisplayName_5->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Sunlight-factor F<sub>z</sub>:", nullptr));
        labelDisplayName_7->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "---", nullptr));
        label_5->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Represents the proportion of radiation that passes through the shading system when shading is activated.", nullptr));
        tabWidgetShading->setTabText(tabWidgetShading->indexOf(Shading), QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Shading properties", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Boundary Condition Side A", nullptr));
        toolButtonSelectBoundaryConditionSideAName->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "...", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "Boundary Condition Side B", nullptr));
        toolButtonSelectBoundaryConditionSideBName->setText(QCoreApplication::translate("SVDBSubSurfaceComponentEditWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBSubSurfaceComponentEditWidget: public Ui_SVDBSubSurfaceComponentEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSUBSURFACECOMPONENTEDITWIDGET_H
