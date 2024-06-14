/********************************************************************************
** Form generated from reading UI file 'SVNotesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNOTESDIALOG_H
#define UI_SVNOTESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVNotesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEditNotes;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SVNotesDialog)
    {
        if (SVNotesDialog->objectName().isEmpty())
            SVNotesDialog->setObjectName(QString::fromUtf8("SVNotesDialog"));
        SVNotesDialog->resize(1402, 907);
        verticalLayout = new QVBoxLayout(SVNotesDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEditNotes = new QPlainTextEdit(SVNotesDialog);
        plainTextEditNotes->setObjectName(QString::fromUtf8("plainTextEditNotes"));

        verticalLayout->addWidget(plainTextEditNotes);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonSave = new QPushButton(SVNotesDialog);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);

        pushButtonCancel = new QPushButton(SVNotesDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SVNotesDialog);

        QMetaObject::connectSlotsByName(SVNotesDialog);
    } // setupUi

    void retranslateUi(QDialog *SVNotesDialog)
    {
        SVNotesDialog->setWindowTitle(QCoreApplication::translate("SVNotesDialog", "Edit project-notes", nullptr));
        plainTextEditNotes->setPlainText(QCoreApplication::translate("SVNotesDialog", "Notizen", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("SVNotesDialog", "Save", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SVNotesDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNotesDialog: public Ui_SVNotesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNOTESDIALOG_H
