/********************************************************************************
** Form generated from reading UI file 'SVLcaLccResultsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVLCALCCRESULTSWIDGET_H
#define UI_SVLCALCCRESULTSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVLcaLccResultsWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPageLCA;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidgetLcaResults;
    QWidget *tabWidgetPageLCC;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidgetLccResults;
    QTableWidget *tableWidgetLccOverview;

    void setupUi(QWidget *SVLcaLccResultsWidget)
    {
        if (SVLcaLccResultsWidget->objectName().isEmpty())
            SVLcaLccResultsWidget->setObjectName(QString::fromUtf8("SVLcaLccResultsWidget"));
        SVLcaLccResultsWidget->resize(1200, 717);
        gridLayout = new QGridLayout(SVLcaLccResultsWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(SVLcaLccResultsWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidgetPageLCA = new QWidget();
        tabWidgetPageLCA->setObjectName(QString::fromUtf8("tabWidgetPageLCA"));
        gridLayout_2 = new QGridLayout(tabWidgetPageLCA);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidgetLcaResults = new QTreeWidget(tabWidgetPageLCA);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetLcaResults->setHeaderItem(__qtreewidgetitem);
        treeWidgetLcaResults->setObjectName(QString::fromUtf8("treeWidgetLcaResults"));

        gridLayout_2->addWidget(treeWidgetLcaResults, 0, 0, 1, 1);

        tabWidget->addTab(tabWidgetPageLCA, QString());
        tabWidgetPageLCC = new QWidget();
        tabWidgetPageLCC->setObjectName(QString::fromUtf8("tabWidgetPageLCC"));
        gridLayout_3 = new QGridLayout(tabWidgetPageLCC);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidgetLccResults = new QTableWidget(tabWidgetPageLCC);
        tableWidgetLccResults->setObjectName(QString::fromUtf8("tableWidgetLccResults"));

        gridLayout_3->addWidget(tableWidgetLccResults, 0, 0, 1, 2);

        tableWidgetLccOverview = new QTableWidget(tabWidgetPageLCC);
        tableWidgetLccOverview->setObjectName(QString::fromUtf8("tableWidgetLccOverview"));
        tableWidgetLccOverview->setMaximumSize(QSize(16777215, 150));

        gridLayout_3->addWidget(tableWidgetLccOverview, 1, 0, 1, 2);

        tabWidget->addTab(tabWidgetPageLCC, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 2);


        retranslateUi(SVLcaLccResultsWidget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SVLcaLccResultsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVLcaLccResultsWidget)
    {
        SVLcaLccResultsWidget->setWindowTitle(QCoreApplication::translate("SVLcaLccResultsWidget", "LCA/LCC Results", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPageLCA), QCoreApplication::translate("SVLcaLccResultsWidget", "Life cycle assessment results", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPageLCC), QCoreApplication::translate("SVLcaLccResultsWidget", "Life cycle cost results", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVLcaLccResultsWidget: public Ui_SVLcaLccResultsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVLCALCCRESULTSWIDGET_H
