/********************************************************************************
** Form generated from reading UI file 'SVPropAddGeometry.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPADDGEOMETRY_H
#define UI_SVPROPADDGEOMETRY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropAddGeometry
{
public:
    QVBoxLayout *verticalLayoutMaster;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonAddRect;
    QPushButton *pushButtonAddPolygon;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonAddWindow;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAddZone;
    QPushButton *pushButtonAddRoof;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAddPipeline;
    QPushButton *pushButtonAddSubStation;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVPropAddGeometry)
    {
        if (SVPropAddGeometry->objectName().isEmpty())
            SVPropAddGeometry->setObjectName(QString::fromUtf8("SVPropAddGeometry"));
        SVPropAddGeometry->resize(456, 597);
        verticalLayoutMaster = new QVBoxLayout(SVPropAddGeometry);
        verticalLayoutMaster->setObjectName(QString::fromUtf8("verticalLayoutMaster"));
        groupBox_5 = new QGroupBox(SVPropAddGeometry);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalSpacer_3 = new QSpacerItem(251, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        pushButtonAddRect = new QPushButton(groupBox_5);
        pushButtonAddRect->setObjectName(QString::fromUtf8("pushButtonAddRect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/icons8/icons8-rectangle-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddRect->setIcon(icon);
        pushButtonAddRect->setIconSize(QSize(24, 24));

        gridLayout_7->addWidget(pushButtonAddRect, 0, 0, 1, 1);

        pushButtonAddPolygon = new QPushButton(groupBox_5);
        pushButtonAddPolygon->setObjectName(QString::fromUtf8("pushButtonAddPolygon"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/icons8/icons8-polygon-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddPolygon->setIcon(icon1);
        pushButtonAddPolygon->setIconSize(QSize(24, 24));

        gridLayout_7->addWidget(pushButtonAddPolygon, 0, 1, 1, 1);


        verticalLayoutMaster->addWidget(groupBox_5);

        groupBox_4 = new QGroupBox(SVPropAddGeometry);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButtonAddWindow = new QPushButton(groupBox_4);
        pushButtonAddWindow->setObjectName(QString::fromUtf8("pushButtonAddWindow"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/icons8/icons8-window-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddWindow->setIcon(icon2);
        pushButtonAddWindow->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(pushButtonAddWindow, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(337, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        pushButtonAddZone = new QPushButton(groupBox_4);
        pushButtonAddZone->setObjectName(QString::fromUtf8("pushButtonAddZone"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/icons8/icons8-3d-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddZone->setIcon(icon3);
        pushButtonAddZone->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(pushButtonAddZone, 0, 0, 1, 1);

        pushButtonAddRoof = new QPushButton(groupBox_4);
        pushButtonAddRoof->setObjectName(QString::fromUtf8("pushButtonAddRoof"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/icons8/icons8-roof-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddRoof->setIcon(icon4);
        pushButtonAddRoof->setIconSize(QSize(24, 24));

        gridLayout_2->addWidget(pushButtonAddRoof, 0, 1, 1, 1);


        verticalLayoutMaster->addWidget(groupBox_4);

        groupBox = new QGroupBox(SVPropAddGeometry);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonAddPipeline = new QPushButton(groupBox);
        pushButtonAddPipeline->setObjectName(QString::fromUtf8("pushButtonAddPipeline"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/icons8/icons8-pipeline-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddPipeline->setIcon(icon5);
        pushButtonAddPipeline->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAddPipeline);

        pushButtonAddSubStation = new QPushButton(groupBox);
        pushButtonAddSubStation->setObjectName(QString::fromUtf8("pushButtonAddSubStation"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gfx/icons8/icons8-haus-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddSubStation->setIcon(icon6);
        pushButtonAddSubStation->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(pushButtonAddSubStation);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayoutMaster->addWidget(groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 394, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutMaster->addItem(verticalSpacer_2);


        retranslateUi(SVPropAddGeometry);

        QMetaObject::connectSlotsByName(SVPropAddGeometry);
    } // setupUi

    void retranslateUi(QWidget *SVPropAddGeometry)
    {
        SVPropAddGeometry->setWindowTitle(QCoreApplication::translate("SVPropAddGeometry", "Form", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("SVPropAddGeometry", "Add geometrical primitives", nullptr));
        pushButtonAddRect->setText(QCoreApplication::translate("SVPropAddGeometry", "Rect", nullptr));
        pushButtonAddPolygon->setText(QCoreApplication::translate("SVPropAddGeometry", "Polygon", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SVPropAddGeometry", "Add Building components", nullptr));
        pushButtonAddWindow->setText(QCoreApplication::translate("SVPropAddGeometry", "Window/Door", nullptr));
        pushButtonAddZone->setText(QCoreApplication::translate("SVPropAddGeometry", "Zone", nullptr));
        pushButtonAddRoof->setText(QCoreApplication::translate("SVPropAddGeometry", "Roof", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPropAddGeometry", "Add Network elements", nullptr));
        pushButtonAddPipeline->setText(QCoreApplication::translate("SVPropAddGeometry", "Pipeline", nullptr));
        pushButtonAddSubStation->setText(QCoreApplication::translate("SVPropAddGeometry", "Sub Stations", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropAddGeometry: public Ui_SVPropAddGeometry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPADDGEOMETRY_H
