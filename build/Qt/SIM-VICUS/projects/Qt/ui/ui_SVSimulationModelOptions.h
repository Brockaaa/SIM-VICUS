/********************************************************************************
** Form generated from reading UI file 'SVSimulationModelOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONMODELOPTIONS_H
#define UI_SVSIMULATIONMODELOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationModelOptions
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_14;
    QFrame *line_3;
    QCheckBox *checkBoxEnableMoistureBalance;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_15;
    QFrame *line_4;
    QPushButton *pushButtonPrecalculateViewFactors;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *spinBoxSolarRadiationToFloor;
    QLabel *labelInitialRelHum;
    QSpinBox *spinBoxSolarRadiationToRoofCeiling;
    QLabel *label_11;
    QtExt::ValidatingLineEdit *lineEditInitialRelativeHumidity;
    QHBoxLayout *horizontalLayoutErrorSumOfFractions;
    QLabel *iconErrorFractionSum;
    QLabel *labelErrorFractionSum;
    QLabel *label_3;
    QLabel *label_25;
    QFrame *line_2;
    QComboBox *comboBoxSolarDistributionModeltype;
    QLabel *label_9;
    QLabel *label;
    QLabel *label_8;
    QSpinBox *spinBoxSolarRadiationToWalls;
    QtExt::ValidatingLineEdit *lineEditInitialTemperature;
    QLabel *label_7;
    QSpinBox *spinBoxSolarRadiationGainsDirectlyToRoomNode;
    QLabel *label_2;
    QLabel *labelInitialRelHumPerc;
    QLabel *label_5;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_6;
    QCheckBox *checkBoxUsePerez;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVSimulationModelOptions)
    {
        if (SVSimulationModelOptions->objectName().isEmpty())
            SVSimulationModelOptions->setObjectName(QString::fromUtf8("SVSimulationModelOptions"));
        SVSimulationModelOptions->resize(1204, 662);
        QPalette palette;
        SVSimulationModelOptions->setPalette(palette);
        verticalLayout = new QVBoxLayout(SVSimulationModelOptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_14 = new QLabel(SVSimulationModelOptions);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout->addWidget(label_14);

        line_3 = new QFrame(SVSimulationModelOptions);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        checkBoxEnableMoistureBalance = new QCheckBox(SVSimulationModelOptions);
        checkBoxEnableMoistureBalance->setObjectName(QString::fromUtf8("checkBoxEnableMoistureBalance"));

        verticalLayout->addWidget(checkBoxEnableMoistureBalance);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        label_15 = new QLabel(SVSimulationModelOptions);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout->addWidget(label_15);

        line_4 = new QFrame(SVSimulationModelOptions);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        pushButtonPrecalculateViewFactors = new QPushButton(SVSimulationModelOptions);
        pushButtonPrecalculateViewFactors->setObjectName(QString::fromUtf8("pushButtonPrecalculateViewFactors"));
        pushButtonPrecalculateViewFactors->setMaximumSize(QSize(250, 16777215));

        verticalLayout->addWidget(pushButtonPrecalculateViewFactors);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_5);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_13 = new QLabel(SVSimulationModelOptions);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 11, 3, 1, 1);

        spinBoxSolarRadiationToFloor = new QSpinBox(SVSimulationModelOptions);
        spinBoxSolarRadiationToFloor->setObjectName(QString::fromUtf8("spinBoxSolarRadiationToFloor"));
        spinBoxSolarRadiationToFloor->setMaximumSize(QSize(400, 16777215));
        spinBoxSolarRadiationToFloor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(spinBoxSolarRadiationToFloor, 14, 1, 1, 1);

        labelInitialRelHum = new QLabel(SVSimulationModelOptions);
        labelInitialRelHum->setObjectName(QString::fromUtf8("labelInitialRelHum"));

        gridLayout->addWidget(labelInitialRelHum, 4, 0, 1, 1);

        spinBoxSolarRadiationToRoofCeiling = new QSpinBox(SVSimulationModelOptions);
        spinBoxSolarRadiationToRoofCeiling->setObjectName(QString::fromUtf8("spinBoxSolarRadiationToRoofCeiling"));
        spinBoxSolarRadiationToRoofCeiling->setMaximumSize(QSize(400, 16777215));
        spinBoxSolarRadiationToRoofCeiling->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(spinBoxSolarRadiationToRoofCeiling, 15, 1, 1, 1);

        label_11 = new QLabel(SVSimulationModelOptions);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 16, 2, 1, 1);

        lineEditInitialRelativeHumidity = new QtExt::ValidatingLineEdit(SVSimulationModelOptions);
        lineEditInitialRelativeHumidity->setObjectName(QString::fromUtf8("lineEditInitialRelativeHumidity"));
        lineEditInitialRelativeHumidity->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditInitialRelativeHumidity, 4, 1, 1, 1);

        horizontalLayoutErrorSumOfFractions = new QHBoxLayout();
        horizontalLayoutErrorSumOfFractions->setObjectName(QString::fromUtf8("horizontalLayoutErrorSumOfFractions"));
        iconErrorFractionSum = new QLabel(SVSimulationModelOptions);
        iconErrorFractionSum->setObjectName(QString::fromUtf8("iconErrorFractionSum"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconErrorFractionSum->sizePolicy().hasHeightForWidth());
        iconErrorFractionSum->setSizePolicy(sizePolicy);
        iconErrorFractionSum->setPixmap(QPixmap(QString::fromUtf8(":/gfx/actions/16x16/error.png")));

        horizontalLayoutErrorSumOfFractions->addWidget(iconErrorFractionSum);

        labelErrorFractionSum = new QLabel(SVSimulationModelOptions);
        labelErrorFractionSum->setObjectName(QString::fromUtf8("labelErrorFractionSum"));
        QPalette palette1;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(227, 227, 227, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(160, 160, 160, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush4);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush6(QColor(105, 105, 105, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush7(QColor(0, 120, 215, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush2);
        QBrush brush8(QColor(0, 0, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Link, brush8);
        QBrush brush9(QColor(255, 0, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush9);
        QBrush brush10(QColor(245, 245, 245, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush10);
        QBrush brush11(QColor(0, 0, 0, 255));
        brush11.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Active, QPalette::NoRole, brush11);
        QBrush brush12(QColor(255, 255, 220, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush12);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        QBrush brush13(QColor(0, 0, 0, 128));
        brush13.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush13);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Link, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush10);
        QBrush brush14(QColor(0, 0, 0, 255));
        brush14.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Inactive, QPalette::NoRole, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush13);
#endif
        QBrush brush15(QColor(120, 120, 120, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        QBrush brush16(QColor(247, 247, 247, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush16);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush15);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Link, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush10);
        QBrush brush17(QColor(0, 0, 0, 255));
        brush17.setStyle(Qt::NoBrush);
        palette1.setBrush(QPalette::Disabled, QPalette::NoRole, brush17);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush13);
#endif
        labelErrorFractionSum->setPalette(palette1);
        QFont font;
        font.setItalic(true);
        labelErrorFractionSum->setFont(font);

        horizontalLayoutErrorSumOfFractions->addWidget(labelErrorFractionSum);


        gridLayout->addLayout(horizontalLayoutErrorSumOfFractions, 17, 1, 1, 1);

        label_3 = new QLabel(SVSimulationModelOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 14, 0, 1, 1);

        label_25 = new QLabel(SVSimulationModelOptions);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 6, 0, 1, 1);

        line_2 = new QFrame(SVSimulationModelOptions);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 4);

        comboBoxSolarDistributionModeltype = new QComboBox(SVSimulationModelOptions);
        comboBoxSolarDistributionModeltype->setObjectName(QString::fromUtf8("comboBoxSolarDistributionModeltype"));
        comboBoxSolarDistributionModeltype->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(comboBoxSolarDistributionModeltype, 13, 1, 1, 2);

        label_9 = new QLabel(SVSimulationModelOptions);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 14, 2, 1, 1);

        label = new QLabel(SVSimulationModelOptions);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 13, 0, 1, 1);

        label_8 = new QLabel(SVSimulationModelOptions);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 11, 2, 1, 1);

        spinBoxSolarRadiationToWalls = new QSpinBox(SVSimulationModelOptions);
        spinBoxSolarRadiationToWalls->setObjectName(QString::fromUtf8("spinBoxSolarRadiationToWalls"));
        spinBoxSolarRadiationToWalls->setMaximumSize(QSize(400, 16777215));
        spinBoxSolarRadiationToWalls->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(spinBoxSolarRadiationToWalls, 16, 1, 1, 1);

        lineEditInitialTemperature = new QtExt::ValidatingLineEdit(SVSimulationModelOptions);
        lineEditInitialTemperature->setObjectName(QString::fromUtf8("lineEditInitialTemperature"));
        lineEditInitialTemperature->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditInitialTemperature, 3, 1, 1, 1);

        label_7 = new QLabel(SVSimulationModelOptions);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 10, 0, 1, 4);

        spinBoxSolarRadiationGainsDirectlyToRoomNode = new QSpinBox(SVSimulationModelOptions);
        spinBoxSolarRadiationGainsDirectlyToRoomNode->setObjectName(QString::fromUtf8("spinBoxSolarRadiationGainsDirectlyToRoomNode"));
        spinBoxSolarRadiationGainsDirectlyToRoomNode->setMaximumSize(QSize(400, 16777215));
        spinBoxSolarRadiationGainsDirectlyToRoomNode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(spinBoxSolarRadiationGainsDirectlyToRoomNode, 11, 1, 1, 1);

        label_2 = new QLabel(SVSimulationModelOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 11, 0, 1, 1);

        labelInitialRelHumPerc = new QLabel(SVSimulationModelOptions);
        labelInitialRelHumPerc->setObjectName(QString::fromUtf8("labelInitialRelHumPerc"));

        gridLayout->addWidget(labelInitialRelHumPerc, 4, 2, 1, 1);

        label_5 = new QLabel(SVSimulationModelOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 16, 0, 1, 1);

        label_12 = new QLabel(SVSimulationModelOptions);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 3, 2, 1, 1);

        label_10 = new QLabel(SVSimulationModelOptions);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 15, 2, 1, 1);

        label_6 = new QLabel(SVSimulationModelOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 2);

        checkBoxUsePerez = new QCheckBox(SVSimulationModelOptions);
        checkBoxUsePerez->setObjectName(QString::fromUtf8("checkBoxUsePerez"));

        gridLayout->addWidget(checkBoxUsePerez, 9, 0, 1, 1);

        label_4 = new QLabel(SVSimulationModelOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 15, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 12, 1, 1, 1);

        line = new QFrame(SVSimulationModelOptions);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 7, 0, 1, 4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_4, 5, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 13, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SVSimulationModelOptions);

        QMetaObject::connectSlotsByName(SVSimulationModelOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationModelOptions)
    {
        SVSimulationModelOptions->setWindowTitle(QCoreApplication::translate("SVSimulationModelOptions", "Form", nullptr));
        label_14->setText(QCoreApplication::translate("SVSimulationModelOptions", "Balance equations", nullptr));
        checkBoxEnableMoistureBalance->setText(QCoreApplication::translate("SVSimulationModelOptions", "Enable moisture balance", nullptr));
        label_15->setText(QCoreApplication::translate("SVSimulationModelOptions", "Long Wave Radiation Heat Exchange", nullptr));
        pushButtonPrecalculateViewFactors->setText(QCoreApplication::translate("SVSimulationModelOptions", "Precalculate View Factors", nullptr));
        label_13->setText(QCoreApplication::translate("SVSimulationModelOptions", "Initial temperature:", nullptr));
        labelInitialRelHum->setText(QCoreApplication::translate("SVSimulationModelOptions", "Initial relative humidity:", nullptr));
        label_11->setText(QCoreApplication::translate("SVSimulationModelOptions", "%", nullptr));
        iconErrorFractionSum->setText(QString());
        labelErrorFractionSum->setText(QCoreApplication::translate("SVSimulationModelOptions", "Radiation load fractions for walls, ceiling and floor must add up to 1.", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationModelOptions", "Percentage of surface solar radiation attributed to floor:", nullptr));
        label_25->setText(QCoreApplication::translate("SVSimulationModelOptions", "Solar radiation model options", nullptr));
        label_9->setText(QCoreApplication::translate("SVSimulationModelOptions", "%", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationModelOptions", "Solar radiation distribution on surfaces:", nullptr));
        label_8->setText(QCoreApplication::translate("SVSimulationModelOptions", "%", nullptr));
        label_7->setText(QCoreApplication::translate("SVSimulationModelOptions", "DIN EN ISO 13791 G.2: no furniture 0 % | small amount of furniture 10 % | large amount of furniture 20 %", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationModelOptions", "Percentage of solar radiation gains attributed direcly to room node:", nullptr));
        labelInitialRelHumPerc->setText(QCoreApplication::translate("SVSimulationModelOptions", "%", nullptr));
        label_5->setText(QCoreApplication::translate("SVSimulationModelOptions", "Percentage of surface solar radiation attributed to walls:", nullptr));
        label_12->setText(QCoreApplication::translate("SVSimulationModelOptions", "C", nullptr));
        label_10->setText(QCoreApplication::translate("SVSimulationModelOptions", "%", nullptr));
        label_6->setText(QCoreApplication::translate("SVSimulationModelOptions", "Initial conditions", nullptr));
        checkBoxUsePerez->setText(QCoreApplication::translate("SVSimulationModelOptions", "Use Perez-Radiation model", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationModelOptions", "Percentage of surface solar radiation attributed to roof/ceiling:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationModelOptions: public Ui_SVSimulationModelOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONMODELOPTIONS_H
