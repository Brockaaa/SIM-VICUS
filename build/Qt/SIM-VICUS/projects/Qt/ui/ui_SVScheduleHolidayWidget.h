/********************************************************************************
** Form generated from reading UI file 'SVScheduleHolidayWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSCHEDULEHOLIDAYWIDGET_H
#define UI_SVSCHEDULEHOLIDAYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVScheduleHolidayWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonAdd;
    QToolButton *toolButtonRemove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SVScheduleHolidayWidget)
    {
        if (SVScheduleHolidayWidget->objectName().isEmpty())
            SVScheduleHolidayWidget->setObjectName(QString::fromUtf8("SVScheduleHolidayWidget"));
        SVScheduleHolidayWidget->resize(327, 492);
        verticalLayout = new QVBoxLayout(SVScheduleHolidayWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(SVScheduleHolidayWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableView = new QTableView(SVScheduleHolidayWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButtonAdd = new QToolButton(SVScheduleHolidayWidget);
        toolButtonAdd->setObjectName(QString::fromUtf8("toolButtonAdd"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAdd->setIcon(icon);
        toolButtonAdd->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonAdd);

        toolButtonRemove = new QToolButton(SVScheduleHolidayWidget);
        toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemove->setIcon(icon1);
        toolButtonRemove->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonRemove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SVScheduleHolidayWidget);

        QMetaObject::connectSlotsByName(SVScheduleHolidayWidget);
    } // setupUi

    void retranslateUi(QWidget *SVScheduleHolidayWidget)
    {
        SVScheduleHolidayWidget->setWindowTitle(QCoreApplication::translate("SVScheduleHolidayWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("SVScheduleHolidayWidget", "Definition of Holidays", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVScheduleHolidayWidget: public Ui_SVScheduleHolidayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSCHEDULEHOLIDAYWIDGET_H
