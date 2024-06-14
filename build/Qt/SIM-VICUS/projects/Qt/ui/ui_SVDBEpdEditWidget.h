/********************************************************************************
** Form generated from reading UI file 'SVDBEpdEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBEPDEDITWIDGET_H
#define UI_SVDBEPDEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBEpdEditWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *labelUUID;
    QtExt::ValidatingLineEdit *lineEditUUID;
    QFrame *line_2;
    QLabel *labelCategory_2;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelCategory;
    QtExt::LanguageStringEditWidget1 *lineEditCategory;
    QLabel *labelManufacturer;
    QtExt::ValidatingLineEdit *lineEditManufacturer;
    QLabel *labelExpireYear;
    QtExt::ValidatingLineEdit *lineEditExpireYear;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QFrame *line;
    QLabel *labelRefUnit;
    QtExt::ValidatingLineEdit *lineEditRefUnit;
    QLabel *labelRefQuantity;
    QtExt::ValidatingLineEdit *lineEditRefQuantity;
    QTableWidget *tableWidgetEpdData;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonAddEpd;
    QToolButton *toolButtonRemoveEpd;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SVDBEpdEditWidget)
    {
        if (SVDBEpdEditWidget->objectName().isEmpty())
            SVDBEpdEditWidget->setObjectName(QString::fromUtf8("SVDBEpdEditWidget"));
        SVDBEpdEditWidget->resize(949, 846);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVDBEpdEditWidget->sizePolicy().hasHeightForWidth());
        SVDBEpdEditWidget->setSizePolicy(sizePolicy);
        SVDBEpdEditWidget->setMinimumSize(QSize(0, 450));
        gridLayout = new QGridLayout(SVDBEpdEditWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelUUID = new QLabel(SVDBEpdEditWidget);
        labelUUID->setObjectName(QString::fromUtf8("labelUUID"));

        gridLayout->addWidget(labelUUID, 0, 0, 1, 1);

        lineEditUUID = new QtExt::ValidatingLineEdit(SVDBEpdEditWidget);
        lineEditUUID->setObjectName(QString::fromUtf8("lineEditUUID"));

        gridLayout->addWidget(lineEditUUID, 0, 1, 1, 1);

        line_2 = new QFrame(SVDBEpdEditWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 2);

        labelCategory_2 = new QLabel(SVDBEpdEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));

        gridLayout->addWidget(labelCategory_2, 2, 0, 2, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBEpdEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 3, 1, 1, 1);

        labelCategory = new QLabel(SVDBEpdEditWidget);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));

        gridLayout->addWidget(labelCategory, 4, 0, 1, 1);

        lineEditCategory = new QtExt::LanguageStringEditWidget1(SVDBEpdEditWidget);
        lineEditCategory->setObjectName(QString::fromUtf8("lineEditCategory"));

        gridLayout->addWidget(lineEditCategory, 4, 1, 1, 1);

        labelManufacturer = new QLabel(SVDBEpdEditWidget);
        labelManufacturer->setObjectName(QString::fromUtf8("labelManufacturer"));

        gridLayout->addWidget(labelManufacturer, 5, 0, 1, 1);

        lineEditManufacturer = new QtExt::ValidatingLineEdit(SVDBEpdEditWidget);
        lineEditManufacturer->setObjectName(QString::fromUtf8("lineEditManufacturer"));

        gridLayout->addWidget(lineEditManufacturer, 5, 1, 1, 1);

        labelExpireYear = new QLabel(SVDBEpdEditWidget);
        labelExpireYear->setObjectName(QString::fromUtf8("labelExpireYear"));

        gridLayout->addWidget(labelExpireYear, 6, 0, 1, 1);

        lineEditExpireYear = new QtExt::ValidatingLineEdit(SVDBEpdEditWidget);
        lineEditExpireYear->setObjectName(QString::fromUtf8("lineEditExpireYear"));

        gridLayout->addWidget(lineEditExpireYear, 6, 1, 1, 1);

        label_2 = new QLabel(SVDBEpdEditWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        textBrowser = new QTextBrowser(SVDBEpdEditWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(16777215, 100));

        gridLayout->addWidget(textBrowser, 7, 1, 1, 1);

        line = new QFrame(SVDBEpdEditWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 8, 0, 1, 2);

        labelRefUnit = new QLabel(SVDBEpdEditWidget);
        labelRefUnit->setObjectName(QString::fromUtf8("labelRefUnit"));

        gridLayout->addWidget(labelRefUnit, 9, 0, 1, 1);

        lineEditRefUnit = new QtExt::ValidatingLineEdit(SVDBEpdEditWidget);
        lineEditRefUnit->setObjectName(QString::fromUtf8("lineEditRefUnit"));

        gridLayout->addWidget(lineEditRefUnit, 9, 1, 1, 1);

        labelRefQuantity = new QLabel(SVDBEpdEditWidget);
        labelRefQuantity->setObjectName(QString::fromUtf8("labelRefQuantity"));

        gridLayout->addWidget(labelRefQuantity, 10, 0, 1, 1);

        lineEditRefQuantity = new QtExt::ValidatingLineEdit(SVDBEpdEditWidget);
        lineEditRefQuantity->setObjectName(QString::fromUtf8("lineEditRefQuantity"));

        gridLayout->addWidget(lineEditRefQuantity, 10, 1, 1, 1);

        tableWidgetEpdData = new QTableWidget(SVDBEpdEditWidget);
        tableWidgetEpdData->setObjectName(QString::fromUtf8("tableWidgetEpdData"));

        gridLayout->addWidget(tableWidgetEpdData, 11, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButtonAddEpd = new QToolButton(SVDBEpdEditWidget);
        toolButtonAddEpd->setObjectName(QString::fromUtf8("toolButtonAddEpd"));
        toolButtonAddEpd->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddEpd->setIcon(icon);

        horizontalLayout->addWidget(toolButtonAddEpd);

        toolButtonRemoveEpd = new QToolButton(SVDBEpdEditWidget);
        toolButtonRemoveEpd->setObjectName(QString::fromUtf8("toolButtonRemoveEpd"));
        toolButtonRemoveEpd->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveEpd->setIcon(icon1);

        horizontalLayout->addWidget(toolButtonRemoveEpd);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 12, 0, 1, 2);


        retranslateUi(SVDBEpdEditWidget);

        QMetaObject::connectSlotsByName(SVDBEpdEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBEpdEditWidget)
    {
        SVDBEpdEditWidget->setWindowTitle(QCoreApplication::translate("SVDBEpdEditWidget", "Construction editor", nullptr));
        labelUUID->setText(QCoreApplication::translate("SVDBEpdEditWidget", "UUID", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Name:", nullptr));
        labelCategory->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Category:", nullptr));
        labelManufacturer->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Manufacturer:", nullptr));
        labelExpireYear->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Expire year:", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Data source:", nullptr));
        labelRefUnit->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Reference Unit:", nullptr));
        labelRefQuantity->setText(QCoreApplication::translate("SVDBEpdEditWidget", "Reference Quantity:", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonAddEpd->setToolTip(QCoreApplication::translate("SVDBEpdEditWidget", "Adds Epd Module", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonAddEpd->setText(QCoreApplication::translate("SVDBEpdEditWidget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonRemoveEpd->setToolTip(QCoreApplication::translate("SVDBEpdEditWidget", "Removes currently selected Module from EPD", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonRemoveEpd->setText(QCoreApplication::translate("SVDBEpdEditWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBEpdEditWidget: public Ui_SVDBEpdEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBEPDEDITWIDGET_H
