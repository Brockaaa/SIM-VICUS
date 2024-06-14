/********************************************************************************
** Form generated from reading UI file 'SVDatabaseEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDATABASEEDITDIALOG_H
#define UI_SVDATABASEEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVDatabaseEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxTableView;
    QGridLayout *gridLayoutTableView;
    QToolButton *toolButtonApplyFilter;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frameBuildInDB;
    QLabel *label_2;
    QFrame *frameUserDB;
    QLabel *label_4;
    QFrame *frameProject;
    QLabel *label_3;
    QTableView *tableView;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonRemoveFromUserDB;
    QToolButton *toolButtonAdd;
    QToolButton *toolButtonCopy;
    QToolButton *toolButtonRemove;
    QLineEdit *lineEditFilter;
    QComboBox *comboBoxColumn;
    QToolButton *toolButtonStoreInUserDB;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonReloadUserDB;
    QPushButton *pushButtonRemoveUnusedElements;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SVDatabaseEditDialog)
    {
        if (SVDatabaseEditDialog->objectName().isEmpty())
            SVDatabaseEditDialog->setObjectName(QString::fromUtf8("SVDatabaseEditDialog"));
        SVDatabaseEditDialog->resize(1115, 815);
        verticalLayout = new QVBoxLayout(SVDatabaseEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxTableView = new QGroupBox(SVDatabaseEditDialog);
        groupBoxTableView->setObjectName(QString::fromUtf8("groupBoxTableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxTableView->sizePolicy().hasHeightForWidth());
        groupBoxTableView->setSizePolicy(sizePolicy);
        gridLayoutTableView = new QGridLayout(groupBoxTableView);
        gridLayoutTableView->setObjectName(QString::fromUtf8("gridLayoutTableView"));
        toolButtonApplyFilter = new QToolButton(groupBoxTableView);
        toolButtonApplyFilter->setObjectName(QString::fromUtf8("toolButtonApplyFilter"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonApplyFilter->setIcon(icon);
        toolButtonApplyFilter->setIconSize(QSize(20, 20));

        gridLayoutTableView->addWidget(toolButtonApplyFilter, 3, 9, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        frameBuildInDB = new QFrame(groupBoxTableView);
        frameBuildInDB->setObjectName(QString::fromUtf8("frameBuildInDB"));
        frameBuildInDB->setMinimumSize(QSize(80, 0));
        frameBuildInDB->setFrameShape(QFrame::StyledPanel);
        frameBuildInDB->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frameBuildInDB);

        label_2 = new QLabel(groupBoxTableView);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        frameUserDB = new QFrame(groupBoxTableView);
        frameUserDB->setObjectName(QString::fromUtf8("frameUserDB"));
        frameUserDB->setMinimumSize(QSize(80, 0));
        frameUserDB->setFrameShape(QFrame::StyledPanel);
        frameUserDB->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frameUserDB);

        label_4 = new QLabel(groupBoxTableView);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        frameProject = new QFrame(groupBoxTableView);
        frameProject->setObjectName(QString::fromUtf8("frameProject"));
        frameProject->setMinimumSize(QSize(80, 0));
        frameProject->setFrameShape(QFrame::StyledPanel);
        frameProject->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(frameProject);

        label_3 = new QLabel(groupBoxTableView);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        gridLayoutTableView->addLayout(horizontalLayout_2, 0, 0, 1, 10);

        tableView = new QTableView(groupBoxTableView);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(0, 150));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setVisible(false);

        gridLayoutTableView->addWidget(tableView, 1, 0, 1, 10);

        label = new QLabel(groupBoxTableView);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayoutTableView->addWidget(label, 3, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(1156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutTableView->addItem(horizontalSpacer, 3, 5, 1, 1);

        toolButtonRemoveFromUserDB = new QToolButton(groupBoxTableView);
        toolButtonRemoveFromUserDB->setObjectName(QString::fromUtf8("toolButtonRemoveFromUserDB"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/fromDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveFromUserDB->setIcon(icon1);
        toolButtonRemoveFromUserDB->setIconSize(QSize(24, 24));

        gridLayoutTableView->addWidget(toolButtonRemoveFromUserDB, 3, 4, 1, 1);

        toolButtonAdd = new QToolButton(groupBoxTableView);
        toolButtonAdd->setObjectName(QString::fromUtf8("toolButtonAdd"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAdd->setIcon(icon2);
        toolButtonAdd->setIconSize(QSize(24, 24));

        gridLayoutTableView->addWidget(toolButtonAdd, 3, 0, 1, 1);

        toolButtonCopy = new QToolButton(groupBoxTableView);
        toolButtonCopy->setObjectName(QString::fromUtf8("toolButtonCopy"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/24x24/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonCopy->setIcon(icon3);
        toolButtonCopy->setIconSize(QSize(24, 24));

        gridLayoutTableView->addWidget(toolButtonCopy, 3, 1, 1, 1);

        toolButtonRemove = new QToolButton(groupBoxTableView);
        toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemove->setIcon(icon4);
        toolButtonRemove->setIconSize(QSize(24, 24));

        gridLayoutTableView->addWidget(toolButtonRemove, 3, 2, 1, 1);

        lineEditFilter = new QLineEdit(groupBoxTableView);
        lineEditFilter->setObjectName(QString::fromUtf8("lineEditFilter"));
        lineEditFilter->setMinimumSize(QSize(250, 0));

        gridLayoutTableView->addWidget(lineEditFilter, 3, 8, 1, 1);

        comboBoxColumn = new QComboBox(groupBoxTableView);
        comboBoxColumn->setObjectName(QString::fromUtf8("comboBoxColumn"));
        comboBoxColumn->setMinimumSize(QSize(150, 25));

        gridLayoutTableView->addWidget(comboBoxColumn, 3, 7, 1, 1);

        toolButtonStoreInUserDB = new QToolButton(groupBoxTableView);
        toolButtonStoreInUserDB->setObjectName(QString::fromUtf8("toolButtonStoreInUserDB"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/actions/24x24/toDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonStoreInUserDB->setIcon(icon5);
        toolButtonStoreInUserDB->setIconSize(QSize(24, 24));

        gridLayoutTableView->addWidget(toolButtonStoreInUserDB, 3, 3, 1, 1);


        verticalLayout->addWidget(groupBoxTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonReloadUserDB = new QPushButton(SVDatabaseEditDialog);
        pushButtonReloadUserDB->setObjectName(QString::fromUtf8("pushButtonReloadUserDB"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gfx/actions/24x24/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonReloadUserDB->setIcon(icon6);
        pushButtonReloadUserDB->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonReloadUserDB);

        pushButtonRemoveUnusedElements = new QPushButton(SVDatabaseEditDialog);
        pushButtonRemoveUnusedElements->setObjectName(QString::fromUtf8("pushButtonRemoveUnusedElements"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/gfx/actions/24x24/broom.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemoveUnusedElements->setIcon(icon7);
        pushButtonRemoveUnusedElements->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonRemoveUnusedElements);

        horizontalSpacer_2 = new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonSelect = new QPushButton(SVDatabaseEditDialog);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));
        pushButtonSelect->setAutoDefault(true);

        horizontalLayout->addWidget(pushButtonSelect);

        pushButtonCancel = new QPushButton(SVDatabaseEditDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonClose = new QPushButton(SVDatabaseEditDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SVDatabaseEditDialog);

        QMetaObject::connectSlotsByName(SVDatabaseEditDialog);
    } // setupUi

    void retranslateUi(QDialog *SVDatabaseEditDialog)
    {
        toolButtonApplyFilter->setText(QCoreApplication::translate("SVDatabaseEditDialog", "...", nullptr));
        label_2->setText(QCoreApplication::translate("SVDatabaseEditDialog", "built-in elements", nullptr));
        label_4->setText(QCoreApplication::translate("SVDatabaseEditDialog", "user db elements", nullptr));
        label_3->setText(QCoreApplication::translate("SVDatabaseEditDialog", "project elements", nullptr));
        label->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Filter:", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonRemoveFromUserDB->setToolTip(QCoreApplication::translate("SVDatabaseEditDialog", "Moves DB element from user database to local project.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonRemoveFromUserDB->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonStoreInUserDB->setToolTip(QCoreApplication::translate("SVDatabaseEditDialog", "Stores local project DB element in user database.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonStoreInUserDB->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonReloadUserDB->setToolTip(QCoreApplication::translate("SVDatabaseEditDialog", "Reloads user database from directory", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonReloadUserDB->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Reload user database", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonRemoveUnusedElements->setToolTip(QCoreApplication::translate("SVDatabaseEditDialog", "Removes project-local database elements that are currently nowhere referenced.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonRemoveUnusedElements->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Remove unused local elements", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Cancel", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SVDatabaseEditDialog", "Close", nullptr));
        (void)SVDatabaseEditDialog;
    } // retranslateUi

};

namespace Ui {
    class SVDatabaseEditDialog: public Ui_SVDatabaseEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDATABASEEDITDIALOG_H
