/********************************************************************************
** Form generated from reading UI file 'SVLogFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVLOGFILEDIALOG_H
#define UI_SVLOGFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "SVLogWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVLogFileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelOpenFileError;
    SVLogWidget *logWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVLogFileDialog)
    {
        if (SVLogFileDialog->objectName().isEmpty())
            SVLogFileDialog->setObjectName(QString::fromUtf8("SVLogFileDialog"));
        SVLogFileDialog->resize(480, 383);
        verticalLayout = new QVBoxLayout(SVLogFileDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelOpenFileError = new QLabel(SVLogFileDialog);
        labelOpenFileError->setObjectName(QString::fromUtf8("labelOpenFileError"));
        labelOpenFileError->setWordWrap(true);

        verticalLayout->addWidget(labelOpenFileError);

        logWidget = new SVLogWidget(SVLogFileDialog);
        logWidget->setObjectName(QString::fromUtf8("logWidget"));

        verticalLayout->addWidget(logWidget);

        buttonBox = new QDialogButtonBox(SVLogFileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(1, 1);

        retranslateUi(SVLogFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVLogFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVLogFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVLogFileDialog);
    } // setupUi

    void retranslateUi(QDialog *SVLogFileDialog)
    {
        SVLogFileDialog->setWindowTitle(QCoreApplication::translate("SVLogFileDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVLogFileDialog: public Ui_SVLogFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVLOGFILEDIALOG_H
