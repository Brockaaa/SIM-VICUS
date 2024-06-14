/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGEDITWIDGET_H
#define UI_SVPROPBUILDINGEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ToolBox.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QtExt::ToolBox *toolBox;

    void setupUi(QWidget *SVPropBuildingEditWidget)
    {
        if (SVPropBuildingEditWidget->objectName().isEmpty())
            SVPropBuildingEditWidget->setObjectName(QString::fromUtf8("SVPropBuildingEditWidget"));
        SVPropBuildingEditWidget->resize(469, 730);
        verticalLayout = new QVBoxLayout(SVPropBuildingEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QtExt::ToolBox(SVPropBuildingEditWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(SVPropBuildingEditWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingEditWidget)
    {
        (void)SVPropBuildingEditWidget;
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingEditWidget: public Ui_SVPropBuildingEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGEDITWIDGET_H
