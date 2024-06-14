/********************************************************************************
** Form generated from reading UI file 'SVDrawingPropertiesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDRAWINGPROPERTIESDIALOG_H
#define UI_SVDRAWINGPROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SVDrawingPropertiesDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEditX;
    QLabel *label_4;
    QLineEdit *lineEditY;
    QLabel *label_5;
    QLineEdit *lineEditZ;
    QLabel *label;
    QLineEdit *lineEditScalingFactor;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_6;
    QLineEdit *lineEditLineWeightScaling;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVDrawingPropertiesDialog)
    {
        if (SVDrawingPropertiesDialog->objectName().isEmpty())
            SVDrawingPropertiesDialog->setObjectName(QString::fromUtf8("SVDrawingPropertiesDialog"));
        SVDrawingPropertiesDialog->resize(492, 180);
        formLayout = new QFormLayout(SVDrawingPropertiesDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(SVDrawingPropertiesDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(SVDrawingPropertiesDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEditX = new QLineEdit(SVDrawingPropertiesDialog);
        lineEditX->setObjectName(QString::fromUtf8("lineEditX"));

        horizontalLayout->addWidget(lineEditX);

        label_4 = new QLabel(SVDrawingPropertiesDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        lineEditY = new QLineEdit(SVDrawingPropertiesDialog);
        lineEditY->setObjectName(QString::fromUtf8("lineEditY"));

        horizontalLayout->addWidget(lineEditY);

        label_5 = new QLabel(SVDrawingPropertiesDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        lineEditZ = new QLineEdit(SVDrawingPropertiesDialog);
        lineEditZ->setObjectName(QString::fromUtf8("lineEditZ"));

        horizontalLayout->addWidget(lineEditZ);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        label = new QLabel(SVDrawingPropertiesDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        lineEditScalingFactor = new QLineEdit(SVDrawingPropertiesDialog);
        lineEditScalingFactor->setObjectName(QString::fromUtf8("lineEditScalingFactor"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditScalingFactor);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(2, QFormLayout::FieldRole, verticalSpacer_2);

        label_6 = new QLabel(SVDrawingPropertiesDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        lineEditLineWeightScaling = new QLineEdit(SVDrawingPropertiesDialog);
        lineEditLineWeightScaling->setObjectName(QString::fromUtf8("lineEditLineWeightScaling"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditLineWeightScaling);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::FieldRole, verticalSpacer);

        buttonBox = new QDialogButtonBox(SVDrawingPropertiesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(5, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(SVDrawingPropertiesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVDrawingPropertiesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVDrawingPropertiesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVDrawingPropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *SVDrawingPropertiesDialog)
    {
        SVDrawingPropertiesDialog->setWindowTitle(QCoreApplication::translate("SVDrawingPropertiesDialog", "Drawing properties", nullptr));
        label_2->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "Offset:", nullptr));
        label_3->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "x", nullptr));
        label_4->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "y", nullptr));
        label_5->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "z", nullptr));
        label->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "Scaling factor: ", nullptr));
        label_6->setText(QCoreApplication::translate("SVDrawingPropertiesDialog", "Line weight scaling:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDrawingPropertiesDialog: public Ui_SVDrawingPropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDRAWINGPROPERTIESDIALOG_H
