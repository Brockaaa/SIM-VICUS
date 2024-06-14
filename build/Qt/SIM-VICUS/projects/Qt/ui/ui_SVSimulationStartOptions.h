/********************************************************************************
** Form generated from reading UI file 'SVSimulationStartOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONSTARTOPTIONS_H
#define UI_SVSIMULATIONSTARTOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ParameterEdit.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationStartOptions
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_11;
    QFrame *line_4;
    QRadioButton *radioButtonEntireProject;
    QRadioButton *radioButtonSelectedGeometry;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QtExt::ParameterEdit *lineEditDuration;
    QComboBox *comboBoxUnitDuration;
    QLabel *label_5;
    QLineEdit *lineEditStartDate;
    QLabel *labelStart;
    QLineEdit *lineEditEndDate;
    QLabel *labelEnd;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QtExt::ValidatingLineEdit *lineEditNumThreads;
    QComboBox *comboBoxVerboseLevel;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBoxStepStats;
    QCheckBox *checkBoxCloseConsoleWindow;
    QLineEdit *lineEditCmdLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelTerminalEmulator;
    QComboBox *comboBoxTermEmulator;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_7;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonTestInit;
    QPushButton *pushButtonShowScreenLog;
    QPushButton *pushButtonExportFMU;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonRun;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *SVSimulationStartOptions)
    {
        if (SVSimulationStartOptions->objectName().isEmpty())
            SVSimulationStartOptions->setObjectName(QString::fromUtf8("SVSimulationStartOptions"));
        SVSimulationStartOptions->resize(1056, 780);
        verticalLayout_4 = new QVBoxLayout(SVSimulationStartOptions);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_11 = new QLabel(SVSimulationStartOptions);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_3->addWidget(label_11);

        line_4 = new QFrame(SVSimulationStartOptions);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_4);

        radioButtonEntireProject = new QRadioButton(SVSimulationStartOptions);
        radioButtonEntireProject->setObjectName(QString::fromUtf8("radioButtonEntireProject"));
        radioButtonEntireProject->setChecked(true);

        verticalLayout_3->addWidget(radioButtonEntireProject);

        radioButtonSelectedGeometry = new QRadioButton(SVSimulationStartOptions);
        radioButtonSelectedGeometry->setObjectName(QString::fromUtf8("radioButtonSelectedGeometry"));
        radioButtonSelectedGeometry->setChecked(false);

        verticalLayout_3->addWidget(radioButtonSelectedGeometry);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_7 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer_7);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_6 = new QLabel(SVSimulationStartOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        line_2 = new QFrame(SVSimulationStartOptions);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditDuration = new QtExt::ParameterEdit(SVSimulationStartOptions);
        lineEditDuration->setObjectName(QString::fromUtf8("lineEditDuration"));
        lineEditDuration->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEditDuration, 2, 1, 1, 1);

        comboBoxUnitDuration = new QComboBox(SVSimulationStartOptions);
        comboBoxUnitDuration->setObjectName(QString::fromUtf8("comboBoxUnitDuration"));

        gridLayout->addWidget(comboBoxUnitDuration, 2, 2, 1, 1);

        label_5 = new QLabel(SVSimulationStartOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEditStartDate = new QLineEdit(SVSimulationStartOptions);
        lineEditStartDate->setObjectName(QString::fromUtf8("lineEditStartDate"));
        lineEditStartDate->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditStartDate, 0, 1, 1, 2);

        labelStart = new QLabel(SVSimulationStartOptions);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));

        gridLayout->addWidget(labelStart, 0, 0, 1, 1);

        lineEditEndDate = new QLineEdit(SVSimulationStartOptions);
        lineEditEndDate->setObjectName(QString::fromUtf8("lineEditEndDate"));
        lineEditEndDate->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditEndDate, 1, 1, 1, 2);

        labelEnd = new QLabel(SVSimulationStartOptions);
        labelEnd->setObjectName(QString::fromUtf8("labelEnd"));

        gridLayout->addWidget(labelEnd, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(SVSimulationStartOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        line = new QFrame(SVSimulationStartOptions);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditNumThreads = new QtExt::ValidatingLineEdit(SVSimulationStartOptions);
        lineEditNumThreads->setObjectName(QString::fromUtf8("lineEditNumThreads"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditNumThreads->sizePolicy().hasHeightForWidth());
        lineEditNumThreads->setSizePolicy(sizePolicy);
        lineEditNumThreads->setMaximumSize(QSize(300, 16777215));

        gridLayout_2->addWidget(lineEditNumThreads, 1, 1, 1, 1);

        comboBoxVerboseLevel = new QComboBox(SVSimulationStartOptions);
        comboBoxVerboseLevel->setObjectName(QString::fromUtf8("comboBoxVerboseLevel"));
        sizePolicy.setHeightForWidth(comboBoxVerboseLevel->sizePolicy().hasHeightForWidth());
        comboBoxVerboseLevel->setSizePolicy(sizePolicy);
        comboBoxVerboseLevel->setMaximumSize(QSize(300, 16777215));

        gridLayout_2->addWidget(comboBoxVerboseLevel, 0, 1, 1, 1);

        label_2 = new QLabel(SVSimulationStartOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(SVSimulationStartOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        checkBoxStepStats = new QCheckBox(SVSimulationStartOptions);
        checkBoxStepStats->setObjectName(QString::fromUtf8("checkBoxStepStats"));

        verticalLayout->addWidget(checkBoxStepStats);

        checkBoxCloseConsoleWindow = new QCheckBox(SVSimulationStartOptions);
        checkBoxCloseConsoleWindow->setObjectName(QString::fromUtf8("checkBoxCloseConsoleWindow"));

        verticalLayout->addWidget(checkBoxCloseConsoleWindow);

        lineEditCmdLine = new QLineEdit(SVSimulationStartOptions);
        lineEditCmdLine->setObjectName(QString::fromUtf8("lineEditCmdLine"));
        lineEditCmdLine->setReadOnly(true);

        verticalLayout->addWidget(lineEditCmdLine);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelTerminalEmulator = new QLabel(SVSimulationStartOptions);
        labelTerminalEmulator->setObjectName(QString::fromUtf8("labelTerminalEmulator"));

        horizontalLayout_3->addWidget(labelTerminalEmulator);

        comboBoxTermEmulator = new QComboBox(SVSimulationStartOptions);
        comboBoxTermEmulator->addItem(QString());
        comboBoxTermEmulator->addItem(QString());
        comboBoxTermEmulator->addItem(QString());
        comboBoxTermEmulator->addItem(QString());
        comboBoxTermEmulator->setObjectName(QString::fromUtf8("comboBoxTermEmulator"));
        sizePolicy.setHeightForWidth(comboBoxTermEmulator->sizePolicy().hasHeightForWidth());
        comboBoxTermEmulator->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(comboBoxTermEmulator);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout);

        verticalSpacer_6 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer_6);

        label_7 = new QLabel(SVSimulationStartOptions);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_4->addWidget(label_7);

        line_3 = new QFrame(SVSimulationStartOptions);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonTestInit = new QPushButton(SVSimulationStartOptions);
        pushButtonTestInit->setObjectName(QString::fromUtf8("pushButtonTestInit"));
        QFont font;
        font.setPointSize(11);
        pushButtonTestInit->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonTestInit->setIcon(icon);
        pushButtonTestInit->setIconSize(QSize(12, 12));
        pushButtonTestInit->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonTestInit);

        pushButtonShowScreenLog = new QPushButton(SVSimulationStartOptions);
        pushButtonShowScreenLog->setObjectName(QString::fromUtf8("pushButtonShowScreenLog"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonShowScreenLog->setIcon(icon1);
        pushButtonShowScreenLog->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonShowScreenLog);

        pushButtonExportFMU = new QPushButton(SVSimulationStartOptions);
        pushButtonExportFMU->setObjectName(QString::fromUtf8("pushButtonExportFMU"));
        pushButtonExportFMU->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/32x32/FMI_32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonExportFMU->setIcon(icon2);
        pushButtonExportFMU->setIconSize(QSize(12, 12));
        pushButtonExportFMU->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonExportFMU);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonRun = new QPushButton(SVSimulationStartOptions);
        pushButtonRun->setObjectName(QString::fromUtf8("pushButtonRun"));
        pushButtonRun->setMinimumSize(QSize(220, 40));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setKerning(true);
        pushButtonRun->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/play-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRun->setIcon(icon3);
        pushButtonRun->setIconSize(QSize(24, 24));
        pushButtonRun->setAutoDefault(false);
        pushButtonRun->setFlat(false);

        horizontalLayout_4->addWidget(pushButtonRun);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        retranslateUi(SVSimulationStartOptions);

        pushButtonExportFMU->setDefault(false);
        pushButtonRun->setDefault(false);


        QMetaObject::connectSlotsByName(SVSimulationStartOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationStartOptions)
    {
        SVSimulationStartOptions->setWindowTitle(QCoreApplication::translate("SVSimulationStartOptions", "Form", nullptr));
        label_11->setText(QCoreApplication::translate("SVSimulationStartOptions", "Run options", nullptr));
        radioButtonEntireProject->setText(QCoreApplication::translate("SVSimulationStartOptions", "Simulate entire project (all buildings and networks)", nullptr));
        radioButtonSelectedGeometry->setText(QCoreApplication::translate("SVSimulationStartOptions", "Simulate selected geometry only", nullptr));
        label_6->setText(QCoreApplication::translate("SVSimulationStartOptions", "Simulation time and duration", nullptr));
        label_5->setText(QCoreApplication::translate("SVSimulationStartOptions", "Duration:", nullptr));
        lineEditStartDate->setPlaceholderText(QCoreApplication::translate("SVSimulationStartOptions", "dd.mm.yyyy hh:mm:ss", nullptr));
        labelStart->setText(QCoreApplication::translate("SVSimulationStartOptions", "Start date:", nullptr));
        lineEditEndDate->setPlaceholderText(QCoreApplication::translate("SVSimulationStartOptions", "dd.mm.yyyy hh:mm:ss", nullptr));
        labelEnd->setText(QCoreApplication::translate("SVSimulationStartOptions", "End date:", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationStartOptions", "Command line solver options", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationStartOptions", "Solver message detail:", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationStartOptions", "Number of parallel threads:", nullptr));
        checkBoxStepStats->setText(QCoreApplication::translate("SVSimulationStartOptions", "Write statistics for each internal solver step", nullptr));
        checkBoxCloseConsoleWindow->setText(QCoreApplication::translate("SVSimulationStartOptions", "Close console window when finished", nullptr));
        labelTerminalEmulator->setText(QCoreApplication::translate("SVSimulationStartOptions", "Terminal emulator:", nullptr));
        comboBoxTermEmulator->setItemText(0, QCoreApplication::translate("SVSimulationStartOptions", "None (background process)", nullptr));
        comboBoxTermEmulator->setItemText(1, QCoreApplication::translate("SVSimulationStartOptions", "XTerm", nullptr));
        comboBoxTermEmulator->setItemText(2, QCoreApplication::translate("SVSimulationStartOptions", "Gnome Terminal", nullptr));
        comboBoxTermEmulator->setItemText(3, QCoreApplication::translate("SVSimulationStartOptions", "Konsole", nullptr));

        label_7->setText(QCoreApplication::translate("SVSimulationStartOptions", "Operations", nullptr));
        pushButtonTestInit->setText(QCoreApplication::translate("SVSimulationStartOptions", "Test initialization ", nullptr));
        pushButtonShowScreenLog->setText(QCoreApplication::translate("SVSimulationStartOptions", "Show log file...", nullptr));
        pushButtonExportFMU->setText(QCoreApplication::translate("SVSimulationStartOptions", "Export FMU...", nullptr));
        pushButtonRun->setText(QCoreApplication::translate("SVSimulationStartOptions", " Start simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationStartOptions: public Ui_SVSimulationStartOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONSTARTOPTIONS_H
