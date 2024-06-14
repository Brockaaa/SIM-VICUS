/********************************************************************************
** Form generated from reading UI file 'SVImportIDFDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVIMPORTIDFDIALOG_H
#define UI_SVIMPORTIDFDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVImportIDFDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBoxEncoding;
    QPushButton *pushButtonImport;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonReplace;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonMerge;

    void setupUi(QDialog *SVImportIDFDialog)
    {
        if (SVImportIDFDialog->objectName().isEmpty())
            SVImportIDFDialog->setObjectName(QString::fromUtf8("SVImportIDFDialog"));
        SVImportIDFDialog->resize(1051, 593);
        verticalLayout_2 = new QVBoxLayout(SVImportIDFDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(SVImportIDFDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxEncoding = new QComboBox(groupBox);
        comboBoxEncoding->setObjectName(QString::fromUtf8("comboBoxEncoding"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxEncoding->sizePolicy().hasHeightForWidth());
        comboBoxEncoding->setSizePolicy(sizePolicy);

        gridLayout->addWidget(comboBoxEncoding, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        pushButtonImport = new QPushButton(SVImportIDFDialog);
        pushButtonImport->setObjectName(QString::fromUtf8("pushButtonImport"));

        verticalLayout_2->addWidget(pushButtonImport);

        groupBox_2 = new QGroupBox(SVImportIDFDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonReplace = new QPushButton(SVImportIDFDialog);
        pushButtonReplace->setObjectName(QString::fromUtf8("pushButtonReplace"));

        horizontalLayout->addWidget(pushButtonReplace);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonMerge = new QPushButton(SVImportIDFDialog);
        pushButtonMerge->setObjectName(QString::fromUtf8("pushButtonMerge"));

        horizontalLayout->addWidget(pushButtonMerge);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(SVImportIDFDialog);

        QMetaObject::connectSlotsByName(SVImportIDFDialog);
    } // setupUi

    void retranslateUi(QDialog *SVImportIDFDialog)
    {
        SVImportIDFDialog->setWindowTitle(QCoreApplication::translate("SVImportIDFDialog", "Import EneryPlus IDF", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVImportIDFDialog", "Import settings", nullptr));
        label->setText(QCoreApplication::translate("SVImportIDFDialog", "Text encoding:", nullptr));
        pushButtonImport->setText(QCoreApplication::translate("SVImportIDFDialog", "Import IDF", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVImportIDFDialog", "Import log", nullptr));
        pushButtonReplace->setText(QCoreApplication::translate("SVImportIDFDialog", "Import as new project", nullptr));
        pushButtonMerge->setText(QCoreApplication::translate("SVImportIDFDialog", "Merge with existing project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVImportIDFDialog: public Ui_SVImportIDFDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVIMPORTIDFDIALOG_H
