/********************************************************************************
** Form generated from reading UI file 'SVDBAcousticSoundAbsorptionEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBACOUSTICSOUNDABSORPTIONEDITWIDGET_H
#define UI_SVDBACOUSTICSOUNDABSORPTIONEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBAcousticSoundAbsorptionEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QTableWidget *tableWidgetSoundAbsorptions;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBAcousticSoundAbsorptionEditWidget)
    {
        if (SVDBAcousticSoundAbsorptionEditWidget->objectName().isEmpty())
            SVDBAcousticSoundAbsorptionEditWidget->setObjectName(QString::fromUtf8("SVDBAcousticSoundAbsorptionEditWidget"));
        SVDBAcousticSoundAbsorptionEditWidget->resize(659, 1020);
        verticalLayout = new QVBoxLayout(SVDBAcousticSoundAbsorptionEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDisplayName = new QLabel(SVDBAcousticSoundAbsorptionEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(labelDisplayName);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBAcousticSoundAbsorptionEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout->addWidget(lineEditName);

        pushButtonColor = new QtExt::ColorButton(SVDBAcousticSoundAbsorptionEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);
        pushButtonColor->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(pushButtonColor);


        verticalLayout->addLayout(horizontalLayout);

        tableWidgetSoundAbsorptions = new QTableWidget(SVDBAcousticSoundAbsorptionEditWidget);
        tableWidgetSoundAbsorptions->setObjectName(QString::fromUtf8("tableWidgetSoundAbsorptions"));

        verticalLayout->addWidget(tableWidgetSoundAbsorptions);

        verticalSpacer = new QSpacerItem(20, 151, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SVDBAcousticSoundAbsorptionEditWidget);

        QMetaObject::connectSlotsByName(SVDBAcousticSoundAbsorptionEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBAcousticSoundAbsorptionEditWidget)
    {
        SVDBAcousticSoundAbsorptionEditWidget->setWindowTitle(QCoreApplication::translate("SVDBAcousticSoundAbsorptionEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBAcousticSoundAbsorptionEditWidget", "Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBAcousticSoundAbsorptionEditWidget: public Ui_SVDBAcousticSoundAbsorptionEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBACOUSTICSOUNDABSORPTIONEDITWIDGET_H
