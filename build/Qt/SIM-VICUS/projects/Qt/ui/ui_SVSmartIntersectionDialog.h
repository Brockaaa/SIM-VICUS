/********************************************************************************
** Form generated from reading UI file 'SVSmartIntersectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSMARTINTERSECTIONDIALOG_H
#define UI_SVSMARTINTERSECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVSmartIntersectionDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QGroupBox *groupBoxProjectSelection;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonEntireProject;
    QRadioButton *radioButtonSelectedGeometry;
    QCheckBox *checkBoxDetailledSettings;
    QFrame *line_2;
    QGroupBox *groupBoxDetailled;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QtExt::ValidatingLineEdit *lineEditConnectSurfacesMaxDistance;
    QLabel *label;
    QLabel *label_10;
    QtExt::ValidatingLineEdit *lineEditConnectSurfacesMaxAngle;
    QLabel *label_2;
    QFrame *line;
    QCheckBox *checkBoxCreateComp;
    QCheckBox *checkBoxReplaceComponentInstances;
    QGroupBox *groupBoxComponents;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QToolButton *toolButtonSelectFloor;
    QToolButton *toolButtonSelectCeiling;
    QLineEdit *lineEditExteriorWallName;
    QToolButton *toolButtonSelectInteriorWall;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *lineEditFloorName;
    QToolButton *toolButtonSelectExteriorWall;
    QLineEdit *lineEditCeilingName;
    QLabel *label_6;
    QToolButton *toolButtonSelectRoof;
    QLineEdit *lineEditInteriorWallName;
    QLineEdit *lineEditRoofName;
    QPushButton *pushButtonStartClipping;
    QGroupBox *groupBoxLog;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonApply;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SVSmartIntersectionDialog)
    {
        if (SVSmartIntersectionDialog->objectName().isEmpty())
            SVSmartIntersectionDialog->setObjectName(QString::fromUtf8("SVSmartIntersectionDialog"));
        SVSmartIntersectionDialog->resize(1002, 788);
        verticalLayout_2 = new QVBoxLayout(SVSmartIntersectionDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_8 = new QLabel(SVSmartIntersectionDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font;
        font.setItalic(true);
        label_8->setFont(font);
        label_8->setWordWrap(true);

        verticalLayout_2->addWidget(label_8);

        groupBoxProjectSelection = new QGroupBox(SVSmartIntersectionDialog);
        groupBoxProjectSelection->setObjectName(QString::fromUtf8("groupBoxProjectSelection"));
        gridLayout_3 = new QGridLayout(groupBoxProjectSelection);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButtonEntireProject = new QRadioButton(groupBoxProjectSelection);
        radioButtonEntireProject->setObjectName(QString::fromUtf8("radioButtonEntireProject"));
        radioButtonEntireProject->setChecked(true);

        gridLayout_3->addWidget(radioButtonEntireProject, 0, 0, 1, 1);

        radioButtonSelectedGeometry = new QRadioButton(groupBoxProjectSelection);
        radioButtonSelectedGeometry->setObjectName(QString::fromUtf8("radioButtonSelectedGeometry"));
        radioButtonSelectedGeometry->setChecked(false);

        gridLayout_3->addWidget(radioButtonSelectedGeometry, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBoxProjectSelection);

        checkBoxDetailledSettings = new QCheckBox(SVSmartIntersectionDialog);
        checkBoxDetailledSettings->setObjectName(QString::fromUtf8("checkBoxDetailledSettings"));

        verticalLayout_2->addWidget(checkBoxDetailledSettings);

        line_2 = new QFrame(SVSmartIntersectionDialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        groupBoxDetailled = new QGroupBox(SVSmartIntersectionDialog);
        groupBoxDetailled->setObjectName(QString::fromUtf8("groupBoxDetailled"));
        groupBoxDetailled->setFlat(true);
        groupBoxDetailled->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBoxDetailled);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_9 = new QLabel(groupBoxDetailled);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        lineEditConnectSurfacesMaxDistance = new QtExt::ValidatingLineEdit(groupBoxDetailled);
        lineEditConnectSurfacesMaxDistance->setObjectName(QString::fromUtf8("lineEditConnectSurfacesMaxDistance"));

        gridLayout_2->addWidget(lineEditConnectSurfacesMaxDistance, 0, 1, 1, 1);

        label = new QLabel(groupBoxDetailled);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 1);

        label_10 = new QLabel(groupBoxDetailled);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        lineEditConnectSurfacesMaxAngle = new QtExt::ValidatingLineEdit(groupBoxDetailled);
        lineEditConnectSurfacesMaxAngle->setObjectName(QString::fromUtf8("lineEditConnectSurfacesMaxAngle"));

        gridLayout_2->addWidget(lineEditConnectSurfacesMaxAngle, 1, 1, 1, 1);

        label_2 = new QLabel(groupBoxDetailled);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 2, 1, 1);

        line = new QFrame(groupBoxDetailled);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 2, 0, 1, 3);

        checkBoxCreateComp = new QCheckBox(groupBoxDetailled);
        checkBoxCreateComp->setObjectName(QString::fromUtf8("checkBoxCreateComp"));
        checkBoxCreateComp->setChecked(true);

        gridLayout_2->addWidget(checkBoxCreateComp, 3, 0, 1, 1);

        checkBoxReplaceComponentInstances = new QCheckBox(groupBoxDetailled);
        checkBoxReplaceComponentInstances->setObjectName(QString::fromUtf8("checkBoxReplaceComponentInstances"));

        gridLayout_2->addWidget(checkBoxReplaceComponentInstances, 4, 0, 1, 3);


        verticalLayout_2->addWidget(groupBoxDetailled);

        groupBoxComponents = new QGroupBox(SVSmartIntersectionDialog);
        groupBoxComponents->setObjectName(QString::fromUtf8("groupBoxComponents"));
        gridLayout = new QGridLayout(groupBoxComponents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBoxComponents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        toolButtonSelectFloor = new QToolButton(groupBoxComponents);
        toolButtonSelectFloor->setObjectName(QString::fromUtf8("toolButtonSelectFloor"));

        gridLayout->addWidget(toolButtonSelectFloor, 7, 2, 1, 1);

        toolButtonSelectCeiling = new QToolButton(groupBoxComponents);
        toolButtonSelectCeiling->setObjectName(QString::fromUtf8("toolButtonSelectCeiling"));

        gridLayout->addWidget(toolButtonSelectCeiling, 6, 2, 1, 1);

        lineEditExteriorWallName = new QLineEdit(groupBoxComponents);
        lineEditExteriorWallName->setObjectName(QString::fromUtf8("lineEditExteriorWallName"));
        lineEditExteriorWallName->setReadOnly(true);

        gridLayout->addWidget(lineEditExteriorWallName, 5, 1, 1, 1);

        toolButtonSelectInteriorWall = new QToolButton(groupBoxComponents);
        toolButtonSelectInteriorWall->setObjectName(QString::fromUtf8("toolButtonSelectInteriorWall"));

        gridLayout->addWidget(toolButtonSelectInteriorWall, 2, 2, 1, 1);

        label_4 = new QLabel(groupBoxComponents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        label_7 = new QLabel(groupBoxComponents);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 9, 0, 1, 1);

        label_3 = new QLabel(groupBoxComponents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditFloorName = new QLineEdit(groupBoxComponents);
        lineEditFloorName->setObjectName(QString::fromUtf8("lineEditFloorName"));
        lineEditFloorName->setReadOnly(true);

        gridLayout->addWidget(lineEditFloorName, 7, 1, 1, 1);

        toolButtonSelectExteriorWall = new QToolButton(groupBoxComponents);
        toolButtonSelectExteriorWall->setObjectName(QString::fromUtf8("toolButtonSelectExteriorWall"));

        gridLayout->addWidget(toolButtonSelectExteriorWall, 5, 2, 1, 1);

        lineEditCeilingName = new QLineEdit(groupBoxComponents);
        lineEditCeilingName->setObjectName(QString::fromUtf8("lineEditCeilingName"));
        lineEditCeilingName->setReadOnly(true);

        gridLayout->addWidget(lineEditCeilingName, 6, 1, 1, 1);

        label_6 = new QLabel(groupBoxComponents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        toolButtonSelectRoof = new QToolButton(groupBoxComponents);
        toolButtonSelectRoof->setObjectName(QString::fromUtf8("toolButtonSelectRoof"));

        gridLayout->addWidget(toolButtonSelectRoof, 9, 2, 1, 1);

        lineEditInteriorWallName = new QLineEdit(groupBoxComponents);
        lineEditInteriorWallName->setObjectName(QString::fromUtf8("lineEditInteriorWallName"));
        lineEditInteriorWallName->setReadOnly(true);

        gridLayout->addWidget(lineEditInteriorWallName, 2, 1, 1, 1);

        lineEditRoofName = new QLineEdit(groupBoxComponents);
        lineEditRoofName->setObjectName(QString::fromUtf8("lineEditRoofName"));
        lineEditRoofName->setReadOnly(true);

        gridLayout->addWidget(lineEditRoofName, 9, 1, 1, 1);


        verticalLayout_2->addWidget(groupBoxComponents);

        pushButtonStartClipping = new QPushButton(SVSmartIntersectionDialog);
        pushButtonStartClipping->setObjectName(QString::fromUtf8("pushButtonStartClipping"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonStartClipping->sizePolicy().hasHeightForWidth());
        pushButtonStartClipping->setSizePolicy(sizePolicy);
        pushButtonStartClipping->setMinimumSize(QSize(150, 0));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        pushButtonStartClipping->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/play-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStartClipping->setIcon(icon);

        verticalLayout_2->addWidget(pushButtonStartClipping);

        groupBoxLog = new QGroupBox(SVSmartIntersectionDialog);
        groupBoxLog->setObjectName(QString::fromUtf8("groupBoxLog"));
        verticalLayout = new QVBoxLayout(groupBoxLog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(groupBoxLog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QFont font2;
        plainTextEdit->setFont(font2);
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addWidget(groupBoxLog);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonApply = new QPushButton(SVSmartIntersectionDialog);
        pushButtonApply->setObjectName(QString::fromUtf8("pushButtonApply"));

        horizontalLayout_2->addWidget(pushButtonApply);

        pushButtonCancel = new QPushButton(SVSmartIntersectionDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_2->addWidget(pushButtonCancel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(7, 1);

        retranslateUi(SVSmartIntersectionDialog);

        QMetaObject::connectSlotsByName(SVSmartIntersectionDialog);
    } // setupUi

    void retranslateUi(QDialog *SVSmartIntersectionDialog)
    {
        SVSmartIntersectionDialog->setWindowTitle(QCoreApplication::translate("SVSmartIntersectionDialog", "Smart-clipping settings", nullptr));
        label_8->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Smart-clipping automatically clips the entire building geometry and creates component instances, so that a one-dimensional heat-exchange can take place.", nullptr));
        groupBoxProjectSelection->setTitle(QCoreApplication::translate("SVSmartIntersectionDialog", "Project options", nullptr));
        radioButtonEntireProject->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Clip entire project (all buildings and geometry)", nullptr));
        radioButtonSelectedGeometry->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Clip selected geometry only", nullptr));
        checkBoxDetailledSettings->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Show detailled settings", nullptr));
        groupBoxDetailled->setTitle(QCoreApplication::translate("SVSmartIntersectionDialog", "Settings", nullptr));
        label_9->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Maximum distances:", nullptr));
        label->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "m", nullptr));
        label_10->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Maximum treshold angle:", nullptr));
        label_2->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "deg", nullptr));
        checkBoxCreateComp->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Create surface connections", nullptr));
        checkBoxReplaceComponentInstances->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Replace all interior components with standard components (see group-box below)", nullptr));
        groupBoxComponents->setTitle(QCoreApplication::translate("SVSmartIntersectionDialog", "Standard Components", nullptr));
        label_5->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Ceiling:", nullptr));
        toolButtonSelectFloor->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "...", nullptr));
        toolButtonSelectCeiling->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "...", nullptr));
        toolButtonSelectInteriorWall->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "...", nullptr));
        label_4->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Exterior wall:", nullptr));
        label_7->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Roof:", nullptr));
        label_3->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Interior wall:", nullptr));
        toolButtonSelectExteriorWall->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "...", nullptr));
        label_6->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Floor:", nullptr));
        toolButtonSelectRoof->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "...", nullptr));
        pushButtonStartClipping->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Start smart-clipping", nullptr));
        groupBoxLog->setTitle(QCoreApplication::translate("SVSmartIntersectionDialog", "Smart-clipping log", nullptr));
        pushButtonApply->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Apply to project", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SVSmartIntersectionDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSmartIntersectionDialog: public Ui_SVSmartIntersectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSMARTINTERSECTIONDIALOG_H
