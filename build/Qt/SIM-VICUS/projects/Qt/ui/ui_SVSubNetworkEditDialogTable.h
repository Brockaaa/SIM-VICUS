/********************************************************************************
** Form generated from reading UI file 'SVSubNetworkEditDialogTable.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSUBNETWORKEDITDIALOGTABLE_H
#define UI_SVSUBNETWORKEDITDIALOGTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSubNetworkEditDialogTable
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *SVSubNetworkEditDialogTable)
    {
        if (SVSubNetworkEditDialogTable->objectName().isEmpty())
            SVSubNetworkEditDialogTable->setObjectName(QString::fromUtf8("SVSubNetworkEditDialogTable"));
        SVSubNetworkEditDialogTable->resize(225, 50);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVSubNetworkEditDialogTable->sizePolicy().hasHeightForWidth());
        SVSubNetworkEditDialogTable->setSizePolicy(sizePolicy);
        SVSubNetworkEditDialogTable->setMinimumSize(QSize(66, 0));
        SVSubNetworkEditDialogTable->setMaximumSize(QSize(600, 50));
        verticalLayout = new QVBoxLayout(SVSubNetworkEditDialogTable);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(SVSubNetworkEditDialogTable);

        QMetaObject::connectSlotsByName(SVSubNetworkEditDialogTable);
    } // setupUi

    void retranslateUi(QWidget *SVSubNetworkEditDialogTable)
    {
        SVSubNetworkEditDialogTable->setWindowTitle(QCoreApplication::translate("SVSubNetworkEditDialogTable", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSubNetworkEditDialogTable: public Ui_SVSubNetworkEditDialogTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSUBNETWORKEDITDIALOGTABLE_H
