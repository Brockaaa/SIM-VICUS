/********************************************************************************
** Form generated from reading UI file 'SVPreferencesPageStyle.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPREFERENCESPAGESTYLE_H
#define UI_SVPREFERENCESPAGESTYLE_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPreferencesPageStyle
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTheme;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelWhitePreview;
    QRadioButton *radioButtonWhite;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelDarkPreview;
    QRadioButton *radioButtonDark;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBoxScaling;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QtExt::ColorButton *pushButtonSelectedSurfaceColor;
    QLabel *label_3;
    QLabel *label_4;
    QtExt::ColorButton *pushButtonMinorGridColor;
    QtExt::ColorButton *pushButtonMajorGridColor;
    QSpacerItem *horizontalSpacer;
    QtExt::ColorButton *pushButtonSceneBackgroundColor;
    QLabel *label_2;
    QPushButton *pushButtonDefault;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVPreferencesPageStyle)
    {
        if (SVPreferencesPageStyle->objectName().isEmpty())
            SVPreferencesPageStyle->setObjectName(QString::fromUtf8("SVPreferencesPageStyle"));
        SVPreferencesPageStyle->resize(669, 548);
        verticalLayout = new QVBoxLayout(SVPreferencesPageStyle);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(SVPreferencesPageStyle);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelTheme = new QLabel(groupBox_2);
        labelTheme->setObjectName(QString::fromUtf8("labelTheme"));

        horizontalLayout->addWidget(labelTheme);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelWhitePreview = new QLabel(groupBox_2);
        labelWhitePreview->setObjectName(QString::fromUtf8("labelWhitePreview"));
        labelWhitePreview->setMinimumSize(QSize(200, 100));

        verticalLayout_2->addWidget(labelWhitePreview);

        radioButtonWhite = new QRadioButton(groupBox_2);
        radioButtonWhite->setObjectName(QString::fromUtf8("radioButtonWhite"));

        verticalLayout_2->addWidget(radioButtonWhite);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        labelDarkPreview = new QLabel(groupBox_2);
        labelDarkPreview->setObjectName(QString::fromUtf8("labelDarkPreview"));
        labelDarkPreview->setMinimumSize(QSize(200, 100));

        verticalLayout_3->addWidget(labelDarkPreview);

        radioButtonDark = new QRadioButton(groupBox_2);
        radioButtonDark->setObjectName(QString::fromUtf8("radioButtonDark"));

        verticalLayout_3->addWidget(radioButtonDark);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(SVPreferencesPageStyle);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        checkBoxScaling = new QCheckBox(groupBox_3);
        checkBoxScaling->setObjectName(QString::fromUtf8("checkBoxScaling"));

        gridLayout_3->addWidget(checkBoxScaling, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(SVPreferencesPageStyle);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        pushButtonSelectedSurfaceColor = new QtExt::ColorButton(groupBox);
        pushButtonSelectedSurfaceColor->setObjectName(QString::fromUtf8("pushButtonSelectedSurfaceColor"));

        gridLayout_2->addWidget(pushButtonSelectedSurfaceColor, 3, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        pushButtonMinorGridColor = new QtExt::ColorButton(groupBox);
        pushButtonMinorGridColor->setObjectName(QString::fromUtf8("pushButtonMinorGridColor"));

        gridLayout_2->addWidget(pushButtonMinorGridColor, 2, 1, 1, 1);

        pushButtonMajorGridColor = new QtExt::ColorButton(groupBox);
        pushButtonMajorGridColor->setObjectName(QString::fromUtf8("pushButtonMajorGridColor"));

        gridLayout_2->addWidget(pushButtonMajorGridColor, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        pushButtonSceneBackgroundColor = new QtExt::ColorButton(groupBox);
        pushButtonSceneBackgroundColor->setObjectName(QString::fromUtf8("pushButtonSceneBackgroundColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonSceneBackgroundColor->sizePolicy().hasHeightForWidth());
        pushButtonSceneBackgroundColor->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButtonSceneBackgroundColor, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        pushButtonDefault = new QPushButton(groupBox);
        pushButtonDefault->setObjectName(QString::fromUtf8("pushButtonDefault"));

        gridLayout_2->addWidget(pushButtonDefault, 0, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(SVPreferencesPageStyle);

        QMetaObject::connectSlotsByName(SVPreferencesPageStyle);
    } // setupUi

    void retranslateUi(QWidget *SVPreferencesPageStyle)
    {
        groupBox_2->setTitle(QCoreApplication::translate("SVPreferencesPageStyle", "Theme", nullptr));
        labelTheme->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Choose Theme:", nullptr));
        labelWhitePreview->setText(QString());
        radioButtonWhite->setText(QCoreApplication::translate("SVPreferencesPageStyle", "white", nullptr));
        labelDarkPreview->setText(QString());
        radioButtonDark->setText(QCoreApplication::translate("SVPreferencesPageStyle", "dark", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVPreferencesPageStyle", "High DPI Options", nullptr));
        checkBoxScaling->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Use scaling for high resolution displays", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVPreferencesPageStyle", "Theme Settings", nullptr));
        label->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Scene background color:", nullptr));
        label_3->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Minor grid line color:", nullptr));
        label_4->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Selected object color:", nullptr));
        label_2->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Major grid line color:", nullptr));
        pushButtonDefault->setText(QCoreApplication::translate("SVPreferencesPageStyle", "Reset", nullptr));
        (void)SVPreferencesPageStyle;
    } // retranslateUi

};

namespace Ui {
    class SVPreferencesPageStyle: public Ui_SVPreferencesPageStyle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPREFERENCESPAGESTYLE_H
