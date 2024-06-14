/********************************************************************************
** Form generated from reading UI file 'NandradFMUGeneratorWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NANDRADFMUGENERATORWIDGET_H
#define UI_NANDRADFMUGENERATORWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"

QT_BEGIN_NAMESPACE

class Ui_NandradFMUGeneratorWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEditNandradProjectFilePath;
    QPushButton *pushButtonSelectNandradProject;
    QFrame *line;
    QLabel *label_2;
    QLineEdit *lineEditModelName;
    QLabel *label_4;
    QtExt::BrowseFilenameWidget *lineEditTargetDirectory;
    QLabel *label_3;
    QLineEdit *lineEditFMUPath;
    QSpacerItem *verticalSpacer;
    QWidget *tabInputVariables;
    QVBoxLayout *verticalLayout;
    QTableView *tableViewInputVars;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButtonAddInputVariable;
    QToolButton *toolButtonRemoveInputVariable;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *lineEditInputVarNameFilter;
    QLabel *label_6;
    QLineEdit *lineEditInputVarDescFilter;
    QWidget *tabOutputVariables;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableViewOutputVars;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButtonAddOutputVariable;
    QToolButton *toolButtonRemoveOutputVariable;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QLineEdit *lineEditOutputVarNameFilter;
    QLabel *label_8;
    QLineEdit *lineEditOutputVarDescFilter;
    QCheckBox *checkBoxUseDisplayNames;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSaveNandradProject;
    QPushButton *pushButtonRefresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonGenerate;

    void setupUi(QWidget *NandradFMUGeneratorWidget)
    {
        if (NandradFMUGeneratorWidget->objectName().isEmpty())
            NandradFMUGeneratorWidget->setObjectName(QString::fromUtf8("NandradFMUGeneratorWidget"));
        NandradFMUGeneratorWidget->resize(1132, 708);
        verticalLayout_2 = new QVBoxLayout(NandradFMUGeneratorWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(NandradFMUGeneratorWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        gridLayout = new QGridLayout(tabGeneral);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(tabGeneral);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        lineEditNandradProjectFilePath = new QLineEdit(tabGeneral);
        lineEditNandradProjectFilePath->setObjectName(QString::fromUtf8("lineEditNandradProjectFilePath"));

        gridLayout->addWidget(lineEditNandradProjectFilePath, 0, 1, 1, 1);

        pushButtonSelectNandradProject = new QPushButton(tabGeneral);
        pushButtonSelectNandradProject->setObjectName(QString::fromUtf8("pushButtonSelectNandradProject"));

        gridLayout->addWidget(pushButtonSelectNandradProject, 0, 2, 1, 1);

        line = new QFrame(tabGeneral);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 3);

        label_2 = new QLabel(tabGeneral);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 2, 1);

        lineEditModelName = new QLineEdit(tabGeneral);
        lineEditModelName->setObjectName(QString::fromUtf8("lineEditModelName"));

        gridLayout->addWidget(lineEditModelName, 3, 1, 1, 2);

        label_4 = new QLabel(tabGeneral);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        lineEditTargetDirectory = new QtExt::BrowseFilenameWidget(tabGeneral);
        lineEditTargetDirectory->setObjectName(QString::fromUtf8("lineEditTargetDirectory"));
        lineEditTargetDirectory->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(lineEditTargetDirectory, 4, 1, 1, 2);

        label_3 = new QLabel(tabGeneral);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        lineEditFMUPath = new QLineEdit(tabGeneral);
        lineEditFMUPath->setObjectName(QString::fromUtf8("lineEditFMUPath"));
        lineEditFMUPath->setReadOnly(false);

        gridLayout->addWidget(lineEditFMUPath, 5, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 365, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);

        tabWidget->addTab(tabGeneral, QString());
        tabInputVariables = new QWidget();
        tabInputVariables->setObjectName(QString::fromUtf8("tabInputVariables"));
        verticalLayout = new QVBoxLayout(tabInputVariables);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableViewInputVars = new QTableView(tabInputVariables);
        tableViewInputVars->setObjectName(QString::fromUtf8("tableViewInputVars"));
        tableViewInputVars->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout->addWidget(tableViewInputVars);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButtonAddInputVariable = new QToolButton(tabInputVariables);
        toolButtonAddInputVariable->setObjectName(QString::fromUtf8("toolButtonAddInputVariable"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddInputVariable->setIcon(icon);
        toolButtonAddInputVariable->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButtonAddInputVariable);

        toolButtonRemoveInputVariable = new QToolButton(tabInputVariables);
        toolButtonRemoveInputVariable->setObjectName(QString::fromUtf8("toolButtonRemoveInputVariable"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveInputVariable->setIcon(icon1);
        toolButtonRemoveInputVariable->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButtonRemoveInputVariable);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label = new QLabel(tabInputVariables);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditInputVarNameFilter = new QLineEdit(tabInputVariables);
        lineEditInputVarNameFilter->setObjectName(QString::fromUtf8("lineEditInputVarNameFilter"));

        horizontalLayout_2->addWidget(lineEditInputVarNameFilter);

        label_6 = new QLabel(tabInputVariables);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEditInputVarDescFilter = new QLineEdit(tabInputVariables);
        lineEditInputVarDescFilter->setObjectName(QString::fromUtf8("lineEditInputVarDescFilter"));

        horizontalLayout_2->addWidget(lineEditInputVarDescFilter);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabInputVariables, QString());
        tabOutputVariables = new QWidget();
        tabOutputVariables->setObjectName(QString::fromUtf8("tabOutputVariables"));
        verticalLayout_3 = new QVBoxLayout(tabOutputVariables);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableViewOutputVars = new QTableView(tabOutputVariables);
        tableViewOutputVars->setObjectName(QString::fromUtf8("tableViewOutputVars"));

        verticalLayout_3->addWidget(tableViewOutputVars);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        toolButtonAddOutputVariable = new QToolButton(tabOutputVariables);
        toolButtonAddOutputVariable->setObjectName(QString::fromUtf8("toolButtonAddOutputVariable"));
        toolButtonAddOutputVariable->setIcon(icon);
        toolButtonAddOutputVariable->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(toolButtonAddOutputVariable);

        toolButtonRemoveOutputVariable = new QToolButton(tabOutputVariables);
        toolButtonRemoveOutputVariable->setObjectName(QString::fromUtf8("toolButtonRemoveOutputVariable"));
        toolButtonRemoveOutputVariable->setIcon(icon1);
        toolButtonRemoveOutputVariable->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(toolButtonRemoveOutputVariable);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_7 = new QLabel(tabOutputVariables);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        lineEditOutputVarNameFilter = new QLineEdit(tabOutputVariables);
        lineEditOutputVarNameFilter->setObjectName(QString::fromUtf8("lineEditOutputVarNameFilter"));

        horizontalLayout_3->addWidget(lineEditOutputVarNameFilter);

        label_8 = new QLabel(tabOutputVariables);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        lineEditOutputVarDescFilter = new QLineEdit(tabOutputVariables);
        lineEditOutputVarDescFilter->setObjectName(QString::fromUtf8("lineEditOutputVarDescFilter"));

        horizontalLayout_3->addWidget(lineEditOutputVarDescFilter);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(tabOutputVariables, QString());

        verticalLayout_2->addWidget(tabWidget);

        checkBoxUseDisplayNames = new QCheckBox(NandradFMUGeneratorWidget);
        checkBoxUseDisplayNames->setObjectName(QString::fromUtf8("checkBoxUseDisplayNames"));
        checkBoxUseDisplayNames->setChecked(true);

        verticalLayout_2->addWidget(checkBoxUseDisplayNames);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonSaveNandradProject = new QPushButton(NandradFMUGeneratorWidget);
        pushButtonSaveNandradProject->setObjectName(QString::fromUtf8("pushButtonSaveNandradProject"));

        horizontalLayout->addWidget(pushButtonSaveNandradProject);

        pushButtonRefresh = new QPushButton(NandradFMUGeneratorWidget);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));

        horizontalLayout->addWidget(pushButtonRefresh);

        horizontalSpacer = new QSpacerItem(530, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonGenerate = new QPushButton(NandradFMUGeneratorWidget);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButtonGenerate->setFont(font);
        pushButtonGenerate->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonGenerate);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(NandradFMUGeneratorWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NandradFMUGeneratorWidget);
    } // setupUi

    void retranslateUi(QWidget *NandradFMUGeneratorWidget)
    {
        label_5->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "NANDRAD Project file:", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSelectNandradProject->setToolTip(QCoreApplication::translate("NandradFMUGeneratorWidget", "Select NANDRAD Project file path and update user interface to configuration stored in project.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSelectNandradProject->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Select NANDRAD Project ...", nullptr));
        label_2->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Model name:", nullptr));
        label_4->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Target directory:", nullptr));
        label_3->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "FMU file path:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("NandradFMUGeneratorWidget", "General Properties", nullptr));
        label->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Variable name filter:", nullptr));
        lineEditInputVarNameFilter->setPlaceholderText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Variable name or parts of it (with/without wildcards)", nullptr));
        label_6->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Description filter:", nullptr));
        lineEditInputVarDescFilter->setPlaceholderText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Description  text or parts of it (with/without wildcards)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabInputVariables), QCoreApplication::translate("NandradFMUGeneratorWidget", "Input variables", nullptr));
        label_7->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Variable name filter:", nullptr));
        lineEditOutputVarNameFilter->setPlaceholderText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Variable name or parts of it (with/without wildcards)", nullptr));
        label_8->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Description filter:", nullptr));
        lineEditOutputVarDescFilter->setPlaceholderText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Description  text or parts of it (with/without wildcards)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOutputVariables), QCoreApplication::translate("NandradFMUGeneratorWidget", "Output variables", nullptr));
        checkBoxUseDisplayNames->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Use display name for FMI Variables", nullptr));
        pushButtonSaveNandradProject->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Save FMU specification in NANDRAD project file", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Reload project and update variable lists", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("NandradFMUGeneratorWidget", "Generate FMU", nullptr));
        (void)NandradFMUGeneratorWidget;
    } // retranslateUi

};

namespace Ui {
    class NandradFMUGeneratorWidget: public Ui_NandradFMUGeneratorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NANDRADFMUGENERATORWIDGET_H
