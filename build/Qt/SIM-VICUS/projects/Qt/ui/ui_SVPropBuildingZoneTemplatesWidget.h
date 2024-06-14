/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingZoneTemplatesWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGZONETEMPLATESWIDGET_H
#define UI_SVPROPBUILDINGZONETEMPLATESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_SVPropBuildingZoneTemplatesWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetZoneTemplates;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxZoneTemplateColorOnlyActive;
    QCheckBox *checkBoxZoneTemplateShowOnlyActive;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonEditZoneTemplates;
    QPushButton *pushButtonExchangeZoneTemplates;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonSelectObjectsWithZoneTemplate;
    QFrame *line;
    QLabel *label_2;
    QWidget *widgetSelectedRooms;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *labelSelectedZoneTemplates;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *pushButtonAssignZoneTemplate;
    QPushButton *pushButtonAssignSelectedZoneTemplate;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SVPropBuildingZoneTemplatesWidget)
    {
        if (SVPropBuildingZoneTemplatesWidget->objectName().isEmpty())
            SVPropBuildingZoneTemplatesWidget->setObjectName(QString::fromUtf8("SVPropBuildingZoneTemplatesWidget"));
        SVPropBuildingZoneTemplatesWidget->resize(703, 910);
        verticalLayout_2 = new QVBoxLayout(SVPropBuildingZoneTemplatesWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidgetZoneTemplates = new QTableWidget(SVPropBuildingZoneTemplatesWidget);
        tableWidgetZoneTemplates->setObjectName(QString::fromUtf8("tableWidgetZoneTemplates"));

        verticalLayout_2->addWidget(tableWidgetZoneTemplates);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBoxZoneTemplateColorOnlyActive = new QCheckBox(SVPropBuildingZoneTemplatesWidget);
        checkBoxZoneTemplateColorOnlyActive->setObjectName(QString::fromUtf8("checkBoxZoneTemplateColorOnlyActive"));

        horizontalLayout_4->addWidget(checkBoxZoneTemplateColorOnlyActive);

        checkBoxZoneTemplateShowOnlyActive = new QCheckBox(SVPropBuildingZoneTemplatesWidget);
        checkBoxZoneTemplateShowOnlyActive->setObjectName(QString::fromUtf8("checkBoxZoneTemplateShowOnlyActive"));

        horizontalLayout_4->addWidget(checkBoxZoneTemplateShowOnlyActive);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonEditZoneTemplates = new QPushButton(SVPropBuildingZoneTemplatesWidget);
        pushButtonEditZoneTemplates->setObjectName(QString::fromUtf8("pushButtonEditZoneTemplates"));
        pushButtonEditZoneTemplates->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonEditZoneTemplates);

        pushButtonExchangeZoneTemplates = new QPushButton(SVPropBuildingZoneTemplatesWidget);
        pushButtonExchangeZoneTemplates->setObjectName(QString::fromUtf8("pushButtonExchangeZoneTemplates"));
        pushButtonExchangeZoneTemplates->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonExchangeZoneTemplates);

        horizontalSpacer_5 = new QSpacerItem(272, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButtonSelectObjectsWithZoneTemplate = new QPushButton(SVPropBuildingZoneTemplatesWidget);
        pushButtonSelectObjectsWithZoneTemplate->setObjectName(QString::fromUtf8("pushButtonSelectObjectsWithZoneTemplate"));
        pushButtonSelectObjectsWithZoneTemplate->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(pushButtonSelectObjectsWithZoneTemplate);


        verticalLayout_2->addLayout(horizontalLayout_3);

        line = new QFrame(SVPropBuildingZoneTemplatesWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        label_2 = new QLabel(SVPropBuildingZoneTemplatesWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        widgetSelectedRooms = new QWidget(SVPropBuildingZoneTemplatesWidget);
        widgetSelectedRooms->setObjectName(QString::fromUtf8("widgetSelectedRooms"));
        verticalLayout = new QVBoxLayout(widgetSelectedRooms);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(widgetSelectedRooms);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        labelSelectedZoneTemplates = new QLabel(widgetSelectedRooms);
        labelSelectedZoneTemplates->setObjectName(QString::fromUtf8("labelSelectedZoneTemplates"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSelectedZoneTemplates->sizePolicy().hasHeightForWidth());
        labelSelectedZoneTemplates->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(labelSelectedZoneTemplates);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widgetSelectedRooms);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        pushButtonAssignZoneTemplate = new QPushButton(widgetSelectedRooms);
        pushButtonAssignZoneTemplate->setObjectName(QString::fromUtf8("pushButtonAssignZoneTemplate"));
        pushButtonAssignZoneTemplate->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAssignZoneTemplate);

        pushButtonAssignSelectedZoneTemplate = new QPushButton(widgetSelectedRooms);
        pushButtonAssignSelectedZoneTemplate->setObjectName(QString::fromUtf8("pushButtonAssignSelectedZoneTemplate"));
        pushButtonAssignSelectedZoneTemplate->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAssignSelectedZoneTemplate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(widgetSelectedRooms);


        retranslateUi(SVPropBuildingZoneTemplatesWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingZoneTemplatesWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingZoneTemplatesWidget)
    {
        SVPropBuildingZoneTemplatesWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxZoneTemplateColorOnlyActive->setToolTip(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Colors only rooms that are selected in zone template table", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxZoneTemplateColorOnlyActive->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Color only selected", nullptr));
#if QT_CONFIG(tooltip)
        checkBoxZoneTemplateShowOnlyActive->setToolTip(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Shows only rooms that are selected in zone template table", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBoxZoneTemplateShowOnlyActive->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Show only selected", nullptr));
        pushButtonEditZoneTemplates->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Edit...", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonExchangeZoneTemplates->setToolTip(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Replaces the zone template association of all selected zones with the currently selected zone template.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonExchangeZoneTemplates->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Exchange...", nullptr));
        pushButtonSelectObjectsWithZoneTemplate->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Select", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Selected room(s)", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Selected zone template:", nullptr));
        labelSelectedZoneTemplates->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Assign Zone template:", nullptr));
        pushButtonAssignZoneTemplate->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "DB...", nullptr));
        pushButtonAssignSelectedZoneTemplate->setText(QCoreApplication::translate("SVPropBuildingZoneTemplatesWidget", "Table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingZoneTemplatesWidget: public Ui_SVPropBuildingZoneTemplatesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGZONETEMPLATESWIDGET_H
