/********************************************************************************
** Form generated from reading UI file 'SVStructuralUnitCreationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSTRUCTURALUNITCREATIONDIALOG_H
#define UI_SVSTRUCTURALUNITCREATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVStructuralUnitCreationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditUnitName;
    QtExt::ColorButton *pushButtonColor;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBoxCreateUnit;

    void setupUi(QDialog *SVStructuralUnitCreationDialog)
    {
        if (SVStructuralUnitCreationDialog->objectName().isEmpty())
            SVStructuralUnitCreationDialog->setObjectName(QString::fromUtf8("SVStructuralUnitCreationDialog"));
        SVStructuralUnitCreationDialog->resize(445, 154);
        verticalLayout = new QVBoxLayout(SVStructuralUnitCreationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(SVStructuralUnitCreationDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditUnitName = new QLineEdit(SVStructuralUnitCreationDialog);
        lineEditUnitName->setObjectName(QString::fromUtf8("lineEditUnitName"));

        horizontalLayout_2->addWidget(lineEditUnitName);

        pushButtonColor = new QtExt::ColorButton(SVStructuralUnitCreationDialog);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));

        horizontalLayout_2->addWidget(pushButtonColor);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBoxCreateUnit = new QDialogButtonBox(SVStructuralUnitCreationDialog);
        buttonBoxCreateUnit->setObjectName(QString::fromUtf8("buttonBoxCreateUnit"));
        buttonBoxCreateUnit->setOrientation(Qt::Horizontal);
        buttonBoxCreateUnit->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBoxCreateUnit);


        retranslateUi(SVStructuralUnitCreationDialog);
        QObject::connect(buttonBoxCreateUnit, SIGNAL(accepted()), SVStructuralUnitCreationDialog, SLOT(accept()));
        QObject::connect(buttonBoxCreateUnit, SIGNAL(rejected()), SVStructuralUnitCreationDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVStructuralUnitCreationDialog);
    } // setupUi

    void retranslateUi(QDialog *SVStructuralUnitCreationDialog)
    {
        SVStructuralUnitCreationDialog->setWindowTitle(QCoreApplication::translate("SVStructuralUnitCreationDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SVStructuralUnitCreationDialog", "Name:", nullptr));
        pushButtonColor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SVStructuralUnitCreationDialog: public Ui_SVStructuralUnitCreationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSTRUCTURALUNITCREATIONDIALOG_H
