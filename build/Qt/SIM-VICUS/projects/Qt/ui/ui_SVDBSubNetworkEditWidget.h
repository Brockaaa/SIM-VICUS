/********************************************************************************
** Form generated from reading UI file 'SVDBSubNetworkEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSUBNETWORKEDITWIDGET_H
#define UI_SVDBSUBNETWORKEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_SubNetworkHoverToSelect.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBSubNetworkEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QtExt::LanguageStringEditWidget1 *lineEditSubNetworkName;
    QtExt::ColorButton *pushButtonColor;
    QHBoxLayout *horizontalLayout_2;
    QFrame *previewFrame;
    QtExt_SubNetworkHoverToSelect *widgetHoverToSelect;
    QPushButton *editSubNetworkButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBSubNetworkEditWidget)
    {
        if (SVDBSubNetworkEditWidget->objectName().isEmpty())
            SVDBSubNetworkEditWidget->setObjectName(QString::fromUtf8("SVDBSubNetworkEditWidget"));
        SVDBSubNetworkEditWidget->resize(853, 840);
        verticalLayout = new QVBoxLayout(SVDBSubNetworkEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditSubNetworkName = new QtExt::LanguageStringEditWidget1(SVDBSubNetworkEditWidget);
        lineEditSubNetworkName->setObjectName(QString::fromUtf8("lineEditSubNetworkName"));

        horizontalLayout->addWidget(lineEditSubNetworkName);

        pushButtonColor = new QtExt::ColorButton(SVDBSubNetworkEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));

        horizontalLayout->addWidget(pushButtonColor);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);

        previewFrame = new QFrame(SVDBSubNetworkEditWidget);
        previewFrame->setObjectName(QString::fromUtf8("previewFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(previewFrame->sizePolicy().hasHeightForWidth());
        previewFrame->setSizePolicy(sizePolicy);
        previewFrame->setMinimumSize(QSize(835, 500));
        previewFrame->setMaximumSize(QSize(835, 500));
        previewFrame->setAutoFillBackground(true);
        previewFrame->setLineWidth(0);
        widgetHoverToSelect = new QtExt_SubNetworkHoverToSelect(previewFrame);
        widgetHoverToSelect->setObjectName(QString::fromUtf8("widgetHoverToSelect"));
        widgetHoverToSelect->setGeometry(QRect(0, 0, 835, 500));
        widgetHoverToSelect->setMinimumSize(QSize(835, 500));
        widgetHoverToSelect->setMaximumSize(QSize(835, 500));

        verticalLayout->addWidget(previewFrame);

        editSubNetworkButton = new QPushButton(SVDBSubNetworkEditWidget);
        editSubNetworkButton->setObjectName(QString::fromUtf8("editSubNetworkButton"));

        verticalLayout->addWidget(editSubNetworkButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(3, 1);

        retranslateUi(SVDBSubNetworkEditWidget);

        QMetaObject::connectSlotsByName(SVDBSubNetworkEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBSubNetworkEditWidget)
    {
        SVDBSubNetworkEditWidget->setWindowTitle(QCoreApplication::translate("SVDBSubNetworkEditWidget", "Form", nullptr));
        pushButtonColor->setText(QCoreApplication::translate("SVDBSubNetworkEditWidget", "...", nullptr));
        editSubNetworkButton->setText(QCoreApplication::translate("SVDBSubNetworkEditWidget", "Edit Sub Network", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBSubNetworkEditWidget: public Ui_SVDBSubNetworkEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSUBNETWORKEDITWIDGET_H
