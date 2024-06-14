/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkGeometryWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKGEOMETRYWIDGET_H
#define UI_SVPROPNETWORKGEOMETRYWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropEditNetwork
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxProperties;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *labelNodeCount;
    QLabel *label;
    QLabel *label_7;
    QLabel *labelTotalLength;
    QLabel *labelEdgeCount;
    QLabel *labelConnectedSymbol;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *labelSubStationCount;
    QGroupBox *groupBoxFluid;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditFluidName;
    QPushButton *pushButtonSelectFluid;
    QGroupBox *groupBoxEditNetwork;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonGenerateIntersections;
    QPushButton *pushButtonConnectBuildings;
    QPushButton *pushButtonReduceRedundantNodes;
    QPushButton *pushButtonReduceDeadEnds;
    QGroupBox *groupBoxRemoveShortEdges;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_24;
    QtExt::ValidatingLineEdit *lineEditThresholdSmallEdge;
    QLabel *label_25;
    QPushButton *pushButtonRemoveSmallEdge;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonEditSimultaneity;
    QGridLayout *gridLayout;
    QtExt::ValidatingLineEdit *lineEditTemperatureDifference;
    QtExt::ValidatingLineEdit *lineEditTemperatureSetpoint;
    QLabel *label_5;
    QtExt::ValidatingLineEdit *lineEditMaxPressureDrop;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *pushButtonSelectPipes;
    QPushButton *pushButtonSizePipeDimensions;
    QGroupBox *groupBoxVisualisation;
    QFormLayout *formLayout_6;
    QLabel *label_22;
    QSlider *horizontalSliderScaleNodes;
    QLabel *label_27;
    QSlider *horizontalSliderScaleEdges;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVPropEditNetwork)
    {
        if (SVPropEditNetwork->objectName().isEmpty())
            SVPropEditNetwork->setObjectName(QString::fromUtf8("SVPropEditNetwork"));
        SVPropEditNetwork->resize(351, 830);
        verticalLayout_3 = new QVBoxLayout(SVPropEditNetwork);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBoxProperties = new QGroupBox(SVPropEditNetwork);
        groupBoxProperties->setObjectName(QString::fromUtf8("groupBoxProperties"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxProperties->sizePolicy().hasHeightForWidth());
        groupBoxProperties->setSizePolicy(sizePolicy);
        formLayout_2 = new QFormLayout(groupBoxProperties);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(groupBoxProperties);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        labelNodeCount = new QLabel(groupBoxProperties);
        labelNodeCount->setObjectName(QString::fromUtf8("labelNodeCount"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, labelNodeCount);

        label = new QLabel(groupBoxProperties);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label);

        label_7 = new QLabel(groupBoxProperties);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_7);

        labelTotalLength = new QLabel(groupBoxProperties);
        labelTotalLength->setObjectName(QString::fromUtf8("labelTotalLength"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, labelTotalLength);

        labelEdgeCount = new QLabel(groupBoxProperties);
        labelEdgeCount->setObjectName(QString::fromUtf8("labelEdgeCount"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, labelEdgeCount);

        labelConnectedSymbol = new QLabel(groupBoxProperties);
        labelConnectedSymbol->setObjectName(QString::fromUtf8("labelConnectedSymbol"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, labelConnectedSymbol);

        label_6 = new QLabel(groupBoxProperties);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_6);

        label_9 = new QLabel(groupBoxProperties);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_9);

        labelSubStationCount = new QLabel(groupBoxProperties);
        labelSubStationCount->setObjectName(QString::fromUtf8("labelSubStationCount"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, labelSubStationCount);


        verticalLayout_3->addWidget(groupBoxProperties);

        groupBoxFluid = new QGroupBox(SVPropEditNetwork);
        groupBoxFluid->setObjectName(QString::fromUtf8("groupBoxFluid"));
        sizePolicy.setHeightForWidth(groupBoxFluid->sizePolicy().hasHeightForWidth());
        groupBoxFluid->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBoxFluid);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEditFluidName = new QLineEdit(groupBoxFluid);
        lineEditFluidName->setObjectName(QString::fromUtf8("lineEditFluidName"));
        lineEditFluidName->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditFluidName);

        pushButtonSelectFluid = new QPushButton(groupBoxFluid);
        pushButtonSelectFluid->setObjectName(QString::fromUtf8("pushButtonSelectFluid"));

        horizontalLayout_2->addWidget(pushButtonSelectFluid);


        verticalLayout_3->addWidget(groupBoxFluid);

        groupBoxEditNetwork = new QGroupBox(SVPropEditNetwork);
        groupBoxEditNetwork->setObjectName(QString::fromUtf8("groupBoxEditNetwork"));
        sizePolicy.setHeightForWidth(groupBoxEditNetwork->sizePolicy().hasHeightForWidth());
        groupBoxEditNetwork->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBoxEditNetwork);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonGenerateIntersections = new QPushButton(groupBoxEditNetwork);
        pushButtonGenerateIntersections->setObjectName(QString::fromUtf8("pushButtonGenerateIntersections"));
        pushButtonGenerateIntersections->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(pushButtonGenerateIntersections);

        pushButtonConnectBuildings = new QPushButton(groupBoxEditNetwork);
        pushButtonConnectBuildings->setObjectName(QString::fromUtf8("pushButtonConnectBuildings"));
        pushButtonConnectBuildings->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(pushButtonConnectBuildings);

        pushButtonReduceRedundantNodes = new QPushButton(groupBoxEditNetwork);
        pushButtonReduceRedundantNodes->setObjectName(QString::fromUtf8("pushButtonReduceRedundantNodes"));
        pushButtonReduceRedundantNodes->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(pushButtonReduceRedundantNodes);

        pushButtonReduceDeadEnds = new QPushButton(groupBoxEditNetwork);
        pushButtonReduceDeadEnds->setObjectName(QString::fromUtf8("pushButtonReduceDeadEnds"));
        pushButtonReduceDeadEnds->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(pushButtonReduceDeadEnds);


        verticalLayout_3->addWidget(groupBoxEditNetwork);

        groupBoxRemoveShortEdges = new QGroupBox(SVPropEditNetwork);
        groupBoxRemoveShortEdges->setObjectName(QString::fromUtf8("groupBoxRemoveShortEdges"));
        sizePolicy.setHeightForWidth(groupBoxRemoveShortEdges->sizePolicy().hasHeightForWidth());
        groupBoxRemoveShortEdges->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(groupBoxRemoveShortEdges);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_24 = new QLabel(groupBoxRemoveShortEdges);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_3->addWidget(label_24);

        lineEditThresholdSmallEdge = new QtExt::ValidatingLineEdit(groupBoxRemoveShortEdges);
        lineEditThresholdSmallEdge->setObjectName(QString::fromUtf8("lineEditThresholdSmallEdge"));

        horizontalLayout_3->addWidget(lineEditThresholdSmallEdge);

        label_25 = new QLabel(groupBoxRemoveShortEdges);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_3->addWidget(label_25);

        pushButtonRemoveSmallEdge = new QPushButton(groupBoxRemoveShortEdges);
        pushButtonRemoveSmallEdge->setObjectName(QString::fromUtf8("pushButtonRemoveSmallEdge"));

        horizontalLayout_3->addWidget(pushButtonRemoveSmallEdge);


        verticalLayout_3->addWidget(groupBoxRemoveShortEdges);

        groupBox = new QGroupBox(SVPropEditNetwork);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButtonEditSimultaneity = new QPushButton(groupBox);
        pushButtonEditSimultaneity->setObjectName(QString::fromUtf8("pushButtonEditSimultaneity"));

        gridLayout_2->addWidget(pushButtonEditSimultaneity, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditTemperatureDifference = new QtExt::ValidatingLineEdit(groupBox);
        lineEditTemperatureDifference->setObjectName(QString::fromUtf8("lineEditTemperatureDifference"));

        gridLayout->addWidget(lineEditTemperatureDifference, 3, 1, 1, 1);

        lineEditTemperatureSetpoint = new QtExt::ValidatingLineEdit(groupBox);
        lineEditTemperatureSetpoint->setObjectName(QString::fromUtf8("lineEditTemperatureSetpoint"));

        gridLayout->addWidget(lineEditTemperatureSetpoint, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        lineEditMaxPressureDrop = new QtExt::ValidatingLineEdit(groupBox);
        lineEditMaxPressureDrop->setObjectName(QString::fromUtf8("lineEditMaxPressureDrop"));

        gridLayout->addWidget(lineEditMaxPressureDrop, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 0, 2, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 2, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 3, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 2);

        pushButtonSelectPipes = new QPushButton(groupBox);
        pushButtonSelectPipes->setObjectName(QString::fromUtf8("pushButtonSelectPipes"));

        gridLayout_2->addWidget(pushButtonSelectPipes, 0, 1, 1, 1);

        pushButtonSizePipeDimensions = new QPushButton(groupBox);
        pushButtonSizePipeDimensions->setObjectName(QString::fromUtf8("pushButtonSizePipeDimensions"));
        pushButtonSizePipeDimensions->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(pushButtonSizePipeDimensions, 3, 0, 1, 2);


        verticalLayout_3->addWidget(groupBox);

        groupBoxVisualisation = new QGroupBox(SVPropEditNetwork);
        groupBoxVisualisation->setObjectName(QString::fromUtf8("groupBoxVisualisation"));
        sizePolicy.setHeightForWidth(groupBoxVisualisation->sizePolicy().hasHeightForWidth());
        groupBoxVisualisation->setSizePolicy(sizePolicy);
        formLayout_6 = new QFormLayout(groupBoxVisualisation);
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        label_22 = new QLabel(groupBoxVisualisation);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_22);

        horizontalSliderScaleNodes = new QSlider(groupBoxVisualisation);
        horizontalSliderScaleNodes->setObjectName(QString::fromUtf8("horizontalSliderScaleNodes"));
        horizontalSliderScaleNodes->setMinimum(1);
        horizontalSliderScaleNodes->setMaximum(70);
        horizontalSliderScaleNodes->setSingleStep(1);
        horizontalSliderScaleNodes->setPageStep(10);
        horizontalSliderScaleNodes->setOrientation(Qt::Horizontal);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, horizontalSliderScaleNodes);

        label_27 = new QLabel(groupBoxVisualisation);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_27);

        horizontalSliderScaleEdges = new QSlider(groupBoxVisualisation);
        horizontalSliderScaleEdges->setObjectName(QString::fromUtf8("horizontalSliderScaleEdges"));
        horizontalSliderScaleEdges->setMinimum(1);
        horizontalSliderScaleEdges->setMaximum(70);
        horizontalSliderScaleEdges->setOrientation(Qt::Horizontal);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, horizontalSliderScaleEdges);


        verticalLayout_3->addWidget(groupBoxVisualisation);

        verticalSpacer = new QSpacerItem(20, 999, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        QWidget::setTabOrder(lineEditFluidName, pushButtonSelectFluid);
        QWidget::setTabOrder(pushButtonSelectFluid, pushButtonGenerateIntersections);
        QWidget::setTabOrder(pushButtonGenerateIntersections, pushButtonConnectBuildings);
        QWidget::setTabOrder(pushButtonConnectBuildings, pushButtonReduceRedundantNodes);
        QWidget::setTabOrder(pushButtonReduceRedundantNodes, pushButtonReduceDeadEnds);
        QWidget::setTabOrder(pushButtonReduceDeadEnds, lineEditThresholdSmallEdge);
        QWidget::setTabOrder(lineEditThresholdSmallEdge, pushButtonRemoveSmallEdge);
        QWidget::setTabOrder(pushButtonRemoveSmallEdge, pushButtonEditSimultaneity);
        QWidget::setTabOrder(pushButtonEditSimultaneity, pushButtonSelectPipes);
        QWidget::setTabOrder(pushButtonSelectPipes, lineEditMaxPressureDrop);
        QWidget::setTabOrder(lineEditMaxPressureDrop, lineEditTemperatureSetpoint);
        QWidget::setTabOrder(lineEditTemperatureSetpoint, lineEditTemperatureDifference);
        QWidget::setTabOrder(lineEditTemperatureDifference, pushButtonSizePipeDimensions);
        QWidget::setTabOrder(pushButtonSizePipeDimensions, horizontalSliderScaleNodes);
        QWidget::setTabOrder(horizontalSliderScaleNodes, horizontalSliderScaleEdges);

        retranslateUi(SVPropEditNetwork);

        QMetaObject::connectSlotsByName(SVPropEditNetwork);
    } // setupUi

    void retranslateUi(QWidget *SVPropEditNetwork)
    {
        SVPropEditNetwork->setWindowTitle(QCoreApplication::translate("SVPropEditNetwork", "Form", nullptr));
        groupBoxProperties->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Properties", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropEditNetwork", "Nodes", nullptr));
        labelNodeCount->setText(QString());
        label->setText(QCoreApplication::translate("SVPropEditNetwork", "Edges", nullptr));
        label_7->setText(QCoreApplication::translate("SVPropEditNetwork", "Total length", nullptr));
        labelTotalLength->setText(QString());
        labelEdgeCount->setText(QString());
        labelConnectedSymbol->setText(QString());
        label_6->setText(QCoreApplication::translate("SVPropEditNetwork", "Network connected", nullptr));
        label_9->setText(QCoreApplication::translate("SVPropEditNetwork", "Sub Stations", nullptr));
        labelSubStationCount->setText(QString());
        groupBoxFluid->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Fluid", nullptr));
        pushButtonSelectFluid->setText(QCoreApplication::translate("SVPropEditNetwork", "Select fluid...", nullptr));
        groupBoxEditNetwork->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Editing Algorithms", nullptr));
        pushButtonGenerateIntersections->setText(QCoreApplication::translate("SVPropEditNetwork", "Generate intersections", nullptr));
        pushButtonConnectBuildings->setText(QCoreApplication::translate("SVPropEditNetwork", "Connect sub stations", nullptr));
        pushButtonReduceRedundantNodes->setText(QCoreApplication::translate("SVPropEditNetwork", "Reduce redundant nodes", nullptr));
        pushButtonReduceDeadEnds->setText(QCoreApplication::translate("SVPropEditNetwork", "Reduce dead ends", nullptr));
        groupBoxRemoveShortEdges->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Remove short edges", nullptr));
        label_24->setText(QCoreApplication::translate("SVPropEditNetwork", "Threshold:", nullptr));
        lineEditThresholdSmallEdge->setText(QCoreApplication::translate("SVPropEditNetwork", "1", nullptr));
        label_25->setText(QCoreApplication::translate("SVPropEditNetwork", "m", nullptr));
        pushButtonRemoveSmallEdge->setText(QCoreApplication::translate("SVPropEditNetwork", "Remove short edges", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Size pipes", nullptr));
        pushButtonEditSimultaneity->setText(QCoreApplication::translate("SVPropEditNetwork", "Edit simultaneity...", nullptr));
        lineEditTemperatureDifference->setText(QCoreApplication::translate("SVPropEditNetwork", "4", nullptr));
        lineEditTemperatureSetpoint->setText(QCoreApplication::translate("SVPropEditNetwork", "10", nullptr));
        label_5->setText(QCoreApplication::translate("SVPropEditNetwork", "Temperature difference:", nullptr));
        lineEditMaxPressureDrop->setText(QCoreApplication::translate("SVPropEditNetwork", "100", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropEditNetwork", "Temperature setpoint:", nullptr));
        label_8->setText(QCoreApplication::translate("SVPropEditNetwork", "Maximum pressure drop:", nullptr));
        label_10->setText(QCoreApplication::translate("SVPropEditNetwork", "Pa/m", nullptr));
        label_11->setText(QCoreApplication::translate("SVPropEditNetwork", "C", nullptr));
        label_12->setText(QCoreApplication::translate("SVPropEditNetwork", "K", nullptr));
        pushButtonSelectPipes->setText(QCoreApplication::translate("SVPropEditNetwork", "Select available pipes...", nullptr));
        pushButtonSizePipeDimensions->setText(QCoreApplication::translate("SVPropEditNetwork", "Run sizing algorithm", nullptr));
        groupBoxVisualisation->setTitle(QCoreApplication::translate("SVPropEditNetwork", "Visualisation", nullptr));
        label_22->setText(QCoreApplication::translate("SVPropEditNetwork", "Scale Nodes", nullptr));
        label_27->setText(QCoreApplication::translate("SVPropEditNetwork", "Scale Pipes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropEditNetwork: public Ui_SVPropEditNetwork {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKGEOMETRYWIDGET_H
