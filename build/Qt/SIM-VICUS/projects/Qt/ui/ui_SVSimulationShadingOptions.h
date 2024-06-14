/********************************************************************************
** Form generated from reading UI file 'SVSimulationShadingOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONSHADINGOPTIONS_H
#define UI_SVSIMULATIONSHADINGOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationShadingOptions
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_14;
    QFrame *line;
    QRadioButton *radioButtonEntireProject;
    QRadioButton *radioButtonSelectedGeometry;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QFrame *line_5;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QLabel *labelInputError;
    QLabel *labelStartTime;
    QLabel *labelLatitude;
    QLabel *labelEndTime;
    QLabel *labelLongitude;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_15;
    QFrame *line_2;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *labelPreviousShadingFile;
    QSpacerItem *horizontalSpacer_7;
    QLabel *labelPreviousShadingFileCreationDate;
    QSpacerItem *horizontalSpacer_9;
    QToolButton *toolButtonDeletePreviousShadingFile;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_16;
    QFrame *line_3;
    QGridLayout *gridLayout_4;
    QComboBox *comboBoxPresets;
    QFrame *line_4;
    QComboBox *comboBoxCalculationMethod;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QtExt::ValidatingLineEdit *lineEditSunCone;
    QLabel *labelGridSize_3;
    QLabel *label_17;
    QComboBox *comboBoxFileType;
    QLineEdit *lineEditShadingFactorFilename;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label;
    QLabel *labelGridSize;
    QLabel *label_12;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_2;
    QtExt::ValidatingLineEdit *lineEditGridSize;
    QLabel *labelGridSize_2;
    QComboBox *comboBoxGeometryMode;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_4;
    QtExt::ValidatingLineEdit *lineEditSteps;
    QLabel *labelGridSize_4;
    QLabel *labelSteps;
    QLabel *label_2;
    QLabel *label_18;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonCalculate;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_4;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SVSimulationShadingOptions)
    {
        if (SVSimulationShadingOptions->objectName().isEmpty())
            SVSimulationShadingOptions->setObjectName(QString::fromUtf8("SVSimulationShadingOptions"));
        SVSimulationShadingOptions->resize(954, 811);
        verticalLayout = new QVBoxLayout(SVSimulationShadingOptions);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_14 = new QLabel(SVSimulationShadingOptions);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout->addWidget(label_14);

        line = new QFrame(SVSimulationShadingOptions);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        radioButtonEntireProject = new QRadioButton(SVSimulationShadingOptions);
        buttonGroup = new QButtonGroup(SVSimulationShadingOptions);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonEntireProject);
        radioButtonEntireProject->setObjectName(QString::fromUtf8("radioButtonEntireProject"));
        radioButtonEntireProject->setEnabled(true);
        radioButtonEntireProject->setChecked(true);

        verticalLayout->addWidget(radioButtonEntireProject);

        radioButtonSelectedGeometry = new QRadioButton(SVSimulationShadingOptions);
        buttonGroup->addButton(radioButtonSelectedGeometry);
        radioButtonSelectedGeometry->setObjectName(QString::fromUtf8("radioButtonSelectedGeometry"));
        radioButtonSelectedGeometry->setChecked(false);

        verticalLayout->addWidget(radioButtonSelectedGeometry);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        label_3 = new QLabel(SVSimulationShadingOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        line_5 = new QFrame(SVSimulationShadingOptions);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_8 = new QLabel(SVSimulationShadingOptions);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 3, 1, 1);

        labelInputError = new QLabel(SVSimulationShadingOptions);
        labelInputError->setObjectName(QString::fromUtf8("labelInputError"));

        gridLayout_5->addWidget(labelInputError, 2, 0, 1, 6);

        labelStartTime = new QLabel(SVSimulationShadingOptions);
        labelStartTime->setObjectName(QString::fromUtf8("labelStartTime"));

        gridLayout_5->addWidget(labelStartTime, 0, 4, 1, 1);

        labelLatitude = new QLabel(SVSimulationShadingOptions);
        labelLatitude->setObjectName(QString::fromUtf8("labelLatitude"));

        gridLayout_5->addWidget(labelLatitude, 0, 1, 1, 1);

        labelEndTime = new QLabel(SVSimulationShadingOptions);
        labelEndTime->setObjectName(QString::fromUtf8("labelEndTime"));

        gridLayout_5->addWidget(labelEndTime, 1, 4, 1, 1);

        labelLongitude = new QLabel(SVSimulationShadingOptions);
        labelLongitude->setObjectName(QString::fromUtf8("labelLongitude"));

        gridLayout_5->addWidget(labelLongitude, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label_6 = new QLabel(SVSimulationShadingOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 1, 0, 1, 1);

        label_9 = new QLabel(SVSimulationShadingOptions);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 1, 3, 1, 1);

        label_5 = new QLabel(SVSimulationShadingOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(146, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 1, 5, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        label_15 = new QLabel(SVSimulationShadingOptions);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        verticalLayout->addWidget(label_15);

        line_2 = new QFrame(SVSimulationShadingOptions);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_11 = new QLabel(SVSimulationShadingOptions);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 1, 0, 1, 1);

        label_10 = new QLabel(SVSimulationShadingOptions);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setScaledContents(false);

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        labelPreviousShadingFile = new QLabel(SVSimulationShadingOptions);
        labelPreviousShadingFile->setObjectName(QString::fromUtf8("labelPreviousShadingFile"));

        gridLayout_2->addWidget(labelPreviousShadingFile, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 3, 1, 1);

        labelPreviousShadingFileCreationDate = new QLabel(SVSimulationShadingOptions);
        labelPreviousShadingFileCreationDate->setObjectName(QString::fromUtf8("labelPreviousShadingFileCreationDate"));

        gridLayout_2->addWidget(labelPreviousShadingFileCreationDate, 1, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 3, 1, 1);

        toolButtonDeletePreviousShadingFile = new QToolButton(SVSimulationShadingOptions);
        toolButtonDeletePreviousShadingFile->setObjectName(QString::fromUtf8("toolButtonDeletePreviousShadingFile"));
        toolButtonDeletePreviousShadingFile->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonDeletePreviousShadingFile->setIcon(icon);

        gridLayout_2->addWidget(toolButtonDeletePreviousShadingFile, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 26, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        label_16 = new QLabel(SVSimulationShadingOptions);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        verticalLayout->addWidget(label_16);

        line_3 = new QFrame(SVSimulationShadingOptions);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        comboBoxPresets = new QComboBox(SVSimulationShadingOptions);
        comboBoxPresets->setObjectName(QString::fromUtf8("comboBoxPresets"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPresets->sizePolicy().hasHeightForWidth());
        comboBoxPresets->setSizePolicy(sizePolicy);
        comboBoxPresets->setMaximumSize(QSize(400, 16777215));

        gridLayout_4->addWidget(comboBoxPresets, 2, 1, 1, 3);

        line_4 = new QFrame(SVSimulationShadingOptions);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_4, 15, 0, 1, 4);

        comboBoxCalculationMethod = new QComboBox(SVSimulationShadingOptions);
        comboBoxCalculationMethod->setObjectName(QString::fromUtf8("comboBoxCalculationMethod"));
        sizePolicy.setHeightForWidth(comboBoxCalculationMethod->sizePolicy().hasHeightForWidth());
        comboBoxCalculationMethod->setSizePolicy(sizePolicy);
        comboBoxCalculationMethod->setMaximumSize(QSize(400, 16777215));

        gridLayout_4->addWidget(comboBoxCalculationMethod, 0, 1, 1, 3);

        verticalSpacer_5 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_4->addItem(verticalSpacer_5, 11, 0, 2, 4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEditSunCone = new QtExt::ValidatingLineEdit(SVSimulationShadingOptions);
        lineEditSunCone->setObjectName(QString::fromUtf8("lineEditSunCone"));
        lineEditSunCone->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(lineEditSunCone);

        labelGridSize_3 = new QLabel(SVSimulationShadingOptions);
        labelGridSize_3->setObjectName(QString::fromUtf8("labelGridSize_3"));

        horizontalLayout_3->addWidget(labelGridSize_3);


        gridLayout_4->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        label_17 = new QLabel(SVSimulationShadingOptions);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_4->addWidget(label_17, 13, 0, 1, 4);

        comboBoxFileType = new QComboBox(SVSimulationShadingOptions);
        comboBoxFileType->setObjectName(QString::fromUtf8("comboBoxFileType"));
        sizePolicy.setHeightForWidth(comboBoxFileType->sizePolicy().hasHeightForWidth());
        comboBoxFileType->setSizePolicy(sizePolicy);
        comboBoxFileType->setMaximumSize(QSize(400, 16777215));

        gridLayout_4->addWidget(comboBoxFileType, 16, 1, 1, 1);

        lineEditShadingFactorFilename = new QLineEdit(SVSimulationShadingOptions);
        lineEditShadingFactorFilename->setObjectName(QString::fromUtf8("lineEditShadingFactorFilename"));
        lineEditShadingFactorFilename->setReadOnly(true);

        gridLayout_4->addWidget(lineEditShadingFactorFilename, 18, 1, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 16, 2, 1, 2);

        label = new QLabel(SVSimulationShadingOptions);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        labelGridSize = new QLabel(SVSimulationShadingOptions);
        labelGridSize->setObjectName(QString::fromUtf8("labelGridSize"));

        gridLayout_4->addWidget(labelGridSize, 3, 0, 1, 1);

        label_12 = new QLabel(SVSimulationShadingOptions);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 7, 0, 1, 1);

        label_4 = new QLabel(SVSimulationShadingOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 4, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 3, 2, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_11, 4, 2, 1, 2);

        label_7 = new QLabel(SVSimulationShadingOptions);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 16, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEditGridSize = new QtExt::ValidatingLineEdit(SVSimulationShadingOptions);
        lineEditGridSize->setObjectName(QString::fromUtf8("lineEditGridSize"));
        lineEditGridSize->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(lineEditGridSize);

        labelGridSize_2 = new QLabel(SVSimulationShadingOptions);
        labelGridSize_2->setObjectName(QString::fromUtf8("labelGridSize_2"));

        horizontalLayout_2->addWidget(labelGridSize_2);


        gridLayout_4->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        comboBoxGeometryMode = new QComboBox(SVSimulationShadingOptions);
        comboBoxGeometryMode->setObjectName(QString::fromUtf8("comboBoxGeometryMode"));
        sizePolicy.setHeightForWidth(comboBoxGeometryMode->sizePolicy().hasHeightForWidth());
        comboBoxGeometryMode->setSizePolicy(sizePolicy);
        comboBoxGeometryMode->setMaximumSize(QSize(400, 16777215));

        gridLayout_4->addWidget(comboBoxGeometryMode, 7, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_13, 18, 2, 1, 2);

        label_13 = new QLabel(SVSimulationShadingOptions);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEditSteps = new QtExt::ValidatingLineEdit(SVSimulationShadingOptions);
        lineEditSteps->setObjectName(QString::fromUtf8("lineEditSteps"));
        lineEditSteps->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(lineEditSteps);

        labelGridSize_4 = new QLabel(SVSimulationShadingOptions);
        labelGridSize_4->setObjectName(QString::fromUtf8("labelGridSize_4"));

        horizontalLayout_4->addWidget(labelGridSize_4);


        gridLayout_4->addLayout(horizontalLayout_4, 6, 1, 1, 1);

        labelSteps = new QLabel(SVSimulationShadingOptions);
        labelSteps->setObjectName(QString::fromUtf8("labelSteps"));

        gridLayout_4->addWidget(labelSteps, 6, 0, 1, 1);

        label_2 = new QLabel(SVSimulationShadingOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 18, 0, 1, 1);

        label_18 = new QLabel(SVSimulationShadingOptions);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QFont font;
        font.setItalic(true);
        label_18->setFont(font);
        label_18->setWordWrap(true);

        gridLayout_4->addWidget(label_18, 10, 0, 1, 4);


        verticalLayout->addLayout(gridLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonCalculate = new QPushButton(SVSimulationShadingOptions);
        pushButtonCalculate->setObjectName(QString::fromUtf8("pushButtonCalculate"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        pushButtonCalculate->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/play-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCalculate->setIcon(icon1);

        horizontalLayout->addWidget(pushButtonCalculate);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(SVSimulationShadingOptions);

        QMetaObject::connectSlotsByName(SVSimulationShadingOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationShadingOptions)
    {
        SVSimulationShadingOptions->setWindowTitle(QCoreApplication::translate("SVSimulationShadingOptions", "Sunlight Factor Calculation", nullptr));
        label_14->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Geometry selection", nullptr));
        radioButtonEntireProject->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Entire project (all buildings and entire geometry)", nullptr));
        radioButtonSelectedGeometry->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Selected geometry only", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Location and simulation data summary", nullptr));
        label_8->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Start time:", nullptr));
        labelInputError->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        labelStartTime->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        labelLatitude->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        labelEndTime->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        labelLongitude->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Longitude [Deg]:", nullptr));
        label_9->setText(QCoreApplication::translate("SVSimulationShadingOptions", "End time:", nullptr));
        label_5->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Latitude [Deg]:", nullptr));
        label_15->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Previous Shading Factor File", nullptr));
        label_11->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Created:", nullptr));
        label_10->setText(QCoreApplication::translate("SVSimulationShadingOptions", "File Name:", nullptr));
        labelPreviousShadingFile->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
        labelPreviousShadingFileCreationDate->setText(QCoreApplication::translate("SVSimulationShadingOptions", "TextLabel", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonDeletePreviousShadingFile->setToolTip(QCoreApplication::translate("SVSimulationShadingOptions", "Delete shading factor file", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonDeletePreviousShadingFile->setText(QString());
        label_16->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Shading calculation parameters", nullptr));
        labelGridSize_3->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Deg", nullptr));
        label_17->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Output file", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Detail presets:", nullptr));
        labelGridSize->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Grid size:", nullptr));
        label_12->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Geometry Mode:", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Similarity angle threshold (sun cone):", nullptr));
        label_7->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Output Type:", nullptr));
        labelGridSize_2->setText(QCoreApplication::translate("SVSimulationShadingOptions", "m", nullptr));
        label_13->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Calculation Mode:", nullptr));
        lineEditSteps->setText(QString());
        labelGridSize_4->setText(QCoreApplication::translate("SVSimulationShadingOptions", "-", nullptr));
        labelSteps->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Steps per hour:", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Shading factor file name:", nullptr));
        label_18->setText(QCoreApplication::translate("SVSimulationShadingOptions", "In ray tracing mode, a grid is created on each surface with its maximum size. A ray is shot from the center of each grid patch in the direction of the sun. If the ray hits an obstacle, the considered area is shaded and a shading factor can be determined from the ratio of the patch area to the total area. In surface clipping mode, on the other hand, all surfaces are projected onto the current surface from the direction of the sun. If this results in overlapping areas, these represent the shaded area, so a shading factor can be formed by the ratio of the overlapping area to the total area.", nullptr));
        pushButtonCalculate->setText(QCoreApplication::translate("SVSimulationShadingOptions", "Run shading-factors calculation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationShadingOptions: public Ui_SVSimulationShadingOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONSHADINGOPTIONS_H
