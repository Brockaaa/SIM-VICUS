/********************************************************************************
** Form generated from reading UI file 'QtExt_ConstructionViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_CONSTRUCTIONVIEWWIDGET_H
#define UI_QTEXT_CONSTRUCTIONVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_ConstructionView.h"

namespace QtExt {

class Ui_ConstructionViewWidget
{
public:
    QAction *actionAssign_material;
    QAction *actionInsert_layer_left;
    QAction *actionInsert_layer_right;
    QAction *actionRemove_layer;
    QAction *actionMove_layer_left;
    QAction *actionMove_layer_right;
    QVBoxLayout *verticalLayout;
    QtExt::ConstructionView *graphicsView;

    void setupUi(QWidget *QtExt__ConstructionViewWidget)
    {
        if (QtExt__ConstructionViewWidget->objectName().isEmpty())
            QtExt__ConstructionViewWidget->setObjectName(QString::fromUtf8("QtExt__ConstructionViewWidget"));
        QtExt__ConstructionViewWidget->resize(500, 326);
        actionAssign_material = new QAction(QtExt__ConstructionViewWidget);
        actionAssign_material->setObjectName(QString::fromUtf8("actionAssign_material"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_assign_material_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAssign_material->setIcon(icon);
        actionInsert_layer_left = new QAction(QtExt__ConstructionViewWidget);
        actionInsert_layer_left->setObjectName(QString::fromUtf8("actionInsert_layer_left"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_insert_layer_left_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert_layer_left->setIcon(icon1);
        actionInsert_layer_right = new QAction(QtExt__ConstructionViewWidget);
        actionInsert_layer_right->setObjectName(QString::fromUtf8("actionInsert_layer_right"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_insert_layer_right_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInsert_layer_right->setIcon(icon2);
        actionRemove_layer = new QAction(QtExt__ConstructionViewWidget);
        actionRemove_layer->setObjectName(QString::fromUtf8("actionRemove_layer"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_remove_layer_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove_layer->setIcon(icon3);
        actionMove_layer_left = new QAction(QtExt__ConstructionViewWidget);
        actionMove_layer_left->setObjectName(QString::fromUtf8("actionMove_layer_left"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_move_layer_to_left_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMove_layer_left->setIcon(icon4);
        actionMove_layer_right = new QAction(QtExt__ConstructionViewWidget);
        actionMove_layer_right->setObjectName(QString::fromUtf8("actionMove_layer_right"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/constructionEditor/Construction_move_layer_to_right_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMove_layer_right->setIcon(icon5);
        verticalLayout = new QVBoxLayout(QtExt__ConstructionViewWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QtExt::ConstructionView(QtExt__ConstructionViewWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(QtExt__ConstructionViewWidget);

        QMetaObject::connectSlotsByName(QtExt__ConstructionViewWidget);
    } // setupUi

    void retranslateUi(QWidget *QtExt__ConstructionViewWidget)
    {
        QtExt__ConstructionViewWidget->setWindowTitle(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Form", nullptr));
        actionAssign_material->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Assign material", nullptr));
#if QT_CONFIG(tooltip)
        actionAssign_material->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Assign material to the selected layer", nullptr));
#endif // QT_CONFIG(tooltip)
        actionInsert_layer_left->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Insert layer left", nullptr));
#if QT_CONFIG(tooltip)
        actionInsert_layer_left->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Insert a new layer left from selected one", nullptr));
#endif // QT_CONFIG(tooltip)
        actionInsert_layer_right->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Insert layer right", nullptr));
#if QT_CONFIG(tooltip)
        actionInsert_layer_right->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Insert a new layer right from selected one", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRemove_layer->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Remove layer", nullptr));
#if QT_CONFIG(tooltip)
        actionRemove_layer->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Remove selected layer", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMove_layer_left->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Move layer left", nullptr));
#if QT_CONFIG(tooltip)
        actionMove_layer_left->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Move selected layer to left", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMove_layer_right->setText(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Move layer right", nullptr));
#if QT_CONFIG(tooltip)
        actionMove_layer_right->setToolTip(QCoreApplication::translate("QtExt::ConstructionViewWidget", "Move selected layer to right", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class ConstructionViewWidget: public Ui_ConstructionViewWidget {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_CONSTRUCTIONVIEWWIDGET_H
