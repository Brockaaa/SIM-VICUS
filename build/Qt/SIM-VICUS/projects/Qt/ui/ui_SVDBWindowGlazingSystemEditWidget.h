/********************************************************************************
** Form generated from reading UI file 'SVDBWindowGlazingSystemEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBWINDOWGLAZINGSYSTEMEDITWIDGET_H
#define UI_SVDBWINDOWGLAZINGSYSTEMEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBWindowGlazingSystemEditWidget
{
public:
    QGridLayout *masterLayout;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelFrameUValue_2;
    QComboBox *comboBoxType;
    QLabel *labelFrameUValue;
    QtExt::ValidatingLineEdit *lineEditUValue;
    QLabel *labelFrameInputUnit;
    QLabel *labelSHGC;
    QtExt::ValidatingLineEdit *lineEditSHGC0;
    QLabel *labelSHGCUnit;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QTableWidget *tableWidgetSHGC;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonCreateSpline;
    QToolButton *toolButtonImportSplineFromClipboard;
    QSpacerItem *horizontalSpacer;
    QwtPlot *shgcPlot;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVDBWindowGlazingSystemEditWidget)
    {
        if (SVDBWindowGlazingSystemEditWidget->objectName().isEmpty())
            SVDBWindowGlazingSystemEditWidget->setObjectName(QString::fromUtf8("SVDBWindowGlazingSystemEditWidget"));
        SVDBWindowGlazingSystemEditWidget->resize(552, 594);
        masterLayout = new QGridLayout(SVDBWindowGlazingSystemEditWidget);
        masterLayout->setObjectName(QString::fromUtf8("masterLayout"));
        labelDisplayName = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        masterLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBWindowGlazingSystemEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMinimumSize(QSize(300, 0));

        masterLayout->addWidget(lineEditName, 0, 2, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBWindowGlazingSystemEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        masterLayout->addWidget(pushButtonColor, 0, 3, 1, 1);

        labelFrameUValue_2 = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelFrameUValue_2->setObjectName(QString::fromUtf8("labelFrameUValue_2"));

        masterLayout->addWidget(labelFrameUValue_2, 1, 0, 1, 1);

        comboBoxType = new QComboBox(SVDBWindowGlazingSystemEditWidget);
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));

        masterLayout->addWidget(comboBoxType, 1, 2, 1, 1);

        labelFrameUValue = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelFrameUValue->setObjectName(QString::fromUtf8("labelFrameUValue"));

        masterLayout->addWidget(labelFrameUValue, 2, 0, 1, 1);

        lineEditUValue = new QtExt::ValidatingLineEdit(SVDBWindowGlazingSystemEditWidget);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));

        masterLayout->addWidget(lineEditUValue, 2, 2, 1, 1);

        labelFrameInputUnit = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelFrameInputUnit->setObjectName(QString::fromUtf8("labelFrameInputUnit"));

        masterLayout->addWidget(labelFrameInputUnit, 2, 3, 1, 1);

        labelSHGC = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelSHGC->setObjectName(QString::fromUtf8("labelSHGC"));

        masterLayout->addWidget(labelSHGC, 3, 0, 1, 2);

        lineEditSHGC0 = new QtExt::ValidatingLineEdit(SVDBWindowGlazingSystemEditWidget);
        lineEditSHGC0->setObjectName(QString::fromUtf8("lineEditSHGC0"));

        masterLayout->addWidget(lineEditSHGC0, 3, 2, 1, 1);

        labelSHGCUnit = new QLabel(SVDBWindowGlazingSystemEditWidget);
        labelSHGCUnit->setObjectName(QString::fromUtf8("labelSHGCUnit"));

        masterLayout->addWidget(labelSHGCUnit, 3, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Preferred);

        masterLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label = new QLabel(SVDBWindowGlazingSystemEditWidget);
        label->setObjectName(QString::fromUtf8("label"));

        masterLayout->addWidget(label, 5, 0, 1, 2);

        tableWidgetSHGC = new QTableWidget(SVDBWindowGlazingSystemEditWidget);
        tableWidgetSHGC->setObjectName(QString::fromUtf8("tableWidgetSHGC"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidgetSHGC->sizePolicy().hasHeightForWidth());
        tableWidgetSHGC->setSizePolicy(sizePolicy1);
        tableWidgetSHGC->setAlternatingRowColors(true);
        tableWidgetSHGC->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSHGC->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetSHGC->horizontalHeader()->setStretchLastSection(true);
        tableWidgetSHGC->verticalHeader()->setVisible(false);

        masterLayout->addWidget(tableWidgetSHGC, 6, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButtonCreateSpline = new QToolButton(SVDBWindowGlazingSystemEditWidget);
        toolButtonCreateSpline->setObjectName(QString::fromUtf8("toolButtonCreateSpline"));

        horizontalLayout->addWidget(toolButtonCreateSpline);

        toolButtonImportSplineFromClipboard = new QToolButton(SVDBWindowGlazingSystemEditWidget);
        toolButtonImportSplineFromClipboard->setObjectName(QString::fromUtf8("toolButtonImportSplineFromClipboard"));

        horizontalLayout->addWidget(toolButtonImportSplineFromClipboard);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        masterLayout->addLayout(horizontalLayout, 7, 0, 1, 4);

        shgcPlot = new QwtPlot(SVDBWindowGlazingSystemEditWidget);
        shgcPlot->setObjectName(QString::fromUtf8("shgcPlot"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(shgcPlot->sizePolicy().hasHeightForWidth());
        shgcPlot->setSizePolicy(sizePolicy2);

        masterLayout->addWidget(shgcPlot, 8, 0, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Expanding);

        masterLayout->addItem(verticalSpacer_2, 8, 3, 1, 1);


        retranslateUi(SVDBWindowGlazingSystemEditWidget);

        QMetaObject::connectSlotsByName(SVDBWindowGlazingSystemEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBWindowGlazingSystemEditWidget)
    {
        SVDBWindowGlazingSystemEditWidget->setWindowTitle(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "Window Glazing System Database", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "Name:", nullptr));
        labelFrameUValue_2->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "Type:", nullptr));
        labelFrameUValue->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "U-Value:", nullptr));
        labelFrameInputUnit->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "W/m2K", nullptr));
        labelSHGC->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "SHGC (normal Incidence):", nullptr));
        labelSHGCUnit->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "-", nullptr));
        label->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "SHGC (angle dependent)", nullptr));
        toolButtonCreateSpline->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "Create standard SHGC curve", nullptr));
        toolButtonImportSplineFromClipboard->setText(QCoreApplication::translate("SVDBWindowGlazingSystemEditWidget", "Import from clipboard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBWindowGlazingSystemEditWidget: public Ui_SVDBWindowGlazingSystemEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBWINDOWGLAZINGSYSTEMEDITWIDGET_H
