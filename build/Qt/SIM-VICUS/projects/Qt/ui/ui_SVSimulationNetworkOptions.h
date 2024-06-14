/********************************************************************************
** Form generated from reading UI file 'SVSimulationNetworkOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONNETWORKOPTIONS_H
#define UI_SVSIMULATIONNETWORKOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationNetworkOptions
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_11;
    QLabel *label_6;
    QFrame *line_2;
    QLabel *label_17;
    QtExt::ValidatingLineEdit *lineEditMaxPipeDiscretization;
    QLabel *label_5;
    QtExt::ValidatingLineEdit *lineEditDefaultFluidTemperature;
    QLabel *label_12;
    QLabel *label_4;
    QComboBox *comboBoxNetwork;
    QtExt::ValidatingLineEdit *lineEditReferencePressure;
    QLabel *label_13;
    QComboBox *comboBoxModelType;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBoxHeatExchangeWithGround;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_14;
    QLabel *label_15;
    QtExt::ValidatingLineEdit *lineEditNumberOfSoilModels;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_2;
    QtExt::ValidatingLineEdit *lineEditPipeDepth;
    QtExt::ValidatingLineEdit *lineEditPipeSpacing;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVSimulationNetworkOptions)
    {
        if (SVSimulationNetworkOptions->objectName().isEmpty())
            SVSimulationNetworkOptions->setObjectName(QString::fromUtf8("SVSimulationNetworkOptions"));
        SVSimulationNetworkOptions->resize(1148, 470);
        verticalLayout = new QVBoxLayout(SVSimulationNetworkOptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(SVSimulationNetworkOptions);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 4, 0, 1, 1);

        label_3 = new QLabel(SVSimulationNetworkOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(SVSimulationNetworkOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 7, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_3->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 7, 2, 1, 1);

        label_11 = new QLabel(SVSimulationNetworkOptions);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 8, 2, 1, 1);

        label_6 = new QLabel(SVSimulationNetworkOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 10, 0, 1, 1);

        line_2 = new QFrame(SVSimulationNetworkOptions);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 5, 0, 1, 3);

        label_17 = new QLabel(SVSimulationNetworkOptions);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 0, 0, 1, 1);

        lineEditMaxPipeDiscretization = new QtExt::ValidatingLineEdit(SVSimulationNetworkOptions);
        lineEditMaxPipeDiscretization->setObjectName(QString::fromUtf8("lineEditMaxPipeDiscretization"));
        lineEditMaxPipeDiscretization->setMaximumSize(QSize(400, 16777215));

        gridLayout_3->addWidget(lineEditMaxPipeDiscretization, 10, 1, 1, 1);

        label_5 = new QLabel(SVSimulationNetworkOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 9, 0, 1, 1);

        lineEditDefaultFluidTemperature = new QtExt::ValidatingLineEdit(SVSimulationNetworkOptions);
        lineEditDefaultFluidTemperature->setObjectName(QString::fromUtf8("lineEditDefaultFluidTemperature"));
        lineEditDefaultFluidTemperature->setMaximumSize(QSize(400, 16777215));

        gridLayout_3->addWidget(lineEditDefaultFluidTemperature, 8, 1, 1, 1);

        label_12 = new QLabel(SVSimulationNetworkOptions);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 9, 2, 1, 1);

        label_4 = new QLabel(SVSimulationNetworkOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 8, 0, 1, 1);

        comboBoxNetwork = new QComboBox(SVSimulationNetworkOptions);
        comboBoxNetwork->setObjectName(QString::fromUtf8("comboBoxNetwork"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxNetwork->sizePolicy().hasHeightForWidth());
        comboBoxNetwork->setSizePolicy(sizePolicy);
        comboBoxNetwork->setMinimumSize(QSize(400, 0));
        comboBoxNetwork->setMaximumSize(QSize(400, 16777215));

        gridLayout_3->addWidget(comboBoxNetwork, 2, 1, 1, 1);

        lineEditReferencePressure = new QtExt::ValidatingLineEdit(SVSimulationNetworkOptions);
        lineEditReferencePressure->setObjectName(QString::fromUtf8("lineEditReferencePressure"));
        lineEditReferencePressure->setMaximumSize(QSize(400, 16777215));

        gridLayout_3->addWidget(lineEditReferencePressure, 9, 1, 1, 1);

        label_13 = new QLabel(SVSimulationNetworkOptions);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 10, 2, 1, 1);

        comboBoxModelType = new QComboBox(SVSimulationNetworkOptions);
        comboBoxModelType->setObjectName(QString::fromUtf8("comboBoxModelType"));
        comboBoxModelType->setMaximumSize(QSize(400, 16777215));

        gridLayout_3->addWidget(comboBoxModelType, 7, 1, 1, 1);

        line_3 = new QFrame(SVSimulationNetworkOptions);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 1, 0, 1, 3);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_4);

        groupBoxHeatExchangeWithGround = new QGroupBox(SVSimulationNetworkOptions);
        groupBoxHeatExchangeWithGround->setObjectName(QString::fromUtf8("groupBoxHeatExchangeWithGround"));
        groupBoxHeatExchangeWithGround->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupBoxHeatExchangeWithGround);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(groupBoxHeatExchangeWithGround);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QFont font;
        font.setItalic(true);
        label_10->setFont(font);

        gridLayout_2->addWidget(label_10, 3, 1, 1, 2);

        label_14 = new QLabel(groupBoxHeatExchangeWithGround);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 0, 2, 1, 1);

        label_15 = new QLabel(groupBoxHeatExchangeWithGround);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 1, 2, 1, 1);

        lineEditNumberOfSoilModels = new QtExt::ValidatingLineEdit(groupBoxHeatExchangeWithGround);
        lineEditNumberOfSoilModels->setObjectName(QString::fromUtf8("lineEditNumberOfSoilModels"));
        lineEditNumberOfSoilModels->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(lineEditNumberOfSoilModels, 2, 1, 1, 1);

        label_16 = new QLabel(groupBoxHeatExchangeWithGround);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        lineEditPipeDepth = new QtExt::ValidatingLineEdit(groupBoxHeatExchangeWithGround);
        lineEditPipeDepth->setObjectName(QString::fromUtf8("lineEditPipeDepth"));
        lineEditPipeDepth->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(lineEditPipeDepth, 1, 1, 1, 1);

        lineEditPipeSpacing = new QtExt::ValidatingLineEdit(groupBoxHeatExchangeWithGround);
        lineEditPipeSpacing->setObjectName(QString::fromUtf8("lineEditPipeSpacing"));
        lineEditPipeSpacing->setMaximumSize(QSize(400, 16777215));

        gridLayout_2->addWidget(lineEditPipeSpacing, 0, 1, 1, 1);

        label_9 = new QLabel(groupBoxHeatExchangeWithGround);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 0, 1, 1);

        label_8 = new QLabel(groupBoxHeatExchangeWithGround);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_7 = new QLabel(groupBoxHeatExchangeWithGround);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxHeatExchangeWithGround);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SVSimulationNetworkOptions);

        QMetaObject::connectSlotsByName(SVSimulationNetworkOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationNetworkOptions)
    {
        SVSimulationNetworkOptions->setWindowTitle(QCoreApplication::translate("SVSimulationNetworkOptions", "Form", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Hydraulic network model options", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Network ", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Type of simulation:", nullptr));
        label_11->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "C", nullptr));
        label_6->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Maximum pipe discretization length:", nullptr));
        label_17->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Select network", nullptr));
        lineEditMaxPipeDiscretization->setText(QString());
        label_5->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Reference pressure:", nullptr));
        label_12->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "bar", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Default/initial fluid temperature:", nullptr));
        lineEditReferencePressure->setText(QString());
        label_13->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "m", nullptr));
        groupBoxHeatExchangeWithGround->setTitle(QCoreApplication::translate("SVSimulationNetworkOptions", "Heat exchange with ground", nullptr));
        label_10->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "set =0 to use a different soil model for each single pipe", nullptr));
        label_14->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "m", nullptr));
        label_15->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "m", nullptr));
        lineEditNumberOfSoilModels->setText(QString());
        label_16->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "-", nullptr));
        lineEditPipeDepth->setText(QString());
        lineEditPipeSpacing->setText(QString());
        label_9->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Number of different soil models:", nullptr));
        label_8->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Pipe depth below surface:", nullptr));
        label_7->setText(QCoreApplication::translate("SVSimulationNetworkOptions", "Pipe spacing:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationNetworkOptions: public Ui_SVSimulationNetworkOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONNETWORKOPTIONS_H
