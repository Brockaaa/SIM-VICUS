/********************************************************************************
** Form generated from reading UI file 'SVNetworkSimultaneityDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKSIMULTANEITYDIALOG_H
#define UI_SVNETWORKSIMULTANEITYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVNetworkSimultaneityDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QwtPlot *widgetPlot;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonAddPoint;
    QToolButton *toolButtonRemovePoint;
    QToolButton *toolButtonCopyToClipboard;
    QToolButton *toolButtonPasteFromClipboard;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSetDefault;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVNetworkSimultaneityDialog)
    {
        if (SVNetworkSimultaneityDialog->objectName().isEmpty())
            SVNetworkSimultaneityDialog->setObjectName(QString::fromUtf8("SVNetworkSimultaneityDialog"));
        SVNetworkSimultaneityDialog->resize(824, 410);
        verticalLayout = new QVBoxLayout(SVNetworkSimultaneityDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetPlot = new QwtPlot(SVNetworkSimultaneityDialog);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        horizontalLayout->addWidget(widgetPlot);

        tableWidget = new QTableWidget(SVNetworkSimultaneityDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonAddPoint = new QToolButton(SVNetworkSimultaneityDialog);
        toolButtonAddPoint->setObjectName(QString::fromUtf8("toolButtonAddPoint"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddPoint->setIcon(icon);

        verticalLayout_2->addWidget(toolButtonAddPoint);

        toolButtonRemovePoint = new QToolButton(SVNetworkSimultaneityDialog);
        toolButtonRemovePoint->setObjectName(QString::fromUtf8("toolButtonRemovePoint"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemovePoint->setIcon(icon1);

        verticalLayout_2->addWidget(toolButtonRemovePoint);

        toolButtonCopyToClipboard = new QToolButton(SVNetworkSimultaneityDialog);
        toolButtonCopyToClipboard->setObjectName(QString::fromUtf8("toolButtonCopyToClipboard"));

        verticalLayout_2->addWidget(toolButtonCopyToClipboard);

        toolButtonPasteFromClipboard = new QToolButton(SVNetworkSimultaneityDialog);
        toolButtonPasteFromClipboard->setObjectName(QString::fromUtf8("toolButtonPasteFromClipboard"));

        verticalLayout_2->addWidget(toolButtonPasteFromClipboard);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonSetDefault = new QPushButton(SVNetworkSimultaneityDialog);
        pushButtonSetDefault->setObjectName(QString::fromUtf8("pushButtonSetDefault"));

        horizontalLayout_2->addWidget(pushButtonSetDefault);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(SVNetworkSimultaneityDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SVNetworkSimultaneityDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVNetworkSimultaneityDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVNetworkSimultaneityDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVNetworkSimultaneityDialog);
    } // setupUi

    void retranslateUi(QDialog *SVNetworkSimultaneityDialog)
    {
        SVNetworkSimultaneityDialog->setWindowTitle(QCoreApplication::translate("SVNetworkSimultaneityDialog", "Dialog", nullptr));
        toolButtonAddPoint->setText(QCoreApplication::translate("SVNetworkSimultaneityDialog", "...", nullptr));
        toolButtonRemovePoint->setText(QCoreApplication::translate("SVNetworkSimultaneityDialog", "...", nullptr));
        toolButtonCopyToClipboard->setText(QString());
        toolButtonPasteFromClipboard->setText(QString());
        pushButtonSetDefault->setText(QCoreApplication::translate("SVNetworkSimultaneityDialog", "Set default function", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkSimultaneityDialog: public Ui_SVNetworkSimultaneityDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKSIMULTANEITYDIALOG_H
