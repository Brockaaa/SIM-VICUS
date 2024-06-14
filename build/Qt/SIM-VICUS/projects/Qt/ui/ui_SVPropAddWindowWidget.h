/********************************************************************************
** Form generated from reading UI file 'SVPropAddWindowWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPADDWINDOWWIDGET_H
#define UI_SVPROPADDWINDOWWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropAddWindowWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelSelectSurfaces;
    QGroupBox *groupBoxWindows;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidgetWindow;
    QWidget *tab;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_5;
    QtExt::ValidatingLineEdit *lineEditWindowPercentage;
    QLabel *label_8;
    QLabel *label_12;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QtExt::ValidatingLineEdit *lineEditWindowOffset;
    QSpinBox *spinBoxMaxHoleCount;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_13;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_5;
    QtExt::ValidatingLineEdit *lineEditWindowDistance;
    QLabel *label_2;
    QSpinBox *spinBoxWindowWidth;
    QSpinBox *spinBoxWindowSillHeight;
    QtExt::ValidatingLineEdit *lineEditWindowHeight;
    QLabel *label_3;
    QSpinBox *spinBoxWindowHeight;
    QLabel *label_4;
    QSpinBox *spinBoxWindowWidthDistance;
    QtExt::ValidatingLineEdit *lineEditWindowWidth;
    QtExt::ValidatingLineEdit *lineEditWindowSillHeight;
    QPushButton *pushButtonChangeLocalOrigin;
    QLabel *label_11;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonCreate;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QRadioButton *radioButtonSubSurfaceTypeWindow;
    QRadioButton *radioButtonSubSurfaceTypeDoor;
    QLabel *label_7;
    QComboBox *comboBoxSubSurfaceComponent;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SVPropAddWindowWidget)
    {
        if (SVPropAddWindowWidget->objectName().isEmpty())
            SVPropAddWindowWidget->setObjectName(QString::fromUtf8("SVPropAddWindowWidget"));
        SVPropAddWindowWidget->resize(428, 646);
        verticalLayout = new QVBoxLayout(SVPropAddWindowWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelSelectSurfaces = new QLabel(SVPropAddWindowWidget);
        labelSelectSurfaces->setObjectName(QString::fromUtf8("labelSelectSurfaces"));
        QFont font;
        font.setItalic(true);
        labelSelectSurfaces->setFont(font);

        verticalLayout->addWidget(labelSelectSurfaces);

        groupBoxWindows = new QGroupBox(SVPropAddWindowWidget);
        groupBoxWindows->setObjectName(QString::fromUtf8("groupBoxWindows"));
        groupBoxWindows->setEnabled(true);
        gridLayout_2 = new QGridLayout(groupBoxWindows);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidgetWindow = new QTabWidget(groupBoxWindows);
        tabWidgetWindow->setObjectName(QString::fromUtf8("tabWidgetWindow"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidgetWindow->sizePolicy().hasHeightForWidth());
        tabWidgetWindow->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_5 = new QGridLayout(tab);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_5->addItem(verticalSpacer_5, 1, 0, 1, 1);

        lineEditWindowPercentage = new QtExt::ValidatingLineEdit(tab);
        lineEditWindowPercentage->setObjectName(QString::fromUtf8("lineEditWindowPercentage"));

        gridLayout_5->addWidget(lineEditWindowPercentage, 0, 1, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_5->addWidget(label_12, 0, 2, 1, 1);

        tabWidgetWindow->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lineEditWindowOffset = new QtExt::ValidatingLineEdit(tab_2);
        lineEditWindowOffset->setObjectName(QString::fromUtf8("lineEditWindowOffset"));

        gridLayout_4->addWidget(lineEditWindowOffset, 0, 1, 1, 1);

        spinBoxMaxHoleCount = new QSpinBox(tab_2);
        spinBoxMaxHoleCount->setObjectName(QString::fromUtf8("spinBoxMaxHoleCount"));
        spinBoxMaxHoleCount->setMinimum(1);

        gridLayout_4->addWidget(spinBoxMaxHoleCount, 1, 1, 1, 1);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 1, 0, 1, 1);

        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 0, 0, 1, 1);

        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 0, 2, 1, 1);

        tabWidgetWindow->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidgetWindow, 3, 0, 1, 3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBoxWindows);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_5 = new QLabel(groupBoxWindows);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        lineEditWindowDistance = new QtExt::ValidatingLineEdit(groupBoxWindows);
        lineEditWindowDistance->setObjectName(QString::fromUtf8("lineEditWindowDistance"));

        gridLayout->addWidget(lineEditWindowDistance, 4, 1, 1, 1);

        label_2 = new QLabel(groupBoxWindows);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        spinBoxWindowWidth = new QSpinBox(groupBoxWindows);
        spinBoxWindowWidth->setObjectName(QString::fromUtf8("spinBoxWindowWidth"));
        spinBoxWindowWidth->setMinimum(1);
        spinBoxWindowWidth->setMaximum(4);
        spinBoxWindowWidth->setValue(2);

        gridLayout->addWidget(spinBoxWindowWidth, 1, 2, 1, 1);

        spinBoxWindowSillHeight = new QSpinBox(groupBoxWindows);
        spinBoxWindowSillHeight->setObjectName(QString::fromUtf8("spinBoxWindowSillHeight"));
        spinBoxWindowSillHeight->setMinimum(1);
        spinBoxWindowSillHeight->setMaximum(4);
        spinBoxWindowSillHeight->setValue(3);

        gridLayout->addWidget(spinBoxWindowSillHeight, 3, 2, 1, 1);

        lineEditWindowHeight = new QtExt::ValidatingLineEdit(groupBoxWindows);
        lineEditWindowHeight->setObjectName(QString::fromUtf8("lineEditWindowHeight"));

        gridLayout->addWidget(lineEditWindowHeight, 2, 1, 1, 1);

        label_3 = new QLabel(groupBoxWindows);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        spinBoxWindowHeight = new QSpinBox(groupBoxWindows);
        spinBoxWindowHeight->setObjectName(QString::fromUtf8("spinBoxWindowHeight"));
        spinBoxWindowHeight->setMinimum(1);
        spinBoxWindowHeight->setMaximum(4);
        spinBoxWindowHeight->setValue(1);

        gridLayout->addWidget(spinBoxWindowHeight, 2, 2, 1, 1);

        label_4 = new QLabel(groupBoxWindows);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        spinBoxWindowWidthDistance = new QSpinBox(groupBoxWindows);
        spinBoxWindowWidthDistance->setObjectName(QString::fromUtf8("spinBoxWindowWidthDistance"));
        spinBoxWindowWidthDistance->setMinimum(1);
        spinBoxWindowWidthDistance->setMaximum(4);
        spinBoxWindowWidthDistance->setValue(4);

        gridLayout->addWidget(spinBoxWindowWidthDistance, 4, 2, 1, 1);

        lineEditWindowWidth = new QtExt::ValidatingLineEdit(groupBoxWindows);
        lineEditWindowWidth->setObjectName(QString::fromUtf8("lineEditWindowWidth"));

        gridLayout->addWidget(lineEditWindowWidth, 1, 1, 1, 1);

        lineEditWindowSillHeight = new QtExt::ValidatingLineEdit(groupBoxWindows);
        lineEditWindowSillHeight->setObjectName(QString::fromUtf8("lineEditWindowSillHeight"));

        gridLayout->addWidget(lineEditWindowSillHeight, 3, 1, 1, 1);

        pushButtonChangeLocalOrigin = new QPushButton(groupBoxWindows);
        pushButtonChangeLocalOrigin->setObjectName(QString::fromUtf8("pushButtonChangeLocalOrigin"));

        gridLayout->addWidget(pushButtonChangeLocalOrigin, 5, 1, 1, 2);

        label_11 = new QLabel(groupBoxWindows);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 2, 1, 1);

        pushButtonCreate = new QPushButton(groupBoxWindows);
        pushButtonCreate->setObjectName(QString::fromUtf8("pushButtonCreate"));

        gridLayout_2->addWidget(pushButtonCreate, 7, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_6 = new QLabel(groupBoxWindows);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        radioButtonSubSurfaceTypeWindow = new QRadioButton(groupBoxWindows);
        radioButtonSubSurfaceTypeWindow->setObjectName(QString::fromUtf8("radioButtonSubSurfaceTypeWindow"));
        radioButtonSubSurfaceTypeWindow->setChecked(true);

        gridLayout_3->addWidget(radioButtonSubSurfaceTypeWindow, 0, 1, 1, 1);

        radioButtonSubSurfaceTypeDoor = new QRadioButton(groupBoxWindows);
        radioButtonSubSurfaceTypeDoor->setObjectName(QString::fromUtf8("radioButtonSubSurfaceTypeDoor"));
        radioButtonSubSurfaceTypeDoor->setEnabled(false);

        gridLayout_3->addWidget(radioButtonSubSurfaceTypeDoor, 1, 1, 1, 1);

        label_7 = new QLabel(groupBoxWindows);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        comboBoxSubSurfaceComponent = new QComboBox(groupBoxWindows);
        comboBoxSubSurfaceComponent->setObjectName(QString::fromUtf8("comboBoxSubSurfaceComponent"));

        gridLayout_3->addWidget(comboBoxSubSurfaceComponent, 2, 1, 1, 1);

        gridLayout_3->setColumnStretch(1, 1);

        gridLayout_2->addLayout(gridLayout_3, 4, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(294, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 7, 1, 1, 2);


        verticalLayout->addWidget(groupBoxWindows);


        retranslateUi(SVPropAddWindowWidget);

        tabWidgetWindow->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVPropAddWindowWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropAddWindowWidget)
    {
        SVPropAddWindowWidget->setWindowTitle(QCoreApplication::translate("SVPropAddWindowWidget", "Form", nullptr));
        labelSelectSurfaces->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Select at least one surface!", nullptr));
        groupBoxWindows->setTitle(QCoreApplication::translate("SVPropAddWindowWidget", "Sub-Surfaces (windows/doors)", nullptr));
        label_8->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Percentage of surface area:", nullptr));
        label_12->setText(QCoreApplication::translate("SVPropAddWindowWidget", "%", nullptr));
        tabWidgetWindow->setTabText(tabWidgetWindow->indexOf(tab), QCoreApplication::translate("SVPropAddWindowWidget", "Percentage distribution", nullptr));
        label_10->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Max. number:", nullptr));
        label_9->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Offset:", nullptr));
        label_13->setText(QCoreApplication::translate("SVPropAddWindowWidget", "m", nullptr));
        tabWidgetWindow->setTabText(tabWidgetWindow->indexOf(tab_2), QCoreApplication::translate("SVPropAddWindowWidget", "Geometric placement", nullptr));
        label->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Width:", nullptr));
        label_5->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Priority", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Height:", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Window-sill height:", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Distance in-between:", nullptr));
        lineEditWindowWidth->setText(QString());
        pushButtonChangeLocalOrigin->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Use next point as origin", nullptr));
        label_11->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Values in m", nullptr));
        pushButtonCreate->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Create", nullptr));
        label_6->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Type:", nullptr));
        radioButtonSubSurfaceTypeWindow->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Window", nullptr));
        radioButtonSubSurfaceTypeDoor->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Door/opaque sub-surface", nullptr));
        label_7->setText(QCoreApplication::translate("SVPropAddWindowWidget", "Component:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropAddWindowWidget: public Ui_SVPropAddWindowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPADDWINDOWWIDGET_H
