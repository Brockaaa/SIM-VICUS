/********************************************************************************
** Form generated from reading UI file 'SVPropBuildingSurfaceConnectionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPBUILDINGSURFACECONNECTIONWIDGET_H
#define UI_SVPROPBUILDINGSURFACECONNECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropBuildingSurfaceConnectionWidget
{
public:
    QGridLayout *mainGridLayout;
    QLabel *label;
    QComboBox *comboBoxHighlightingMode;
    QTableWidget *tableWidgetInterlinkedSurfaces;
    QPushButton *pushButtonRemoveComponentInstance;
    QSpacerItem *horizontalSpacer_11;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButtonSmartClipping;

    void setupUi(QWidget *SVPropBuildingSurfaceConnectionWidget)
    {
        if (SVPropBuildingSurfaceConnectionWidget->objectName().isEmpty())
            SVPropBuildingSurfaceConnectionWidget->setObjectName(QString::fromUtf8("SVPropBuildingSurfaceConnectionWidget"));
        SVPropBuildingSurfaceConnectionWidget->resize(546, 583);
        mainGridLayout = new QGridLayout(SVPropBuildingSurfaceConnectionWidget);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        label = new QLabel(SVPropBuildingSurfaceConnectionWidget);
        label->setObjectName(QString::fromUtf8("label"));

        mainGridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxHighlightingMode = new QComboBox(SVPropBuildingSurfaceConnectionWidget);
        comboBoxHighlightingMode->setObjectName(QString::fromUtf8("comboBoxHighlightingMode"));

        mainGridLayout->addWidget(comboBoxHighlightingMode, 0, 1, 1, 1);

        tableWidgetInterlinkedSurfaces = new QTableWidget(SVPropBuildingSurfaceConnectionWidget);
        tableWidgetInterlinkedSurfaces->setObjectName(QString::fromUtf8("tableWidgetInterlinkedSurfaces"));

        mainGridLayout->addWidget(tableWidgetInterlinkedSurfaces, 1, 0, 1, 2);

        pushButtonRemoveComponentInstance = new QPushButton(SVPropBuildingSurfaceConnectionWidget);
        pushButtonRemoveComponentInstance->setObjectName(QString::fromUtf8("pushButtonRemoveComponentInstance"));
        pushButtonRemoveComponentInstance->setIconSize(QSize(24, 24));

        mainGridLayout->addWidget(pushButtonRemoveComponentInstance, 2, 0, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(377, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainGridLayout->addItem(horizontalSpacer_11, 2, 1, 1, 1);

        groupBox = new QGroupBox(SVPropBuildingSurfaceConnectionWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonSmartClipping = new QPushButton(groupBox);
        pushButtonSmartClipping->setObjectName(QString::fromUtf8("pushButtonSmartClipping"));

        gridLayout->addWidget(pushButtonSmartClipping, 0, 0, 1, 1);


        mainGridLayout->addWidget(groupBox, 3, 0, 1, 2);


        retranslateUi(SVPropBuildingSurfaceConnectionWidget);

        QMetaObject::connectSlotsByName(SVPropBuildingSurfaceConnectionWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropBuildingSurfaceConnectionWidget)
    {
        SVPropBuildingSurfaceConnectionWidget->setWindowTitle(QCoreApplication::translate("SVPropBuildingSurfaceConnectionWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("SVPropBuildingSurfaceConnectionWidget", "Highlighting mode:", nullptr));
        pushButtonRemoveComponentInstance->setText(QCoreApplication::translate("SVPropBuildingSurfaceConnectionWidget", "Remove connection", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPropBuildingSurfaceConnectionWidget", "Smart Surface Connections", nullptr));
        pushButtonSmartClipping->setText(QCoreApplication::translate("SVPropBuildingSurfaceConnectionWidget", "Open smart-clipping", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropBuildingSurfaceConnectionWidget: public Ui_SVPropBuildingSurfaceConnectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPBUILDINGSURFACECONNECTIONWIDGET_H
