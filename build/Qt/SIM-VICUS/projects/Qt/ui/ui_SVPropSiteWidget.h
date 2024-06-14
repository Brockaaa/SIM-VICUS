/********************************************************************************
** Form generated from reading UI file 'SVPropSiteWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPROPSITEWIDGET_H
#define UI_SVPROPSITEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPropSiteWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEditMaxDimensions;
    QLineEdit *lineEditGridLineSpacing;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *lineEditViewDepth;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVPropSiteWidget)
    {
        if (SVPropSiteWidget->objectName().isEmpty())
            SVPropSiteWidget->setObjectName(QString::fromUtf8("SVPropSiteWidget"));
        SVPropSiteWidget->resize(363, 447);
        verticalLayout = new QVBoxLayout(SVPropSiteWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(SVPropSiteWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditMaxDimensions = new QLineEdit(groupBox_2);
        lineEditMaxDimensions->setObjectName(QString::fromUtf8("lineEditMaxDimensions"));

        gridLayout->addWidget(lineEditMaxDimensions, 0, 1, 1, 1);

        lineEditGridLineSpacing = new QLineEdit(groupBox_2);
        lineEditGridLineSpacing->setObjectName(QString::fromUtf8("lineEditGridLineSpacing"));

        gridLayout->addWidget(lineEditGridLineSpacing, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEditViewDepth = new QLineEdit(groupBox_2);
        lineEditViewDepth->setObjectName(QString::fromUtf8("lineEditViewDepth"));

        gridLayout->addWidget(lineEditViewDepth, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 3, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 222, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SVPropSiteWidget);

        QMetaObject::connectSlotsByName(SVPropSiteWidget);
    } // setupUi

    void retranslateUi(QWidget *SVPropSiteWidget)
    {
        SVPropSiteWidget->setWindowTitle(QCoreApplication::translate("SVPropSiteWidget", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVPropSiteWidget", "Grid settings", nullptr));
        label_6->setText(QCoreApplication::translate("SVPropSiteWidget", "m", nullptr));
        label_2->setText(QCoreApplication::translate("SVPropSiteWidget", "Dimensions:", nullptr));
        label_4->setText(QCoreApplication::translate("SVPropSiteWidget", "View depth:", nullptr));
        label_3->setText(QCoreApplication::translate("SVPropSiteWidget", "Major grid line spacing:", nullptr));
        label_7->setText(QCoreApplication::translate("SVPropSiteWidget", "m", nullptr));
        label_5->setText(QCoreApplication::translate("SVPropSiteWidget", "m", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPropSiteWidget: public Ui_SVPropSiteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPROPSITEWIDGET_H
