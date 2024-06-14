/********************************************************************************
** Form generated from reading UI file 'SVDBScheduleAddDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSCHEDULEADDDIALOG_H
#define UI_SVDBSCHEDULEADDDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SVDBScheduleAddDialog
{
public:
    QGridLayout *gridLayout;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QComboBox *comboBoxScheduleType;
    QLabel *labelScheduleType_2;
    QComboBox *comboBoxInterpolationMethod;
    QLabel *labelScheduleType;
    QDialogButtonBox *buttonBox;
    QLabel *labelDisplayName;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SVDBScheduleAddDialog)
    {
        if (SVDBScheduleAddDialog->objectName().isEmpty())
            SVDBScheduleAddDialog->setObjectName(QString::fromUtf8("SVDBScheduleAddDialog"));
        SVDBScheduleAddDialog->resize(400, 207);
        gridLayout = new QGridLayout(SVDBScheduleAddDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBScheduleAddDialog);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 0, 1, 1, 2);

        comboBoxScheduleType = new QComboBox(SVDBScheduleAddDialog);
        comboBoxScheduleType->setObjectName(QString::fromUtf8("comboBoxScheduleType"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxScheduleType->sizePolicy().hasHeightForWidth());
        comboBoxScheduleType->setSizePolicy(sizePolicy);

        gridLayout->addWidget(comboBoxScheduleType, 1, 1, 1, 2);

        labelScheduleType_2 = new QLabel(SVDBScheduleAddDialog);
        labelScheduleType_2->setObjectName(QString::fromUtf8("labelScheduleType_2"));

        gridLayout->addWidget(labelScheduleType_2, 3, 0, 1, 1);

        comboBoxInterpolationMethod = new QComboBox(SVDBScheduleAddDialog);
        comboBoxInterpolationMethod->setObjectName(QString::fromUtf8("comboBoxInterpolationMethod"));

        gridLayout->addWidget(comboBoxInterpolationMethod, 3, 1, 1, 2);

        labelScheduleType = new QLabel(SVDBScheduleAddDialog);
        labelScheduleType->setObjectName(QString::fromUtf8("labelScheduleType"));

        gridLayout->addWidget(labelScheduleType, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SVDBScheduleAddDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 0, 1, 3);

        labelDisplayName = new QLabel(SVDBScheduleAddDialog);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(labelDisplayName, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 2, 1, 1);


        retranslateUi(SVDBScheduleAddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVDBScheduleAddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVDBScheduleAddDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVDBScheduleAddDialog);
    } // setupUi

    void retranslateUi(QDialog *SVDBScheduleAddDialog)
    {
        SVDBScheduleAddDialog->setWindowTitle(QCoreApplication::translate("SVDBScheduleAddDialog", "Dialog", nullptr));
        labelScheduleType_2->setText(QCoreApplication::translate("SVDBScheduleAddDialog", "Interpolation Method:", nullptr));
        labelScheduleType->setText(QCoreApplication::translate("SVDBScheduleAddDialog", "Schedule Type:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBScheduleAddDialog", "Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBScheduleAddDialog: public Ui_SVDBScheduleAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSCHEDULEADDDIALOG_H
