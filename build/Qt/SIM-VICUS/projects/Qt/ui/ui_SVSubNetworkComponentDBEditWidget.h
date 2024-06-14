/********************************************************************************
** Form generated from reading UI file 'SVSubNetworkComponentDBEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
#define UI_SVSUBNETWORKCOMPONENTDBEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSubNetworkComponentDBEditWidget
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *SVSubNetworkComponentDBEditWidget)
    {
        if (SVSubNetworkComponentDBEditWidget->objectName().isEmpty())
            SVSubNetworkComponentDBEditWidget->setObjectName(QString::fromUtf8("SVSubNetworkComponentDBEditWidget"));
        SVSubNetworkComponentDBEditWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(SVSubNetworkComponentDBEditWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(SVSubNetworkComponentDBEditWidget);

        QMetaObject::connectSlotsByName(SVSubNetworkComponentDBEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVSubNetworkComponentDBEditWidget)
    {
        SVSubNetworkComponentDBEditWidget->setWindowTitle(QCoreApplication::translate("SVSubNetworkComponentDBEditWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSubNetworkComponentDBEditWidget: public Ui_SVSubNetworkComponentDBEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
