/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingComponentOrientationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGCOMPONENTORIENTATIONWIDGET_H
#define UI_SVPROPBUILDINGCOMPONENTORIENTATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingComponentOrientationWidget
{
public:
    QGridLayout *gridLayout;
    QCheckBox *checkBoxShowAllComponentOrientations;
    QLabel *labelComponentSelection;
    QComboBox *comboBoxComponentSelection;
    QGridLayout *gridLayout_4;
    QFrame *frameSideA;
    QLabel *label_2;
    QFrame *frameSideB;
    QLabel *label_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *labelComponentOrientationInfo;
    QPushButton *pushButtonAlignComponentToSideA;
    QPushButton *pushButtonAlignComponentToSideB;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVPropBuildingComponentOrientationWidget)
    {
        if (SVPropBuildingComponentOrientationWidget->objectName().isEmpty())
            SVPropBuildingComponentOrientationWidget->setObjectName(QString::fromUtf8("SVPropBuildingComponentOrientationWidget"));
        SVPropBuildingComponentOrientationWidget->resize(579, 511);
        gridLayout = new QGridLayout(SVPropBuildingComponentOrientationWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBoxShowAllComponentOrientations = new QCheckBox(SVPropBuildingComponentOrientationWidget);
        checkBoxShowAllComponentOrientations->setObjectName(QString::fromUtf8("checkBoxShowAllComponentOrientations"));
        checkBoxShowAllComponentOrientations->setChecked(true);

        gridLayout->addWidget(checkBoxShowAllComponentOrientations, 0, 0, 1, 2);

        labelComponentSelection = new QLabel(SVPropBuildingComponentOrientationWidget);
        labelComponentSelection->setObjectName(QString::fromUtf8("labelComponentSelection"));

        gridLayout->addWidget(labelComponentSelection, 1, 0, 1, 1);

        comboBoxComponentSelection = new QComboBox(SVPropBuildingComponentOrientationWidget);
        comboBoxComponentSelection->setObjectName(QString::fromUtf8("comboBoxComponentSelection"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxComponentSelection->sizePolicy().hasHeightForWidth());
        comboBoxComponentSelection->setSizePolicy(sizePolicy);

        gridLayout->addWidget(comboBoxComponentSelection, 1, 1, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frameSideA = new QFrame(SVPropBuildingComponentOrientationWidget);
        frameSideA->setObjectName(QString::fromUtf8("frameSideA"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameSideA->sizePolicy().hasHeightForWidth());
        frameSideA->setSizePolicy(sizePolicy1);
        frameSideA->setMinimumSize(QSize(24, 24));
        frameSideA->setAutoFillBackground(true);
        frameSideA->setFrameShape(QFrame::Box);
        frameSideA->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frameSideA, 0, 0, 1, 1);

        label_2 = new QLabel(SVPropBuildingComponentOrientationWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 1, 1, 1);

        frameSideB = new QFrame(SVPropBuildingComponentOrientationWidget);
        frameSideB->setObjectName(QString::fromUtf8("frameSideB"));
        sizePolicy1.setHeightForWidth(frameSideB->sizePolicy().hasHeightForWidth());
        frameSideB->setSizePolicy(sizePolicy1);
        frameSideB->setMinimumSize(QSize(24, 24));
        frameSideB->setAutoFillBackground(true);
        frameSideB->setFrameShape(QFrame::StyledPanel);
        frameSideB->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(frameSideB, 1, 0, 1, 1);

        label_3 = new QLabel(SVPropBuildingComponentOrientationWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_4, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(SVPropBuildingComponentOrientationWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelComponentOrientationInfo = new QLabel(groupBox_4);
        labelComponentOrientationInfo->setObjectName(QString::fromUtf8("labelComponentOrientationInfo"));

        gridLayout_3->addWidget(labelComponentOrientationInfo, 0, 0, 1, 3);

        pushButtonAlignComponentToSideA = new QPushButton(groupBox_4);
        pushButtonAlignComponentToSideA->setObjectName(QString::fromUtf8("pushButtonAlignComponentToSideA"));

        gridLayout_3->addWidget(pushButtonAlignComponentToSideA, 1, 0, 1, 1);

        pushButtonAlignComponentToSideB = new QPushButton(groupBox_4);
        pushButtonAlignComponentToSideB->setObjectName(QString::fromUtf8("pushButtonAlignComponentToSideB"));

        gridLayout_3->addWidget(pushButtonAlignComponentToSideB, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(339, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox_4, 3, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 226, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);


        retranslateUi(SVPropBuildingComponentOrientationWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingComponentOrientationWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingComponentOrientationWidget)
    {
        SVPropBuildingComponentOrientationWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Form", nullptr));
        checkBoxShowAllComponentOrientations->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Show all components", nullptr));
        labelComponentSelection->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Component:", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Side A", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Side B", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Selected components", nullptr));
        labelComponentOrientationInfo->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "No surfaces with components selected", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAlignComponentToSideA->setToolTip(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Component will be aligned so that side A of the component corresponds to the selected surface.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAlignComponentToSideA->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Align to side A", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAlignComponentToSideB->setToolTip(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Component will be aligned so that side B of the component corresponds to the selected surface.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAlignComponentToSideB->setText(QCoreApplication::translate("SVPropBuildingComponentOrientationWidget", "Align to side B", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingComponentOrientationWidget: public Ui_SVPropBuildingComponentOrientationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGCOMPONENTORIENTATIONWIDGET_H
