/********************************************************************************
** Form generated from reading UI file 'SVLocalCoordinateView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVLOCALCOORDINATEVIEW_H
#define UI_SVLOCALCOORDINATEVIEW_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVLocalCoordinateView
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelCoordinateSystem;
    QtExt::ValidatingLineEdit *lineEditXValue;
    QtExt::ValidatingLineEdit *lineEditYValue;
    QtExt::ValidatingLineEdit *lineEditZValue;
    QToolButton *toolButtonAlignCoordinateSystem;
    QToolButton *toolButtonMoveCoordinateSystem;
    QSpacerItem *horizontalSpacer;
    QLabel *labelBoundingBox;
    QtExt::ValidatingLineEdit *lineEditBoundingBoxDimensionX;
    QtExt::ValidatingLineEdit *lineEditBoundingBoxDimensionY;
    QtExt::ValidatingLineEdit *lineEditBoundingBoxDimensionZ;
    QToolButton *toolButtonInformation;

    void setupUi(QWidget *SVLocalCoordinateView)
    {
        if (SVLocalCoordinateView->objectName().isEmpty())
            SVLocalCoordinateView->setObjectName(QString::fromUtf8("SVLocalCoordinateView"));
        SVLocalCoordinateView->resize(700, 31);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVLocalCoordinateView->sizePolicy().hasHeightForWidth());
        SVLocalCoordinateView->setSizePolicy(sizePolicy);
        SVLocalCoordinateView->setMinimumSize(QSize(0, 0));
        SVLocalCoordinateView->setMaximumSize(QSize(700, 16777215));
        horizontalLayout = new QHBoxLayout(SVLocalCoordinateView);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelCoordinateSystem = new QLabel(SVLocalCoordinateView);
        labelCoordinateSystem->setObjectName(QString::fromUtf8("labelCoordinateSystem"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelCoordinateSystem->sizePolicy().hasHeightForWidth());
        labelCoordinateSystem->setSizePolicy(sizePolicy1);
        labelCoordinateSystem->setMaximumSize(QSize(24, 24));
        labelCoordinateSystem->setPixmap(QPixmap(QString::fromUtf8(":/gfx/icons8/icons8-abscissa-80(2).png")));
        labelCoordinateSystem->setScaledContents(true);

        horizontalLayout->addWidget(labelCoordinateSystem);

        lineEditXValue = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditXValue->setObjectName(QString::fromUtf8("lineEditXValue"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditXValue->sizePolicy().hasHeightForWidth());
        lineEditXValue->setSizePolicy(sizePolicy2);
        lineEditXValue->setMinimumSize(QSize(0, 28));
        lineEditXValue->setMaximumSize(QSize(80, 16777215));
        lineEditXValue->setReadOnly(true);

        horizontalLayout->addWidget(lineEditXValue);

        lineEditYValue = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditYValue->setObjectName(QString::fromUtf8("lineEditYValue"));
        sizePolicy2.setHeightForWidth(lineEditYValue->sizePolicy().hasHeightForWidth());
        lineEditYValue->setSizePolicy(sizePolicy2);
        lineEditYValue->setMinimumSize(QSize(0, 28));
        lineEditYValue->setMaximumSize(QSize(80, 16777215));
        lineEditYValue->setReadOnly(true);

        horizontalLayout->addWidget(lineEditYValue);

        lineEditZValue = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditZValue->setObjectName(QString::fromUtf8("lineEditZValue"));
        sizePolicy2.setHeightForWidth(lineEditZValue->sizePolicy().hasHeightForWidth());
        lineEditZValue->setSizePolicy(sizePolicy2);
        lineEditZValue->setMinimumSize(QSize(0, 28));
        lineEditZValue->setMaximumSize(QSize(80, 16777215));
        lineEditZValue->setReadOnly(true);

        horizontalLayout->addWidget(lineEditZValue);

        toolButtonAlignCoordinateSystem = new QToolButton(SVLocalCoordinateView);
        toolButtonAlignCoordinateSystem->setObjectName(QString::fromUtf8("toolButtonAlignCoordinateSystem"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/icons8/icons8-abscissa-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAlignCoordinateSystem->setIcon(icon);
        toolButtonAlignCoordinateSystem->setIconSize(QSize(24, 24));
        toolButtonAlignCoordinateSystem->setCheckable(true);
        toolButtonAlignCoordinateSystem->setChecked(true);

        horizontalLayout->addWidget(toolButtonAlignCoordinateSystem);

        toolButtonMoveCoordinateSystem = new QToolButton(SVLocalCoordinateView);
        toolButtonMoveCoordinateSystem->setObjectName(QString::fromUtf8("toolButtonMoveCoordinateSystem"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/icons8/icons8-abscissa-80(1).png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonMoveCoordinateSystem->setIcon(icon1);
        toolButtonMoveCoordinateSystem->setIconSize(QSize(24, 24));
        toolButtonMoveCoordinateSystem->setCheckable(true);
        toolButtonMoveCoordinateSystem->setChecked(true);

        horizontalLayout->addWidget(toolButtonMoveCoordinateSystem);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelBoundingBox = new QLabel(SVLocalCoordinateView);
        labelBoundingBox->setObjectName(QString::fromUtf8("labelBoundingBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelBoundingBox->sizePolicy().hasHeightForWidth());
        labelBoundingBox->setSizePolicy(sizePolicy3);
        labelBoundingBox->setMaximumSize(QSize(24, 24));
        labelBoundingBox->setPixmap(QPixmap(QString::fromUtf8(":/gfx/icons8/icons8-size-80.png")));
        labelBoundingBox->setScaledContents(true);

        horizontalLayout->addWidget(labelBoundingBox);

        lineEditBoundingBoxDimensionX = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditBoundingBoxDimensionX->setObjectName(QString::fromUtf8("lineEditBoundingBoxDimensionX"));
        sizePolicy2.setHeightForWidth(lineEditBoundingBoxDimensionX->sizePolicy().hasHeightForWidth());
        lineEditBoundingBoxDimensionX->setSizePolicy(sizePolicy2);
        lineEditBoundingBoxDimensionX->setMinimumSize(QSize(0, 28));
        lineEditBoundingBoxDimensionX->setMaximumSize(QSize(80, 16777215));
        lineEditBoundingBoxDimensionX->setReadOnly(true);

        horizontalLayout->addWidget(lineEditBoundingBoxDimensionX);

        lineEditBoundingBoxDimensionY = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditBoundingBoxDimensionY->setObjectName(QString::fromUtf8("lineEditBoundingBoxDimensionY"));
        sizePolicy2.setHeightForWidth(lineEditBoundingBoxDimensionY->sizePolicy().hasHeightForWidth());
        lineEditBoundingBoxDimensionY->setSizePolicy(sizePolicy2);
        lineEditBoundingBoxDimensionY->setMinimumSize(QSize(0, 28));
        lineEditBoundingBoxDimensionY->setMaximumSize(QSize(80, 16777215));
        lineEditBoundingBoxDimensionY->setReadOnly(true);

        horizontalLayout->addWidget(lineEditBoundingBoxDimensionY);

        lineEditBoundingBoxDimensionZ = new QtExt::ValidatingLineEdit(SVLocalCoordinateView);
        lineEditBoundingBoxDimensionZ->setObjectName(QString::fromUtf8("lineEditBoundingBoxDimensionZ"));
        sizePolicy2.setHeightForWidth(lineEditBoundingBoxDimensionZ->sizePolicy().hasHeightForWidth());
        lineEditBoundingBoxDimensionZ->setSizePolicy(sizePolicy2);
        lineEditBoundingBoxDimensionZ->setMinimumSize(QSize(0, 28));
        lineEditBoundingBoxDimensionZ->setMaximumSize(QSize(80, 16777215));
        lineEditBoundingBoxDimensionZ->setReadOnly(true);

        horizontalLayout->addWidget(lineEditBoundingBoxDimensionZ);

        toolButtonInformation = new QToolButton(SVLocalCoordinateView);
        toolButtonInformation->setObjectName(QString::fromUtf8("toolButtonInformation"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonInformation->setIcon(icon2);
        toolButtonInformation->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonInformation);


        retranslateUi(SVLocalCoordinateView);

        QMetaObject::connectSlotsByName(SVLocalCoordinateView);
    } // setupUi

    void retranslateUi(QWidget *SVLocalCoordinateView)
    {
        labelCoordinateSystem->setText(QString());
#if QT_CONFIG(tooltip)
        toolButtonAlignCoordinateSystem->setToolTip(QCoreApplication::translate("SVLocalCoordinateView", "Toggles mode for aligning local coordinate system to surface orientation (F4)", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonAlignCoordinateSystem->setText(QCoreApplication::translate("SVLocalCoordinateView", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonMoveCoordinateSystem->setToolTip(QCoreApplication::translate("SVLocalCoordinateView", "Toggles mode for moving local coordinate system (F5)", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonMoveCoordinateSystem->setText(QCoreApplication::translate("SVLocalCoordinateView", "...", nullptr));
        labelBoundingBox->setText(QString());
        toolButtonInformation->setText(QCoreApplication::translate("SVLocalCoordinateView", "i", nullptr));
        (void)SVLocalCoordinateView;
    } // retranslateUi

};

namespace Ui {
    class SVLocalCoordinateView: public Ui_SVLocalCoordinateView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVLOCALCOORDINATEVIEW_H
