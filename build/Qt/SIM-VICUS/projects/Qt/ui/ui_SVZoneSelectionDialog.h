/********************************************************************************
** Form generated from reading UI file 'SVZoneSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVZONESELECTIONDIALOG_H
#define UI_SVZONESELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVZoneSelectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QLineEdit *lineEditFilter;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVZoneSelectionDialog)
    {
        if (SVZoneSelectionDialog->objectName().isEmpty())
            SVZoneSelectionDialog->setObjectName(QString::fromUtf8("SVZoneSelectionDialog"));
        SVZoneSelectionDialog->resize(493, 402);
        verticalLayout = new QVBoxLayout(SVZoneSelectionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listView = new QListView(SVZoneSelectionDialog);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        lineEditFilter = new QLineEdit(SVZoneSelectionDialog);
        lineEditFilter->setObjectName(QString::fromUtf8("lineEditFilter"));

        verticalLayout->addWidget(lineEditFilter);

        buttonBox = new QDialogButtonBox(SVZoneSelectionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SVZoneSelectionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVZoneSelectionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVZoneSelectionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVZoneSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *SVZoneSelectionDialog)
    {
        SVZoneSelectionDialog->setWindowTitle(QCoreApplication::translate("SVZoneSelectionDialog", "Select zone", nullptr));
        lineEditFilter->setPlaceholderText(QCoreApplication::translate("SVZoneSelectionDialog", "Type text to filter zone list", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVZoneSelectionDialog: public Ui_SVZoneSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVZONESELECTIONDIALOG_H
