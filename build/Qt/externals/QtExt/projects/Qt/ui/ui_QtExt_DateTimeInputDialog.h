/********************************************************************************
** Form generated from reading UI file 'QtExt_DateTimeInputDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_DATETIMEINPUTDIALOG_H
#define UI_QTEXT_DATETIMEINPUTDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DateTimeInputDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QDateEdit *dateEdit;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *DateTimeInputDialog)
    {
        if (DateTimeInputDialog->objectName().isEmpty())
            DateTimeInputDialog->setObjectName(QString::fromUtf8("DateTimeInputDialog"));
        DateTimeInputDialog->resize(276, 81);
        gridLayout = new QGridLayout(DateTimeInputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        dateEdit = new QDateEdit(DateTimeInputDialog);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setMaximumDate(QDate(2021, 12, 31));
        dateEdit->setMinimumDate(QDate(2021, 1, 1));

        gridLayout->addWidget(dateEdit, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DateTimeInputDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);

        label = new QLabel(DateTimeInputDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(DateTimeInputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DateTimeInputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DateTimeInputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DateTimeInputDialog);
    } // setupUi

    void retranslateUi(QDialog *DateTimeInputDialog)
    {
        DateTimeInputDialog->setWindowTitle(QCoreApplication::translate("DateTimeInputDialog", "Dialog", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("DateTimeInputDialog", "dd.MM.", nullptr));
        label->setText(QCoreApplication::translate("DateTimeInputDialog", "label", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DateTimeInputDialog: public Ui_DateTimeInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEXT_DATETIMEINPUTDIALOG_H
