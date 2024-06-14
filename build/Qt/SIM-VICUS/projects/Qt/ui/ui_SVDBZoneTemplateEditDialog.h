/********************************************************************************
** Form generated from reading UI file 'SVDBZoneTemplateEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBZONETEMPLATEEDITDIALOG_H
#define UI_SVDBZONETEMPLATEEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_SVDBZoneTemplateEditDialog
{
public:
    QGridLayout *gridLayoutMaster;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QToolButton *toolButtonStoreInUserDB;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonAdd;
    QToolButton *toolButtonRemove;
    QToolButton *toolButtonCopy;
    QToolButton *toolButtonRemoveFromUserDB;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonReloadUserDB;
    QPushButton *pushButtonRemoveUnusedElements;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonSelect;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SVDBZoneTemplateEditDialog)
    {
        if (SVDBZoneTemplateEditDialog->objectName().isEmpty())
            SVDBZoneTemplateEditDialog->setObjectName(QString::fromUtf8("SVDBZoneTemplateEditDialog"));
        SVDBZoneTemplateEditDialog->resize(822, 563);
        gridLayoutMaster = new QGridLayout(SVDBZoneTemplateEditDialog);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        groupBox = new QGroupBox(SVDBZoneTemplateEditDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButtonStoreInUserDB = new QToolButton(groupBox);
        toolButtonStoreInUserDB->setObjectName(QString::fromUtf8("toolButtonStoreInUserDB"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/toDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonStoreInUserDB->setIcon(icon);
        toolButtonStoreInUserDB->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonStoreInUserDB, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(1156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 5, 1, 2);

        toolButtonAdd = new QToolButton(groupBox);
        toolButtonAdd->setObjectName(QString::fromUtf8("toolButtonAdd"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAdd->setIcon(icon1);
        toolButtonAdd->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonAdd, 2, 0, 1, 1);

        toolButtonRemove = new QToolButton(groupBox);
        toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemove->setIcon(icon2);
        toolButtonRemove->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonRemove, 2, 2, 1, 1);

        toolButtonCopy = new QToolButton(groupBox);
        toolButtonCopy->setObjectName(QString::fromUtf8("toolButtonCopy"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/24x24/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonCopy->setIcon(icon3);
        toolButtonCopy->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonCopy, 2, 1, 1, 1);

        toolButtonRemoveFromUserDB = new QToolButton(groupBox);
        toolButtonRemoveFromUserDB->setObjectName(QString::fromUtf8("toolButtonRemoveFromUserDB"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/actions/24x24/fromDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveFromUserDB->setIcon(icon4);
        toolButtonRemoveFromUserDB->setIconSize(QSize(24, 24));

        gridLayout->addWidget(toolButtonRemoveFromUserDB, 2, 4, 1, 1);

        treeView = new QTreeView(groupBox);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setAlternatingRowColors(true);
        treeView->setSelectionMode(QAbstractItemView::SingleSelection);
        treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeView->setRootIsDecorated(true);
        treeView->setUniformRowHeights(true);

        gridLayout->addWidget(treeView, 0, 0, 1, 7);


        gridLayoutMaster->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonReloadUserDB = new QPushButton(SVDBZoneTemplateEditDialog);
        pushButtonReloadUserDB->setObjectName(QString::fromUtf8("pushButtonReloadUserDB"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/actions/24x24/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonReloadUserDB->setIcon(icon5);

        horizontalLayout->addWidget(pushButtonReloadUserDB);

        pushButtonRemoveUnusedElements = new QPushButton(SVDBZoneTemplateEditDialog);
        pushButtonRemoveUnusedElements->setObjectName(QString::fromUtf8("pushButtonRemoveUnusedElements"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gfx/actions/24x24/broom.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemoveUnusedElements->setIcon(icon6);

        horizontalLayout->addWidget(pushButtonRemoveUnusedElements);

        horizontalSpacer_2 = new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonSelect = new QPushButton(SVDBZoneTemplateEditDialog);
        pushButtonSelect->setObjectName(QString::fromUtf8("pushButtonSelect"));

        horizontalLayout->addWidget(pushButtonSelect);

        pushButtonCancel = new QPushButton(SVDBZoneTemplateEditDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonClose = new QPushButton(SVDBZoneTemplateEditDialog);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        horizontalLayout->addWidget(pushButtonClose);


        gridLayoutMaster->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SVDBZoneTemplateEditDialog);

        QMetaObject::connectSlotsByName(SVDBZoneTemplateEditDialog);
    } // setupUi

    void retranslateUi(QDialog *SVDBZoneTemplateEditDialog)
    {
        SVDBZoneTemplateEditDialog->setWindowTitle(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Zone Template Database", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Zone Templates", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonStoreInUserDB->setToolTip(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Stores local project DB element in user database.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonStoreInUserDB->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonRemoveFromUserDB->setToolTip(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Moves DB element from user database to local project.", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonRemoveFromUserDB->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonReloadUserDB->setToolTip(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Reloads user database from directory", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonReloadUserDB->setText(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Reload user database", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonRemoveUnusedElements->setToolTip(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Removes project-local database elements that are currently nowhere referenced.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonRemoveUnusedElements->setText(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Remove unused local elements", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Select", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Cancel", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("SVDBZoneTemplateEditDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBZoneTemplateEditDialog: public Ui_SVDBZoneTemplateEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBZONETEMPLATEEDITDIALOG_H
