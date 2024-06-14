/********************************************************************************
** Form generated from reading UI file 'SVGeometryView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVGEOMETRYVIEW_H
#define UI_SVGEOMETRYVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "SVPropertyWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVGeometryView
{
public:
    QAction *actionSnap;
    QAction *actionMeasure;
    QAction *actionXLock;
    QAction *actionYLock;
    QAction *actionZLock;
    QAction *actionAddGeometry;
    QAction *actionTranslateGeometry;
    QAction *actionRotateGeometry;
    QAction *actionScaleGeometry;
    QAction *actionAlignGeometry;
    QAction *actionCopyGeometry;
    QAction *actionBuildingParametrization;
    QAction *actionNetworkParametrization;
    QAction *actionSiteParametrization;
    QAction *actionAcousticParametrization;
    QAction *actionShowResults;
    QAction *actionStructuralUnits;
    QVBoxLayout *mainLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *sceneVBoxLayout;
    QWidget *widgetSceneViewDummy;
    QToolBar *geometryToolBar;
    QToolBar *modeSelectionToolBar;
    SVPropertyWidget *propertyWidget;

    void setupUi(QWidget *SVGeometryView)
    {
        if (SVGeometryView->objectName().isEmpty())
            SVGeometryView->setObjectName(QString::fromUtf8("SVGeometryView"));
        SVGeometryView->resize(1148, 754);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVGeometryView->sizePolicy().hasHeightForWidth());
        SVGeometryView->setSizePolicy(sizePolicy);
        actionSnap = new QAction(SVGeometryView);
        actionSnap->setObjectName(QString::fromUtf8("actionSnap"));
        actionSnap->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/icons8/icons8-magnet-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSnap->setIcon(icon);
        actionMeasure = new QAction(SVGeometryView);
        actionMeasure->setObjectName(QString::fromUtf8("actionMeasure"));
        actionMeasure->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/icons8/icons8-width-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMeasure->setIcon(icon1);
        actionXLock = new QAction(SVGeometryView);
        actionXLock->setObjectName(QString::fromUtf8("actionXLock"));
        actionXLock->setCheckable(true);
        actionYLock = new QAction(SVGeometryView);
        actionYLock->setObjectName(QString::fromUtf8("actionYLock"));
        actionYLock->setCheckable(true);
        actionZLock = new QAction(SVGeometryView);
        actionZLock->setObjectName(QString::fromUtf8("actionZLock"));
        actionZLock->setCheckable(true);
        actionAddGeometry = new QAction(SVGeometryView);
        actionAddGeometry->setObjectName(QString::fromUtf8("actionAddGeometry"));
        actionAddGeometry->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/icons8/icons8-add-layer-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddGeometry->setIcon(icon2);
        actionTranslateGeometry = new QAction(SVGeometryView);
        actionTranslateGeometry->setObjectName(QString::fromUtf8("actionTranslateGeometry"));
        actionTranslateGeometry->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/icons8/icons8-in-alle-richtungen-skalieren-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTranslateGeometry->setIcon(icon3);
        actionRotateGeometry = new QAction(SVGeometryView);
        actionRotateGeometry->setObjectName(QString::fromUtf8("actionRotateGeometry"));
        actionRotateGeometry->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/gfx/icons8/icons8-verfuegbare-updates-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotateGeometry->setIcon(icon4);
        actionScaleGeometry = new QAction(SVGeometryView);
        actionScaleGeometry->setObjectName(QString::fromUtf8("actionScaleGeometry"));
        actionScaleGeometry->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/gfx/icons8/icons8-skalieren-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScaleGeometry->setIcon(icon5);
        actionAlignGeometry = new QAction(SVGeometryView);
        actionAlignGeometry->setObjectName(QString::fromUtf8("actionAlignGeometry"));
        actionAlignGeometry->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gfx/icons8/icons8-kategorisieren-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAlignGeometry->setIcon(icon6);
        actionCopyGeometry = new QAction(SVGeometryView);
        actionCopyGeometry->setObjectName(QString::fromUtf8("actionCopyGeometry"));
        actionCopyGeometry->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/gfx/icons8/icons8-kopieren-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopyGeometry->setIcon(icon7);
        actionBuildingParametrization = new QAction(SVGeometryView);
        actionBuildingParametrization->setObjectName(QString::fromUtf8("actionBuildingParametrization"));
        actionBuildingParametrization->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/gfx/icons8/icons8-heim-automatisierung-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBuildingParametrization->setIcon(icon8);
        actionNetworkParametrization = new QAction(SVGeometryView);
        actionNetworkParametrization->setObjectName(QString::fromUtf8("actionNetworkParametrization"));
        actionNetworkParametrization->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/gfx/icons8/icons8-netzdiagramm-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetworkParametrization->setIcon(icon9);
        actionSiteParametrization = new QAction(SVGeometryView);
        actionSiteParametrization->setObjectName(QString::fromUtf8("actionSiteParametrization"));
        actionSiteParametrization->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/gfx/icons8/icons8-gitter-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSiteParametrization->setIcon(icon10);
        actionAcousticParametrization = new QAction(SVGeometryView);
        actionAcousticParametrization->setObjectName(QString::fromUtf8("actionAcousticParametrization"));
        actionAcousticParametrization->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/gfx/icons8/icons8-audiowelle-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAcousticParametrization->setIcon(icon11);
        actionShowResults = new QAction(SVGeometryView);
        actionShowResults->setObjectName(QString::fromUtf8("actionShowResults"));
        actionShowResults->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/gfx/icons8/icons8-futures-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowResults->setIcon(icon12);
        actionStructuralUnits = new QAction(SVGeometryView);
        actionStructuralUnits->setObjectName(QString::fromUtf8("actionStructuralUnits"));
        actionStructuralUnits->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/gfx/icons8/icons8-box-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStructuralUnits->setIcon(icon13);
        mainLayout = new QVBoxLayout(SVGeometryView);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        splitter = new QSplitter(SVGeometryView);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sceneVBoxLayout = new QVBoxLayout();
        sceneVBoxLayout->setObjectName(QString::fromUtf8("sceneVBoxLayout"));
        widgetSceneViewDummy = new QWidget(layoutWidget);
        widgetSceneViewDummy->setObjectName(QString::fromUtf8("widgetSceneViewDummy"));
        sizePolicy.setHeightForWidth(widgetSceneViewDummy->sizePolicy().hasHeightForWidth());
        widgetSceneViewDummy->setSizePolicy(sizePolicy);
        widgetSceneViewDummy->setMinimumSize(QSize(500, 0));

        sceneVBoxLayout->addWidget(widgetSceneViewDummy);

        geometryToolBar = new QToolBar(layoutWidget);
        geometryToolBar->setObjectName(QString::fromUtf8("geometryToolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(geometryToolBar->sizePolicy().hasHeightForWidth());
        geometryToolBar->setSizePolicy(sizePolicy1);
        geometryToolBar->setMinimumSize(QSize(10, 10));
        geometryToolBar->setMaximumSize(QSize(16777215, 32));
        geometryToolBar->setMovable(false);
        geometryToolBar->setFloatable(false);

        sceneVBoxLayout->addWidget(geometryToolBar);


        horizontalLayout->addLayout(sceneVBoxLayout);

        modeSelectionToolBar = new QToolBar(layoutWidget);
        modeSelectionToolBar->setObjectName(QString::fromUtf8("modeSelectionToolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(modeSelectionToolBar->sizePolicy().hasHeightForWidth());
        modeSelectionToolBar->setSizePolicy(sizePolicy2);
        modeSelectionToolBar->setMinimumSize(QSize(0, 0));
        modeSelectionToolBar->setMaximumSize(QSize(48, 16777215));
        modeSelectionToolBar->setMovable(false);
        modeSelectionToolBar->setOrientation(Qt::Vertical);
        modeSelectionToolBar->setIconSize(QSize(32, 32));
        modeSelectionToolBar->setFloatable(false);

        horizontalLayout->addWidget(modeSelectionToolBar);

        splitter->addWidget(layoutWidget);
        propertyWidget = new SVPropertyWidget(splitter);
        propertyWidget->setObjectName(QString::fromUtf8("propertyWidget"));
        splitter->addWidget(propertyWidget);

        mainLayout->addWidget(splitter);


        geometryToolBar->addAction(actionSnap);
        geometryToolBar->addSeparator();
        geometryToolBar->addAction(actionMeasure);
        geometryToolBar->addSeparator();
        geometryToolBar->addAction(actionXLock);
        geometryToolBar->addAction(actionYLock);
        geometryToolBar->addAction(actionZLock);
        modeSelectionToolBar->addAction(actionAddGeometry);
        modeSelectionToolBar->addSeparator();
        modeSelectionToolBar->addAction(actionTranslateGeometry);
        modeSelectionToolBar->addAction(actionRotateGeometry);
        modeSelectionToolBar->addAction(actionScaleGeometry);
        modeSelectionToolBar->addSeparator();
        modeSelectionToolBar->addAction(actionAlignGeometry);
        modeSelectionToolBar->addAction(actionCopyGeometry);
        modeSelectionToolBar->addSeparator();
        modeSelectionToolBar->addAction(actionBuildingParametrization);
        modeSelectionToolBar->addAction(actionAcousticParametrization);
        modeSelectionToolBar->addAction(actionStructuralUnits);
        modeSelectionToolBar->addSeparator();
        modeSelectionToolBar->addAction(actionNetworkParametrization);
        modeSelectionToolBar->addAction(actionSiteParametrization);
        modeSelectionToolBar->addSeparator();
        modeSelectionToolBar->addAction(actionShowResults);

        retranslateUi(SVGeometryView);

        QMetaObject::connectSlotsByName(SVGeometryView);
    } // setupUi

    void retranslateUi(QWidget *SVGeometryView)
    {
        SVGeometryView->setWindowTitle(QCoreApplication::translate("SVGeometryView", "Form", nullptr));
        actionSnap->setText(QCoreApplication::translate("SVGeometryView", "Snap", nullptr));
#if QT_CONFIG(tooltip)
        actionSnap->setToolTip(QCoreApplication::translate("SVGeometryView", "Toggles object snap on/off (F3)", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMeasure->setText(QCoreApplication::translate("SVGeometryView", "Measure", nullptr));
#if QT_CONFIG(tooltip)
        actionMeasure->setToolTip(QCoreApplication::translate("SVGeometryView", "Toggles distance measurement mode on/off", nullptr));
#endif // QT_CONFIG(tooltip)
        actionXLock->setText(QCoreApplication::translate("SVGeometryView", "X", nullptr));
        actionYLock->setText(QCoreApplication::translate("SVGeometryView", "Y", nullptr));
        actionZLock->setText(QCoreApplication::translate("SVGeometryView", "Z", nullptr));
#if QT_CONFIG(tooltip)
        actionZLock->setToolTip(QCoreApplication::translate("SVGeometryView", "Z", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddGeometry->setText(QCoreApplication::translate("SVGeometryView", "Add geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionAddGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Add geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTranslateGeometry->setText(QCoreApplication::translate("SVGeometryView", "Translate geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionTranslateGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Move geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRotateGeometry->setText(QCoreApplication::translate("SVGeometryView", "Rotate geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionRotateGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Rotate geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionScaleGeometry->setText(QCoreApplication::translate("SVGeometryView", "Rotate geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionScaleGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Scale geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAlignGeometry->setText(QCoreApplication::translate("SVGeometryView", "Align geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionAlignGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Align geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCopyGeometry->setText(QCoreApplication::translate("SVGeometryView", "Copy geometry", nullptr));
#if QT_CONFIG(tooltip)
        actionCopyGeometry->setToolTip(QCoreApplication::translate("SVGeometryView", "Switches to \"Copy geometry\" property view", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBuildingParametrization->setText(QCoreApplication::translate("SVGeometryView", "Edit Building Parametrization", nullptr));
#if QT_CONFIG(tooltip)
        actionBuildingParametrization->setToolTip(QCoreApplication::translate("SVGeometryView", "Edit Building Parametrization", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNetworkParametrization->setText(QCoreApplication::translate("SVGeometryView", "Edit Network Parametrization", nullptr));
#if QT_CONFIG(tooltip)
        actionNetworkParametrization->setToolTip(QCoreApplication::translate("SVGeometryView", "Edit Network Parametrization", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSiteParametrization->setText(QCoreApplication::translate("SVGeometryView", "actionSiteParametrization", nullptr));
#if QT_CONFIG(tooltip)
        actionSiteParametrization->setToolTip(QCoreApplication::translate("SVGeometryView", "Edit Site Parametrization", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAcousticParametrization->setText(QCoreApplication::translate("SVGeometryView", "Acoustic parametrization", nullptr));
#if QT_CONFIG(tooltip)
        actionAcousticParametrization->setToolTip(QCoreApplication::translate("SVGeometryView", "Acoustic parametrization", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShowResults->setText(QCoreApplication::translate("SVGeometryView", "Show Results", nullptr));
#if QT_CONFIG(tooltip)
        actionShowResults->setToolTip(QCoreApplication::translate("SVGeometryView", "Show Results", nullptr));
#endif // QT_CONFIG(tooltip)
        actionStructuralUnits->setText(QCoreApplication::translate("SVGeometryView", "Structural units parametrization", nullptr));
#if QT_CONFIG(tooltip)
        actionStructuralUnits->setToolTip(QCoreApplication::translate("SVGeometryView", "Structural unit parametrization", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class SVGeometryView: public Ui_SVGeometryView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVGEOMETRYVIEW_H
