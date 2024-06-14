/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingZoneProperty.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGZONEPROPERTY_H
#define UI_SVPROPBUILDINGZONEPROPERTY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingZoneProperty
{
public:
    QGridLayout *mainGridLayout;
    QTableView *tableViewZones;
    QLabel *label_6;
    QComboBox *comboBoxBuildingFilter;
    QLineEdit *lineEditNameFilter;
    QGroupBox *groupBoxSelectedComponent2;
    QGridLayout *gridLayout;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonFloorAreaSelectedRooms;
    QPushButton *pushButtonVolumeSelectedRooms;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonFloorAreaAllRooms;
    QPushButton *pushButtonVolumeAllRooms;
    QLabel *label_7;
    QComboBox *comboBoxBuildingLevelFilter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonAssignSurface;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *SVPropBuildingZoneProperty)
    {
        if (SVPropBuildingZoneProperty->objectName().isEmpty())
            SVPropBuildingZoneProperty->setObjectName(QString::fromUtf8("SVPropBuildingZoneProperty"));
        SVPropBuildingZoneProperty->resize(706, 761);
        mainGridLayout = new QGridLayout(SVPropBuildingZoneProperty);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        tableViewZones = new QTableView(SVPropBuildingZoneProperty);
        tableViewZones->setObjectName(QString::fromUtf8("tableViewZones"));
        tableViewZones->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewZones->setSortingEnabled(true);

        mainGridLayout->addWidget(tableViewZones, 4, 0, 1, 2);

        label_6 = new QLabel(SVPropBuildingZoneProperty);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        mainGridLayout->addWidget(label_6, 0, 0, 1, 1);

        comboBoxBuildingFilter = new QComboBox(SVPropBuildingZoneProperty);
        comboBoxBuildingFilter->setObjectName(QString::fromUtf8("comboBoxBuildingFilter"));

        mainGridLayout->addWidget(comboBoxBuildingFilter, 0, 1, 1, 1);

        lineEditNameFilter = new QLineEdit(SVPropBuildingZoneProperty);
        lineEditNameFilter->setObjectName(QString::fromUtf8("lineEditNameFilter"));

        mainGridLayout->addWidget(lineEditNameFilter, 2, 1, 1, 1);

        groupBoxSelectedComponent2 = new QGroupBox(SVPropBuildingZoneProperty);
        groupBoxSelectedComponent2->setObjectName(QString::fromUtf8("groupBoxSelectedComponent2"));
        gridLayout = new QGridLayout(groupBoxSelectedComponent2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        line = new QFrame(groupBoxSelectedComponent2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBoxSelectedComponent2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonFloorAreaSelectedRooms = new QPushButton(groupBoxSelectedComponent2);
        pushButtonFloorAreaSelectedRooms->setObjectName(QString::fromUtf8("pushButtonFloorAreaSelectedRooms"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonFloorAreaSelectedRooms->sizePolicy().hasHeightForWidth());
        pushButtonFloorAreaSelectedRooms->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButtonFloorAreaSelectedRooms);

        pushButtonVolumeSelectedRooms = new QPushButton(groupBoxSelectedComponent2);
        pushButtonVolumeSelectedRooms->setObjectName(QString::fromUtf8("pushButtonVolumeSelectedRooms"));

        horizontalLayout_2->addWidget(pushButtonVolumeSelectedRooms);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBoxSelectedComponent2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonFloorAreaAllRooms = new QPushButton(groupBoxSelectedComponent2);
        pushButtonFloorAreaAllRooms->setObjectName(QString::fromUtf8("pushButtonFloorAreaAllRooms"));

        horizontalLayout->addWidget(pushButtonFloorAreaAllRooms);

        pushButtonVolumeAllRooms = new QPushButton(groupBoxSelectedComponent2);
        pushButtonVolumeAllRooms->setObjectName(QString::fromUtf8("pushButtonVolumeAllRooms"));

        horizontalLayout->addWidget(pushButtonVolumeAllRooms);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        mainGridLayout->addWidget(groupBoxSelectedComponent2, 6, 0, 1, 2);

        label_7 = new QLabel(SVPropBuildingZoneProperty);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        mainGridLayout->addWidget(label_7, 1, 0, 1, 1);

        comboBoxBuildingLevelFilter = new QComboBox(SVPropBuildingZoneProperty);
        comboBoxBuildingLevelFilter->setObjectName(QString::fromUtf8("comboBoxBuildingLevelFilter"));

        mainGridLayout->addWidget(comboBoxBuildingLevelFilter, 1, 1, 1, 1);

        groupBox = new QGroupBox(SVPropBuildingZoneProperty);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButtonAssignSurface = new QPushButton(groupBox);
        pushButtonAssignSurface->setObjectName(QString::fromUtf8("pushButtonAssignSurface"));

        verticalLayout_2->addWidget(pushButtonAssignSurface);


        mainGridLayout->addWidget(groupBox, 7, 0, 1, 2);

        label_8 = new QLabel(SVPropBuildingZoneProperty);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        mainGridLayout->addWidget(label_8, 3, 0, 1, 1);

        label_3 = new QLabel(SVPropBuildingZoneProperty);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        mainGridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(SVPropBuildingZoneProperty);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setItalic(true);
        label_4->setFont(font);

        mainGridLayout->addWidget(label_4, 5, 0, 1, 1);


        retranslateUi(SVPropBuildingZoneProperty);

        QMetaObject::connectSlotsByName(SVPropBuildingZoneProperty);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingZoneProperty)
    {
        SVPropBuildingZoneProperty->setWindowTitle(QCoreApplication::translate("SVPropBuildingZoneProperty", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Building:", nullptr));
        groupBoxSelectedComponent2->setTitle(QCoreApplication::translate("SVPropBuildingZoneProperty", "Update Floor Areas / Volumes", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Only selected rooms:", nullptr));
        pushButtonFloorAreaSelectedRooms->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Floor area", nullptr));
        pushButtonVolumeSelectedRooms->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Volume", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "All rooms:", nullptr));
        pushButtonFloorAreaAllRooms->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Floor area", nullptr));
        pushButtonVolumeAllRooms->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Volume", nullptr));
        label_7->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Building level:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPropBuildingZoneProperty", "Other", nullptr));
        pushButtonAssignSurface->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Assign selected surfaces to room", nullptr));
        label_8->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Rooms/Zones:", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Room Name:", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropBuildingZoneProperty", "Double-Click on room name for additional information", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingZoneProperty: public Ui_SVPropBuildingZoneProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGZONEPROPERTY_H
