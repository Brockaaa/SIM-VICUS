/********************************************************************************
** Form generated from reading UI file 'SVDBScheduleDailyCycleEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSCHEDULEDAILYCYCLEEDITWIDGET_H
#define UI_SVDBSCHEDULEDAILYCYCLEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "SVDBDailyCycleInputWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVDBScheduleDailyCycleEditWidget
{
public:
    QGridLayout *gridLayout;
    SVDBDailyCycleInputWidget *dailyCycleInputWidget;
    QTableWidget *tableWidgetDayCycle;
    QLabel *labelEditInfo;

    void setupUi(QWidget *SVDBScheduleDailyCycleEditWidget)
    {
        if (SVDBScheduleDailyCycleEditWidget->objectName().isEmpty())
            SVDBScheduleDailyCycleEditWidget->setObjectName(QString::fromUtf8("SVDBScheduleDailyCycleEditWidget"));
        SVDBScheduleDailyCycleEditWidget->resize(657, 318);
        gridLayout = new QGridLayout(SVDBScheduleDailyCycleEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        dailyCycleInputWidget = new SVDBDailyCycleInputWidget(SVDBScheduleDailyCycleEditWidget);
        dailyCycleInputWidget->setObjectName(QString::fromUtf8("dailyCycleInputWidget"));

        gridLayout->addWidget(dailyCycleInputWidget, 0, 0, 1, 1);

        tableWidgetDayCycle = new QTableWidget(SVDBScheduleDailyCycleEditWidget);
        if (tableWidgetDayCycle->columnCount() < 2)
            tableWidgetDayCycle->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetDayCycle->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetDayCycle->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidgetDayCycle->rowCount() < 1)
            tableWidgetDayCycle->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDayCycle->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDayCycle->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetDayCycle->setItem(0, 1, __qtablewidgetitem4);
        tableWidgetDayCycle->setObjectName(QString::fromUtf8("tableWidgetDayCycle"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetDayCycle->sizePolicy().hasHeightForWidth());
        tableWidgetDayCycle->setSizePolicy(sizePolicy);
        tableWidgetDayCycle->setMaximumSize(QSize(200, 16777215));
        tableWidgetDayCycle->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidgetDayCycle->setSelectionBehavior(QAbstractItemView::SelectItems);
        tableWidgetDayCycle->horizontalHeader()->setStretchLastSection(true);
        tableWidgetDayCycle->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidgetDayCycle, 0, 1, 2, 1);

        labelEditInfo = new QLabel(SVDBScheduleDailyCycleEditWidget);
        labelEditInfo->setObjectName(QString::fromUtf8("labelEditInfo"));
        QFont font;
        font.setItalic(true);
        labelEditInfo->setFont(font);
        labelEditInfo->setWordWrap(true);

        gridLayout->addWidget(labelEditInfo, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        retranslateUi(SVDBScheduleDailyCycleEditWidget);

        QMetaObject::connectSlotsByName(SVDBScheduleDailyCycleEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBScheduleDailyCycleEditWidget)
    {
        SVDBScheduleDailyCycleEditWidget->setWindowTitle(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetDayCycle->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "Zeitraum", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetDayCycle->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "Wert", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDayCycle->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "1", nullptr));

        const bool __sortingEnabled = tableWidgetDayCycle->isSortingEnabled();
        tableWidgetDayCycle->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDayCycle->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "0:00 - 1:00", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetDayCycle->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "3.5", nullptr));
        tableWidgetDayCycle->setSortingEnabled(__sortingEnabled);

        labelEditInfo->setText(QCoreApplication::translate("SVDBScheduleDailyCycleEditWidget", "To edit several values together, select multiple cells in table and type a number followed by enter.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBScheduleDailyCycleEditWidget: public Ui_SVDBScheduleDailyCycleEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSCHEDULEDAILYCYCLEEDITWIDGET_H
