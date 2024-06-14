/********************************************************************************
** Form generated from reading UI file 'SVDBVentilationNaturalEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBVENTILATIONNATURALEDITWIDGET_H
#define UI_SVDBVENTILATIONNATURALEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>

QT_BEGIN_NAMESPACE

class Ui_SVDBVentilationNaturalEditWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QLabel *labelDisplayName;
    QLabel *labelScheduleHeating;
    QLabel *labelAirChangeRate;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QwtPlot *widgetPlot;
    QtExt::ValidatingLineEdit *lineEditAirChangeRate;
    QToolButton *toolButtonSelectSchedule;
    QLabel *labelConvectiveFactorUnit_2;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelConvectiveFactorUnit;
    QLineEdit *lineEditScheduleName;
    QtExt::LanguageStringEditWidget1 *lineEditName;

    void setupUi(QWidget *SVDBVentilationNaturalEditWidget)
    {
        if (SVDBVentilationNaturalEditWidget->objectName().isEmpty())
            SVDBVentilationNaturalEditWidget->setObjectName(QString::fromUtf8("SVDBVentilationNaturalEditWidget"));
        SVDBVentilationNaturalEditWidget->resize(479, 397);
        gridLayoutMaster = new QGridLayout(SVDBVentilationNaturalEditWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        labelDisplayName = new QLabel(SVDBVentilationNaturalEditWidget);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));

        gridLayoutMaster->addWidget(labelDisplayName, 0, 0, 1, 1);

        labelScheduleHeating = new QLabel(SVDBVentilationNaturalEditWidget);
        labelScheduleHeating->setObjectName(QString::fromUtf8("labelScheduleHeating"));

        gridLayoutMaster->addWidget(labelScheduleHeating, 2, 0, 1, 1);

        labelAirChangeRate = new QLabel(SVDBVentilationNaturalEditWidget);
        labelAirChangeRate->setObjectName(QString::fromUtf8("labelAirChangeRate"));

        gridLayoutMaster->addWidget(labelAirChangeRate, 1, 0, 1, 2);

        groupBox = new QGroupBox(SVDBVentilationNaturalEditWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);


        gridLayoutMaster->addWidget(groupBox, 3, 0, 1, 3);

        widgetPlot = new QwtPlot(SVDBVentilationNaturalEditWidget);
        widgetPlot->setObjectName(QString::fromUtf8("widgetPlot"));

        gridLayoutMaster->addWidget(widgetPlot, 4, 0, 1, 3);

        lineEditAirChangeRate = new QtExt::ValidatingLineEdit(SVDBVentilationNaturalEditWidget);
        lineEditAirChangeRate->setObjectName(QString::fromUtf8("lineEditAirChangeRate"));
        lineEditAirChangeRate->setMaximumSize(QSize(16777215, 16777215));

        gridLayoutMaster->addWidget(lineEditAirChangeRate, 1, 2, 1, 1);

        toolButtonSelectSchedule = new QToolButton(SVDBVentilationNaturalEditWidget);
        toolButtonSelectSchedule->setObjectName(QString::fromUtf8("toolButtonSelectSchedule"));

        gridLayoutMaster->addWidget(toolButtonSelectSchedule, 2, 4, 1, 1);

        labelConvectiveFactorUnit_2 = new QLabel(SVDBVentilationNaturalEditWidget);
        labelConvectiveFactorUnit_2->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit_2"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit_2, 2, 3, 1, 1);

        pushButtonColor = new QtExt::ColorButton(SVDBVentilationNaturalEditWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);

        gridLayoutMaster->addWidget(pushButtonColor, 0, 3, 1, 1);

        labelConvectiveFactorUnit = new QLabel(SVDBVentilationNaturalEditWidget);
        labelConvectiveFactorUnit->setObjectName(QString::fromUtf8("labelConvectiveFactorUnit"));

        gridLayoutMaster->addWidget(labelConvectiveFactorUnit, 1, 3, 1, 1);

        lineEditScheduleName = new QLineEdit(SVDBVentilationNaturalEditWidget);
        lineEditScheduleName->setObjectName(QString::fromUtf8("lineEditScheduleName"));
        lineEditScheduleName->setReadOnly(true);

        gridLayoutMaster->addWidget(lineEditScheduleName, 2, 2, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(SVDBVentilationNaturalEditWidget);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayoutMaster->addWidget(lineEditName, 0, 2, 1, 1);


        retranslateUi(SVDBVentilationNaturalEditWidget);

        QMetaObject::connectSlotsByName(SVDBVentilationNaturalEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBVentilationNaturalEditWidget)
    {
        SVDBVentilationNaturalEditWidget->setWindowTitle(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Form", nullptr));
        labelDisplayName->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Name:", nullptr));
        labelScheduleHeating->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Schedule Name:", nullptr));
        labelAirChangeRate->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Air Change Rate:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Model Parameter", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "Implement later Blast and DOE model with constant, temperature and wind velocity values.", nullptr));
        toolButtonSelectSchedule->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "...", nullptr));
        labelConvectiveFactorUnit_2->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "1/h", nullptr));
        labelConvectiveFactorUnit->setText(QCoreApplication::translate("SVDBVentilationNaturalEditWidget", "1/h", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBVentilationNaturalEditWidget: public Ui_SVDBVentilationNaturalEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBVENTILATIONNATURALEDITWIDGET_H
