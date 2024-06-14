/********************************************************************************
** Form generated from reading UI file 'SVNetworkDialogSelectPipes.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKDIALOGSELECTPIPES_H
#define UI_SVNETWORKDIALOGSELECTPIPES_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVNetworkDialogSelectPipes
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidgetDatabase;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonRemove;
    QSpacerItem *verticalSpacer;
    QTableWidget *tableWidgetNetwork;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVNetworkDialogSelectPipes)
    {
        if (SVNetworkDialogSelectPipes->objectName().isEmpty())
            SVNetworkDialogSelectPipes->setObjectName(QString::fromUtf8("SVNetworkDialogSelectPipes"));
        SVNetworkDialogSelectPipes->resize(717, 596);
        verticalLayout_2 = new QVBoxLayout(SVNetworkDialogSelectPipes);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidgetDatabase = new QTableWidget(SVNetworkDialogSelectPipes);
        tableWidgetDatabase->setObjectName(QString::fromUtf8("tableWidgetDatabase"));

        horizontalLayout->addWidget(tableWidgetDatabase);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonAdd = new QPushButton(SVNetworkDialogSelectPipes);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAdd->setIcon(icon);

        verticalLayout->addWidget(pushButtonAdd);

        pushButtonRemove = new QPushButton(SVNetworkDialogSelectPipes);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemove->setIcon(icon1);

        verticalLayout->addWidget(pushButtonRemove);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        tableWidgetNetwork = new QTableWidget(SVNetworkDialogSelectPipes);
        tableWidgetNetwork->setObjectName(QString::fromUtf8("tableWidgetNetwork"));

        horizontalLayout->addWidget(tableWidgetNetwork);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SVNetworkDialogSelectPipes);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SVNetworkDialogSelectPipes);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVNetworkDialogSelectPipes, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVNetworkDialogSelectPipes, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVNetworkDialogSelectPipes);
    } // setupUi

    void retranslateUi(QDialog *SVNetworkDialogSelectPipes)
    {
        SVNetworkDialogSelectPipes->setWindowTitle(QCoreApplication::translate("SVNetworkDialogSelectPipes", "Select Pipes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkDialogSelectPipes: public Ui_SVNetworkDialogSelectPipes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKDIALOGSELECTPIPES_H
