/********************************************************************************
** Form generated from reading UI file 'SVPropFloorManagerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPFLOORMANAGERWIDGET_H
#define UI_SVPROPFLOORMANAGERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropFloorManagerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAddBuilding;
    QPushButton *pushButtonRemoveBuilding;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButtonAddLevel;
    QPushButton *pushButtonRemoveLevel;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButtonAssignRooms;
    QPushButton *pushButtonAssignLevel;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *SVPropFloorManagerWidget)
    {
        if (SVPropFloorManagerWidget->objectName().isEmpty())
            SVPropFloorManagerWidget->setObjectName(QString::fromUtf8("SVPropFloorManagerWidget"));
        SVPropFloorManagerWidget->resize(910, 743);
        verticalLayout = new QVBoxLayout(SVPropFloorManagerWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(SVPropFloorManagerWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(2, QString::fromUtf8("3"));
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setAlternatingRowColors(true);
        treeWidget->setColumnCount(3);
        treeWidget->header()->setStretchLastSection(false);

        verticalLayout->addWidget(treeWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonAddBuilding = new QPushButton(SVPropFloorManagerWidget);
        pushButtonAddBuilding->setObjectName(QString::fromUtf8("pushButtonAddBuilding"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddBuilding->setIcon(icon);

        horizontalLayout_4->addWidget(pushButtonAddBuilding);

        pushButtonRemoveBuilding = new QPushButton(SVPropFloorManagerWidget);
        pushButtonRemoveBuilding->setObjectName(QString::fromUtf8("pushButtonRemoveBuilding"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemoveBuilding->setIcon(icon1);

        horizontalLayout_4->addWidget(pushButtonRemoveBuilding);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButtonAddLevel = new QPushButton(SVPropFloorManagerWidget);
        pushButtonAddLevel->setObjectName(QString::fromUtf8("pushButtonAddLevel"));
        pushButtonAddLevel->setIcon(icon);

        horizontalLayout_6->addWidget(pushButtonAddLevel);

        pushButtonRemoveLevel = new QPushButton(SVPropFloorManagerWidget);
        pushButtonRemoveLevel->setObjectName(QString::fromUtf8("pushButtonRemoveLevel"));
        pushButtonRemoveLevel->setIcon(icon1);

        horizontalLayout_6->addWidget(pushButtonRemoveLevel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButtonAssignRooms = new QPushButton(SVPropFloorManagerWidget);
        pushButtonAssignRooms->setObjectName(QString::fromUtf8("pushButtonAssignRooms"));

        horizontalLayout_5->addWidget(pushButtonAssignRooms);

        pushButtonAssignLevel = new QPushButton(SVPropFloorManagerWidget);
        pushButtonAssignLevel->setObjectName(QString::fromUtf8("pushButtonAssignLevel"));

        horizontalLayout_5->addWidget(pushButtonAssignLevel);

        horizontalSpacer_5 = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(SVPropFloorManagerWidget);

        QMetaObject::connectSlotsByName(SVPropFloorManagerWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropFloorManagerWidget)
    {
        SVPropFloorManagerWidget->setWindowTitle(QCoreApplication::translate("SVPropFloorManagerWidget", "Floor manager", nullptr));
        pushButtonAddBuilding->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Add building", nullptr));
        pushButtonRemoveBuilding->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Remove building", nullptr));
        pushButtonAddLevel->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Add level", nullptr));
        pushButtonRemoveLevel->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Remove level", nullptr));
        pushButtonAssignRooms->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Assign selected rooms", nullptr));
        pushButtonAssignLevel->setText(QCoreApplication::translate("SVPropFloorManagerWidget", "Assign selected levels", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropFloorManagerWidget: public Ui_SVPropFloorManagerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPFLOORMANAGERWIDGET_H
