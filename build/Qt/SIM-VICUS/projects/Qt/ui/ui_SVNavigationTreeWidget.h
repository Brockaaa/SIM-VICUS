/********************************************************************************
** Form generated from reading UI file 'SVNavigationTreeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNAVIGATIONTREEWIDGET_H
#define UI_SVNAVIGATIONTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVNavigationTreeWidget
{
public:
    QAction *actionRemoveSelected;
    QAction *actionShowSelected;
    QAction *actionHideSelected;
    QAction *actionSelectAll;
    QAction *actionDeselectAll;
    QAction *actionSmartSelect;
    QAction *actionInvertSelection;
    QVBoxLayout *verticalLayout;
    QToolBar *toolBar;
    QTreeWidget *treeWidget;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVNavigationTreeWidget)
    {
        if (SVNavigationTreeWidget->objectName().isEmpty())
            SVNavigationTreeWidget->setObjectName(QString::fromUtf8("SVNavigationTreeWidget"));
        SVNavigationTreeWidget->resize(1026, 637);
        actionRemoveSelected = new QAction(SVNavigationTreeWidget);
        actionRemoveSelected->setObjectName(QString::fromUtf8("actionRemoveSelected"));
        actionShowSelected = new QAction(SVNavigationTreeWidget);
        actionShowSelected->setObjectName(QString::fromUtf8("actionShowSelected"));
        actionHideSelected = new QAction(SVNavigationTreeWidget);
        actionHideSelected->setObjectName(QString::fromUtf8("actionHideSelected"));
        actionSelectAll = new QAction(SVNavigationTreeWidget);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        actionDeselectAll = new QAction(SVNavigationTreeWidget);
        actionDeselectAll->setObjectName(QString::fromUtf8("actionDeselectAll"));
        actionSmartSelect = new QAction(SVNavigationTreeWidget);
        actionSmartSelect->setObjectName(QString::fromUtf8("actionSmartSelect"));
        actionInvertSelection = new QAction(SVNavigationTreeWidget);
        actionInvertSelection->setObjectName(QString::fromUtf8("actionInvertSelection"));
        verticalLayout = new QVBoxLayout(SVNavigationTreeWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBar = new QToolBar(SVNavigationTreeWidget);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy);
        toolBar->setMaximumSize(QSize(16777215, 32));
        toolBar->setAutoFillBackground(true);
        toolBar->setIconSize(QSize(32, 32));
        toolBar->setFloatable(false);

        verticalLayout->addWidget(toolBar);

        treeWidget = new QTreeWidget(SVNavigationTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
        treeWidget->setHeaderHidden(true);
        treeWidget->setExpandsOnDoubleClick(false);

        verticalLayout->addWidget(treeWidget);

        verticalSpacer = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);


        toolBar->addAction(actionRemoveSelected);
        toolBar->addAction(actionHideSelected);
        toolBar->addAction(actionShowSelected);
        toolBar->addAction(actionSelectAll);
        toolBar->addAction(actionDeselectAll);
        toolBar->addAction(actionInvertSelection);
        toolBar->addAction(actionSmartSelect);

        retranslateUi(SVNavigationTreeWidget);

        QMetaObject::connectSlotsByName(SVNavigationTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *SVNavigationTreeWidget)
    {
        SVNavigationTreeWidget->setWindowTitle(QCoreApplication::translate("SVNavigationTreeWidget", "Interface/Boundary", nullptr));
        actionRemoveSelected->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Remove (Del)", nullptr));
#if QT_CONFIG(tooltip)
        actionRemoveSelected->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Removed selected objects (Del)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionRemoveSelected->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShowSelected->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Show selected objects", nullptr));
#if QT_CONFIG(tooltip)
        actionShowSelected->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Makes all selected objects visible (F7)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionShowSelected->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "F7", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHideSelected->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Hides selected objects", nullptr));
#if QT_CONFIG(tooltip)
        actionHideSelected->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Hides all selected objects (F6)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionHideSelected->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "F6", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelectAll->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Select all", nullptr));
#if QT_CONFIG(tooltip)
        actionSelectAll->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Selects all selectable objects (Ctrl + A)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSelectAll->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDeselectAll->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Deselect all", nullptr));
#if QT_CONFIG(tooltip)
        actionDeselectAll->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Deselects all objects (Esc)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDeselectAll->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSmartSelect->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Smart select", nullptr));
#if QT_CONFIG(tooltip)
        actionSmartSelect->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Select objects based on properties (Ctrl + .)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSmartSelect->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "Ctrl+.", nullptr));
#endif // QT_CONFIG(shortcut)
        actionInvertSelection->setText(QCoreApplication::translate("SVNavigationTreeWidget", "Invert selection", nullptr));
#if QT_CONFIG(tooltip)
        actionInvertSelection->setToolTip(QCoreApplication::translate("SVNavigationTreeWidget", "Inverts current selection (Ctrl + I)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionInvertSelection->setShortcut(QCoreApplication::translate("SVNavigationTreeWidget", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class SVNavigationTreeWidget: public Ui_SVNavigationTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNAVIGATIONTREEWIDGET_H
