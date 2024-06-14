/********************************************************************************
** Form generated from reading UI file 'SVDBDuplicatesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBDUPLICATESDIALOG_H
#define UI_SVDBDUPLICATESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVDBDuplicatesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTextEdit *textEditLeft;
    QTextEdit *textEditRight;
    QPushButton *pushButtonTakeLeft;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonTakeRight;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVDBDuplicatesDialog)
    {
        if (SVDBDuplicatesDialog->objectName().isEmpty())
            SVDBDuplicatesDialog->setObjectName(QString::fromUtf8("SVDBDuplicatesDialog"));
        SVDBDuplicatesDialog->resize(1186, 791);
        verticalLayout = new QVBoxLayout(SVDBDuplicatesDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(SVDBDuplicatesDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        groupBox = new QGroupBox(SVDBDuplicatesDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEditLeft = new QTextEdit(groupBox);
        textEditLeft->setObjectName(QString::fromUtf8("textEditLeft"));

        gridLayout->addWidget(textEditLeft, 0, 0, 1, 2);

        textEditRight = new QTextEdit(groupBox);
        textEditRight->setObjectName(QString::fromUtf8("textEditRight"));

        gridLayout->addWidget(textEditRight, 0, 2, 1, 2);

        pushButtonTakeLeft = new QPushButton(groupBox);
        pushButtonTakeLeft->setObjectName(QString::fromUtf8("pushButtonTakeLeft"));

        gridLayout->addWidget(pushButtonTakeLeft, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(320, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(320, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        pushButtonTakeRight = new QPushButton(groupBox);
        pushButtonTakeRight->setObjectName(QString::fromUtf8("pushButtonTakeRight"));

        gridLayout->addWidget(pushButtonTakeRight, 1, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(SVDBDuplicatesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SVDBDuplicatesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVDBDuplicatesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVDBDuplicatesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVDBDuplicatesDialog);
    } // setupUi

    void retranslateUi(QDialog *SVDBDuplicatesDialog)
    {
        SVDBDuplicatesDialog->setWindowTitle(QCoreApplication::translate("SVDBDuplicatesDialog", "Remove duplicate elements from database", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBDuplicatesDialog", "Differences", nullptr));
        textEditLeft->setHtml(QCoreApplication::translate("SVDBDuplicatesDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButtonTakeLeft->setText(QCoreApplication::translate("SVDBDuplicatesDialog", "Keep left", nullptr));
        pushButtonTakeRight->setText(QCoreApplication::translate("SVDBDuplicatesDialog", "Keep right", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBDuplicatesDialog: public Ui_SVDBDuplicatesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBDUPLICATESDIALOG_H
