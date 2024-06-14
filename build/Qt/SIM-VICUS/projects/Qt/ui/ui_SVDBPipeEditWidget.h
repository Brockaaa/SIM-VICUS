/********************************************************************************
** Form generated from reading UI file 'SVDBPipeEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBPIPEEDITWIDGET_H
#define UI_SVDBPIPEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBPipeEditWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_9;
    QtExt::ColorButton *pushButtonColor;
    QLabel *label_5;
    QtExt::ValidatingLineEdit *lineEditWallDensity;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_13;
    QtExt::ValidatingLineEdit *lineEditWallThickness;
    QLabel *label_11;
    QLabel *label_16;
    QtExt::LanguageStringEditWidget1 *lineEditCategory;
    QLabel *label_3;
    QLabel *label_15;
    QLabel *label_14;
    QtExt::ValidatingLineEdit *lineEditInsulationThickness;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QtExt::ValidatingLineEdit *lineEditWallRoughness;
    QtExt::ValidatingLineEdit *lineEditWallLambda;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLineEdit *lineEditUValue;
    QtExt::ValidatingLineEdit *lineEditInsulationLambda;
    QLabel *label_4;
    QtExt::ValidatingLineEdit *lineEditOuterDiameter;
    QLabel *label_17;
    QtExt::ValidatingLineEdit *lineEditWallHeatCapacity;
    QLabel *label_18;
    QLabel *label_19;

    void setupUi(QWidget *SVDBPipeEditWidget)
    {
        if (SVDBPipeEditWidget->objectName().isEmpty())
            SVDBPipeEditWidget->setObjectName(QString::fromUtf8("SVDBPipeEditWidget"));
        SVDBPipeEditWidget->resize(864, 450);
        gridLayout = new QGridLayout(SVDBPipeEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(SVDBPipeEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 3, 1, 1);

        label_9 = new QLabel(SVDBPipeEditWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBPipeEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButtonColor, 0, 3, 1, 1);

        label_5 = new QLabel(SVDBPipeEditWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        lineEditWallDensity = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditWallDensity->setObjectName(QString::fromUtf8("lineEditWallDensity"));

        gridLayout->addWidget(lineEditWallDensity, 6, 2, 1, 1);

        label_6 = new QLabel(SVDBPipeEditWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 3, 1, 1);

        label_8 = new QLabel(SVDBPipeEditWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 4, 3, 1, 1);

        label_7 = new QLabel(SVDBPipeEditWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_13 = new QLabel(SVDBPipeEditWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 1, 0, 1, 1);

        lineEditWallThickness = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditWallThickness->setObjectName(QString::fromUtf8("lineEditWallThickness"));

        gridLayout->addWidget(lineEditWallThickness, 3, 2, 1, 1);

        label_11 = new QLabel(SVDBPipeEditWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 9, 0, 1, 1);

        label_16 = new QLabel(SVDBPipeEditWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 6, 0, 1, 1);

        lineEditCategory = new QtExt::LanguageStringEditWidget1(SVDBPipeEditWidget);
        lineEditCategory->setObjectName(QString::fromUtf8("lineEditCategory"));

        gridLayout->addWidget(lineEditCategory, 1, 2, 1, 1);

        label_3 = new QLabel(SVDBPipeEditWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 2);

        label_15 = new QLabel(SVDBPipeEditWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 10, 3, 1, 1);

        label_14 = new QLabel(SVDBPipeEditWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 10, 0, 1, 1);

        lineEditInsulationThickness = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditInsulationThickness->setObjectName(QString::fromUtf8("lineEditInsulationThickness"));

        gridLayout->addWidget(lineEditInsulationThickness, 8, 2, 1, 1);

        label = new QLabel(SVDBPipeEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 11, 2, 1, 1);

        lineEditWallRoughness = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditWallRoughness->setObjectName(QString::fromUtf8("lineEditWallRoughness"));

        gridLayout->addWidget(lineEditWallRoughness, 4, 2, 1, 1);

        lineEditWallLambda = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditWallLambda->setObjectName(QString::fromUtf8("lineEditWallLambda"));

        gridLayout->addWidget(lineEditWallLambda, 5, 2, 1, 1);

        label_10 = new QLabel(SVDBPipeEditWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 8, 3, 1, 1);

        label_12 = new QLabel(SVDBPipeEditWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 9, 3, 1, 1);

        labelDisplayName = new QLabel(SVDBPipeEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBPipeEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(lineEditName, 0, 2, 1, 1);

        lineEditUValue = new QLineEdit(SVDBPipeEditWidget);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));
        lineEditUValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditUValue->setReadOnly(true);

        gridLayout->addWidget(lineEditUValue, 10, 2, 1, 1);

        lineEditInsulationLambda = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditInsulationLambda->setObjectName(QString::fromUtf8("lineEditInsulationLambda"));
        lineEditInsulationLambda->setReadOnly(false);

        gridLayout->addWidget(lineEditInsulationLambda, 9, 2, 1, 1);

        label_4 = new QLabel(SVDBPipeEditWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 3, 1, 1);

        lineEditOuterDiameter = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditOuterDiameter->setObjectName(QString::fromUtf8("lineEditOuterDiameter"));

        gridLayout->addWidget(lineEditOuterDiameter, 2, 2, 1, 1);

        label_17 = new QLabel(SVDBPipeEditWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 7, 0, 1, 1);

        lineEditWallHeatCapacity = new QtExt::ValidatingLineEdit(SVDBPipeEditWidget);
        lineEditWallHeatCapacity->setObjectName(QString::fromUtf8("lineEditWallHeatCapacity"));

        gridLayout->addWidget(lineEditWallHeatCapacity, 7, 2, 1, 1);

        label_18 = new QLabel(SVDBPipeEditWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 6, 3, 1, 1);

        label_19 = new QLabel(SVDBPipeEditWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 7, 3, 1, 1);

        QWidget::setTabOrder(lineEditName, lineEditCategory);
        QWidget::setTabOrder(lineEditCategory, lineEditOuterDiameter);
        QWidget::setTabOrder(lineEditOuterDiameter, lineEditWallThickness);
        QWidget::setTabOrder(lineEditWallThickness, lineEditWallRoughness);
        QWidget::setTabOrder(lineEditWallRoughness, lineEditWallLambda);
        QWidget::setTabOrder(lineEditWallLambda, lineEditWallDensity);
        QWidget::setTabOrder(lineEditWallDensity, lineEditWallHeatCapacity);
        QWidget::setTabOrder(lineEditWallHeatCapacity, lineEditInsulationThickness);
        QWidget::setTabOrder(lineEditInsulationThickness, lineEditInsulationLambda);
        QWidget::setTabOrder(lineEditInsulationLambda, lineEditUValue);
        QWidget::setTabOrder(lineEditUValue, pushButtonColor);

        retranslateUi(SVDBPipeEditWidget);

        QMetaObject::connectSlotsByName(SVDBPipeEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBPipeEditWidget)
    {
        SVDBPipeEditWidget->setWindowTitle(QCoreApplication::translate("SVDBPipeEditWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBPipeEditWidget", "mm", nullptr));
        label_9->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Insulation thickness:", nullptr));
        label_5->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Wall thermal conductivity:", nullptr));
        label_6->setText(QCoreApplication::translate("SVDBPipeEditWidget", "W/mK", nullptr));
        label_8->setText(QCoreApplication::translate("SVDBPipeEditWidget", "mm", nullptr));
        label_7->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Wall roughness:", nullptr));
        label_13->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Category:", nullptr));
        label_11->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Insulation thermal conductivity:", nullptr));
        label_16->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Wall density:", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Wall thickness:", nullptr));
        label_15->setText(QCoreApplication::translate("SVDBPipeEditWidget", "W/mK", nullptr));
        label_14->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Effective conductivity per m pipe length:", nullptr));
        label->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Outer diameter:", nullptr));
        label_10->setText(QCoreApplication::translate("SVDBPipeEditWidget", "mm", nullptr));
        label_12->setText(QCoreApplication::translate("SVDBPipeEditWidget", "W/mK", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Name:", nullptr));
        label_4->setText(QCoreApplication::translate("SVDBPipeEditWidget", "mm", nullptr));
        label_17->setText(QCoreApplication::translate("SVDBPipeEditWidget", "Wall specific heat capacity:", nullptr));
        label_18->setText(QCoreApplication::translate("SVDBPipeEditWidget", "kg/m\302\263", nullptr));
        label_19->setText(QCoreApplication::translate("SVDBPipeEditWidget", "J/kgK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBPipeEditWidget: public Ui_SVDBPipeEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBPIPEEDITWIDGET_H
