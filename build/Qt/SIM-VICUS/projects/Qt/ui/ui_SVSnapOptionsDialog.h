/********************************************************************************
** Form generated from reading UI file 'SVSnapOptionsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSNAPOPTIONSDIALOG_H
#define UI_SVSNAPOPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_ValidatingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_SVSnapOptionsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton;
    QCheckBox *checkBoxGridPlane;
    QCheckBox *checkBoxObjectVertex;
    QCheckBox *checkBoxObjectCenter;
    QCheckBox *checkBoxObjectEdge;
    QCheckBox *checkBoxDrawing;
    QCheckBox *checkBoxDrawingLine;
    QWidget *widgetSnapDistance;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QtExt::ValidatingLineEdit *lineEditSnapDistance;
    QLabel *label_2;

    void setupUi(QDialog *SVSnapOptionsDialog)
    {
        if (SVSnapOptionsDialog->objectName().isEmpty())
            SVSnapOptionsDialog->setObjectName(QString::fromUtf8("SVSnapOptionsDialog"));
        SVSnapOptionsDialog->resize(170, 258);
        verticalLayout = new QVBoxLayout(SVSnapOptionsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolButton = new QToolButton(SVSnapOptionsDialog);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);
        toolButton->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setKerning(true);
        toolButton->setFont(font);
        toolButton->setLayoutDirection(Qt::LeftToRight);
        toolButton->setPopupMode(QToolButton::DelayedPopup);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolButton->setAutoRaise(false);
        toolButton->setArrowType(Qt::DownArrow);

        verticalLayout->addWidget(toolButton);

        checkBoxGridPlane = new QCheckBox(SVSnapOptionsDialog);
        checkBoxGridPlane->setObjectName(QString::fromUtf8("checkBoxGridPlane"));

        verticalLayout->addWidget(checkBoxGridPlane);

        checkBoxObjectVertex = new QCheckBox(SVSnapOptionsDialog);
        checkBoxObjectVertex->setObjectName(QString::fromUtf8("checkBoxObjectVertex"));

        verticalLayout->addWidget(checkBoxObjectVertex);

        checkBoxObjectCenter = new QCheckBox(SVSnapOptionsDialog);
        checkBoxObjectCenter->setObjectName(QString::fromUtf8("checkBoxObjectCenter"));

        verticalLayout->addWidget(checkBoxObjectCenter);

        checkBoxObjectEdge = new QCheckBox(SVSnapOptionsDialog);
        checkBoxObjectEdge->setObjectName(QString::fromUtf8("checkBoxObjectEdge"));

        verticalLayout->addWidget(checkBoxObjectEdge);

        checkBoxDrawing = new QCheckBox(SVSnapOptionsDialog);
        checkBoxDrawing->setObjectName(QString::fromUtf8("checkBoxDrawing"));

        verticalLayout->addWidget(checkBoxDrawing);

        checkBoxDrawingLine = new QCheckBox(SVSnapOptionsDialog);
        checkBoxDrawingLine->setObjectName(QString::fromUtf8("checkBoxDrawingLine"));

        verticalLayout->addWidget(checkBoxDrawingLine);

        widgetSnapDistance = new QWidget(SVSnapOptionsDialog);
        widgetSnapDistance->setObjectName(QString::fromUtf8("widgetSnapDistance"));
        horizontalLayout = new QHBoxLayout(widgetSnapDistance);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(widgetSnapDistance);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        lineEditSnapDistance = new QtExt::ValidatingLineEdit(widgetSnapDistance);
        lineEditSnapDistance->setObjectName(QString::fromUtf8("lineEditSnapDistance"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditSnapDistance->sizePolicy().hasHeightForWidth());
        lineEditSnapDistance->setSizePolicy(sizePolicy2);
        lineEditSnapDistance->setMinimumSize(QSize(0, 0));
        lineEditSnapDistance->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(lineEditSnapDistance);

        label_2 = new QLabel(widgetSnapDistance);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addWidget(widgetSnapDistance);


        retranslateUi(SVSnapOptionsDialog);

        QMetaObject::connectSlotsByName(SVSnapOptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *SVSnapOptionsDialog)
    {
        SVSnapOptionsDialog->setWindowTitle(QCoreApplication::translate("SVSnapOptionsDialog", "Dialog", nullptr));
        toolButton->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Snap options", nullptr));
        checkBoxGridPlane->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Grid plane", nullptr));
        checkBoxObjectVertex->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Object points", nullptr));
        checkBoxObjectCenter->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Object center", nullptr));
        checkBoxObjectEdge->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Object edge center", nullptr));
        checkBoxDrawing->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Drawing", nullptr));
        checkBoxDrawingLine->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Drawing line", nullptr));
        label->setText(QCoreApplication::translate("SVSnapOptionsDialog", "Distance:", nullptr));
        label_2->setText(QCoreApplication::translate("SVSnapOptionsDialog", "m", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSnapOptionsDialog: public Ui_SVSnapOptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSNAPOPTIONSDIALOG_H
