/********************************************************************************
** Form generated from reading UI file 'SVPropNetworkEdgesWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPNETWORKEDGESWIDGET_H
#define UI_SVPROPNETWORKEDGESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropNetworkEdgesWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxEdge;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLabel *label_22;
    QLineEdit *lineEditEdgeDisplayName;
    QLabel *labelPipeLength;
    QCheckBox *checkBoxSupplyPipe;
    QGroupBox *groupBoxCurrentPipes;
    QGridLayout *gridLayout_5;
    QPushButton *pushButtonExchangePipe;
    QPushButton *pushButtonSelectEdgesWithPipe;
    QTableWidget *tableWidgetPipes;
    QPushButton *pushButtonEditPipe;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxSelectedPipe;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QPushButton *pushButtonAssignPipe;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelSelectedPipe;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVPropNetworkEdgesWidget)
    {
        if (SVPropNetworkEdgesWidget->objectName().isEmpty())
            SVPropNetworkEdgesWidget->setObjectName(QString::fromUtf8("SVPropNetworkEdgesWidget"));
        SVPropNetworkEdgesWidget->resize(797, 633);
        verticalLayout = new QVBoxLayout(SVPropNetworkEdgesWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxEdge = new QGroupBox(SVPropNetworkEdgesWidget);
        groupBoxEdge->setObjectName(QString::fromUtf8("groupBoxEdge"));
        gridLayout = new QGridLayout(groupBoxEdge);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_11 = new QLabel(groupBoxEdge);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        label_22 = new QLabel(groupBoxEdge);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout->addWidget(label_22, 0, 0, 1, 1);

        lineEditEdgeDisplayName = new QLineEdit(groupBoxEdge);
        lineEditEdgeDisplayName->setObjectName(QString::fromUtf8("lineEditEdgeDisplayName"));

        gridLayout->addWidget(lineEditEdgeDisplayName, 0, 1, 1, 1);

        labelPipeLength = new QLabel(groupBoxEdge);
        labelPipeLength->setObjectName(QString::fromUtf8("labelPipeLength"));

        gridLayout->addWidget(labelPipeLength, 2, 1, 1, 1);

        checkBoxSupplyPipe = new QCheckBox(groupBoxEdge);
        checkBoxSupplyPipe->setObjectName(QString::fromUtf8("checkBoxSupplyPipe"));

        gridLayout->addWidget(checkBoxSupplyPipe, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBoxEdge);

        groupBoxCurrentPipes = new QGroupBox(SVPropNetworkEdgesWidget);
        groupBoxCurrentPipes->setObjectName(QString::fromUtf8("groupBoxCurrentPipes"));
        gridLayout_5 = new QGridLayout(groupBoxCurrentPipes);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButtonExchangePipe = new QPushButton(groupBoxCurrentPipes);
        pushButtonExchangePipe->setObjectName(QString::fromUtf8("pushButtonExchangePipe"));
        pushButtonExchangePipe->setIconSize(QSize(24, 24));

        gridLayout_5->addWidget(pushButtonExchangePipe, 1, 1, 1, 1);

        pushButtonSelectEdgesWithPipe = new QPushButton(groupBoxCurrentPipes);
        pushButtonSelectEdgesWithPipe->setObjectName(QString::fromUtf8("pushButtonSelectEdgesWithPipe"));
        pushButtonSelectEdgesWithPipe->setIconSize(QSize(24, 24));

        gridLayout_5->addWidget(pushButtonSelectEdgesWithPipe, 1, 3, 1, 1);

        tableWidgetPipes = new QTableWidget(groupBoxCurrentPipes);
        tableWidgetPipes->setObjectName(QString::fromUtf8("tableWidgetPipes"));

        gridLayout_5->addWidget(tableWidgetPipes, 0, 0, 1, 5);

        pushButtonEditPipe = new QPushButton(groupBoxCurrentPipes);
        pushButtonEditPipe->setObjectName(QString::fromUtf8("pushButtonEditPipe"));
        pushButtonEditPipe->setIconSize(QSize(24, 24));

        gridLayout_5->addWidget(pushButtonEditPipe, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(280, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBoxCurrentPipes);

        groupBoxSelectedPipe = new QGroupBox(SVPropNetworkEdgesWidget);
        groupBoxSelectedPipe->setObjectName(QString::fromUtf8("groupBoxSelectedPipe"));
        gridLayout_4 = new QGridLayout(groupBoxSelectedPipe);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBoxSelectedPipe);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        pushButtonAssignPipe = new QPushButton(groupBoxSelectedPipe);
        pushButtonAssignPipe->setObjectName(QString::fromUtf8("pushButtonAssignPipe"));
        pushButtonAssignPipe->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonAssignPipe);

        horizontalSpacer_2 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout_3, 1, 0, 1, 2);

        labelSelectedPipe = new QLabel(groupBoxSelectedPipe);
        labelSelectedPipe->setObjectName(QString::fromUtf8("labelSelectedPipe"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedPipe->sizePolicy().hasHeightForWidth());
        labelSelectedPipe->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(labelSelectedPipe, 0, 1, 1, 1);

        label_6 = new QLabel(groupBoxSelectedPipe);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxSelectedPipe);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(SVPropNetworkEdgesWidget);

        QMetaObject::connectSlotsByName(SVPropNetworkEdgesWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropNetworkEdgesWidget)
    {
        SVPropNetworkEdgesWidget->setWindowTitle(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Form", nullptr));
        groupBoxEdge->setTitle(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Edit Pipeline", nullptr));
        label_11->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Length", nullptr));
        label_22->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Name:", nullptr));
        labelPipeLength->setText(QString());
        checkBoxSupplyPipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "supply pipe", nullptr));
        groupBoxCurrentPipes->setTitle(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Pipes used in current project", nullptr));
        pushButtonExchangePipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Exchange...", nullptr));
        pushButtonSelectEdgesWithPipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Select", nullptr));
        pushButtonEditPipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Edit...", nullptr));
        groupBoxSelectedPipe->setTitle(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Selected Pipe", nullptr));
        label->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Assign pipe:", nullptr));
        pushButtonAssignPipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "DB...", nullptr));
        labelSelectedPipe->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("SVPropNetworkEdgesWidget", "Selected:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropNetworkEdgesWidget: public Ui_SVPropNetworkEdgesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPNETWORKEDGESWIDGET_H
