/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingSubComponentsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGSUBCOMPONENTSWIDGET_H
#define UI_SVPROPBUILDINGSUBCOMPONENTSWIDGET_H

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

class Ui_SVPropBuildingSubComponentsWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetSubSurfaceComponents;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonEditSubSurfaceComponents;
    QPushButton *pushButtonExchangeSubSurfaceComponents;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonSelectObjectsWithSubSurfaceComponent;
    QFrame *line;
    QLabel *label;
    QWidget *widgetSelectedSubComponent;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLabel *labelSelectedSubSurfaceComponents;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QPushButton *pushButtonAssignSubSurfaceComponent;
    QPushButton *pushButtonAssignComponentFromTable;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButtonAssignInsideSubSurfaceComponent;
    QWidget *widget;

    void setupUi(QWidget *SVPropBuildingSubComponentsWidget)
    {
        if (SVPropBuildingSubComponentsWidget->objectName().isEmpty())
            SVPropBuildingSubComponentsWidget->setObjectName(QString::fromUtf8("SVPropBuildingSubComponentsWidget"));
        SVPropBuildingSubComponentsWidget->resize(1125, 737);
        verticalLayout_2 = new QVBoxLayout(SVPropBuildingSubComponentsWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidgetSubSurfaceComponents = new QTableWidget(SVPropBuildingSubComponentsWidget);
        tableWidgetSubSurfaceComponents->setObjectName(QString::fromUtf8("tableWidgetSubSurfaceComponents"));

        verticalLayout_2->addWidget(tableWidgetSubSurfaceComponents);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonEditSubSurfaceComponents = new QPushButton(SVPropBuildingSubComponentsWidget);
        pushButtonEditSubSurfaceComponents->setObjectName(QString::fromUtf8("pushButtonEditSubSurfaceComponents"));
        pushButtonEditSubSurfaceComponents->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonEditSubSurfaceComponents);

        pushButtonExchangeSubSurfaceComponents = new QPushButton(SVPropBuildingSubComponentsWidget);
        pushButtonExchangeSubSurfaceComponents->setObjectName(QString::fromUtf8("pushButtonExchangeSubSurfaceComponents"));
        pushButtonExchangeSubSurfaceComponents->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonExchangeSubSurfaceComponents);

        horizontalSpacer_7 = new QSpacerItem(399, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        pushButtonSelectObjectsWithSubSurfaceComponent = new QPushButton(SVPropBuildingSubComponentsWidget);
        pushButtonSelectObjectsWithSubSurfaceComponent->setObjectName(QString::fromUtf8("pushButtonSelectObjectsWithSubSurfaceComponent"));
        pushButtonSelectObjectsWithSubSurfaceComponent->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonSelectObjectsWithSubSurfaceComponent);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(SVPropBuildingSubComponentsWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        label = new QLabel(SVPropBuildingSubComponentsWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        widgetSelectedSubComponent = new QWidget(SVPropBuildingSubComponentsWidget);
        widgetSelectedSubComponent->setObjectName(QString::fromUtf8("widgetSelectedSubComponent"));
        verticalLayout = new QVBoxLayout(widgetSelectedSubComponent);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(widgetSelectedSubComponent);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        labelSelectedSubSurfaceComponents = new QLabel(widgetSelectedSubComponent);
        labelSelectedSubSurfaceComponents->setObjectName(QString::fromUtf8("labelSelectedSubSurfaceComponents"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedSubSurfaceComponents->sizePolicy().hasHeightForWidth());
        labelSelectedSubSurfaceComponents->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(labelSelectedSubSurfaceComponents);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widgetSelectedSubComponent);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        pushButtonAssignSubSurfaceComponent = new QPushButton(widgetSelectedSubComponent);
        pushButtonAssignSubSurfaceComponent->setObjectName(QString::fromUtf8("pushButtonAssignSubSurfaceComponent"));
        pushButtonAssignSubSurfaceComponent->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonAssignSubSurfaceComponent);

        pushButtonAssignComponentFromTable = new QPushButton(widgetSelectedSubComponent);
        pushButtonAssignComponentFromTable->setObjectName(QString::fromUtf8("pushButtonAssignComponentFromTable"));
        pushButtonAssignComponentFromTable->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonAssignComponentFromTable);

        horizontalSpacer_8 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        pushButtonAssignInsideSubSurfaceComponent = new QPushButton(widgetSelectedSubComponent);
        pushButtonAssignInsideSubSurfaceComponent->setObjectName(QString::fromUtf8("pushButtonAssignInsideSubSurfaceComponent"));
        pushButtonAssignInsideSubSurfaceComponent->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(pushButtonAssignInsideSubSurfaceComponent);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(widgetSelectedSubComponent);

        widget = new QWidget(SVPropBuildingSubComponentsWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout_2->addWidget(widget);


        retranslateUi(SVPropBuildingSubComponentsWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingSubComponentsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingSubComponentsWidget)
    {
        SVPropBuildingSubComponentsWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Form", nullptr));
        pushButtonEditSubSurfaceComponents->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Edit...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonExchangeSubSurfaceComponents->setToolTip(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Replaces the component association of all objects with the currently selected component.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonExchangeSubSurfaceComponents->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Exchange...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSelectObjectsWithSubSurfaceComponent->setToolTip(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Selects all objects/surfaces which are associated with the selected component.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSelectObjectsWithSubSurfaceComponent->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Select", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Selected sub-surface(s)", nullptr));
        label_5->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Selected sub-surface component:", nullptr));
        labelSelectedSubSurfaceComponents->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Assign component:", nullptr));
        pushButtonAssignSubSurfaceComponent->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "DB...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAssignComponentFromTable->setToolTip(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Assign the sub-surface component selected in the table above to all currently selected sub-surfaces.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAssignComponentFromTable->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Table", nullptr));
        pushButtonAssignInsideSubSurfaceComponent->setText(QCoreApplication::translate("SVPropBuildingSubComponentsWidget", "Link...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingSubComponentsWidget: public Ui_SVPropBuildingSubComponentsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGSUBCOMPONENTSWIDGET_H
