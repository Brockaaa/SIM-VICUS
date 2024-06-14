/********************************************************************************
** Form generated from reading UI file 'SVPropStructuralUnitEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPSTRUCTURALUNITEDITWIDGET_H
#define UI_SVPROPSTRUCTURALUNITEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ToolBox.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropStructuralUnitEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QtExt::ToolBox *toolBox;

    void setupUi(QWidget *SVPropStructuralUnitEditWidget)
    {
        if (SVPropStructuralUnitEditWidget->objectName().isEmpty())
            SVPropStructuralUnitEditWidget->setObjectName(QString::fromUtf8("SVPropStructuralUnitEditWidget"));
        SVPropStructuralUnitEditWidget->resize(438, 747);
        verticalLayout = new QVBoxLayout(SVPropStructuralUnitEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QtExt::ToolBox(SVPropStructuralUnitEditWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(SVPropStructuralUnitEditWidget);

        QMetaObject::connectSlotsByName(SVPropStructuralUnitEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropStructuralUnitEditWidget)
    {
        SVPropStructuralUnitEditWidget->setWindowTitle(QCoreApplication::translate("SVPropStructuralUnitEditWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropStructuralUnitEditWidget: public Ui_SVPropStructuralUnitEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPSTRUCTURALUNITEDITWIDGET_H
