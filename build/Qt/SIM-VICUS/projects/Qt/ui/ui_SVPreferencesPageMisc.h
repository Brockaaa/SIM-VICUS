/********************************************************************************
** Form generated from reading UI file 'SVPreferencesPageMisc.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPREFERENCESPAGEMISC_H
#define UI_SVPREFERENCESPAGEMISC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPreferencesPageMisc
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBoxDontUseNativeDialogs;
    QLabel *label;
    QGroupBox *groupBoxAutoSaving;
    QGridLayout *gridLayout;
    QSpinBox *spinBoxAutosaveInterval;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonResetDoNotShowAgainDialogs;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVPreferencesPageMisc)
    {
        if (SVPreferencesPageMisc->objectName().isEmpty())
            SVPreferencesPageMisc->setObjectName(QString::fromUtf8("SVPreferencesPageMisc"));
        SVPreferencesPageMisc->resize(611, 491);
        verticalLayout_4 = new QVBoxLayout(SVPreferencesPageMisc);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(SVPreferencesPageMisc);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBoxDontUseNativeDialogs = new QCheckBox(groupBox);
        checkBoxDontUseNativeDialogs->setObjectName(QString::fromUtf8("checkBoxDontUseNativeDialogs"));

        verticalLayout->addWidget(checkBoxDontUseNativeDialogs);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setItalic(true);
        label->setFont(font);

        verticalLayout->addWidget(label);


        verticalLayout_4->addWidget(groupBox);

        groupBoxAutoSaving = new QGroupBox(SVPreferencesPageMisc);
        groupBoxAutoSaving->setObjectName(QString::fromUtf8("groupBoxAutoSaving"));
        groupBoxAutoSaving->setCheckable(true);
        gridLayout = new QGridLayout(groupBoxAutoSaving);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBoxAutosaveInterval = new QSpinBox(groupBoxAutoSaving);
        spinBoxAutosaveInterval->setObjectName(QString::fromUtf8("spinBoxAutosaveInterval"));
        spinBoxAutosaveInterval->setMinimumSize(QSize(100, 0));
        spinBoxAutosaveInterval->setLayoutDirection(Qt::LeftToRight);
        spinBoxAutosaveInterval->setMinimum(1);
        spinBoxAutosaveInterval->setMaximum(300);

        gridLayout->addWidget(spinBoxAutosaveInterval, 1, 1, 1, 1);

        label_5 = new QLabel(groupBoxAutoSaving);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(groupBoxAutoSaving);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        label_2 = new QLabel(groupBoxAutoSaving);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 0, 0, 1, 3);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout_4->addWidget(groupBoxAutoSaving);

        groupBox_2 = new QGroupBox(SVPreferencesPageMisc);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButtonResetDoNotShowAgainDialogs = new QPushButton(groupBox_2);
        pushButtonResetDoNotShowAgainDialogs->setObjectName(QString::fromUtf8("pushButtonResetDoNotShowAgainDialogs"));

        verticalLayout_3->addWidget(pushButtonResetDoNotShowAgainDialogs);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        retranslateUi(SVPreferencesPageMisc);

        QMetaObject::connectSlotsByName(SVPreferencesPageMisc);
    } // setupUi

    void retranslateUi(QWidget *SVPreferencesPageMisc)
    {
        groupBox->setTitle(QCoreApplication::translate("SVPreferencesPageMisc", "Miscellaneous Settings", nullptr));
        checkBoxDontUseNativeDialogs->setText(QCoreApplication::translate("SVPreferencesPageMisc", "Do not use native file/color dialogs", nullptr));
        label->setText(QCoreApplication::translate("SVPreferencesPageMisc", "Use this option if you have problems when selecting files or colors.", nullptr));
        groupBoxAutoSaving->setTitle(QCoreApplication::translate("SVPreferencesPageMisc", "Enable Autosaving", nullptr));
        label_5->setText(QCoreApplication::translate("SVPreferencesPageMisc", "Interval:", nullptr));
        label_6->setText(QCoreApplication::translate("SVPreferencesPageMisc", "min", nullptr));
        label_2->setText(QCoreApplication::translate("SVPreferencesPageMisc", "Backup files are placed alongside project files with extension '.vicus~'.", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVPreferencesPageMisc", "Reset Settings", nullptr));
        pushButtonResetDoNotShowAgainDialogs->setText(QCoreApplication::translate("SVPreferencesPageMisc", "Reset all \"Do not show again\" dialog confirmations", nullptr));
        (void)SVPreferencesPageMisc;
    } // retranslateUi

};

namespace Ui {
    class SVPreferencesPageMisc: public Ui_SVPreferencesPageMisc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPREFERENCESPAGEMISC_H
