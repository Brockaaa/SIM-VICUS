/********************************************************************************
** Form generated from reading UI file 'SVSubNetworkEditDialogTableItem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSUBNETWORKEDITDIALOGTABLEITEM_H
#define UI_SVSUBNETWORKEDITDIALOGTABLEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSubNetworkEditDialogTableItem
{
public:

    void setupUi(QWidget *SVSubNetworkEditDialogTableItem)
    {
        if (SVSubNetworkEditDialogTableItem->objectName().isEmpty())
            SVSubNetworkEditDialogTableItem->setObjectName(QString::fromUtf8("SVSubNetworkEditDialogTableItem"));
        SVSubNetworkEditDialogTableItem->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVSubNetworkEditDialogTableItem->sizePolicy().hasHeightForWidth());
        SVSubNetworkEditDialogTableItem->setSizePolicy(sizePolicy);

        retranslateUi(SVSubNetworkEditDialogTableItem);

        QMetaObject::connectSlotsByName(SVSubNetworkEditDialogTableItem);
    } // setupUi

    void retranslateUi(QWidget *SVSubNetworkEditDialogTableItem)
    {
        SVSubNetworkEditDialogTableItem->setWindowTitle(QCoreApplication::translate("SVSubNetworkEditDialogTableItem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSubNetworkEditDialogTableItem: public Ui_SVSubNetworkEditDialogTableItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSUBNETWORKEDITDIALOGTABLEITEM_H
