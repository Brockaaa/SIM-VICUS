/********************************************************************************
** Form generated from reading UI file 'SVPropEditGeometry.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPEDITGEOMETRY_H
#define UI_SVPROPEDITGEOMETRY_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropEditGeometry
{
public:
    QVBoxLayout *verticalLayoutMaster;
    QStackedWidget *stackedWidget;
    QWidget *pageTranslation;
    QVBoxLayout *verticalLayoutTrans;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonTranslationAbsolute;
    QRadioButton *radioButtonTranslationRelative;
    QRadioButton *radioButtonTranslationRelativeLCS;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTranslateX;
    QtExt::ValidatingLineEdit *lineEditTranslateX;
    QLabel *labelTranslateY;
    QtExt::ValidatingLineEdit *lineEditTranslateY;
    QLabel *labelTranslateZ;
    QtExt::ValidatingLineEdit *lineEditTranslateZ;
    QWidget *pageRotation;
    QVBoxLayout *verticalLayoutRot;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QLabel *labelRotateInclinationAbs;
    QLabel *labelRotationY;
    QtExt::ValidatingLineEdit *lineEditRotateY;
    QtExt::ValidatingLineEdit *lineEditRotateOrientation;
    QtExt::ValidatingLineEdit *lineEditRotateX;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButtonRotationAlignToAngles;
    QRadioButton *radioButtonRotationRelative;
    QtExt::ValidatingLineEdit *lineEditRotateZ;
    QSpacerItem *verticalSpacer_6;
    QLabel *labelRotateOrientationAbs;
    QLabel *labelRotationZ;
    QtExt::ValidatingLineEdit *lineEditRotateInclination;
    QLabel *labelRotationX;
    QPushButton *pushButtonThreePointRotation;
    QSpacerItem *verticalSpacer_7;
    QWidget *pageScaling;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButtonScaleResize;
    QRadioButton *radioButtonScaleFactor;
    QCheckBox *checkBoxKeepAspectRatio;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelScaleX;
    QtExt::ValidatingLineEdit *lineEditScaleX;
    QLabel *labelScaleY;
    QtExt::ValidatingLineEdit *lineEditScaleY;
    QLabel *labelScaleZ;
    QtExt::ValidatingLineEdit *lineEditScaleZ;
    QLabel *label_2;
    QWidget *pageAlignment;
    QVBoxLayout *verticalLayoutAlign;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButtonCenterHorizontally;
    QPushButton *pushButtonCenterVertically;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pushButtonFlipNormals;
    QPushButton *pushButtonFixSurfaceOrientation;
    QWidget *pageCopy;
    QVBoxLayout *verticalLayoutCopy;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *pushButtonCopyBuilding;
    QPushButton *pushButtonCopyBuildingLevel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelScaleX_2;
    QtExt::ValidatingLineEdit *lineEditCopyX;
    QLabel *labelScaleY_2;
    QtExt::ValidatingLineEdit *lineEditCopyY;
    QLabel *labelScaleZ_2;
    QtExt::ValidatingLineEdit *lineEditCopyZ;
    QPushButton *pushButtonCopySurface;
    QPushButton *pushButtonCopyRoom;
    QPushButton *pushButtonCopySubsurface;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonApply;
    QPushButton *pushButtonCancel;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVPropEditGeometry)
    {
        if (SVPropEditGeometry->objectName().isEmpty())
            SVPropEditGeometry->setObjectName(QString::fromUtf8("SVPropEditGeometry"));
        SVPropEditGeometry->resize(505, 500);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVPropEditGeometry->sizePolicy().hasHeightForWidth());
        SVPropEditGeometry->setSizePolicy(sizePolicy);
        verticalLayoutMaster = new QVBoxLayout(SVPropEditGeometry);
        verticalLayoutMaster->setObjectName(QString::fromUtf8("verticalLayoutMaster"));
        stackedWidget = new QStackedWidget(SVPropEditGeometry);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        pageTranslation = new QWidget();
        pageTranslation->setObjectName(QString::fromUtf8("pageTranslation"));
        verticalLayoutTrans = new QVBoxLayout(pageTranslation);
        verticalLayoutTrans->setObjectName(QString::fromUtf8("verticalLayoutTrans"));
        groupBox = new QGroupBox(pageTranslation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButtonTranslationAbsolute = new QRadioButton(groupBox);
        radioButtonTranslationAbsolute->setObjectName(QString::fromUtf8("radioButtonTranslationAbsolute"));

        verticalLayout->addWidget(radioButtonTranslationAbsolute);

        radioButtonTranslationRelative = new QRadioButton(groupBox);
        radioButtonTranslationRelative->setObjectName(QString::fromUtf8("radioButtonTranslationRelative"));
        radioButtonTranslationRelative->setChecked(false);

        verticalLayout->addWidget(radioButtonTranslationRelative);

        radioButtonTranslationRelativeLCS = new QRadioButton(groupBox);
        radioButtonTranslationRelativeLCS->setObjectName(QString::fromUtf8("radioButtonTranslationRelativeLCS"));
        radioButtonTranslationRelativeLCS->setChecked(true);

        verticalLayout->addWidget(radioButtonTranslationRelativeLCS);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelTranslateX = new QLabel(groupBox);
        labelTranslateX->setObjectName(QString::fromUtf8("labelTranslateX"));
        labelTranslateX->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(labelTranslateX);

        lineEditTranslateX = new QtExt::ValidatingLineEdit(groupBox);
        lineEditTranslateX->setObjectName(QString::fromUtf8("lineEditTranslateX"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditTranslateX->sizePolicy().hasHeightForWidth());
        lineEditTranslateX->setSizePolicy(sizePolicy2);
        lineEditTranslateX->setMinimumSize(QSize(50, 0));
        lineEditTranslateX->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEditTranslateX);

        labelTranslateY = new QLabel(groupBox);
        labelTranslateY->setObjectName(QString::fromUtf8("labelTranslateY"));
        labelTranslateY->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(labelTranslateY);

        lineEditTranslateY = new QtExt::ValidatingLineEdit(groupBox);
        lineEditTranslateY->setObjectName(QString::fromUtf8("lineEditTranslateY"));
        sizePolicy2.setHeightForWidth(lineEditTranslateY->sizePolicy().hasHeightForWidth());
        lineEditTranslateY->setSizePolicy(sizePolicy2);
        lineEditTranslateY->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(lineEditTranslateY);

        labelTranslateZ = new QLabel(groupBox);
        labelTranslateZ->setObjectName(QString::fromUtf8("labelTranslateZ"));
        labelTranslateZ->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(labelTranslateZ);

        lineEditTranslateZ = new QtExt::ValidatingLineEdit(groupBox);
        lineEditTranslateZ->setObjectName(QString::fromUtf8("lineEditTranslateZ"));
        sizePolicy2.setHeightForWidth(lineEditTranslateZ->sizePolicy().hasHeightForWidth());
        lineEditTranslateZ->setSizePolicy(sizePolicy2);
        lineEditTranslateZ->setMinimumSize(QSize(50, 0));

        horizontalLayout->addWidget(lineEditTranslateZ);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayoutTrans->addWidget(groupBox);

        stackedWidget->addWidget(pageTranslation);
        pageRotation = new QWidget();
        pageRotation->setObjectName(QString::fromUtf8("pageRotation"));
        verticalLayoutRot = new QVBoxLayout(pageRotation);
        verticalLayoutRot->setObjectName(QString::fromUtf8("verticalLayoutRot"));
        groupBox_3 = new QGroupBox(pageRotation);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        labelRotateInclinationAbs = new QLabel(groupBox_3);
        labelRotateInclinationAbs->setObjectName(QString::fromUtf8("labelRotateInclinationAbs"));
        labelRotateInclinationAbs->setEnabled(true);

        gridLayout_5->addWidget(labelRotateInclinationAbs, 2, 0, 1, 1);

        labelRotationY = new QLabel(groupBox_3);
        labelRotationY->setObjectName(QString::fromUtf8("labelRotationY"));
        labelRotationY->setMinimumSize(QSize(0, 0));

        gridLayout_5->addWidget(labelRotationY, 4, 0, 1, 1);

        lineEditRotateY = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditRotateY->setObjectName(QString::fromUtf8("lineEditRotateY"));
        sizePolicy2.setHeightForWidth(lineEditRotateY->sizePolicy().hasHeightForWidth());
        lineEditRotateY->setSizePolicy(sizePolicy2);
        lineEditRotateY->setMinimumSize(QSize(50, 0));

        gridLayout_5->addWidget(lineEditRotateY, 4, 1, 1, 1);

        lineEditRotateOrientation = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditRotateOrientation->setObjectName(QString::fromUtf8("lineEditRotateOrientation"));
        lineEditRotateOrientation->setEnabled(true);

        gridLayout_5->addWidget(lineEditRotateOrientation, 1, 1, 1, 1);

        lineEditRotateX = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditRotateX->setObjectName(QString::fromUtf8("lineEditRotateX"));
        sizePolicy2.setHeightForWidth(lineEditRotateX->sizePolicy().hasHeightForWidth());
        lineEditRotateX->setSizePolicy(sizePolicy2);
        lineEditRotateX->setMinimumSize(QSize(50, 0));
        lineEditRotateX->setClearButtonEnabled(false);

        gridLayout_5->addWidget(lineEditRotateX, 3, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButtonRotationAlignToAngles = new QRadioButton(groupBox_3);
        radioButtonRotationAlignToAngles->setObjectName(QString::fromUtf8("radioButtonRotationAlignToAngles"));

        horizontalLayout_6->addWidget(radioButtonRotationAlignToAngles);

        radioButtonRotationRelative = new QRadioButton(groupBox_3);
        radioButtonRotationRelative->setObjectName(QString::fromUtf8("radioButtonRotationRelative"));
        radioButtonRotationRelative->setChecked(true);

        horizontalLayout_6->addWidget(radioButtonRotationRelative);


        gridLayout_5->addLayout(horizontalLayout_6, 0, 0, 1, 2);

        lineEditRotateZ = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditRotateZ->setObjectName(QString::fromUtf8("lineEditRotateZ"));
        sizePolicy2.setHeightForWidth(lineEditRotateZ->sizePolicy().hasHeightForWidth());
        lineEditRotateZ->setSizePolicy(sizePolicy2);
        lineEditRotateZ->setMinimumSize(QSize(50, 0));

        gridLayout_5->addWidget(lineEditRotateZ, 5, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_5->addItem(verticalSpacer_6, 6, 1, 1, 1);

        labelRotateOrientationAbs = new QLabel(groupBox_3);
        labelRotateOrientationAbs->setObjectName(QString::fromUtf8("labelRotateOrientationAbs"));
        labelRotateOrientationAbs->setEnabled(true);

        gridLayout_5->addWidget(labelRotateOrientationAbs, 1, 0, 1, 1);

        labelRotationZ = new QLabel(groupBox_3);
        labelRotationZ->setObjectName(QString::fromUtf8("labelRotationZ"));
        labelRotationZ->setMinimumSize(QSize(0, 0));

        gridLayout_5->addWidget(labelRotationZ, 5, 0, 1, 1);

        lineEditRotateInclination = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditRotateInclination->setObjectName(QString::fromUtf8("lineEditRotateInclination"));
        lineEditRotateInclination->setEnabled(true);

        gridLayout_5->addWidget(lineEditRotateInclination, 2, 1, 1, 1);

        labelRotationX = new QLabel(groupBox_3);
        labelRotationX->setObjectName(QString::fromUtf8("labelRotationX"));
        labelRotationX->setMinimumSize(QSize(0, 0));

        gridLayout_5->addWidget(labelRotationX, 3, 0, 1, 1);

        pushButtonThreePointRotation = new QPushButton(groupBox_3);
        pushButtonThreePointRotation->setObjectName(QString::fromUtf8("pushButtonThreePointRotation"));

        gridLayout_5->addWidget(pushButtonThreePointRotation, 7, 0, 1, 2);


        verticalLayoutRot->addWidget(groupBox_3);

        verticalSpacer_7 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayoutRot->addItem(verticalSpacer_7);

        stackedWidget->addWidget(pageRotation);
        pageScaling = new QWidget();
        pageScaling->setObjectName(QString::fromUtf8("pageScaling"));
        verticalLayout_2 = new QVBoxLayout(pageScaling);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_6 = new QGroupBox(pageScaling);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        radioButtonScaleResize = new QRadioButton(groupBox_6);
        radioButtonScaleResize->setObjectName(QString::fromUtf8("radioButtonScaleResize"));

        horizontalLayout_7->addWidget(radioButtonScaleResize);

        radioButtonScaleFactor = new QRadioButton(groupBox_6);
        radioButtonScaleFactor->setObjectName(QString::fromUtf8("radioButtonScaleFactor"));
        radioButtonScaleFactor->setChecked(true);

        horizontalLayout_7->addWidget(radioButtonScaleFactor);


        gridLayout_2->addLayout(horizontalLayout_7, 0, 0, 1, 1);

        checkBoxKeepAspectRatio = new QCheckBox(groupBox_6);
        checkBoxKeepAspectRatio->setObjectName(QString::fromUtf8("checkBoxKeepAspectRatio"));

        gridLayout_2->addWidget(checkBoxKeepAspectRatio, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        labelScaleX = new QLabel(groupBox_6);
        labelScaleX->setObjectName(QString::fromUtf8("labelScaleX"));
        labelScaleX->setMinimumSize(QSize(0, 0));

        horizontalLayout_8->addWidget(labelScaleX);

        lineEditScaleX = new QtExt::ValidatingLineEdit(groupBox_6);
        lineEditScaleX->setObjectName(QString::fromUtf8("lineEditScaleX"));
        sizePolicy2.setHeightForWidth(lineEditScaleX->sizePolicy().hasHeightForWidth());
        lineEditScaleX->setSizePolicy(sizePolicy2);
        lineEditScaleX->setMinimumSize(QSize(50, 0));
        lineEditScaleX->setClearButtonEnabled(false);

        horizontalLayout_8->addWidget(lineEditScaleX);

        labelScaleY = new QLabel(groupBox_6);
        labelScaleY->setObjectName(QString::fromUtf8("labelScaleY"));
        labelScaleY->setMinimumSize(QSize(0, 0));

        horizontalLayout_8->addWidget(labelScaleY);

        lineEditScaleY = new QtExt::ValidatingLineEdit(groupBox_6);
        lineEditScaleY->setObjectName(QString::fromUtf8("lineEditScaleY"));
        sizePolicy2.setHeightForWidth(lineEditScaleY->sizePolicy().hasHeightForWidth());
        lineEditScaleY->setSizePolicy(sizePolicy2);
        lineEditScaleY->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(lineEditScaleY);

        labelScaleZ = new QLabel(groupBox_6);
        labelScaleZ->setObjectName(QString::fromUtf8("labelScaleZ"));
        labelScaleZ->setMinimumSize(QSize(0, 0));

        horizontalLayout_8->addWidget(labelScaleZ);

        lineEditScaleZ = new QtExt::ValidatingLineEdit(groupBox_6);
        lineEditScaleZ->setObjectName(QString::fromUtf8("lineEditScaleZ"));
        sizePolicy2.setHeightForWidth(lineEditScaleZ->sizePolicy().hasHeightForWidth());
        lineEditScaleZ->setSizePolicy(sizePolicy2);
        lineEditScaleZ->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(lineEditScaleZ);


        gridLayout_2->addLayout(horizontalLayout_8, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_6);

        label_2 = new QLabel(pageScaling);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setItalic(true);
        label_2->setFont(font);
        label_2->setWordWrap(true);

        verticalLayout_2->addWidget(label_2);

        stackedWidget->addWidget(pageScaling);
        pageAlignment = new QWidget();
        pageAlignment->setObjectName(QString::fromUtf8("pageAlignment"));
        sizePolicy.setHeightForWidth(pageAlignment->sizePolicy().hasHeightForWidth());
        pageAlignment->setSizePolicy(sizePolicy);
        verticalLayoutAlign = new QVBoxLayout(pageAlignment);
        verticalLayoutAlign->setObjectName(QString::fromUtf8("verticalLayoutAlign"));
        groupBox_7 = new QGroupBox(pageAlignment);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        sizePolicy1.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy1);
        verticalLayout_8 = new QVBoxLayout(groupBox_7);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pushButtonCenterHorizontally = new QPushButton(groupBox_7);
        pushButtonCenterHorizontally->setObjectName(QString::fromUtf8("pushButtonCenterHorizontally"));

        verticalLayout_8->addWidget(pushButtonCenterHorizontally);

        pushButtonCenterVertically = new QPushButton(groupBox_7);
        pushButtonCenterVertically->setObjectName(QString::fromUtf8("pushButtonCenterVertically"));

        verticalLayout_8->addWidget(pushButtonCenterVertically);


        verticalLayoutAlign->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(pageAlignment);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        sizePolicy1.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy1);
        verticalLayout_9 = new QVBoxLayout(groupBox_8);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pushButtonFlipNormals = new QPushButton(groupBox_8);
        pushButtonFlipNormals->setObjectName(QString::fromUtf8("pushButtonFlipNormals"));

        verticalLayout_9->addWidget(pushButtonFlipNormals);

        pushButtonFixSurfaceOrientation = new QPushButton(groupBox_8);
        pushButtonFixSurfaceOrientation->setObjectName(QString::fromUtf8("pushButtonFixSurfaceOrientation"));

        verticalLayout_9->addWidget(pushButtonFixSurfaceOrientation);


        verticalLayoutAlign->addWidget(groupBox_8);

        stackedWidget->addWidget(pageAlignment);
        pageCopy = new QWidget();
        pageCopy->setObjectName(QString::fromUtf8("pageCopy"));
        verticalLayoutCopy = new QVBoxLayout(pageCopy);
        verticalLayoutCopy->setObjectName(QString::fromUtf8("verticalLayoutCopy"));
        groupBox_2 = new QGroupBox(pageCopy);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonCopyBuilding = new QPushButton(groupBox_2);
        pushButtonCopyBuilding->setObjectName(QString::fromUtf8("pushButtonCopyBuilding"));

        gridLayout->addWidget(pushButtonCopyBuilding, 3, 2, 1, 1);

        pushButtonCopyBuildingLevel = new QPushButton(groupBox_2);
        pushButtonCopyBuildingLevel->setObjectName(QString::fromUtf8("pushButtonCopyBuildingLevel"));

        gridLayout->addWidget(pushButtonCopyBuildingLevel, 3, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelScaleX_2 = new QLabel(groupBox_2);
        labelScaleX_2->setObjectName(QString::fromUtf8("labelScaleX_2"));
        labelScaleX_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(labelScaleX_2);

        lineEditCopyX = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditCopyX->setObjectName(QString::fromUtf8("lineEditCopyX"));
        sizePolicy2.setHeightForWidth(lineEditCopyX->sizePolicy().hasHeightForWidth());
        lineEditCopyX->setSizePolicy(sizePolicy2);
        lineEditCopyX->setMinimumSize(QSize(50, 0));
        lineEditCopyX->setClearButtonEnabled(false);

        horizontalLayout_4->addWidget(lineEditCopyX);

        labelScaleY_2 = new QLabel(groupBox_2);
        labelScaleY_2->setObjectName(QString::fromUtf8("labelScaleY_2"));
        labelScaleY_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(labelScaleY_2);

        lineEditCopyY = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditCopyY->setObjectName(QString::fromUtf8("lineEditCopyY"));
        sizePolicy2.setHeightForWidth(lineEditCopyY->sizePolicy().hasHeightForWidth());
        lineEditCopyY->setSizePolicy(sizePolicy2);
        lineEditCopyY->setMinimumSize(QSize(50, 0));

        horizontalLayout_4->addWidget(lineEditCopyY);

        labelScaleZ_2 = new QLabel(groupBox_2);
        labelScaleZ_2->setObjectName(QString::fromUtf8("labelScaleZ_2"));
        labelScaleZ_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(labelScaleZ_2);

        lineEditCopyZ = new QtExt::ValidatingLineEdit(groupBox_2);
        lineEditCopyZ->setObjectName(QString::fromUtf8("lineEditCopyZ"));
        sizePolicy2.setHeightForWidth(lineEditCopyZ->sizePolicy().hasHeightForWidth());
        lineEditCopyZ->setSizePolicy(sizePolicy2);
        lineEditCopyZ->setMinimumSize(QSize(50, 0));

        horizontalLayout_4->addWidget(lineEditCopyZ);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 3);

        pushButtonCopySurface = new QPushButton(groupBox_2);
        pushButtonCopySurface->setObjectName(QString::fromUtf8("pushButtonCopySurface"));

        gridLayout->addWidget(pushButtonCopySurface, 2, 0, 1, 1);

        pushButtonCopyRoom = new QPushButton(groupBox_2);
        pushButtonCopyRoom->setObjectName(QString::fromUtf8("pushButtonCopyRoom"));

        gridLayout->addWidget(pushButtonCopyRoom, 3, 0, 1, 1);

        pushButtonCopySubsurface = new QPushButton(groupBox_2);
        pushButtonCopySubsurface->setObjectName(QString::fromUtf8("pushButtonCopySubsurface"));

        gridLayout->addWidget(pushButtonCopySubsurface, 2, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 3);


        verticalLayoutCopy->addWidget(groupBox_2);

        stackedWidget->addWidget(pageCopy);

        verticalLayoutMaster->addWidget(stackedWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonApply = new QPushButton(SVPropEditGeometry);
        pushButtonApply->setObjectName(QString::fromUtf8("pushButtonApply"));

        horizontalLayout_3->addWidget(pushButtonApply);

        pushButtonCancel = new QPushButton(SVPropEditGeometry);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_3->addWidget(pushButtonCancel);


        verticalLayoutMaster->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutMaster->addItem(verticalSpacer_3);

        QWidget::setTabOrder(lineEditTranslateX, lineEditTranslateY);
        QWidget::setTabOrder(lineEditTranslateY, lineEditTranslateZ);
        QWidget::setTabOrder(lineEditTranslateZ, radioButtonRotationAlignToAngles);
        QWidget::setTabOrder(radioButtonRotationAlignToAngles, radioButtonRotationRelative);
        QWidget::setTabOrder(radioButtonRotationRelative, lineEditRotateOrientation);
        QWidget::setTabOrder(lineEditRotateOrientation, lineEditRotateInclination);
        QWidget::setTabOrder(lineEditRotateInclination, lineEditRotateX);
        QWidget::setTabOrder(lineEditRotateX, lineEditRotateY);
        QWidget::setTabOrder(lineEditRotateY, lineEditRotateZ);
        QWidget::setTabOrder(lineEditRotateZ, pushButtonThreePointRotation);
        QWidget::setTabOrder(pushButtonThreePointRotation, radioButtonScaleResize);
        QWidget::setTabOrder(radioButtonScaleResize, radioButtonScaleFactor);
        QWidget::setTabOrder(radioButtonScaleFactor, lineEditScaleX);
        QWidget::setTabOrder(lineEditScaleX, lineEditScaleY);
        QWidget::setTabOrder(lineEditScaleY, lineEditScaleZ);
        QWidget::setTabOrder(lineEditScaleZ, pushButtonCenterHorizontally);
        QWidget::setTabOrder(pushButtonCenterHorizontally, pushButtonCenterVertically);
        QWidget::setTabOrder(pushButtonCenterVertically, lineEditCopyX);
        QWidget::setTabOrder(lineEditCopyX, lineEditCopyY);
        QWidget::setTabOrder(lineEditCopyY, lineEditCopyZ);
        QWidget::setTabOrder(lineEditCopyZ, pushButtonCopySurface);
        QWidget::setTabOrder(pushButtonCopySurface, pushButtonCopySubsurface);
        QWidget::setTabOrder(pushButtonCopySubsurface, pushButtonCopyRoom);
        QWidget::setTabOrder(pushButtonCopyRoom, pushButtonCopyBuildingLevel);
        QWidget::setTabOrder(pushButtonCopyBuildingLevel, pushButtonCopyBuilding);
        QWidget::setTabOrder(pushButtonCopyBuilding, pushButtonApply);
        QWidget::setTabOrder(pushButtonApply, pushButtonCancel);

        retranslateUi(SVPropEditGeometry);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVPropEditGeometry);
    } // setupUi

    void retranslateUi(QWidget *SVPropEditGeometry)
    {
        groupBox->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Move selected geometry", nullptr));
        radioButtonTranslationAbsolute->setText(QCoreApplication::translate("SVPropEditGeometry", "Move to world coordinates", nullptr));
        radioButtonTranslationRelative->setText(QCoreApplication::translate("SVPropEditGeometry", "Relative to world coordinates", nullptr));
        radioButtonTranslationRelativeLCS->setText(QCoreApplication::translate("SVPropEditGeometry", "Relative to local coordinates", nullptr));
        labelTranslateX->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224X", nullptr));
        labelTranslateY->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Y", nullptr));
        labelTranslateZ->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Z", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Rotate selected geometry", nullptr));
        labelRotateInclinationAbs->setText(QCoreApplication::translate("SVPropEditGeometry", "Inclination [\302\260]:", nullptr));
        labelRotationY->setText(QCoreApplication::translate("SVPropEditGeometry", "Rotation around local Y-Axis [\302\260]:", nullptr));
        radioButtonRotationAlignToAngles->setText(QCoreApplication::translate("SVPropEditGeometry", "Align surface to angles", nullptr));
        radioButtonRotationRelative->setText(QCoreApplication::translate("SVPropEditGeometry", "Relative rotation", nullptr));
        labelRotateOrientationAbs->setText(QCoreApplication::translate("SVPropEditGeometry", "Orientation [\302\260]:", nullptr));
        labelRotationZ->setText(QCoreApplication::translate("SVPropEditGeometry", "Rotation around local Z-Axis [\302\260]:", nullptr));
        labelRotationX->setText(QCoreApplication::translate("SVPropEditGeometry", "Rotation around local X-Axis [\302\260]:", nullptr));
        pushButtonThreePointRotation->setText(QCoreApplication::translate("SVPropEditGeometry", "Interactive three-point rotation", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Scale selected geometry", nullptr));
        radioButtonScaleResize->setText(QCoreApplication::translate("SVPropEditGeometry", "Resize geometry", nullptr));
        radioButtonScaleFactor->setText(QCoreApplication::translate("SVPropEditGeometry", "Scale by factor", nullptr));
        checkBoxKeepAspectRatio->setText(QCoreApplication::translate("SVPropEditGeometry", "Keep aspect ratio", nullptr));
        labelScaleX->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224X", nullptr));
        labelScaleY->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Y", nullptr));
        labelScaleZ->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Z", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropEditGeometry", "To change scaling factors of DXF-drawing, double-click on layer in Navigation Tree on the left-side pane", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Align geometry", nullptr));
        pushButtonCenterHorizontally->setText(QCoreApplication::translate("SVPropEditGeometry", "Center objects horizontally", nullptr));
        pushButtonCenterVertically->setText(QCoreApplication::translate("SVPropEditGeometry", "Center objects vertically", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Surface orientation", nullptr));
        pushButtonFlipNormals->setText(QCoreApplication::translate("SVPropEditGeometry", "Flip surface normals", nullptr));
        pushButtonFixSurfaceOrientation->setText(QCoreApplication::translate("SVPropEditGeometry", "Fix surface orientation (pointing outside)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVPropEditGeometry", "Copy selected geometry", nullptr));
        pushButtonCopyBuilding->setText(QCoreApplication::translate("SVPropEditGeometry", "Buildings", nullptr));
        pushButtonCopyBuildingLevel->setText(QCoreApplication::translate("SVPropEditGeometry", "Building levels", nullptr));
        labelScaleX_2->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224X", nullptr));
        labelScaleY_2->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Y", nullptr));
        labelScaleZ_2->setText(QCoreApplication::translate("SVPropEditGeometry", "\316\224Z", nullptr));
        pushButtonCopySurface->setText(QCoreApplication::translate("SVPropEditGeometry", "Surfaces", nullptr));
        pushButtonCopyRoom->setText(QCoreApplication::translate("SVPropEditGeometry", "Rooms", nullptr));
        pushButtonCopySubsurface->setText(QCoreApplication::translate("SVPropEditGeometry", "Windows/Doors", nullptr));
        label->setText(QCoreApplication::translate("SVPropEditGeometry", "Enter translation with respect to local coordinate system.", nullptr));
        pushButtonApply->setText(QCoreApplication::translate("SVPropEditGeometry", "Apply", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SVPropEditGeometry", "Cancel", nullptr));
        (void)SVPropEditGeometry;
    } // retranslateUi

};

namespace Ui {
    class SVPropEditGeometry: public Ui_SVPropEditGeometry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPEDITGEOMETRY_H
