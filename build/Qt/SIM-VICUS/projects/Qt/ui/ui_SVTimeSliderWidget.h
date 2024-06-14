/********************************************************************************
** Form generated from reading UI file 'SVTimeSliderWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVTIMESLIDERWIDGET_H
#define UI_SVTIMESLIDERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "QtExt_IconButton.h"
#include "SVNonEquidistantSlider.h"

QT_BEGIN_NAMESPACE

class Ui_SVTimeSliderWidget
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEditCurrentTime;
    QHBoxLayout *horizontalLayout;
    QtExt::IconButton *widgetReset;
    QtExt::IconButton *widgetFastRewind;
    QtExt::IconButton *widgetPlay;
    QtExt::IconButton *widgetRecord;
    QtExt::IconButton *widgetFastForeward;
    QtExt::IconButton *widgetEnd;
    QLabel *labelCurrentTime;
    QLineEdit *lineEditOffsetFromStart;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBoxUnit;
    QSlider *horizontalSliderDisplaySpeed;
    SVNonEquidistantSlider *widgetSlider;
    QLabel *labelCurrentTime_2;

    void setupUi(QWidget *SVTimeSliderWidget)
    {
        if (SVTimeSliderWidget->objectName().isEmpty())
            SVTimeSliderWidget->setObjectName(QString::fromUtf8("SVTimeSliderWidget"));
        SVTimeSliderWidget->resize(649, 117);
        gridLayout = new QGridLayout(SVTimeSliderWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditCurrentTime = new QLineEdit(SVTimeSliderWidget);
        lineEditCurrentTime->setObjectName(QString::fromUtf8("lineEditCurrentTime"));
        lineEditCurrentTime->setReadOnly(true);

        gridLayout->addWidget(lineEditCurrentTime, 1, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetReset = new QtExt::IconButton(SVTimeSliderWidget);
        widgetReset->setObjectName(QString::fromUtf8("widgetReset"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetReset->sizePolicy().hasHeightForWidth());
        widgetReset->setSizePolicy(sizePolicy);
        widgetReset->setMinimumSize(QSize(24, 24));
        widgetReset->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetReset);

        widgetFastRewind = new QtExt::IconButton(SVTimeSliderWidget);
        widgetFastRewind->setObjectName(QString::fromUtf8("widgetFastRewind"));
        sizePolicy.setHeightForWidth(widgetFastRewind->sizePolicy().hasHeightForWidth());
        widgetFastRewind->setSizePolicy(sizePolicy);
        widgetFastRewind->setMinimumSize(QSize(24, 24));
        widgetFastRewind->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetFastRewind);

        widgetPlay = new QtExt::IconButton(SVTimeSliderWidget);
        widgetPlay->setObjectName(QString::fromUtf8("widgetPlay"));
        sizePolicy.setHeightForWidth(widgetPlay->sizePolicy().hasHeightForWidth());
        widgetPlay->setSizePolicy(sizePolicy);
        widgetPlay->setMinimumSize(QSize(24, 24));
        widgetPlay->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetPlay);

        widgetRecord = new QtExt::IconButton(SVTimeSliderWidget);
        widgetRecord->setObjectName(QString::fromUtf8("widgetRecord"));
        widgetRecord->setEnabled(false);
        sizePolicy.setHeightForWidth(widgetRecord->sizePolicy().hasHeightForWidth());
        widgetRecord->setSizePolicy(sizePolicy);
        widgetRecord->setMinimumSize(QSize(24, 24));
        widgetRecord->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetRecord);

        widgetFastForeward = new QtExt::IconButton(SVTimeSliderWidget);
        widgetFastForeward->setObjectName(QString::fromUtf8("widgetFastForeward"));
        sizePolicy.setHeightForWidth(widgetFastForeward->sizePolicy().hasHeightForWidth());
        widgetFastForeward->setSizePolicy(sizePolicy);
        widgetFastForeward->setMinimumSize(QSize(24, 24));
        widgetFastForeward->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetFastForeward);

        widgetEnd = new QtExt::IconButton(SVTimeSliderWidget);
        widgetEnd->setObjectName(QString::fromUtf8("widgetEnd"));
        sizePolicy.setHeightForWidth(widgetEnd->sizePolicy().hasHeightForWidth());
        widgetEnd->setSizePolicy(sizePolicy);
        widgetEnd->setMinimumSize(QSize(24, 24));
        widgetEnd->setMaximumSize(QSize(24, 24));

        horizontalLayout->addWidget(widgetEnd);


        gridLayout->addLayout(horizontalLayout, 1, 3, 1, 1);

        labelCurrentTime = new QLabel(SVTimeSliderWidget);
        labelCurrentTime->setObjectName(QString::fromUtf8("labelCurrentTime"));
        labelCurrentTime->setTextFormat(Qt::PlainText);
        labelCurrentTime->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(labelCurrentTime, 1, 0, 1, 1);

        lineEditOffsetFromStart = new QLineEdit(SVTimeSliderWidget);
        lineEditOffsetFromStart->setObjectName(QString::fromUtf8("lineEditOffsetFromStart"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditOffsetFromStart->sizePolicy().hasHeightForWidth());
        lineEditOffsetFromStart->setSizePolicy(sizePolicy1);
        lineEditOffsetFromStart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lineEditOffsetFromStart, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        comboBoxUnit = new QComboBox(SVTimeSliderWidget);
        comboBoxUnit->setObjectName(QString::fromUtf8("comboBoxUnit"));

        gridLayout->addWidget(comboBoxUnit, 3, 2, 1, 1);

        horizontalSliderDisplaySpeed = new QSlider(SVTimeSliderWidget);
        horizontalSliderDisplaySpeed->setObjectName(QString::fromUtf8("horizontalSliderDisplaySpeed"));
        sizePolicy1.setHeightForWidth(horizontalSliderDisplaySpeed->sizePolicy().hasHeightForWidth());
        horizontalSliderDisplaySpeed->setSizePolicy(sizePolicy1);
        horizontalSliderDisplaySpeed->setMinimumSize(QSize(70, 0));
        horizontalSliderDisplaySpeed->setSliderPosition(50);
        horizontalSliderDisplaySpeed->setOrientation(Qt::Horizontal);
        horizontalSliderDisplaySpeed->setTickPosition(QSlider::TicksBelow);

        gridLayout->addWidget(horizontalSliderDisplaySpeed, 1, 5, 1, 1);

        widgetSlider = new SVNonEquidistantSlider(SVTimeSliderWidget);
        widgetSlider->setObjectName(QString::fromUtf8("widgetSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetSlider->sizePolicy().hasHeightForWidth());
        widgetSlider->setSizePolicy(sizePolicy2);
        widgetSlider->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(widgetSlider, 0, 0, 1, 6);

        labelCurrentTime_2 = new QLabel(SVTimeSliderWidget);
        labelCurrentTime_2->setObjectName(QString::fromUtf8("labelCurrentTime_2"));
        labelCurrentTime_2->setTextFormat(Qt::PlainText);
        labelCurrentTime_2->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(labelCurrentTime_2, 3, 0, 1, 1);


        retranslateUi(SVTimeSliderWidget);

        QMetaObject::connectSlotsByName(SVTimeSliderWidget);
    } // setupUi

    void retranslateUi(QWidget *SVTimeSliderWidget)
    {
        SVTimeSliderWidget->setWindowTitle(QCoreApplication::translate("SVTimeSliderWidget", "Form", nullptr));
        labelCurrentTime->setText(QCoreApplication::translate("SVTimeSliderWidget", "Current ", nullptr));
#if QT_CONFIG(tooltip)
        horizontalSliderDisplaySpeed->setToolTip(QCoreApplication::translate("SVTimeSliderWidget", "Controls animation speed.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelCurrentTime_2->setText(QCoreApplication::translate("SVTimeSliderWidget", "Offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVTimeSliderWidget: public Ui_SVTimeSliderWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVTIMESLIDERWIDGET_H
