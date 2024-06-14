/********************************************************************************
** Form generated from reading UI file 'QtExt_MaterialDatabaseSelectionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_MATERIALDATABASESELECTIONWIDGET_H
#define UI_QTEXT_MATERIALDATABASESELECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace QtExt {

class Ui_MaterialDatabaseSelectionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEditProducerFilter;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditMaterialNameFilter;
    QLabel *labelProducerFilterCaption;
    QComboBox *comboBoxCategories;
    QLineEdit *lineEditSourceFilter;
    QLineEdit *lineEditCommentFilter;
    QLabel *label_4;
    QLabel *label_5;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSelectedMaterialCaption;
    QLabel *labelSelectedMaterial;
    QLabel *label_3;
    QTextEdit *textEditAdditional;

    void setupUi(QWidget *QtExt__MaterialDatabaseSelectionWidget)
    {
        if (QtExt__MaterialDatabaseSelectionWidget->objectName().isEmpty())
            QtExt__MaterialDatabaseSelectionWidget->setObjectName(QString::fromUtf8("QtExt__MaterialDatabaseSelectionWidget"));
        QtExt__MaterialDatabaseSelectionWidget->resize(1042, 570);
        verticalLayout = new QVBoxLayout(QtExt__MaterialDatabaseSelectionWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditProducerFilter = new QLineEdit(QtExt__MaterialDatabaseSelectionWidget);
        lineEditProducerFilter->setObjectName(QString::fromUtf8("lineEditProducerFilter"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditProducerFilter->sizePolicy().hasHeightForWidth());
        lineEditProducerFilter->setSizePolicy(sizePolicy);
        lineEditProducerFilter->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(lineEditProducerFilter, 1, 3, 1, 1);

        label = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditMaterialNameFilter = new QLineEdit(QtExt__MaterialDatabaseSelectionWidget);
        lineEditMaterialNameFilter->setObjectName(QString::fromUtf8("lineEditMaterialNameFilter"));
        sizePolicy.setHeightForWidth(lineEditMaterialNameFilter->sizePolicy().hasHeightForWidth());
        lineEditMaterialNameFilter->setSizePolicy(sizePolicy);
        lineEditMaterialNameFilter->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(lineEditMaterialNameFilter, 1, 1, 1, 1);

        labelProducerFilterCaption = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        labelProducerFilterCaption->setObjectName(QString::fromUtf8("labelProducerFilterCaption"));

        gridLayout->addWidget(labelProducerFilterCaption, 1, 2, 1, 1);

        comboBoxCategories = new QComboBox(QtExt__MaterialDatabaseSelectionWidget);
        comboBoxCategories->setObjectName(QString::fromUtf8("comboBoxCategories"));
        sizePolicy.setHeightForWidth(comboBoxCategories->sizePolicy().hasHeightForWidth());
        comboBoxCategories->setSizePolicy(sizePolicy);
        comboBoxCategories->setMinimumSize(QSize(250, 0));

        gridLayout->addWidget(comboBoxCategories, 0, 1, 1, 3);

        lineEditSourceFilter = new QLineEdit(QtExt__MaterialDatabaseSelectionWidget);
        lineEditSourceFilter->setObjectName(QString::fromUtf8("lineEditSourceFilter"));

        gridLayout->addWidget(lineEditSourceFilter, 2, 1, 1, 1);

        lineEditCommentFilter = new QLineEdit(QtExt__MaterialDatabaseSelectionWidget);
        lineEditCommentFilter->setObjectName(QString::fromUtf8("lineEditCommentFilter"));

        gridLayout->addWidget(lineEditCommentFilter, 2, 3, 1, 1);

        label_4 = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tableView = new QTableView(QtExt__MaterialDatabaseSelectionWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(4);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSelectedMaterialCaption = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        labelSelectedMaterialCaption->setObjectName(QString::fromUtf8("labelSelectedMaterialCaption"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        labelSelectedMaterialCaption->setFont(font);

        horizontalLayout->addWidget(labelSelectedMaterialCaption);

        labelSelectedMaterial = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        labelSelectedMaterial->setObjectName(QString::fromUtf8("labelSelectedMaterial"));
        labelSelectedMaterial->setFont(font);

        horizontalLayout->addWidget(labelSelectedMaterial);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        label_3 = new QLabel(QtExt__MaterialDatabaseSelectionWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setTextFormat(Qt::PlainText);
        label_3->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(label_3);

        textEditAdditional = new QTextEdit(QtExt__MaterialDatabaseSelectionWidget);
        textEditAdditional->setObjectName(QString::fromUtf8("textEditAdditional"));
        textEditAdditional->setMaximumSize(QSize(16777215, 100));
        textEditAdditional->setReadOnly(true);
        textEditAdditional->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(textEditAdditional);


        retranslateUi(QtExt__MaterialDatabaseSelectionWidget);

        QMetaObject::connectSlotsByName(QtExt__MaterialDatabaseSelectionWidget);
    } // setupUi

    void retranslateUi(QWidget *QtExt__MaterialDatabaseSelectionWidget)
    {
        QtExt__MaterialDatabaseSelectionWidget->setWindowTitle(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Category Filter", nullptr));
        label_2->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Material Name Filter", nullptr));
        labelProducerFilterCaption->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Producer Filter", nullptr));
        label_4->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Data source filter", nullptr));
        label_5->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Comment filter", nullptr));
        labelSelectedMaterialCaption->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Selected Material:", nullptr));
        labelSelectedMaterial->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Nothing", nullptr));
        label_3->setText(QCoreApplication::translate("QtExt::MaterialDatabaseSelectionWidget", "Remarks", nullptr));
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class MaterialDatabaseSelectionWidget: public Ui_MaterialDatabaseSelectionWidget {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_MATERIALDATABASESELECTIONWIDGET_H
