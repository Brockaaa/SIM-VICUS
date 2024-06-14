/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingComponentsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGCOMPONENTSWIDGET_H
#define UI_SVPROPBUILDINGCOMPONENTSWIDGET_H

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

class Ui_SVPropBuildingComponentsWidget
{
public:
    QVBoxLayout *mainLayout;
    QTableWidget *tableWidgetComponents;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonEditComponents;
    QPushButton *pushButtonExchangeComponents;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSelectObjectsWithComponent;
    QFrame *line_2;
    QLabel *label_2;
    QWidget *widgetSelectedComponent;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *labelSelectedComponents;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QPushButton *pushButtonAssignComponent;
    QPushButton *pushButtonAssignComponentFromTable;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAssignInsideComponent;

    void setupUi(QWidget *SVPropBuildingComponentsWidget)
    {
        if (SVPropBuildingComponentsWidget->objectName().isEmpty())
            SVPropBuildingComponentsWidget->setObjectName(QString::fromUtf8("SVPropBuildingComponentsWidget"));
        SVPropBuildingComponentsWidget->resize(901, 887);
        mainLayout = new QVBoxLayout(SVPropBuildingComponentsWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        tableWidgetComponents = new QTableWidget(SVPropBuildingComponentsWidget);
        tableWidgetComponents->setObjectName(QString::fromUtf8("tableWidgetComponents"));

        mainLayout->addWidget(tableWidgetComponents);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonEditComponents = new QPushButton(SVPropBuildingComponentsWidget);
        pushButtonEditComponents->setObjectName(QString::fromUtf8("pushButtonEditComponents"));
        pushButtonEditComponents->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonEditComponents);

        pushButtonExchangeComponents = new QPushButton(SVPropBuildingComponentsWidget);
        pushButtonExchangeComponents->setObjectName(QString::fromUtf8("pushButtonExchangeComponents"));
        pushButtonExchangeComponents->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonExchangeComponents);

        horizontalSpacer = new QSpacerItem(614, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonSelectObjectsWithComponent = new QPushButton(SVPropBuildingComponentsWidget);
        pushButtonSelectObjectsWithComponent->setObjectName(QString::fromUtf8("pushButtonSelectObjectsWithComponent"));
        pushButtonSelectObjectsWithComponent->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonSelectObjectsWithComponent);


        mainLayout->addLayout(horizontalLayout_3);

        line_2 = new QFrame(SVPropBuildingComponentsWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        mainLayout->addWidget(line_2);

        label_2 = new QLabel(SVPropBuildingComponentsWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        label_2->setFont(font);

        mainLayout->addWidget(label_2);

        widgetSelectedComponent = new QWidget(SVPropBuildingComponentsWidget);
        widgetSelectedComponent->setObjectName(QString::fromUtf8("widgetSelectedComponent"));
        verticalLayout = new QVBoxLayout(widgetSelectedComponent);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widgetSelectedComponent);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        labelSelectedComponents = new QLabel(widgetSelectedComponent);
        labelSelectedComponents->setObjectName(QString::fromUtf8("labelSelectedComponents"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedComponents->sizePolicy().hasHeightForWidth());
        labelSelectedComponents->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(labelSelectedComponents);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(widgetSelectedComponent);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButtonAssignComponent = new QPushButton(widgetSelectedComponent);
        pushButtonAssignComponent->setObjectName(QString::fromUtf8("pushButtonAssignComponent"));
        pushButtonAssignComponent->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAssignComponent);

        pushButtonAssignComponentFromTable = new QPushButton(widgetSelectedComponent);
        pushButtonAssignComponentFromTable->setObjectName(QString::fromUtf8("pushButtonAssignComponentFromTable"));
        pushButtonAssignComponentFromTable->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAssignComponentFromTable);

        horizontalSpacer_2 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonAssignInsideComponent = new QPushButton(widgetSelectedComponent);
        pushButtonAssignInsideComponent->setObjectName(QString::fromUtf8("pushButtonAssignInsideComponent"));
        pushButtonAssignInsideComponent->setMinimumSize(QSize(0, 30));
        pushButtonAssignInsideComponent->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAssignInsideComponent);


        verticalLayout->addLayout(horizontalLayout);


        mainLayout->addWidget(widgetSelectedComponent);


        retranslateUi(SVPropBuildingComponentsWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingComponentsWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingComponentsWidget)
    {
        SVPropBuildingComponentsWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Form", nullptr));
        pushButtonEditComponents->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Edit...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonExchangeComponents->setToolTip(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Replaces the component association of all objects with the currently selected component.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonExchangeComponents->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Exchange...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSelectObjectsWithComponent->setToolTip(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Selects all objects/surfaces which are associated with the selected component.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSelectObjectsWithComponent->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Select", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Selected surface(s)", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Selected component:", nullptr));
        labelSelectedComponents->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Assign component:", nullptr));
        pushButtonAssignComponent->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "DB...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAssignComponentFromTable->setToolTip(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Assign the component selected in the table above to all currently selected surfaces.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAssignComponentFromTable->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Table", nullptr));
        pushButtonAssignInsideComponent->setText(QCoreApplication::translate("SVPropBuildingComponentsWidget", "Link...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingComponentsWidget: public Ui_SVPropBuildingComponentsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGCOMPONENTSWIDGET_H
