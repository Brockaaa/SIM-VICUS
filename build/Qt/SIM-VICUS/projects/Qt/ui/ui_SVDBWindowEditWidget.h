/********************************************************************************
** Form generated from reading UI file 'SVDBWindowEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBWINDOWEDITWIDGET_H
#define UI_SVDBWINDOWEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBWindowEditWidget
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *masterLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelUValue;
    QLineEdit *lineEditUValue;
    QLabel *labelUValue_2;
    QLabel *labelSHGC;
    QLineEdit *lineEditSHGC;
    QLabel *labelSHGCUnit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditGlazingSystemName;
    QToolButton *toolButtonSelectGlazingSystemName;
    QwtPlot *shgcPlot;
    QGroupBox *groupBoxFrame;
    QGridLayout *gridLayout_4;
    QLabel *labelFrameInput_2;
    QtExt::ValidatingLineEdit *lineEditFrameInput;
    QLabel *labelFrameInputUnit;
    QComboBox *comboBoxFrameMethod;
    QToolButton *toolButtonSelectFrameMaterial;
    QLabel *labelFrameMaterial;
    QLineEdit *lineEditFrameMaterialName;
    QtExt::ValidatingLineEdit *lineEditFrameMaterialThickness;
    QLabel *label;
    QLabel *labelFrameInputUnit_2;
    QLabel *labelFrameInput;
    QGroupBox *groupBoxFrame_2;
    QGridLayout *gridLayout_3;
    QtExt::ValidatingLineEdit *lineEditDividerMaterialThickness;
    QLabel *labelDividerInput2;
    QLabel *labelDividerInputUnit;
    QLabel *label_2;
    QLineEdit *lineEditDividerMaterialName;
    QLabel *labelDividerInputUnit_3;
    QComboBox *comboBoxDividerMethod;
    QtExt::ValidatingLineEdit *lineEditDividerInput;
    QToolButton *toolButtonSelectDividerMaterial;
    QLabel *labelDividerMaterial;
    QLabel *labelDividerInput;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBWindowEditWidget)
    {
        if (SVDBWindowEditWidget->objectName().isEmpty())
            SVDBWindowEditWidget->setObjectName(QString::fromUtf8("SVDBWindowEditWidget"));
        SVDBWindowEditWidget->resize(477, 955);
        gridLayout_5 = new QGridLayout(SVDBWindowEditWidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        masterLayout = new QGridLayout();
        masterLayout->setObjectName(QString::fromUtf8("masterLayout"));
        labelDisplayName = new QLabel(SVDBWindowEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        masterLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBWindowEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setReadOnly(false);

        masterLayout->addWidget(lineEditName, 0, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBWindowEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        masterLayout->addWidget(pushButtonColor, 0, 2, 1, 1);

        labelUValue = new QLabel(SVDBWindowEditWidget);
        labelUValue->setObjectName(QString::fromUtf8("labelUValue"));

        masterLayout->addWidget(labelUValue, 1, 0, 1, 1);

        lineEditUValue = new QLineEdit(SVDBWindowEditWidget);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));
        lineEditUValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditUValue->setReadOnly(true);

        masterLayout->addWidget(lineEditUValue, 1, 1, 1, 1);

        labelUValue_2 = new QLabel(SVDBWindowEditWidget);
        labelUValue_2->setObjectName(QString::fromUtf8("labelUValue_2"));

        masterLayout->addWidget(labelUValue_2, 1, 2, 1, 1);

        labelSHGC = new QLabel(SVDBWindowEditWidget);
        labelSHGC->setObjectName(QString::fromUtf8("labelSHGC"));

        masterLayout->addWidget(labelSHGC, 2, 0, 1, 1);

        lineEditSHGC = new QLineEdit(SVDBWindowEditWidget);
        lineEditSHGC->setObjectName(QString::fromUtf8("lineEditSHGC"));
        lineEditSHGC->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditSHGC->setReadOnly(true);

        masterLayout->addWidget(lineEditSHGC, 2, 1, 1, 1);

        labelSHGCUnit = new QLabel(SVDBWindowEditWidget);
        labelSHGCUnit->setObjectName(QString::fromUtf8("labelSHGCUnit"));

        masterLayout->addWidget(labelSHGCUnit, 2, 2, 1, 1);


        gridLayout_5->addLayout(masterLayout, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(SVDBWindowEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditGlazingSystemName = new QLineEdit(groupBox_2);
        lineEditGlazingSystemName->setObjectName(QString::fromUtf8("lineEditGlazingSystemName"));
        lineEditGlazingSystemName->setReadOnly(true);

        gridLayout_2->addWidget(lineEditGlazingSystemName, 0, 0, 1, 1);

        toolButtonSelectGlazingSystemName = new QToolButton(groupBox_2);
        toolButtonSelectGlazingSystemName->setObjectName(QString::fromUtf8("toolButtonSelectGlazingSystemName"));

        gridLayout_2->addWidget(toolButtonSelectGlazingSystemName, 0, 1, 1, 1);

        shgcPlot = new QwtPlot(groupBox_2);
        shgcPlot->setObjectName(QString::fromUtf8("shgcPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(shgcPlot->sizePolicy().hasHeightForWidth());
        shgcPlot->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(shgcPlot, 1, 0, 1, 2);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBoxFrame = new QGroupBox(SVDBWindowEditWidget);
        groupBoxFrame->setObjectName(QString::fromUtf8("groupBoxFrame"));
        gridLayout_4 = new QGridLayout(groupBoxFrame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        labelFrameInput_2 = new QLabel(groupBoxFrame);
        labelFrameInput_2->setObjectName(QString::fromUtf8("labelFrameInput_2"));

        gridLayout_4->addWidget(labelFrameInput_2, 3, 0, 1, 1);

        lineEditFrameInput = new QtExt::ValidatingLineEdit(groupBoxFrame);
        lineEditFrameInput->setObjectName(QString::fromUtf8("lineEditFrameInput"));

        gridLayout_4->addWidget(lineEditFrameInput, 1, 1, 1, 1);

        labelFrameInputUnit = new QLabel(groupBoxFrame);
        labelFrameInputUnit->setObjectName(QString::fromUtf8("labelFrameInputUnit"));

        gridLayout_4->addWidget(labelFrameInputUnit, 1, 2, 1, 1);

        comboBoxFrameMethod = new QComboBox(groupBoxFrame);
        comboBoxFrameMethod->setObjectName(QString::fromUtf8("comboBoxFrameMethod"));

        gridLayout_4->addWidget(comboBoxFrameMethod, 0, 1, 1, 2);

        toolButtonSelectFrameMaterial = new QToolButton(groupBoxFrame);
        toolButtonSelectFrameMaterial->setObjectName(QString::fromUtf8("toolButtonSelectFrameMaterial"));

        gridLayout_4->addWidget(toolButtonSelectFrameMaterial, 2, 2, 1, 1);

        labelFrameMaterial = new QLabel(groupBoxFrame);
        labelFrameMaterial->setObjectName(QString::fromUtf8("labelFrameMaterial"));

        gridLayout_4->addWidget(labelFrameMaterial, 2, 0, 1, 1);

        lineEditFrameMaterialName = new QLineEdit(groupBoxFrame);
        lineEditFrameMaterialName->setObjectName(QString::fromUtf8("lineEditFrameMaterialName"));
        lineEditFrameMaterialName->setReadOnly(true);

        gridLayout_4->addWidget(lineEditFrameMaterialName, 2, 1, 1, 1);

        lineEditFrameMaterialThickness = new QtExt::ValidatingLineEdit(groupBoxFrame);
        lineEditFrameMaterialThickness->setObjectName(QString::fromUtf8("lineEditFrameMaterialThickness"));

        gridLayout_4->addWidget(lineEditFrameMaterialThickness, 3, 1, 1, 1);

        label = new QLabel(groupBoxFrame);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        labelFrameInputUnit_2 = new QLabel(groupBoxFrame);
        labelFrameInputUnit_2->setObjectName(QString::fromUtf8("labelFrameInputUnit_2"));

        gridLayout_4->addWidget(labelFrameInputUnit_2, 3, 2, 1, 1);

        labelFrameInput = new QLabel(groupBoxFrame);
        labelFrameInput->setObjectName(QString::fromUtf8("labelFrameInput"));

        gridLayout_4->addWidget(labelFrameInput, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBoxFrame, 2, 0, 1, 1);

        groupBoxFrame_2 = new QGroupBox(SVDBWindowEditWidget);
        groupBoxFrame_2->setObjectName(QString::fromUtf8("groupBoxFrame_2"));
        gridLayout_3 = new QGridLayout(groupBoxFrame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEditDividerMaterialThickness = new QtExt::ValidatingLineEdit(groupBoxFrame_2);
        lineEditDividerMaterialThickness->setObjectName(QString::fromUtf8("lineEditDividerMaterialThickness"));

        gridLayout_3->addWidget(lineEditDividerMaterialThickness, 3, 1, 1, 1);

        labelDividerInput2 = new QLabel(groupBoxFrame_2);
        labelDividerInput2->setObjectName(QString::fromUtf8("labelDividerInput2"));

        gridLayout_3->addWidget(labelDividerInput2, 3, 0, 1, 1);

        labelDividerInputUnit = new QLabel(groupBoxFrame_2);
        labelDividerInputUnit->setObjectName(QString::fromUtf8("labelDividerInputUnit"));

        gridLayout_3->addWidget(labelDividerInputUnit, 1, 2, 1, 1);

        label_2 = new QLabel(groupBoxFrame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        lineEditDividerMaterialName = new QLineEdit(groupBoxFrame_2);
        lineEditDividerMaterialName->setObjectName(QString::fromUtf8("lineEditDividerMaterialName"));
        lineEditDividerMaterialName->setReadOnly(true);

        gridLayout_3->addWidget(lineEditDividerMaterialName, 2, 1, 1, 1);

        labelDividerInputUnit_3 = new QLabel(groupBoxFrame_2);
        labelDividerInputUnit_3->setObjectName(QString::fromUtf8("labelDividerInputUnit_3"));

        gridLayout_3->addWidget(labelDividerInputUnit_3, 3, 2, 1, 1);

        comboBoxDividerMethod = new QComboBox(groupBoxFrame_2);
        comboBoxDividerMethod->setObjectName(QString::fromUtf8("comboBoxDividerMethod"));

        gridLayout_3->addWidget(comboBoxDividerMethod, 0, 1, 1, 2);

        lineEditDividerInput = new QtExt::ValidatingLineEdit(groupBoxFrame_2);
        lineEditDividerInput->setObjectName(QString::fromUtf8("lineEditDividerInput"));

        gridLayout_3->addWidget(lineEditDividerInput, 1, 1, 1, 1);

        toolButtonSelectDividerMaterial = new QToolButton(groupBoxFrame_2);
        toolButtonSelectDividerMaterial->setObjectName(QString::fromUtf8("toolButtonSelectDividerMaterial"));

        gridLayout_3->addWidget(toolButtonSelectDividerMaterial, 2, 2, 1, 1);

        labelDividerMaterial = new QLabel(groupBoxFrame_2);
        labelDividerMaterial->setObjectName(QString::fromUtf8("labelDividerMaterial"));

        gridLayout_3->addWidget(labelDividerMaterial, 2, 0, 1, 1);

        labelDividerInput = new QLabel(groupBoxFrame_2);
        labelDividerInput->setObjectName(QString::fromUtf8("labelDividerInput"));

        gridLayout_3->addWidget(labelDividerInput, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBoxFrame_2, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 155, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 4, 0, 1, 1);


        retranslateUi(SVDBWindowEditWidget);

        QMetaObject::connectSlotsByName(SVDBWindowEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBWindowEditWidget)
    {
        SVDBWindowEditWidget->setWindowTitle(QCoreApplication::translate("SVDBWindowEditWidget", "Window Database", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Name:", nullptr));
        labelUValue->setText(QCoreApplication::translate("SVDBWindowEditWidget", "U-value:", nullptr));
#if QT_CONFIG(tooltip)
        lineEditUValue->setToolTip(QCoreApplication::translate("SVDBWindowEditWidget", "U-value is being calculated using standard exchange coefficients.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelUValue_2->setText(QCoreApplication::translate("SVDBWindowEditWidget", "W/m2K", nullptr));
        labelSHGC->setText(QCoreApplication::translate("SVDBWindowEditWidget", "SHGC:", nullptr));
        labelSHGCUnit->setText(QCoreApplication::translate("SVDBWindowEditWidget", "-", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVDBWindowEditWidget", "GlazingSystem", nullptr));
        toolButtonSelectGlazingSystemName->setText(QCoreApplication::translate("SVDBWindowEditWidget", "...", nullptr));
        groupBoxFrame->setTitle(QCoreApplication::translate("SVDBWindowEditWidget", "Frame", nullptr));
        labelFrameInput_2->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Material Thickness:", nullptr));
        labelFrameInputUnit->setText(QCoreApplication::translate("SVDBWindowEditWidget", "m", nullptr));
        toolButtonSelectFrameMaterial->setText(QCoreApplication::translate("SVDBWindowEditWidget", "...", nullptr));
        labelFrameMaterial->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Material:", nullptr));
        label->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Method:", nullptr));
        labelFrameInputUnit_2->setText(QCoreApplication::translate("SVDBWindowEditWidget", "m", nullptr));
        labelFrameInput->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Width:", nullptr));
        groupBoxFrame_2->setTitle(QCoreApplication::translate("SVDBWindowEditWidget", "Divider", nullptr));
        labelDividerInput2->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Material Thickness:", nullptr));
        labelDividerInputUnit->setText(QCoreApplication::translate("SVDBWindowEditWidget", "m", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Method:", nullptr));
        labelDividerInputUnit_3->setText(QCoreApplication::translate("SVDBWindowEditWidget", "m", nullptr));
        toolButtonSelectDividerMaterial->setText(QCoreApplication::translate("SVDBWindowEditWidget", "...", nullptr));
        labelDividerMaterial->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Material:", nullptr));
        labelDividerInput->setText(QCoreApplication::translate("SVDBWindowEditWidget", "Width:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBWindowEditWidget: public Ui_SVDBWindowEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBWINDOWEDITWIDGET_H
