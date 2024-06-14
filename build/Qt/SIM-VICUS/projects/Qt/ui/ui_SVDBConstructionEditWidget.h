/********************************************************************************
** Form generated from reading UI file 'SVDBConstructionEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBCONSTRUCTIONEDITWIDGET_H
#define UI_SVDBCONSTRUCTIONEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_ConstructionViewWidget.h"
#include "QtExt_ValidatingLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_SVDBConstructionEditWidget
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *comboBoxMaterialKind;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QtExt::LanguageStringEditWidget1 *lineEditDataSource;
    QLabel *label_4;
    QComboBox *comboBoxConstructionUsage;
    QLabel *label_2;
    QComboBox *comboBoxInsulationKind;
    QLabel *label_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QtExt::ValidatingLineEdit *lineEditImpactSound;
    QLabel *label_8;
    QtExt::ValidatingLineEdit *lineEditAirSoundRes;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *spinBoxLayerCount;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *labelUValue;
    QLineEdit *lineEditUValue;
    QLabel *labelUValueUnit;
    QFrame *line;
    QPushButton *pushButtonFlipConstruction;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QtExt::ConstructionViewWidget *widgetConstructionView;

    void setupUi(QWidget *SVDBConstructionEditWidget)
    {
        if (SVDBConstructionEditWidget->objectName().isEmpty())
            SVDBConstructionEditWidget->setObjectName(QString::fromUtf8("SVDBConstructionEditWidget"));
        SVDBConstructionEditWidget->resize(567, 674);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVDBConstructionEditWidget->sizePolicy().hasHeightForWidth());
        SVDBConstructionEditWidget->setSizePolicy(sizePolicy);
        SVDBConstructionEditWidget->setMinimumSize(QSize(0, 440));
        horizontalLayout_4 = new QHBoxLayout(SVDBConstructionEditWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(SVDBConstructionEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxMaterialKind = new QComboBox(groupBox);
        comboBoxMaterialKind->setObjectName(QString::fromUtf8("comboBoxMaterialKind"));

        gridLayout->addWidget(comboBoxMaterialKind, 5, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(label_3);

        lineEditName = new QtExt::LanguageStringEditWidget1(groupBox);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout_3->addWidget(lineEditName);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_5);

        lineEditDataSource = new QtExt::LanguageStringEditWidget1(groupBox);
        lineEditDataSource->setObjectName(QString::fromUtf8("lineEditDataSource"));

        horizontalLayout_6->addWidget(lineEditDataSource);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        comboBoxConstructionUsage = new QComboBox(groupBox);
        comboBoxConstructionUsage->setObjectName(QString::fromUtf8("comboBoxConstructionUsage"));

        gridLayout->addWidget(comboBoxConstructionUsage, 3, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        comboBoxInsulationKind = new QComboBox(groupBox);
        comboBoxInsulationKind->setObjectName(QString::fromUtf8("comboBoxInsulationKind"));

        gridLayout->addWidget(comboBoxInsulationKind, 4, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_3 = new QGroupBox(SVDBConstructionEditWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setEnabled(false);
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(170, 0));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        lineEditImpactSound = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditImpactSound->setObjectName(QString::fromUtf8("lineEditImpactSound"));

        gridLayout_2->addWidget(lineEditImpactSound, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(170, 0));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        lineEditAirSoundRes = new QtExt::ValidatingLineEdit(groupBox_3);
        lineEditAirSoundRes->setObjectName(QString::fromUtf8("lineEditAirSoundRes"));

        gridLayout_2->addWidget(lineEditAirSoundRes, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 0, 2, 1, 2);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(SVDBConstructionEditWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label);

        spinBoxLayerCount = new QSpinBox(groupBox_2);
        spinBoxLayerCount->setObjectName(QString::fromUtf8("spinBoxLayerCount"));
        spinBoxLayerCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxLayerCount->setMinimum(1);
        spinBoxLayerCount->setMaximum(15);

        horizontalLayout_5->addWidget(spinBoxLayerCount);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelUValue = new QLabel(groupBox_2);
        labelUValue->setObjectName(QString::fromUtf8("labelUValue"));

        horizontalLayout->addWidget(labelUValue);

        lineEditUValue = new QLineEdit(groupBox_2);
        lineEditUValue->setObjectName(QString::fromUtf8("lineEditUValue"));
        lineEditUValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditUValue->setReadOnly(true);

        horizontalLayout->addWidget(lineEditUValue);

        labelUValueUnit = new QLabel(groupBox_2);
        labelUValueUnit->setObjectName(QString::fromUtf8("labelUValueUnit"));

        horizontalLayout->addWidget(labelUValueUnit);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        pushButtonFlipConstruction = new QPushButton(groupBox_2);
        pushButtonFlipConstruction->setObjectName(QString::fromUtf8("pushButtonFlipConstruction"));

        verticalLayout->addWidget(pushButtonFlipConstruction);

        splitter = new QSplitter(groupBox_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        splitter->addWidget(tableWidget);
        tableWidget->verticalHeader()->setVisible(false);
        widgetConstructionView = new QtExt::ConstructionViewWidget(splitter);
        widgetConstructionView->setObjectName(QString::fromUtf8("widgetConstructionView"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetConstructionView->sizePolicy().hasHeightForWidth());
        widgetConstructionView->setSizePolicy(sizePolicy2);
        widgetConstructionView->setMinimumSize(QSize(150, 0));
        splitter->addWidget(widgetConstructionView);

        verticalLayout->addWidget(splitter);


        verticalLayout_2->addWidget(groupBox_2);


        horizontalLayout_4->addLayout(verticalLayout_2);


        retranslateUi(SVDBConstructionEditWidget);

        QMetaObject::connectSlotsByName(SVDBConstructionEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBConstructionEditWidget)
    {
        SVDBConstructionEditWidget->setWindowTitle(QCoreApplication::translate("SVDBConstructionEditWidget", "Construction editor", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBConstructionEditWidget", "Construction description", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Name:", nullptr));
        label_5->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Data source:", nullptr));
        label_4->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Main/load bearing material:", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Insulation type:", nullptr));
        label_6->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Construction usage:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SVDBConstructionEditWidget", "Acoustic properties", nullptr));
        label_7->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Impact Sound value:", nullptr));
        label_8->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Air Sound Resistance:", nullptr));
        label_9->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "dB", nullptr));
        label_10->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "dB", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SVDBConstructionEditWidget", "Material layers", nullptr));
        label->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Number of layers:", nullptr));
        labelUValue->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "<html><head/><body><p>U-Value <span style=\" font-size:7pt;\">(assuming standard heat transfer coefficients)</span>:</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        lineEditUValue->setToolTip(QCoreApplication::translate("SVDBConstructionEditWidget", "The U-value is calculated using standard inside/outside heat transfer surface resistances of 0.13 and 0.04 W/m2K.", nullptr));
#endif // QT_CONFIG(tooltip)
        labelUValueUnit->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "<html><head/><body><p>W/m<span style=\" vertical-align:super;\">2</span>K</p></body></html>", nullptr));
        pushButtonFlipConstruction->setText(QCoreApplication::translate("SVDBConstructionEditWidget", "Flip construction layers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBConstructionEditWidget: public Ui_SVDBConstructionEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBCONSTRUCTIONEDITWIDGET_H
