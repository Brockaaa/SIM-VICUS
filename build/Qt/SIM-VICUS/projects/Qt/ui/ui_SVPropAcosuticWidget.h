/********************************************************************************
** Form generated from reading UI file 'SVPropAcosuticWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPACOSUTICWIDGET_H
#define UI_SVPROPACOSUTICWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ToolBox.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropAcosuticWidget
{
public:
    QVBoxLayout *verticalLayout;
    QtExt::ToolBox *toolBox;

    void setupUi(QWidget *SVPropAcosuticWidget)
    {
        if (SVPropAcosuticWidget->objectName().isEmpty())
            SVPropAcosuticWidget->setObjectName(QString::fromUtf8("SVPropAcosuticWidget"));
        SVPropAcosuticWidget->resize(400, 715);
        verticalLayout = new QVBoxLayout(SVPropAcosuticWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QtExt::ToolBox(SVPropAcosuticWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(SVPropAcosuticWidget);

        QMetaObject::connectSlotsByName(SVPropAcosuticWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropAcosuticWidget)
    {
        SVPropAcosuticWidget->setWindowTitle(QCoreApplication::translate("SVPropAcosuticWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropAcosuticWidget: public Ui_SVPropAcosuticWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPACOSUTICWIDGET_H
