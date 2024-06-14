/********************************************************************************
** Form generated from reading UI file 'SVDBMaterialEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBMATERIALEDITWIDGET_H
#define UI_SVDBMATERIALEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVDBMaterialEditWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidgetThermal;
    QWidget *Thermal;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *labelDisplayName;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QtExt::ColorButton *pushButtonColor;
    QLabel *labelCategory;
    QComboBox *comboBoxCategory;
    QGridLayout *gridLayout;
    QLabel *labelConductivity;
    QtExt::ValidatingLineEdit *lineEditConductivity;
    QLabel *labelConductivity_2;
    QLabel *labelDensity;
    QtExt::ValidatingLineEdit *lineEditDensity;
    QLabel *labelDensity_5;
    QLabel *labelSpecHeatCapacity;
    QtExt::ValidatingLineEdit *lineEditSpecHeatCapacity;
    QLabel *labelSpecHeatCapacity_2;
    QGraphicsView *graphicsViewCategoryPicture;
    QWidget *EPD;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton;
    QTabWidget *tabWidgetLca;
    QWidget *production;
    QGridLayout *gridLayout_11;
    QLineEdit *lineEditCatA;
    QToolButton *toolButtonSelectCatA;
    QTableWidget *tableWidgetCatA;
    QWidget *usage;
    QGridLayout *gridLayout_7;
    QLineEdit *lineEditCatB;
    QToolButton *toolButtonSelectCatB;
    QTableWidget *tableWidgetCatB;
    QWidget *disposal;
    QGridLayout *gridLayout_12;
    QLineEdit *lineEditCatC;
    QToolButton *toolButtonSelectCatC;
    QTableWidget *tableWidgetCatC;
    QWidget *deposit;
    QGridLayout *gridLayout_13;
    QLineEdit *lineEditCatD;
    QToolButton *toolButtonSelectCatD;
    QTableWidget *tableWidgetCatD;
    QFrame *line;
    QWidget *Information;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *labelManufacturer;
    QtExt::LanguageStringEditWidget1 *lineEditManufacturer;
    QLabel *labelDataSource;
    QtExt::LanguageStringEditWidget1 *lineEditDataSource;
    QLabel *labelNotes;
    QtExt::LanguageStringEditWidget1 *lineEditNotes;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SVDBMaterialEditWidget)
    {
        if (SVDBMaterialEditWidget->objectName().isEmpty())
            SVDBMaterialEditWidget->setObjectName(QString::fromUtf8("SVDBMaterialEditWidget"));
        SVDBMaterialEditWidget->resize(623, 747);
        verticalLayout = new QVBoxLayout(SVDBMaterialEditWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidgetThermal = new QTabWidget(SVDBMaterialEditWidget);
        tabWidgetThermal->setObjectName(QString::fromUtf8("tabWidgetThermal"));
        Thermal = new QWidget();
        Thermal->setObjectName(QString::fromUtf8("Thermal"));
        gridLayout_3 = new QGridLayout(Thermal);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelDisplayName = new QLabel(Thermal);
        labelDisplayName->setObjectName(QString::fromUtf8("labelDisplayName"));
        labelDisplayName->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(labelDisplayName, 0, 0, 1, 1);

        lineEditName = new QtExt::LanguageStringEditWidget1(Thermal);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout_2->addWidget(lineEditName, 0, 1, 1, 1);

        pushButtonColor = new QtExt::ColorButton(Thermal);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonColor->sizePolicy().hasHeightForWidth());
        pushButtonColor->setSizePolicy(sizePolicy);
        pushButtonColor->setMinimumSize(QSize(40, 0));

        gridLayout_2->addWidget(pushButtonColor, 0, 2, 1, 1);

        labelCategory = new QLabel(Thermal);
        labelCategory->setObjectName(QString::fromUtf8("labelCategory"));
        labelCategory->setMinimumSize(QSize(60, 0));

        gridLayout_2->addWidget(labelCategory, 1, 0, 1, 1);

        comboBoxCategory = new QComboBox(Thermal);
        comboBoxCategory->setObjectName(QString::fromUtf8("comboBoxCategory"));

        gridLayout_2->addWidget(comboBoxCategory, 1, 1, 1, 2);


        verticalLayout_2->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelConductivity = new QLabel(Thermal);
        labelConductivity->setObjectName(QString::fromUtf8("labelConductivity"));

        gridLayout->addWidget(labelConductivity, 0, 0, 1, 1);

        lineEditConductivity = new QtExt::ValidatingLineEdit(Thermal);
        lineEditConductivity->setObjectName(QString::fromUtf8("lineEditConductivity"));

        gridLayout->addWidget(lineEditConductivity, 0, 1, 1, 1);

        labelConductivity_2 = new QLabel(Thermal);
        labelConductivity_2->setObjectName(QString::fromUtf8("labelConductivity_2"));

        gridLayout->addWidget(labelConductivity_2, 0, 2, 1, 1);

        labelDensity = new QLabel(Thermal);
        labelDensity->setObjectName(QString::fromUtf8("labelDensity"));

        gridLayout->addWidget(labelDensity, 1, 0, 1, 1);

        lineEditDensity = new QtExt::ValidatingLineEdit(Thermal);
        lineEditDensity->setObjectName(QString::fromUtf8("lineEditDensity"));

        gridLayout->addWidget(lineEditDensity, 1, 1, 1, 1);

        labelDensity_5 = new QLabel(Thermal);
        labelDensity_5->setObjectName(QString::fromUtf8("labelDensity_5"));

        gridLayout->addWidget(labelDensity_5, 1, 2, 1, 1);

        labelSpecHeatCapacity = new QLabel(Thermal);
        labelSpecHeatCapacity->setObjectName(QString::fromUtf8("labelSpecHeatCapacity"));

        gridLayout->addWidget(labelSpecHeatCapacity, 2, 0, 1, 1);

        lineEditSpecHeatCapacity = new QtExt::ValidatingLineEdit(Thermal);
        lineEditSpecHeatCapacity->setObjectName(QString::fromUtf8("lineEditSpecHeatCapacity"));

        gridLayout->addWidget(lineEditSpecHeatCapacity, 2, 1, 1, 1);

        labelSpecHeatCapacity_2 = new QLabel(Thermal);
        labelSpecHeatCapacity_2->setObjectName(QString::fromUtf8("labelSpecHeatCapacity_2"));

        gridLayout->addWidget(labelSpecHeatCapacity_2, 2, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        graphicsViewCategoryPicture = new QGraphicsView(Thermal);
        graphicsViewCategoryPicture->setObjectName(QString::fromUtf8("graphicsViewCategoryPicture"));

        verticalLayout_2->addWidget(graphicsViewCategoryPicture);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        tabWidgetThermal->addTab(Thermal, QString());
        EPD = new QWidget();
        EPD->setObjectName(QString::fromUtf8("EPD"));
        gridLayout_6 = new QGridLayout(EPD);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButton = new QPushButton(EPD);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_6->addWidget(pushButton, 3, 0, 1, 2);

        tabWidgetLca = new QTabWidget(EPD);
        tabWidgetLca->setObjectName(QString::fromUtf8("tabWidgetLca"));
        production = new QWidget();
        production->setObjectName(QString::fromUtf8("production"));
        gridLayout_11 = new QGridLayout(production);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        lineEditCatA = new QLineEdit(production);
        lineEditCatA->setObjectName(QString::fromUtf8("lineEditCatA"));
        lineEditCatA->setEnabled(false);

        gridLayout_11->addWidget(lineEditCatA, 0, 0, 1, 1);

        toolButtonSelectCatA = new QToolButton(production);
        toolButtonSelectCatA->setObjectName(QString::fromUtf8("toolButtonSelectCatA"));

        gridLayout_11->addWidget(toolButtonSelectCatA, 0, 1, 1, 1);

        tableWidgetCatA = new QTableWidget(production);
        tableWidgetCatA->setObjectName(QString::fromUtf8("tableWidgetCatA"));
        tableWidgetCatA->setMinimumSize(QSize(0, 300));

        gridLayout_11->addWidget(tableWidgetCatA, 1, 0, 1, 2);

        tabWidgetLca->addTab(production, QString());
        usage = new QWidget();
        usage->setObjectName(QString::fromUtf8("usage"));
        gridLayout_7 = new QGridLayout(usage);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        lineEditCatB = new QLineEdit(usage);
        lineEditCatB->setObjectName(QString::fromUtf8("lineEditCatB"));
        lineEditCatB->setEnabled(false);

        gridLayout_7->addWidget(lineEditCatB, 0, 0, 1, 1);

        toolButtonSelectCatB = new QToolButton(usage);
        toolButtonSelectCatB->setObjectName(QString::fromUtf8("toolButtonSelectCatB"));

        gridLayout_7->addWidget(toolButtonSelectCatB, 0, 1, 1, 1);

        tableWidgetCatB = new QTableWidget(usage);
        tableWidgetCatB->setObjectName(QString::fromUtf8("tableWidgetCatB"));
        tableWidgetCatB->setMinimumSize(QSize(0, 100));

        gridLayout_7->addWidget(tableWidgetCatB, 1, 0, 1, 2);

        tabWidgetLca->addTab(usage, QString());
        disposal = new QWidget();
        disposal->setObjectName(QString::fromUtf8("disposal"));
        gridLayout_12 = new QGridLayout(disposal);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        lineEditCatC = new QLineEdit(disposal);
        lineEditCatC->setObjectName(QString::fromUtf8("lineEditCatC"));
        lineEditCatC->setEnabled(false);

        gridLayout_12->addWidget(lineEditCatC, 0, 0, 1, 1);

        toolButtonSelectCatC = new QToolButton(disposal);
        toolButtonSelectCatC->setObjectName(QString::fromUtf8("toolButtonSelectCatC"));

        gridLayout_12->addWidget(toolButtonSelectCatC, 0, 1, 1, 1);

        tableWidgetCatC = new QTableWidget(disposal);
        tableWidgetCatC->setObjectName(QString::fromUtf8("tableWidgetCatC"));
        tableWidgetCatC->setMinimumSize(QSize(0, 100));

        gridLayout_12->addWidget(tableWidgetCatC, 1, 0, 1, 2);

        tabWidgetLca->addTab(disposal, QString());
        deposit = new QWidget();
        deposit->setObjectName(QString::fromUtf8("deposit"));
        gridLayout_13 = new QGridLayout(deposit);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        lineEditCatD = new QLineEdit(deposit);
        lineEditCatD->setObjectName(QString::fromUtf8("lineEditCatD"));
        lineEditCatD->setEnabled(false);

        gridLayout_13->addWidget(lineEditCatD, 0, 0, 1, 1);

        toolButtonSelectCatD = new QToolButton(deposit);
        toolButtonSelectCatD->setObjectName(QString::fromUtf8("toolButtonSelectCatD"));
        toolButtonSelectCatD->setEnabled(true);

        gridLayout_13->addWidget(toolButtonSelectCatD, 0, 1, 1, 1);

        tableWidgetCatD = new QTableWidget(deposit);
        tableWidgetCatD->setObjectName(QString::fromUtf8("tableWidgetCatD"));

        gridLayout_13->addWidget(tableWidgetCatD, 1, 0, 1, 2);

        tabWidgetLca->addTab(deposit, QString());

        gridLayout_6->addWidget(tabWidgetLca, 0, 0, 1, 2);

        line = new QFrame(EPD);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line, 2, 0, 1, 2);

        tabWidgetThermal->addTab(EPD, QString());
        Information = new QWidget();
        Information->setObjectName(QString::fromUtf8("Information"));
        gridLayout_5 = new QGridLayout(Information);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        labelManufacturer = new QLabel(Information);
        labelManufacturer->setObjectName(QString::fromUtf8("labelManufacturer"));

        gridLayout_4->addWidget(labelManufacturer, 0, 0, 1, 1);

        lineEditManufacturer = new QtExt::LanguageStringEditWidget1(Information);
        lineEditManufacturer->setObjectName(QString::fromUtf8("lineEditManufacturer"));

        gridLayout_4->addWidget(lineEditManufacturer, 0, 1, 1, 1);

        labelDataSource = new QLabel(Information);
        labelDataSource->setObjectName(QString::fromUtf8("labelDataSource"));

        gridLayout_4->addWidget(labelDataSource, 1, 0, 1, 1);

        lineEditDataSource = new QtExt::LanguageStringEditWidget1(Information);
        lineEditDataSource->setObjectName(QString::fromUtf8("lineEditDataSource"));

        gridLayout_4->addWidget(lineEditDataSource, 1, 1, 1, 1);

        labelNotes = new QLabel(Information);
        labelNotes->setObjectName(QString::fromUtf8("labelNotes"));

        gridLayout_4->addWidget(labelNotes, 2, 0, 1, 1);

        lineEditNotes = new QtExt::LanguageStringEditWidget1(Information);
        lineEditNotes->setObjectName(QString::fromUtf8("lineEditNotes"));

        gridLayout_4->addWidget(lineEditNotes, 2, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 234, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidgetThermal->addTab(Information, QString());

        verticalLayout->addWidget(tabWidgetThermal);

        QWidget::setTabOrder(lineEditDensity, lineEditSpecHeatCapacity);
        QWidget::setTabOrder(lineEditSpecHeatCapacity, graphicsViewCategoryPicture);
        QWidget::setTabOrder(graphicsViewCategoryPicture, lineEditManufacturer);
        QWidget::setTabOrder(lineEditManufacturer, lineEditDataSource);
        QWidget::setTabOrder(lineEditDataSource, lineEditNotes);
        QWidget::setTabOrder(lineEditNotes, tabWidgetThermal);
        QWidget::setTabOrder(tabWidgetThermal, lineEditConductivity);
        QWidget::setTabOrder(lineEditConductivity, lineEditName);
        QWidget::setTabOrder(lineEditName, pushButtonColor);
        QWidget::setTabOrder(pushButtonColor, comboBoxCategory);

        retranslateUi(SVDBMaterialEditWidget);

        tabWidgetThermal->setCurrentIndex(0);
        tabWidgetLca->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVDBMaterialEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBMaterialEditWidget)
    {
        labelDisplayName->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Name:", nullptr));
        labelCategory->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Category:", nullptr));
        labelConductivity->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Conductivity:", nullptr));
        labelConductivity_2->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "W/mK", nullptr));
        labelDensity->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Density:", nullptr));
        labelDensity_5->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "kg/m3", nullptr));
        labelSpecHeatCapacity->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Spec. heat capacity:", nullptr));
        labelSpecHeatCapacity_2->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "J/kgK", nullptr));
        tabWidgetThermal->setTabText(tabWidgetThermal->indexOf(Thermal), QCoreApplication::translate("SVDBMaterialEditWidget", "Thermal", nullptr));
#if QT_CONFIG(accessibility)
        EPD->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Assign EPD to all Categories", nullptr));
        toolButtonSelectCatA->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "...", nullptr));
        tabWidgetLca->setTabText(tabWidgetLca->indexOf(production), QCoreApplication::translate("SVDBMaterialEditWidget", "Production", nullptr));
        toolButtonSelectCatB->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "...", nullptr));
        tabWidgetLca->setTabText(tabWidgetLca->indexOf(usage), QCoreApplication::translate("SVDBMaterialEditWidget", "Usage", nullptr));
        toolButtonSelectCatC->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "...", nullptr));
        tabWidgetLca->setTabText(tabWidgetLca->indexOf(disposal), QCoreApplication::translate("SVDBMaterialEditWidget", "Disposal", nullptr));
        toolButtonSelectCatD->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "...", nullptr));
        tabWidgetLca->setTabText(tabWidgetLca->indexOf(deposit), QCoreApplication::translate("SVDBMaterialEditWidget", "Deposit", nullptr));
        tabWidgetThermal->setTabText(tabWidgetThermal->indexOf(EPD), QCoreApplication::translate("SVDBMaterialEditWidget", "EPD", nullptr));
        labelManufacturer->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Manufacturer:", nullptr));
        labelDataSource->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Data source:", nullptr));
        labelNotes->setText(QCoreApplication::translate("SVDBMaterialEditWidget", "Notes:", nullptr));
        tabWidgetThermal->setTabText(tabWidgetThermal->indexOf(Information), QCoreApplication::translate("SVDBMaterialEditWidget", "Information", nullptr));
        (void)SVDBMaterialEditWidget;
    } // retranslateUi

};

namespace Ui {
    class SVDBMaterialEditWidget: public Ui_SVDBMaterialEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBMATERIALEDITWIDGET_H
