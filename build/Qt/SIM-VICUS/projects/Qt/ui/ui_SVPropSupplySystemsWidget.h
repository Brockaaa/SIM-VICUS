/********************************************************************************
** Form generated from reading UI file 'SVPropSupplySystemsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPSUPPLYSYSTEMSWIDGET_H
#define UI_SVPROPSUPPLYSYSTEMSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropSupplySystemsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetSupplySystems;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonEditSupplySystem;
    QPushButton *pushButtonExchangeSupplySystem;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonSelectSupplySystem;
    QFrame *line;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *labelSelectedSupplySystem;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonAssignSupplySystem;
    QPushButton *pushButtonRemoveSupplySystem;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *SVPropSupplySystemsWidget)
    {
        if (SVPropSupplySystemsWidget->objectName().isEmpty())
            SVPropSupplySystemsWidget->setObjectName(QString::fromUtf8("SVPropSupplySystemsWidget"));
        SVPropSupplySystemsWidget->resize(551, 819);
        verticalLayout = new QVBoxLayout(SVPropSupplySystemsWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidgetSupplySystems = new QTableWidget(SVPropSupplySystemsWidget);
        tableWidgetSupplySystems->setObjectName(QString::fromUtf8("tableWidgetSupplySystems"));

        verticalLayout->addWidget(tableWidgetSupplySystems);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonEditSupplySystem = new QPushButton(SVPropSupplySystemsWidget);
        pushButtonEditSupplySystem->setObjectName(QString::fromUtf8("pushButtonEditSupplySystem"));
        pushButtonEditSupplySystem->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonEditSupplySystem);

        pushButtonExchangeSupplySystem = new QPushButton(SVPropSupplySystemsWidget);
        pushButtonExchangeSupplySystem->setObjectName(QString::fromUtf8("pushButtonExchangeSupplySystem"));
        pushButtonExchangeSupplySystem->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonExchangeSupplySystem);

        horizontalSpacer_4 = new QSpacerItem(267, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        pushButtonSelectSupplySystem = new QPushButton(SVPropSupplySystemsWidget);
        pushButtonSelectSupplySystem->setObjectName(QString::fromUtf8("pushButtonSelectSupplySystem"));
        pushButtonSelectSupplySystem->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonSelectSupplySystem);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(SVPropSupplySystemsWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_2 = new QLabel(SVPropSupplySystemsWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(SVPropSupplySystemsWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        labelSelectedSupplySystem = new QLabel(SVPropSupplySystemsWidget);
        labelSelectedSupplySystem->setObjectName(QString::fromUtf8("labelSelectedSupplySystem"));

        horizontalLayout_2->addWidget(labelSelectedSupplySystem);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonAssignSupplySystem = new QPushButton(SVPropSupplySystemsWidget);
        pushButtonAssignSupplySystem->setObjectName(QString::fromUtf8("pushButtonAssignSupplySystem"));
        pushButtonAssignSupplySystem->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonAssignSupplySystem);

        pushButtonRemoveSupplySystem = new QPushButton(SVPropSupplySystemsWidget);
        pushButtonRemoveSupplySystem->setObjectName(QString::fromUtf8("pushButtonRemoveSupplySystem"));
        pushButtonRemoveSupplySystem->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(pushButtonRemoveSupplySystem);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(SVPropSupplySystemsWidget);

        QMetaObject::connectSlotsByName(SVPropSupplySystemsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropSupplySystemsWidget)
    {
        SVPropSupplySystemsWidget->setWindowTitle(QCoreApplication::translate("SVPropSupplySystemsWidget", "Form", nullptr));
        pushButtonEditSupplySystem->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Edit...", nullptr));
        pushButtonExchangeSupplySystem->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Exchange...", nullptr));
        pushButtonSelectSupplySystem->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Select...", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Selected supply system(s):", nullptr));
        label->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Selected Supply System:", nullptr));
        labelSelectedSupplySystem->setText(QString());
        pushButtonAssignSupplySystem->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Assign...", nullptr));
        pushButtonRemoveSupplySystem->setText(QCoreApplication::translate("SVPropSupplySystemsWidget", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropSupplySystemsWidget: public Ui_SVPropSupplySystemsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPSUPPLYSYSTEMSWIDGET_H
