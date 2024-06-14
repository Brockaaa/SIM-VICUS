/********************************************************************************
** Form generated from reading UI file 'SVPropResultsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPRESULTSWIDGET_H
#define UI_SVPROPRESULTSWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"
#include "SVTimeSliderWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVPropResultsWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QtExt::BrowseFilenameWidget *resultsDir;
    QToolButton *toolButtonSetDefaultDirectory;
    QGroupBox *groupBoxAvailableOutputs;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonRefreshDirectory;
    QTableWidget *tableWidgetAvailableResults;
    QLabel *label;
    QCheckBox *checkBoxConvertToAbsolute;
    QGroupBox *groupBoxColormap;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QPushButton *pushButtonSetDefaultColormap;
    QPushButton *pushButtonSetColormapViridis;
    QPushButton *pushButtonSetColormapSpectral;
    QPushButton *pushButtonReadColormap;
    QPushButton *pushButtonSaveColormap;
    QLabel *label_3;
    QLabel *label_4;
    QtExt::ValidatingLineEdit *lineEditMaxValue;
    QtExt::ValidatingLineEdit *lineEditMinValue;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSetLocalMinMax;
    QPushButton *pushButtonSetGlobalMinMax;
    QGroupBox *groupBoxAnalysis;
    QGridLayout *gridLayout;
    QPushButton *pushButtonJumpToMax;
    QPushButton *pushButtonFindMinObject;
    QPushButton *pushButtonJumpToMin;
    QLabel *label_6;
    QLabel *label_2;
    QPushButton *pushButtonFindMaxObject;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelCurrentValue;
    QLineEdit *lineEditCurrentValue;
    QGroupBox *groupBoxTime;
    QVBoxLayout *verticalLayout;
    SVTimeSliderWidget *widgetTimeSlider;

    void setupUi(QWidget *SVPropResultsWidget)
    {
        if (SVPropResultsWidget->objectName().isEmpty())
            SVPropResultsWidget->setObjectName(QString::fromUtf8("SVPropResultsWidget"));
        SVPropResultsWidget->resize(445, 717);
        verticalLayout_2 = new QVBoxLayout(SVPropResultsWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(SVPropResultsWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        resultsDir = new QtExt::BrowseFilenameWidget(groupBox);
        resultsDir->setObjectName(QString::fromUtf8("resultsDir"));

        horizontalLayout->addWidget(resultsDir);

        toolButtonSetDefaultDirectory = new QToolButton(groupBox);
        toolButtonSetDefaultDirectory->setObjectName(QString::fromUtf8("toolButtonSetDefaultDirectory"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/arrow-source-grey.png"), QSize(), QIcon::Normal, QIcon::On);
        toolButtonSetDefaultDirectory->setIcon(icon);

        horizontalLayout->addWidget(toolButtonSetDefaultDirectory);


        verticalLayout_2->addWidget(groupBox);

        groupBoxAvailableOutputs = new QGroupBox(SVPropResultsWidget);
        groupBoxAvailableOutputs->setObjectName(QString::fromUtf8("groupBoxAvailableOutputs"));
        verticalLayout_3 = new QVBoxLayout(groupBoxAvailableOutputs);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButtonRefreshDirectory = new QPushButton(groupBoxAvailableOutputs);
        pushButtonRefreshDirectory->setObjectName(QString::fromUtf8("pushButtonRefreshDirectory"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/reload.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonRefreshDirectory->setIcon(icon1);
        pushButtonRefreshDirectory->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButtonRefreshDirectory);

        tableWidgetAvailableResults = new QTableWidget(groupBoxAvailableOutputs);
        tableWidgetAvailableResults->setObjectName(QString::fromUtf8("tableWidgetAvailableResults"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetAvailableResults->sizePolicy().hasHeightForWidth());
        tableWidgetAvailableResults->setSizePolicy(sizePolicy);
        tableWidgetAvailableResults->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_3->addWidget(tableWidgetAvailableResults);

        label = new QLabel(groupBoxAvailableOutputs);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setItalic(true);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        checkBoxConvertToAbsolute = new QCheckBox(groupBoxAvailableOutputs);
        checkBoxConvertToAbsolute->setObjectName(QString::fromUtf8("checkBoxConvertToAbsolute"));

        verticalLayout_3->addWidget(checkBoxConvertToAbsolute);


        verticalLayout_2->addWidget(groupBoxAvailableOutputs);

        groupBoxColormap = new QGroupBox(SVPropResultsWidget);
        groupBoxColormap->setObjectName(QString::fromUtf8("groupBoxColormap"));
        gridLayout_2 = new QGridLayout(groupBoxColormap);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(groupBoxColormap);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        pushButtonSetDefaultColormap = new QPushButton(groupBoxColormap);
        pushButtonSetDefaultColormap->setObjectName(QString::fromUtf8("pushButtonSetDefaultColormap"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonSetDefaultColormap->sizePolicy().hasHeightForWidth());
        pushButtonSetDefaultColormap->setSizePolicy(sizePolicy2);
        pushButtonSetDefaultColormap->setMinimumSize(QSize(40, 0));
        pushButtonSetDefaultColormap->setMaximumSize(QSize(30, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/colormap_turbo.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSetDefaultColormap->setIcon(icon2);
        pushButtonSetDefaultColormap->setIconSize(QSize(36, 12));

        gridLayout_2->addWidget(pushButtonSetDefaultColormap, 0, 1, 1, 1);

        pushButtonSetColormapViridis = new QPushButton(groupBoxColormap);
        pushButtonSetColormapViridis->setObjectName(QString::fromUtf8("pushButtonSetColormapViridis"));
        sizePolicy2.setHeightForWidth(pushButtonSetColormapViridis->sizePolicy().hasHeightForWidth());
        pushButtonSetColormapViridis->setSizePolicy(sizePolicy2);
        pushButtonSetColormapViridis->setMinimumSize(QSize(40, 0));
        pushButtonSetColormapViridis->setMaximumSize(QSize(30, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/colormap_viridis.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSetColormapViridis->setIcon(icon3);
        pushButtonSetColormapViridis->setIconSize(QSize(36, 12));

        gridLayout_2->addWidget(pushButtonSetColormapViridis, 0, 2, 1, 1);

        pushButtonSetColormapSpectral = new QPushButton(groupBoxColormap);
        pushButtonSetColormapSpectral->setObjectName(QString::fromUtf8("pushButtonSetColormapSpectral"));
        sizePolicy2.setHeightForWidth(pushButtonSetColormapSpectral->sizePolicy().hasHeightForWidth());
        pushButtonSetColormapSpectral->setSizePolicy(sizePolicy2);
        pushButtonSetColormapSpectral->setMinimumSize(QSize(40, 0));
        pushButtonSetColormapSpectral->setMaximumSize(QSize(30, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/actions/colormap_spectral.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSetColormapSpectral->setIcon(icon4);
        pushButtonSetColormapSpectral->setIconSize(QSize(36, 12));

        gridLayout_2->addWidget(pushButtonSetColormapSpectral, 0, 3, 1, 1);

        pushButtonReadColormap = new QPushButton(groupBoxColormap);
        pushButtonReadColormap->setObjectName(QString::fromUtf8("pushButtonReadColormap"));
        pushButtonReadColormap->setIconSize(QSize(16, 16));

        gridLayout_2->addWidget(pushButtonReadColormap, 0, 4, 1, 1);

        pushButtonSaveColormap = new QPushButton(groupBoxColormap);
        pushButtonSaveColormap->setObjectName(QString::fromUtf8("pushButtonSaveColormap"));
        pushButtonSaveColormap->setIconSize(QSize(16, 16));

        gridLayout_2->addWidget(pushButtonSaveColormap, 0, 5, 1, 1);

        label_3 = new QLabel(groupBoxColormap);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(groupBoxColormap);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        lineEditMaxValue = new QtExt::ValidatingLineEdit(groupBoxColormap);
        lineEditMaxValue->setObjectName(QString::fromUtf8("lineEditMaxValue"));

        gridLayout_2->addWidget(lineEditMaxValue, 1, 1, 1, 5);

        lineEditMinValue = new QtExt::ValidatingLineEdit(groupBoxColormap);
        lineEditMinValue->setObjectName(QString::fromUtf8("lineEditMinValue"));

        gridLayout_2->addWidget(lineEditMinValue, 2, 1, 1, 5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonSetLocalMinMax = new QPushButton(groupBoxColormap);
        pushButtonSetLocalMinMax->setObjectName(QString::fromUtf8("pushButtonSetLocalMinMax"));
        pushButtonSetLocalMinMax->setMinimumSize(QSize(0, 0));
        pushButtonSetLocalMinMax->setIconSize(QSize(24, 24));
        pushButtonSetLocalMinMax->setAutoRepeatDelay(302);

        horizontalLayout_2->addWidget(pushButtonSetLocalMinMax);

        pushButtonSetGlobalMinMax = new QPushButton(groupBoxColormap);
        pushButtonSetGlobalMinMax->setObjectName(QString::fromUtf8("pushButtonSetGlobalMinMax"));
        pushButtonSetGlobalMinMax->setMinimumSize(QSize(0, 0));
        pushButtonSetGlobalMinMax->setIconSize(QSize(24, 24));
        pushButtonSetGlobalMinMax->setAutoRepeatDelay(302);

        horizontalLayout_2->addWidget(pushButtonSetGlobalMinMax);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 1, 1, 5);


        verticalLayout_2->addWidget(groupBoxColormap);

        groupBoxAnalysis = new QGroupBox(SVPropResultsWidget);
        groupBoxAnalysis->setObjectName(QString::fromUtf8("groupBoxAnalysis"));
        gridLayout = new QGridLayout(groupBoxAnalysis);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonJumpToMax = new QPushButton(groupBoxAnalysis);
        pushButtonJumpToMax->setObjectName(QString::fromUtf8("pushButtonJumpToMax"));
        pushButtonJumpToMax->setMinimumSize(QSize(0, 0));
        pushButtonJumpToMax->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonJumpToMax, 0, 1, 1, 1);

        pushButtonFindMinObject = new QPushButton(groupBoxAnalysis);
        pushButtonFindMinObject->setObjectName(QString::fromUtf8("pushButtonFindMinObject"));
        pushButtonFindMinObject->setMinimumSize(QSize(0, 0));
        pushButtonFindMinObject->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonFindMinObject, 1, 2, 1, 1);

        pushButtonJumpToMin = new QPushButton(groupBoxAnalysis);
        pushButtonJumpToMin->setObjectName(QString::fromUtf8("pushButtonJumpToMin"));
        pushButtonJumpToMin->setMinimumSize(QSize(0, 0));
        pushButtonJumpToMin->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonJumpToMin, 0, 2, 1, 1);

        label_6 = new QLabel(groupBoxAnalysis);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        label_2 = new QLabel(groupBoxAnalysis);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pushButtonFindMaxObject = new QPushButton(groupBoxAnalysis);
        pushButtonFindMaxObject->setObjectName(QString::fromUtf8("pushButtonFindMaxObject"));
        pushButtonFindMaxObject->setMinimumSize(QSize(0, 0));
        pushButtonFindMaxObject->setIconSize(QSize(24, 24));

        gridLayout->addWidget(pushButtonFindMaxObject, 1, 1, 1, 1);

        label_7 = new QLabel(groupBoxAnalysis);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelCurrentValue = new QLabel(groupBoxAnalysis);
        labelCurrentValue->setObjectName(QString::fromUtf8("labelCurrentValue"));

        horizontalLayout_3->addWidget(labelCurrentValue);

        lineEditCurrentValue = new QLineEdit(groupBoxAnalysis);
        lineEditCurrentValue->setObjectName(QString::fromUtf8("lineEditCurrentValue"));
        lineEditCurrentValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditCurrentValue->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEditCurrentValue);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 2);


        verticalLayout_2->addWidget(groupBoxAnalysis);

        groupBoxTime = new QGroupBox(SVPropResultsWidget);
        groupBoxTime->setObjectName(QString::fromUtf8("groupBoxTime"));
        verticalLayout = new QVBoxLayout(groupBoxTime);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widgetTimeSlider = new SVTimeSliderWidget(groupBoxTime);
        widgetTimeSlider->setObjectName(QString::fromUtf8("widgetTimeSlider"));

        verticalLayout->addWidget(widgetTimeSlider);


        verticalLayout_2->addWidget(groupBoxTime);


        retranslateUi(SVPropResultsWidget);

        QMetaObject::connectSlotsByName(SVPropResultsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropResultsWidget)
    {
        SVPropResultsWidget->setWindowTitle(QCoreApplication::translate("SVPropResultsWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPropResultsWidget", "Results directory", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonSetDefaultDirectory->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Reset to default output directory.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonSetDefaultDirectory->setText(QString());
        groupBoxAvailableOutputs->setTitle(QCoreApplication::translate("SVPropResultsWidget", "Available outputs", nullptr));
        pushButtonRefreshDirectory->setText(QCoreApplication::translate("SVPropResultsWidget", "Refresh list of available outputs", nullptr));
        label->setText(QCoreApplication::translate("SVPropResultsWidget", "Double-click output quantity to read/update data set!", nullptr));
        checkBoxConvertToAbsolute->setText(QCoreApplication::translate("SVPropResultsWidget", "convert to absolute values", nullptr));
        groupBoxColormap->setTitle(QCoreApplication::translate("SVPropResultsWidget", "Colormap", nullptr));
        label_5->setText(QCoreApplication::translate("SVPropResultsWidget", "Colormap", nullptr));
        pushButtonSetDefaultColormap->setText(QString());
        pushButtonSetColormapViridis->setText(QString());
        pushButtonSetColormapSpectral->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonReadColormap->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Read colormap from file ...", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonReadColormap->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonSaveColormap->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Save colormap to file ...", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSaveColormap->setText(QString());
        label_3->setText(QCoreApplication::translate("SVPropResultsWidget", "Maximum:", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropResultsWidget", "Minimum:", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSetLocalMinMax->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "set colormap range to current minimum / maximum", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSetLocalMinMax->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonSetGlobalMinMax->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "set colormap range to minimum / maximum of entire timeseries", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSetGlobalMinMax->setText(QString());
        groupBoxAnalysis->setTitle(QCoreApplication::translate("SVPropResultsWidget", "Analysis", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonJumpToMax->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Jump to time point of the maximum value of entire data set", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonJumpToMax->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonFindMinObject->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Show object with minimum value at current time point", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonFindMinObject->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonJumpToMin->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Jump to time point of the minimum value of entire data set", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonJumpToMin->setText(QString());
        label_6->setText(QCoreApplication::translate("SVPropResultsWidget", "Find object", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropResultsWidget", "Set time point", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonFindMaxObject->setToolTip(QCoreApplication::translate("SVPropResultsWidget", "Show object with maximum value at current time point", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonFindMaxObject->setText(QString());
        label_7->setText(QCoreApplication::translate("SVPropResultsWidget", "Current selection", nullptr));
        labelCurrentValue->setText(QCoreApplication::translate("SVPropResultsWidget", "None selected", nullptr));
        groupBoxTime->setTitle(QCoreApplication::translate("SVPropResultsWidget", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropResultsWidget: public Ui_SVPropResultsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPRESULTSWIDGET_H
