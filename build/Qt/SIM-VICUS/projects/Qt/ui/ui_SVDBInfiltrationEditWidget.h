/********************************************************************************
** Form generated from reading UI file 'SVDBInfiltrationEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBINFILTRATIONEDITWIDGET_H
#define UI_SVDBINFILTRATIONEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBInfiltrationEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QLabel *labelShieldCoefficientUnit;
    QtExt::ValidatingLineEdit *lineEditAirChangeRate;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QLabel *labelShieldCoefficient;
    QLabel *labelDisplayName;
    QtExt::ColorButton *pushButtonColor;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *labelAirChangeRateUnit;
    QLabel *labelCategory_2;
    QLabel *labelAirChangeRate;
    QComboBox *comboBoxMethod;
    QtExt::ValidatingLineEdit *lineEditShieldCoefficient;
    QwtPlot *widgetPlot;

    void setupUi(QWidget *SVDBInfiltrationEditWidget)
    {
        if (SVDBInfiltrationEditWidget->objectName().isEmpty())
            SVDBInfiltrationEditWidget->setObjectName(QString::fromUtf8("SVDBInfiltrationEditWidget"));
        SVDBInfiltrationEditWidget->resize(479, 482);
        gridLayoutMaster = new QGridLayout(SVDBInfiltrationEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        labelShieldCoefficientUnit = new QLabel(SVDBInfiltrationEditWidget);
        labelShieldCoefficientUnit->setObjectName(QString::fromUtf8("labelShieldCoefficientUnit"));

        gridLayoutMaster->addWidget(labelShieldCoefficientUnit, 3, 3, 1, 1);

        lineEditAirChangeRate = new QtExt::ValidatingLineEdit(SVDBInfiltrationEditWidget);
        lineEditAirChangeRate->setObjectName(QString::fromUtf8("lineEditAirChangeRate"));
        lineEditAirChangeRate->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditAirChangeRate, 2, 2, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBInfiltrationEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 1, 1, 2);

        labelShieldCoefficient = new QLabel(SVDBInfiltrationEditWidget);
        labelShieldCoefficient->setObjectName(QString::fromUtf8("labelShieldCoefficient"));

        gridLayoutMaster->addWidget(labelShieldCoefficient, 3, 0, 1, 2);

        labelDisplayName = new QLabel(SVDBInfiltrationEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBInfiltrationEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 3, 1, 1);

        groupBox = new QGroupBox(SVDBInfiltrationEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);


        gridLayoutMaster->addWidget(groupBox, 4, 0, 1, 3);

        labelAirChangeRateUnit = new QLabel(SVDBInfiltrationEditWidget);
        labelAirChangeRateUnit->setObjectName(QString::fromUtf8("labelAirChangeRateUnit"));

        gridLayoutMaster->addWidget(labelAirChangeRateUnit, 2, 3, 1, 1);

        labelCategory_2 = new QLabel(SVDBInfiltrationEditWidget);
        labelCategory_2->setObjectName(QString::fromUtf8("labelCategory_2"));

        gridLayoutMaster->addWidget(labelCategory_2, 1, 0, 1, 1);

        labelAirChangeRate = new QLabel(SVDBInfiltrationEditWidget);
        labelAirChangeRate->setObjectName(QString::fromUtf8("labelAirChangeRate"));

        gridLayoutMaster->addWidget(labelAirChangeRate, 2, 0, 1, 2);

        comboBoxMethod = new QComboBox(SVDBInfiltrationEditWidget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        gridLayoutMaster->addWidget(comboBoxMethod, 1, 1, 1, 3);

        lineEditShieldCoefficient = new QtExt::ValidatingLineEdit(SVDBInfiltrationEditWidget);
        lineEditShieldCoefficient->setObjectName(QString::fromUtf8("lineEditShieldCoefficient"));
        lineEditShieldCoefficient->setMaximumSize(QSize(100, 16777215));

        gridLayoutMaster->addWidget(lineEditShieldCoefficient, 3, 2, 1, 1);

        widgetPlot = new QwtPlot(SVDBInfiltrationEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 5, 0, 1, 3);


        retranslateUi(SVDBInfiltrationEditWidget);

        QMetaObject::connectSlotsByName(SVDBInfiltrationEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBInfiltrationEditWidget)
    {
        SVDBInfiltrationEditWidget->setWindowTitle(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Form", nullptr));
        labelShieldCoefficientUnit->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "-", nullptr));
        labelShieldCoefficient->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Shield Coefficient:", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Name:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Mode Parameter", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Implement later Blast and DOE model with constant, temperature and wind velocity values.", nullptr));
        labelAirChangeRateUnit->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "1/h", nullptr));
        labelCategory_2->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Method:", nullptr));
        labelAirChangeRate->setText(QCoreApplication::translate("SVDBInfiltrationEditWidget", "Air Change Rate:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBInfiltrationEditWidget: public Ui_SVDBInfiltrationEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBINFILTRATIONEDITWIDGET_H
