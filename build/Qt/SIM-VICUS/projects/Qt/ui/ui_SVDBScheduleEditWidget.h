/********************************************************************************
** Form generated from reading UI file 'SVDBScheduleEditWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBSCHEDULEEDITWIDGET_H
#define UI_SVDBSCHEDULEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_LanguageStringEditWidget1.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwt_plot.h>
#include "QtExt_BrowseFilenameWidget.h"
#include "SVDBScheduleDailyCycleEditWidget.h"
#include "SVTimeSeriesPreviewWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVDBScheduleEditWidget
{
public:
    QVBoxLayout *verticalLayoutMaster;
    QWidget *widgetPeriod;
    QHBoxLayout *horizontalLayout_4;
    QtExt::LanguageStringEditWidget1 *lineEditName;
    QRadioButton *radioButtonDailyCycles;
    QRadioButton *radioButtonAnnualSchedules;
    QStackedWidget *stackedWidget;
    QWidget *pageDailyCycle;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QTableWidget *tableWidgetPeriods;
    QwtPlot *plotWidget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButtonAddPeriod;
    QToolButton *toolButtonCopyPeriod;
    QToolButton *toolButtonRemovePeriode;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QRadioButton *radioButtonLinear;
    QRadioButton *radioButtonConstant;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBoxDailyCycle;
    QGridLayout *gridLayout_2;
    QWidget *widgetDailyCycleAndDayTypes;
    QGridLayout *gridLayout_3;
    QWidget *widgetDayTypes;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QCheckBox *checkBoxMonday;
    QCheckBox *checkBoxTuesday;
    QCheckBox *checkBoxWednesday;
    QCheckBox *checkBoxThursday;
    QCheckBox *checkBoxFriday;
    QFrame *line;
    QCheckBox *checkBoxSaturday;
    QCheckBox *checkBoxSunday;
    QFrame *line_2;
    QCheckBox *checkBoxHoliday;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonSelectWeekDays;
    QPushButton *pushButtonSelectWeekEnds;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButtonBackward;
    QToolButton *toolButtonForward;
    QToolButton *toolButtonAddCurrentDailyCycle;
    QToolButton *toolButtonDeleteCurrentDailyCycle;
    QSpacerItem *horizontalSpacer_3;
    SVDBScheduleDailyCycleEditWidget *widgetDailyCycle;
    QFrame *line_3;
    QWidget *pageAnnualSchedule;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QRadioButton *radioButtonAnnualScheduleLinear;
    QRadioButton *radioButtonAnnualScheduleConstant;
    QSpacerItem *horizontalSpacer_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonPasteAnnualDataFromClipboard;
    QTableWidget *tableWidgetCopiedSplineData;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_5;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *labelFileNameReference;
    QPushButton *pushButtonEditAnnualDataInTexteditor;
    QRadioButton *radioButtonRelativeFilePath;
    QRadioButton *radioButtonAbsoluteFilePath;
    QtExt::BrowseFilenameWidget *filepathAnnualDataFile;
    QSpacerItem *verticalSpacer_9;
    QWidget *widgetColumnSelection;
    QGridLayout *gridLayoutColumnSelection;
    QLabel *labelColumnSelection;
    QSpacerItem *verticalSpacerColumnSelection;
    QListWidget *listWidgetColumnSelection;
    SVTimeSeriesPreviewWidget *widgetTimeSeriesPreview;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SVDBScheduleEditWidget)
    {
        if (SVDBScheduleEditWidget->objectName().isEmpty())
            SVDBScheduleEditWidget->setObjectName(QString::fromUtf8("SVDBScheduleEditWidget"));
        SVDBScheduleEditWidget->resize(1000, 746);
        SVDBScheduleEditWidget->setMinimumSize(QSize(1000, 0));
        verticalLayoutMaster = new QVBoxLayout(SVDBScheduleEditWidget);
        verticalLayoutMaster->setObjectName(QString::fromUtf8("verticalLayoutMaster"));
        widgetPeriod = new QWidget(SVDBScheduleEditWidget);
        widgetPeriod->setObjectName(QString::fromUtf8("widgetPeriod"));
        horizontalLayout_4 = new QHBoxLayout(widgetPeriod);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEditName = new QtExt::LanguageStringEditWidget1(widgetPeriod);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout_4->addWidget(lineEditName);

        radioButtonDailyCycles = new QRadioButton(widgetPeriod);
        radioButtonDailyCycles->setObjectName(QString::fromUtf8("radioButtonDailyCycles"));
        radioButtonDailyCycles->setChecked(true);

        horizontalLayout_4->addWidget(radioButtonDailyCycles);

        radioButtonAnnualSchedules = new QRadioButton(widgetPeriod);
        radioButtonAnnualSchedules->setObjectName(QString::fromUtf8("radioButtonAnnualSchedules"));

        horizontalLayout_4->addWidget(radioButtonAnnualSchedules);


        verticalLayoutMaster->addWidget(widgetPeriod);

        stackedWidget = new QStackedWidget(SVDBScheduleEditWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageDailyCycle = new QWidget();
        pageDailyCycle->setObjectName(QString::fromUtf8("pageDailyCycle"));
        verticalLayout_2 = new QVBoxLayout(pageDailyCycle);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(pageDailyCycle);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        tableWidgetPeriods = new QTableWidget(pageDailyCycle);
        tableWidgetPeriods->setObjectName(QString::fromUtf8("tableWidgetPeriods"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetPeriods->sizePolicy().hasHeightForWidth());
        tableWidgetPeriods->setSizePolicy(sizePolicy);
        tableWidgetPeriods->setAlternatingRowColors(true);
        tableWidgetPeriods->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetPeriods->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetPeriods->horizontalHeader()->setStretchLastSection(true);
        tableWidgetPeriods->verticalHeader()->setVisible(false);

        gridLayout_4->addWidget(tableWidgetPeriods, 1, 0, 1, 1);

        plotWidget = new QwtPlot(pageDailyCycle);
        plotWidget->setObjectName(QString::fromUtf8("plotWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plotWidget->sizePolicy().hasHeightForWidth());
        plotWidget->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(plotWidget, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButtonAddPeriod = new QToolButton(pageDailyCycle);
        toolButtonAddPeriod->setObjectName(QString::fromUtf8("toolButtonAddPeriod"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAddPeriod->setIcon(icon);
        toolButtonAddPeriod->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButtonAddPeriod);

        toolButtonCopyPeriod = new QToolButton(pageDailyCycle);
        toolButtonCopyPeriod->setObjectName(QString::fromUtf8("toolButtonCopyPeriod"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonCopyPeriod->setIcon(icon1);
        toolButtonCopyPeriod->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButtonCopyPeriod);

        toolButtonRemovePeriode = new QToolButton(pageDailyCycle);
        toolButtonRemovePeriode->setObjectName(QString::fromUtf8("toolButtonRemovePeriode"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemovePeriode->setIcon(icon2);
        toolButtonRemovePeriode->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(toolButtonRemovePeriode);

        horizontalSpacer = new QSpacerItem(40, 30, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_4->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(pageDailyCycle);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        radioButtonLinear = new QRadioButton(pageDailyCycle);
        radioButtonLinear->setObjectName(QString::fromUtf8("radioButtonLinear"));
        radioButtonLinear->setChecked(true);

        horizontalLayout_3->addWidget(radioButtonLinear);

        radioButtonConstant = new QRadioButton(pageDailyCycle);
        radioButtonConstant->setObjectName(QString::fromUtf8("radioButtonConstant"));

        horizontalLayout_3->addWidget(radioButtonConstant);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_4->addLayout(horizontalLayout_3, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_4);

        groupBoxDailyCycle = new QGroupBox(pageDailyCycle);
        groupBoxDailyCycle->setObjectName(QString::fromUtf8("groupBoxDailyCycle"));
        gridLayout_2 = new QGridLayout(groupBoxDailyCycle);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widgetDailyCycleAndDayTypes = new QWidget(groupBoxDailyCycle);
        widgetDailyCycleAndDayTypes->setObjectName(QString::fromUtf8("widgetDailyCycleAndDayTypes"));
        gridLayout_3 = new QGridLayout(widgetDailyCycleAndDayTypes);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetDayTypes = new QWidget(widgetDailyCycleAndDayTypes);
        widgetDayTypes->setObjectName(QString::fromUtf8("widgetDayTypes"));
        verticalLayout = new QVBoxLayout(widgetDayTypes);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(widgetDayTypes);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        checkBoxMonday = new QCheckBox(widgetDayTypes);
        checkBoxMonday->setObjectName(QString::fromUtf8("checkBoxMonday"));

        verticalLayout->addWidget(checkBoxMonday);

        checkBoxTuesday = new QCheckBox(widgetDayTypes);
        checkBoxTuesday->setObjectName(QString::fromUtf8("checkBoxTuesday"));

        verticalLayout->addWidget(checkBoxTuesday);

        checkBoxWednesday = new QCheckBox(widgetDayTypes);
        checkBoxWednesday->setObjectName(QString::fromUtf8("checkBoxWednesday"));

        verticalLayout->addWidget(checkBoxWednesday);

        checkBoxThursday = new QCheckBox(widgetDayTypes);
        checkBoxThursday->setObjectName(QString::fromUtf8("checkBoxThursday"));

        verticalLayout->addWidget(checkBoxThursday);

        checkBoxFriday = new QCheckBox(widgetDayTypes);
        checkBoxFriday->setObjectName(QString::fromUtf8("checkBoxFriday"));

        verticalLayout->addWidget(checkBoxFriday);

        line = new QFrame(widgetDayTypes);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        checkBoxSaturday = new QCheckBox(widgetDayTypes);
        checkBoxSaturday->setObjectName(QString::fromUtf8("checkBoxSaturday"));

        verticalLayout->addWidget(checkBoxSaturday);

        checkBoxSunday = new QCheckBox(widgetDayTypes);
        checkBoxSunday->setObjectName(QString::fromUtf8("checkBoxSunday"));
        checkBoxSunday->setCheckable(true);
        checkBoxSunday->setChecked(false);
        checkBoxSunday->setTristate(false);

        verticalLayout->addWidget(checkBoxSunday);

        line_2 = new QFrame(widgetDayTypes);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        checkBoxHoliday = new QCheckBox(widgetDayTypes);
        checkBoxHoliday->setObjectName(QString::fromUtf8("checkBoxHoliday"));

        verticalLayout->addWidget(checkBoxHoliday);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonSelectWeekDays = new QPushButton(widgetDayTypes);
        pushButtonSelectWeekDays->setObjectName(QString::fromUtf8("pushButtonSelectWeekDays"));

        verticalLayout->addWidget(pushButtonSelectWeekDays);

        pushButtonSelectWeekEnds = new QPushButton(widgetDayTypes);
        pushButtonSelectWeekEnds->setObjectName(QString::fromUtf8("pushButtonSelectWeekEnds"));

        verticalLayout->addWidget(pushButtonSelectWeekEnds);

        line_5 = new QFrame(widgetDayTypes);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(17, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButtonBackward = new QToolButton(widgetDayTypes);
        toolButtonBackward->setObjectName(QString::fromUtf8("toolButtonBackward"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/qss_icons/rc/arrow_left_focus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonBackward->setIcon(icon3);
        toolButtonBackward->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonBackward);

        toolButtonForward = new QToolButton(widgetDayTypes);
        toolButtonForward->setObjectName(QString::fromUtf8("toolButtonForward"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/qss_icons/rc/arrow_right_focus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonForward->setIcon(icon4);
        toolButtonForward->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonForward);

        toolButtonAddCurrentDailyCycle = new QToolButton(widgetDayTypes);
        toolButtonAddCurrentDailyCycle->setObjectName(QString::fromUtf8("toolButtonAddCurrentDailyCycle"));
        toolButtonAddCurrentDailyCycle->setIcon(icon);
        toolButtonAddCurrentDailyCycle->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonAddCurrentDailyCycle);

        toolButtonDeleteCurrentDailyCycle = new QToolButton(widgetDayTypes);
        toolButtonDeleteCurrentDailyCycle->setObjectName(QString::fromUtf8("toolButtonDeleteCurrentDailyCycle"));
        toolButtonDeleteCurrentDailyCycle->setIcon(icon2);
        toolButtonDeleteCurrentDailyCycle->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(toolButtonDeleteCurrentDailyCycle);

        horizontalSpacer_3 = new QSpacerItem(17, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_3->addWidget(widgetDayTypes, 0, 2, 1, 1);

        widgetDailyCycle = new SVDBScheduleDailyCycleEditWidget(widgetDailyCycleAndDayTypes);
        widgetDailyCycle->setObjectName(QString::fromUtf8("widgetDailyCycle"));

        gridLayout_3->addWidget(widgetDailyCycle, 0, 0, 1, 1);

        line_3 = new QFrame(widgetDailyCycleAndDayTypes);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 0, 1, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);

        gridLayout_2->addWidget(widgetDailyCycleAndDayTypes, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBoxDailyCycle);

        stackedWidget->addWidget(pageDailyCycle);
        pageAnnualSchedule = new QWidget();
        pageAnnualSchedule->setObjectName(QString::fromUtf8("pageAnnualSchedule"));
        horizontalLayout_5 = new QHBoxLayout(pageAnnualSchedule);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(pageAnnualSchedule);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        radioButtonAnnualScheduleLinear = new QRadioButton(pageAnnualSchedule);
        buttonGroup = new QButtonGroup(SVDBScheduleEditWidget);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonAnnualScheduleLinear);
        radioButtonAnnualScheduleLinear->setObjectName(QString::fromUtf8("radioButtonAnnualScheduleLinear"));
        radioButtonAnnualScheduleLinear->setChecked(true);

        horizontalLayout_6->addWidget(radioButtonAnnualScheduleLinear);

        radioButtonAnnualScheduleConstant = new QRadioButton(pageAnnualSchedule);
        buttonGroup->addButton(radioButtonAnnualScheduleConstant);
        radioButtonAnnualScheduleConstant->setObjectName(QString::fromUtf8("radioButtonAnnualScheduleConstant"));

        horizontalLayout_6->addWidget(radioButtonAnnualScheduleConstant);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_5->addLayout(horizontalLayout_6);

        tabWidget = new QTabWidget(pageAnnualSchedule);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushButtonPasteAnnualDataFromClipboard = new QPushButton(tab);
        pushButtonPasteAnnualDataFromClipboard->setObjectName(QString::fromUtf8("pushButtonPasteAnnualDataFromClipboard"));

        verticalLayout_4->addWidget(pushButtonPasteAnnualDataFromClipboard);

        tableWidgetCopiedSplineData = new QTableWidget(tab);
        tableWidgetCopiedSplineData->setObjectName(QString::fromUtf8("tableWidgetCopiedSplineData"));

        verticalLayout_4->addWidget(tableWidgetCopiedSplineData);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        labelFileNameReference = new QLabel(tab_2);
        labelFileNameReference->setObjectName(QString::fromUtf8("labelFileNameReference"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelFileNameReference->sizePolicy().hasHeightForWidth());
        labelFileNameReference->setSizePolicy(sizePolicy2);

        gridLayout_5->addWidget(labelFileNameReference, 1, 1, 1, 1);

        pushButtonEditAnnualDataInTexteditor = new QPushButton(tab_2);
        pushButtonEditAnnualDataInTexteditor->setObjectName(QString::fromUtf8("pushButtonEditAnnualDataInTexteditor"));

        gridLayout_5->addWidget(pushButtonEditAnnualDataInTexteditor, 1, 2, 1, 1);

        radioButtonRelativeFilePath = new QRadioButton(tab_2);
        radioButtonRelativeFilePath->setObjectName(QString::fromUtf8("radioButtonRelativeFilePath"));
        radioButtonRelativeFilePath->setChecked(true);

        gridLayout_5->addWidget(radioButtonRelativeFilePath, 2, 1, 1, 1);

        radioButtonAbsoluteFilePath = new QRadioButton(tab_2);
        radioButtonAbsoluteFilePath->setObjectName(QString::fromUtf8("radioButtonAbsoluteFilePath"));

        gridLayout_5->addWidget(radioButtonAbsoluteFilePath, 3, 1, 1, 1);

        filepathAnnualDataFile = new QtExt::BrowseFilenameWidget(tab_2);
        filepathAnnualDataFile->setObjectName(QString::fromUtf8("filepathAnnualDataFile"));
        sizePolicy2.setHeightForWidth(filepathAnnualDataFile->sizePolicy().hasHeightForWidth());
        filepathAnnualDataFile->setSizePolicy(sizePolicy2);
        filepathAnnualDataFile->setFocusPolicy(Qt::StrongFocus);

        gridLayout_5->addWidget(filepathAnnualDataFile, 0, 1, 1, 2);


        verticalLayout_3->addLayout(gridLayout_5);

        verticalSpacer_9 = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_9);

        widgetColumnSelection = new QWidget(tab_2);
        widgetColumnSelection->setObjectName(QString::fromUtf8("widgetColumnSelection"));
        gridLayoutColumnSelection = new QGridLayout(widgetColumnSelection);
        gridLayoutColumnSelection->setObjectName(QString::fromUtf8("gridLayoutColumnSelection"));
        gridLayoutColumnSelection->setContentsMargins(0, 0, 0, -1);
        labelColumnSelection = new QLabel(widgetColumnSelection);
        labelColumnSelection->setObjectName(QString::fromUtf8("labelColumnSelection"));

        gridLayoutColumnSelection->addWidget(labelColumnSelection, 0, 0, 1, 2);

        verticalSpacerColumnSelection = new QSpacerItem(20, 166, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayoutColumnSelection->addItem(verticalSpacerColumnSelection, 1, 0, 1, 1);

        listWidgetColumnSelection = new QListWidget(widgetColumnSelection);
        listWidgetColumnSelection->setObjectName(QString::fromUtf8("listWidgetColumnSelection"));
        listWidgetColumnSelection->setAlternatingRowColors(true);
        listWidgetColumnSelection->setSelectionMode(QAbstractItemView::SingleSelection);
        listWidgetColumnSelection->setSelectionBehavior(QAbstractItemView::SelectItems);

        gridLayoutColumnSelection->addWidget(listWidgetColumnSelection, 1, 1, 1, 1);


        verticalLayout_3->addWidget(widgetColumnSelection);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_5->addWidget(tabWidget);


        horizontalLayout_5->addLayout(verticalLayout_5);

        widgetTimeSeriesPreview = new SVTimeSeriesPreviewWidget(pageAnnualSchedule);
        widgetTimeSeriesPreview->setObjectName(QString::fromUtf8("widgetTimeSeriesPreview"));
        sizePolicy1.setHeightForWidth(widgetTimeSeriesPreview->sizePolicy().hasHeightForWidth());
        widgetTimeSeriesPreview->setSizePolicy(sizePolicy1);
        widgetTimeSeriesPreview->setMinimumSize(QSize(200, 200));

        horizontalLayout_5->addWidget(widgetTimeSeriesPreview);

        stackedWidget->addWidget(pageAnnualSchedule);

        verticalLayoutMaster->addWidget(stackedWidget);

        stackedWidget->raise();
        widgetPeriod->raise();

        retranslateUi(SVDBScheduleEditWidget);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SVDBScheduleEditWidget);
    } // setupUi

    void retranslateUi(QWidget *SVDBScheduleEditWidget)
    {
        SVDBScheduleEditWidget->setWindowTitle(QCoreApplication::translate("SVDBScheduleEditWidget", "Form", nullptr));
        radioButtonDailyCycles->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Daily cycles", nullptr));
        radioButtonAnnualSchedules->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Annual schedules", nullptr));
        label_2->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Periods", nullptr));
        label->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Interpolation:", nullptr));
        radioButtonLinear->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "linear", nullptr));
        radioButtonConstant->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "constant", nullptr));
        groupBoxDailyCycle->setTitle(QCoreApplication::translate("SVDBScheduleEditWidget", "Daily schedule", nullptr));
        label_4->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Day types", nullptr));
        checkBoxMonday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Monday", nullptr));
        checkBoxTuesday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Tuesday", nullptr));
        checkBoxWednesday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Wednesday", nullptr));
        checkBoxThursday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Thursday", nullptr));
        checkBoxFriday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Friday", nullptr));
        checkBoxSaturday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Saturday", nullptr));
        checkBoxSunday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Sunday", nullptr));
        checkBoxHoliday->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Holiday", nullptr));
        pushButtonSelectWeekDays->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Select all week days", nullptr));
        pushButtonSelectWeekEnds->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Select all week end days", nullptr));
        label_3->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Interpolation:", nullptr));
        radioButtonAnnualScheduleLinear->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "linear", nullptr));
        radioButtonAnnualScheduleConstant->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "constant", nullptr));
        pushButtonPasteAnnualDataFromClipboard->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Paste from clipboard", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SVDBScheduleEditWidget", "Copied data", nullptr));
        label_9->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Data file:", nullptr));
        label_7->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Reference:", nullptr));
        labelFileNameReference->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "TextLabel", nullptr));
        pushButtonEditAnnualDataInTexteditor->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Edit...", nullptr));
        radioButtonRelativeFilePath->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Reference with file path relative to project file", nullptr));
        radioButtonAbsoluteFilePath->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Reference with absolute file path", nullptr));
        labelColumnSelection->setText(QCoreApplication::translate("SVDBScheduleEditWidget", "Select column in data file:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SVDBScheduleEditWidget", "From TSV file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBScheduleEditWidget: public Ui_SVDBScheduleEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBSCHEDULEEDITWIDGET_H
