/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkNodesWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKNODESWIDGET_H
#define UI_SVPROPNETWORKNODESWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropNetworkNodesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxEditNode;
    QGridLayout *gridLayout;
    QLabel *label_19;
    QComboBox *comboBoxNodeType;
    QLabel *label_20;
    QLineEdit *lineEditNodeId;
    QLabel *label_21;
    QLineEdit *lineEditNodeName;
    QLabel *label_23;
    QtExt::ValidatingLineEdit *lineEditNodeMaximumHeatingDemand;
    QLabel *label_27;
    QGroupBox *groupBoxPosition;
    QHBoxLayout *horizontalLayout_6;
    QtExt::ValidatingLineEdit *lineEditNodeXPosition;
    QtExt::ValidatingLineEdit *lineEditNodeYPosition;
    QtExt::ValidatingLineEdit *lineEditNodeZPosition;
    QGridLayout *gridLayout_12;
    QFrame *frameMixer;
    QFrame *frameSubStation;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QFrame *frameSource;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVPropNetworkNodesWidget)
    {
        if (SVPropNetworkNodesWidget->objectName().isEmpty())
            SVPropNetworkNodesWidget->setObjectName(QString::fromUtf8("SVPropNetworkNodesWidget"));
        SVPropNetworkNodesWidget->resize(632, 652);
        verticalLayout = new QVBoxLayout(SVPropNetworkNodesWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxEditNode = new QGroupBox(SVPropNetworkNodesWidget);
        groupBoxEditNode->setObjectName(QString::fromUtf8("groupBoxEditNode"));
        gridLayout = new QGridLayout(groupBoxEditNode);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_19 = new QLabel(groupBoxEditNode);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 0, 0, 1, 1);

        comboBoxNodeType = new QComboBox(groupBoxEditNode);
        comboBoxNodeType->setObjectName(QString::fromUtf8("comboBoxNodeType"));

        gridLayout->addWidget(comboBoxNodeType, 0, 1, 1, 1);

        label_20 = new QLabel(groupBoxEditNode);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 1, 0, 1, 1);

        lineEditNodeId = new QLineEdit(groupBoxEditNode);
        lineEditNodeId->setObjectName(QString::fromUtf8("lineEditNodeId"));
        lineEditNodeId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lineEditNodeId, 1, 1, 1, 1);

        label_21 = new QLabel(groupBoxEditNode);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout->addWidget(label_21, 2, 0, 1, 1);

        lineEditNodeName = new QLineEdit(groupBoxEditNode);
        lineEditNodeName->setObjectName(QString::fromUtf8("lineEditNodeName"));
        lineEditNodeName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lineEditNodeName, 2, 1, 1, 1);

        label_23 = new QLabel(groupBoxEditNode);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 3, 0, 1, 1);

        lineEditNodeMaximumHeatingDemand = new QtExt::ValidatingLineEdit(groupBoxEditNode);
        lineEditNodeMaximumHeatingDemand->setObjectName(QString::fromUtf8("lineEditNodeMaximumHeatingDemand"));

        gridLayout->addWidget(lineEditNodeMaximumHeatingDemand, 3, 1, 1, 1);

        label_27 = new QLabel(groupBoxEditNode);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout->addWidget(label_27, 3, 2, 1, 1);


        verticalLayout->addWidget(groupBoxEditNode);

        groupBoxPosition = new QGroupBox(SVPropNetworkNodesWidget);
        groupBoxPosition->setObjectName(QString::fromUtf8("groupBoxPosition"));
        horizontalLayout_6 = new QHBoxLayout(groupBoxPosition);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lineEditNodeXPosition = new QtExt::ValidatingLineEdit(groupBoxPosition);
        lineEditNodeXPosition->setObjectName(QString::fromUtf8("lineEditNodeXPosition"));

        horizontalLayout_6->addWidget(lineEditNodeXPosition);

        lineEditNodeYPosition = new QtExt::ValidatingLineEdit(groupBoxPosition);
        lineEditNodeYPosition->setObjectName(QString::fromUtf8("lineEditNodeYPosition"));

        horizontalLayout_6->addWidget(lineEditNodeYPosition);

        lineEditNodeZPosition = new QtExt::ValidatingLineEdit(groupBoxPosition);
        lineEditNodeZPosition->setObjectName(QString::fromUtf8("lineEditNodeZPosition"));

        horizontalLayout_6->addWidget(lineEditNodeZPosition);


        verticalLayout->addWidget(groupBoxPosition);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        frameMixer = new QFrame(SVPropNetworkNodesWidget);
        frameMixer->setObjectName(QString::fromUtf8("frameMixer"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameMixer->sizePolicy().hasHeightForWidth());
        frameMixer->setSizePolicy(sizePolicy);
        frameMixer->setMinimumSize(QSize(24, 24));
        frameMixer->setAutoFillBackground(true);
        frameMixer->setFrameShape(QFrame::StyledPanel);
        frameMixer->setFrameShadow(QFrame::Raised);

        gridLayout_12->addWidget(frameMixer, 1, 0, 1, 1);

        frameSubStation = new QFrame(SVPropNetworkNodesWidget);
        frameSubStation->setObjectName(QString::fromUtf8("frameSubStation"));
        sizePolicy.setHeightForWidth(frameSubStation->sizePolicy().hasHeightForWidth());
        frameSubStation->setSizePolicy(sizePolicy);
        frameSubStation->setMinimumSize(QSize(24, 24));
        frameSubStation->setAutoFillBackground(true);
        frameSubStation->setFrameShape(QFrame::StyledPanel);
        frameSubStation->setFrameShadow(QFrame::Raised);

        gridLayout_12->addWidget(frameSubStation, 2, 0, 1, 1);

        label_24 = new QLabel(SVPropNetworkNodesWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_12->addWidget(label_24, 1, 1, 1, 1);

        label_25 = new QLabel(SVPropNetworkNodesWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_12->addWidget(label_25, 2, 1, 1, 1);

        label_26 = new QLabel(SVPropNetworkNodesWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_12->addWidget(label_26, 0, 1, 1, 1);

        frameSource = new QFrame(SVPropNetworkNodesWidget);
        frameSource->setObjectName(QString::fromUtf8("frameSource"));
        sizePolicy.setHeightForWidth(frameSource->sizePolicy().hasHeightForWidth());
        frameSource->setSizePolicy(sizePolicy);
        frameSource->setMinimumSize(QSize(24, 24));
        frameSource->setAutoFillBackground(true);
        frameSource->setFrameShape(QFrame::StyledPanel);
        frameSource->setFrameShadow(QFrame::Raised);

        gridLayout_12->addWidget(frameSource, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_12);

        verticalSpacer_2 = new QSpacerItem(20, 333, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(SVPropNetworkNodesWidget);

        QMetaObject::connectSlotsByName(SVPropNetworkNodesWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropNetworkNodesWidget)
    {
        SVPropNetworkNodesWidget->setWindowTitle(QCoreApplication::translate("SVPropNetworkNodesWidget", "Form", nullptr));
        groupBoxEditNode->setTitle(QCoreApplication::translate("SVPropNetworkNodesWidget", "Edit Node", nullptr));
        label_19->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Type:", nullptr));
        label_20->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Node id:", nullptr));
        label_21->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Name:", nullptr));
        label_23->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Installed power (maximum load):", nullptr));
#if QT_CONFIG(tooltip)
        lineEditNodeMaximumHeatingDemand->setToolTip(QCoreApplication::translate("SVPropNetworkNodesWidget", "This is the maximum power of this sub station, used for pipe dimensioning", nullptr));
#endif // QT_CONFIG(tooltip)
        label_27->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "kW", nullptr));
        groupBoxPosition->setTitle(QCoreApplication::translate("SVPropNetworkNodesWidget", "Position", nullptr));
        label_24->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Mixer", nullptr));
        label_25->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Sub Station", nullptr));
        label_26->setText(QCoreApplication::translate("SVPropNetworkNodesWidget", "Source", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropNetworkNodesWidget: public Ui_SVPropNetworkNodesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKNODESWIDGET_H
