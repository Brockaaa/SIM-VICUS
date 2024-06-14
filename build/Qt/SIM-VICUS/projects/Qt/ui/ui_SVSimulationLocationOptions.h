/********************************************************************************
** Form generated from reading UI file 'SVSimulationLocationOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONLOCATIONOPTIONS_H
#define UI_SVSIMULATIONLOCATIONOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtExt_ValueInputComboBox.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVSimulationLocationOptions
{
public:
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditTextFilter;
    QTableView *tableViewClimateFiles;
    QtExt::BrowseFilenameWidget *filepathClimateDataFile;
    QLabel *labelTextFilter;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButtonUserPathAbsolute;
    QRadioButton *radioButtonUserPathRelative;
    QLabel *label;
    QWidget *widgetUserPathOptions;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_2;
    QRadioButton *radioButtonFromDB;
    QRadioButton *radioButtonCustomFilePath;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButtonOpenDWDConverter;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowserDescription;
    QFrame *line;
    QFrame *line_3;
    QLabel *label_2;
    QLabel *label_3;
    QFormLayout *formLayout;
    QLabel *labelLatitude;
    QtExt::ValidatingLineEdit *lineEditLatitude;
    QLabel *labelLongitude;
    QtExt::ValidatingLineEdit *lineEditLongitude;
    QLabel *labelTimeZone;
    QComboBox *comboBoxTimeZone;
    QLabel *label_4;
    QtExt::ValueInputComboBox *comboBoxAlbedo;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget1;
    QVBoxLayout *plotLayout;
    QwtPlot *plotTemp;
    QwtPlot *plotRelHum;
    QwtPlot *plotRadShortWave;
    QwtPlot *plotRadLongWave;
    QwtPlot *plotWind;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SVSimulationLocationOptions)
    {
        if (SVSimulationLocationOptions->objectName().isEmpty())
            SVSimulationLocationOptions->setObjectName(QString::fromUtf8("SVSimulationLocationOptions"));
        SVSimulationLocationOptions->resize(1135, 696);
        gridLayout_3 = new QGridLayout(SVSimulationLocationOptions);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter = new QSplitter(SVSimulationLocationOptions);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditTextFilter = new QLineEdit(layoutWidget);
        lineEditTextFilter->setObjectName(QString::fromUtf8("lineEditTextFilter"));

        gridLayout_2->addWidget(lineEditTextFilter, 3, 1, 1, 2);

        tableViewClimateFiles = new QTableView(layoutWidget);
        tableViewClimateFiles->setObjectName(QString::fromUtf8("tableViewClimateFiles"));

        gridLayout_2->addWidget(tableViewClimateFiles, 4, 0, 1, 3);

        filepathClimateDataFile = new QtExt::BrowseFilenameWidget(layoutWidget);
        filepathClimateDataFile->setObjectName(QString::fromUtf8("filepathClimateDataFile"));
        filepathClimateDataFile->setMinimumSize(QSize(0, 20));

        gridLayout_2->addWidget(filepathClimateDataFile, 5, 1, 1, 1);

        labelTextFilter = new QLabel(layoutWidget);
        labelTextFilter->setObjectName(QString::fromUtf8("labelTextFilter"));

        gridLayout_2->addWidget(labelTextFilter, 3, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        radioButtonUserPathAbsolute = new QRadioButton(layoutWidget);
        radioButtonUserPathAbsolute->setObjectName(QString::fromUtf8("radioButtonUserPathAbsolute"));
        radioButtonUserPathAbsolute->setChecked(true);

        verticalLayout_3->addWidget(radioButtonUserPathAbsolute);

        radioButtonUserPathRelative = new QRadioButton(layoutWidget);
        radioButtonUserPathRelative->setObjectName(QString::fromUtf8("radioButtonUserPathRelative"));

        verticalLayout_3->addWidget(radioButtonUserPathRelative);


        gridLayout_2->addLayout(verticalLayout_3, 6, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 2);

        widgetUserPathOptions = new QWidget(layoutWidget);
        widgetUserPathOptions->setObjectName(QString::fromUtf8("widgetUserPathOptions"));
        verticalLayout_2 = new QVBoxLayout(widgetUserPathOptions);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        gridLayout_2->addWidget(widgetUserPathOptions, 6, 0, 1, 1);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 1, 0, 1, 3);

        radioButtonFromDB = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(SVSimulationLocationOptions);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonFromDB);
        radioButtonFromDB->setObjectName(QString::fromUtf8("radioButtonFromDB"));

        gridLayout_2->addWidget(radioButtonFromDB, 2, 0, 1, 3);

        radioButtonCustomFilePath = new QRadioButton(layoutWidget);
        buttonGroup->addButton(radioButtonCustomFilePath);
        radioButtonCustomFilePath->setObjectName(QString::fromUtf8("radioButtonCustomFilePath"));

        gridLayout_2->addWidget(radioButtonCustomFilePath, 5, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        pushButtonOpenDWDConverter = new QPushButton(layoutWidget);
        pushButtonOpenDWDConverter->setObjectName(QString::fromUtf8("pushButtonOpenDWDConverter"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonOpenDWDConverter->sizePolicy().hasHeightForWidth());
        pushButtonOpenDWDConverter->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/DWDWeatherDataConverter.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOpenDWDConverter->setIcon(icon);
        pushButtonOpenDWDConverter->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(pushButtonOpenDWDConverter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowserDescription = new QTextBrowser(layoutWidget);
        textBrowserDescription->setObjectName(QString::fromUtf8("textBrowserDescription"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowserDescription->sizePolicy().hasHeightForWidth());
        textBrowserDescription->setSizePolicy(sizePolicy1);
        textBrowserDescription->setMinimumSize(QSize(0, 50));
        textBrowserDescription->setBaseSize(QSize(0, 100));

        gridLayout->addWidget(textBrowserDescription, 3, 0, 3, 1);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 1);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 2, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelLatitude = new QLabel(layoutWidget);
        labelLatitude->setObjectName(QString::fromUtf8("labelLatitude"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelLatitude);

        lineEditLatitude = new QtExt::ValidatingLineEdit(layoutWidget);
        lineEditLatitude->setObjectName(QString::fromUtf8("lineEditLatitude"));
        lineEditLatitude->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditLatitude);

        labelLongitude = new QLabel(layoutWidget);
        labelLongitude->setObjectName(QString::fromUtf8("labelLongitude"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelLongitude);

        lineEditLongitude = new QtExt::ValidatingLineEdit(layoutWidget);
        lineEditLongitude->setObjectName(QString::fromUtf8("lineEditLongitude"));
        lineEditLongitude->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditLongitude);

        labelTimeZone = new QLabel(layoutWidget);
        labelTimeZone->setObjectName(QString::fromUtf8("labelTimeZone"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelTimeZone);

        comboBoxTimeZone = new QComboBox(layoutWidget);
        comboBoxTimeZone->setObjectName(QString::fromUtf8("comboBoxTimeZone"));
        comboBoxTimeZone->setMinimumSize(QSize(100, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxTimeZone);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        comboBoxAlbedo = new QtExt::ValueInputComboBox(layoutWidget);
        comboBoxAlbedo->setObjectName(QString::fromUtf8("comboBoxAlbedo"));
        comboBoxAlbedo->setMinimumSize(QSize(250, 0));
        comboBoxAlbedo->setEditable(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBoxAlbedo);

        verticalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer_2);


        gridLayout->addLayout(formLayout, 3, 1, 3, 1);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout->addLayout(gridLayout);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        plotLayout = new QVBoxLayout(layoutWidget1);
        plotLayout->setObjectName(QString::fromUtf8("plotLayout"));
        plotLayout->setContentsMargins(0, 0, 0, 0);
        plotTemp = new QwtPlot(layoutWidget1);
        plotTemp->setObjectName(QString::fromUtf8("plotTemp"));
        plotTemp->setEnabled(false);
        plotTemp->setMinimumSize(QSize(0, 100));
        plotTemp->setMaximumSize(QSize(16777215, 16777215));

        plotLayout->addWidget(plotTemp);

        plotRelHum = new QwtPlot(layoutWidget1);
        plotRelHum->setObjectName(QString::fromUtf8("plotRelHum"));
        plotRelHum->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plotRelHum->sizePolicy().hasHeightForWidth());
        plotRelHum->setSizePolicy(sizePolicy2);
        plotRelHum->setMinimumSize(QSize(0, 100));

        plotLayout->addWidget(plotRelHum);

        plotRadShortWave = new QwtPlot(layoutWidget1);
        plotRadShortWave->setObjectName(QString::fromUtf8("plotRadShortWave"));
        plotRadShortWave->setEnabled(false);
        plotRadShortWave->setMinimumSize(QSize(0, 100));
        plotRadShortWave->setMaximumSize(QSize(16777215, 16777215));

        plotLayout->addWidget(plotRadShortWave);

        plotRadLongWave = new QwtPlot(layoutWidget1);
        plotRadLongWave->setObjectName(QString::fromUtf8("plotRadLongWave"));
        plotRadLongWave->setEnabled(false);
        plotRadLongWave->setMinimumSize(QSize(400, 100));
        plotRadLongWave->setMaximumSize(QSize(16777215, 16777215));

        plotLayout->addWidget(plotRadLongWave);

        plotWind = new QwtPlot(layoutWidget1);
        plotWind->setObjectName(QString::fromUtf8("plotWind"));
        plotWind->setEnabled(false);
        plotWind->setMinimumSize(QSize(0, 100));
        plotWind->setMaximumSize(QSize(16777215, 16777215));

        plotLayout->addWidget(plotWind);

        plotLayout->setStretch(0, 1);
        plotLayout->setStretch(1, 1);
        plotLayout->setStretch(2, 1);
        plotLayout->setStretch(3, 1);
        plotLayout->setStretch(4, 1);
        splitter->addWidget(layoutWidget1);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(SVSimulationLocationOptions);

        QMetaObject::connectSlotsByName(SVSimulationLocationOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationLocationOptions)
    {
        SVSimulationLocationOptions->setWindowTitle(QCoreApplication::translate("SVSimulationLocationOptions", "Form", nullptr));
        labelTextFilter->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Text filter:", nullptr));
        radioButtonUserPathAbsolute->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Store absolute path", nullptr));
        radioButtonUserPathRelative->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Store path relative to project file", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Climate data", nullptr));
        radioButtonFromDB->setText(QCoreApplication::translate("SVSimulationLocationOptions", "From climate database", nullptr));
        radioButtonCustomFilePath->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Custom file path", nullptr));
        pushButtonOpenDWDConverter->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Download DWD Weather ", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Climate data description", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Edit location", nullptr));
        labelLatitude->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Latitude [+90..-90 Deg]:", nullptr));
        labelLongitude->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Longitude [-180..180 Deg]:", nullptr));
        labelTimeZone->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Time zone:", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationLocationOptions", "Albedo [0..1]:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationLocationOptions: public Ui_SVSimulationLocationOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONLOCATIONOPTIONS_H
