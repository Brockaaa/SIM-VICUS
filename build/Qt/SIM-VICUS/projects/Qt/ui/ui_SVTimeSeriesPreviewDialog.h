/********************************************************************************
** Form generated from reading UI file 'SVTimeSeriesPreviewDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVTIMESERIESPREVIEWDIALOG_H
#define UI_SVTIMESERIESPREVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_BrowseFilenameWidget.h"
#include "SVTimeSeriesPreviewWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVTimeSeriesPreviewDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_5;
    QLabel *labelFileNameReference;
    QLabel *label_7;
    QRadioButton *radioButtonAbsoluteFilePath;
    QLabel *label_9;
    QtExt::BrowseFilenameWidget *filepathDataFile;
    QPushButton *pushButtonEditAnnualDataInTexteditor;
    QRadioButton *radioButtonRelativeFilePath;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QRadioButton *radioButtonInterpolationLinear;
    QRadioButton *radioButtonInterpolationConstant;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widgetColumnSelection;
    QGridLayout *gridLayoutColumnSelection;
    QLabel *labelColumnSelection;
    QSpacerItem *verticalSpacerColumnSelection;
    QListWidget *listWidgetColumnSelection;
    SVTimeSeriesPreviewWidget *widgetTimeSeriesPreview;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;

    void setupUi(QDialog *SVTimeSeriesPreviewDialog)
    {
        if (SVTimeSeriesPreviewDialog->objectName().isEmpty())
            SVTimeSeriesPreviewDialog->setObjectName(QString::fromUtf8("SVTimeSeriesPreviewDialog"));
        SVTimeSeriesPreviewDialog->resize(918, 615);
        verticalLayout_2 = new QVBoxLayout(SVTimeSeriesPreviewDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        labelFileNameReference = new QLabel(SVTimeSeriesPreviewDialog);
        labelFileNameReference->setObjectName(QString::fromUtf8("labelFileNameReference"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelFileNameReference->sizePolicy().hasHeightForWidth());
        labelFileNameReference->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(labelFileNameReference, 1, 1, 1, 1);

        label_7 = new QLabel(SVTimeSeriesPreviewDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        radioButtonAbsoluteFilePath = new QRadioButton(SVTimeSeriesPreviewDialog);
        buttonGroup_2 = new QButtonGroup(SVTimeSeriesPreviewDialog);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(radioButtonAbsoluteFilePath);
        radioButtonAbsoluteFilePath->setObjectName(QString::fromUtf8("radioButtonAbsoluteFilePath"));

        gridLayout_5->addWidget(radioButtonAbsoluteFilePath, 3, 1, 1, 1);

        label_9 = new QLabel(SVTimeSeriesPreviewDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        filepathDataFile = new QtExt::BrowseFilenameWidget(SVTimeSeriesPreviewDialog);
        filepathDataFile->setObjectName(QString::fromUtf8("filepathDataFile"));
        sizePolicy.setHeightForWidth(filepathDataFile->sizePolicy().hasHeightForWidth());
        filepathDataFile->setSizePolicy(sizePolicy);
        filepathDataFile->setFocusPolicy(Qt::StrongFocus);

        gridLayout_5->addWidget(filepathDataFile, 0, 1, 1, 2);

        pushButtonEditAnnualDataInTexteditor = new QPushButton(SVTimeSeriesPreviewDialog);
        pushButtonEditAnnualDataInTexteditor->setObjectName(QString::fromUtf8("pushButtonEditAnnualDataInTexteditor"));

        gridLayout_5->addWidget(pushButtonEditAnnualDataInTexteditor, 1, 2, 1, 1);

        radioButtonRelativeFilePath = new QRadioButton(SVTimeSeriesPreviewDialog);
        buttonGroup_2->addButton(radioButtonRelativeFilePath);
        radioButtonRelativeFilePath->setObjectName(QString::fromUtf8("radioButtonRelativeFilePath"));

        gridLayout_5->addWidget(radioButtonRelativeFilePath, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(SVTimeSeriesPreviewDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        radioButtonInterpolationLinear = new QRadioButton(SVTimeSeriesPreviewDialog);
        buttonGroup = new QButtonGroup(SVTimeSeriesPreviewDialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonInterpolationLinear);
        radioButtonInterpolationLinear->setObjectName(QString::fromUtf8("radioButtonInterpolationLinear"));

        horizontalLayout_6->addWidget(radioButtonInterpolationLinear);

        radioButtonInterpolationConstant = new QRadioButton(SVTimeSeriesPreviewDialog);
        buttonGroup->addButton(radioButtonInterpolationConstant);
        radioButtonInterpolationConstant->setObjectName(QString::fromUtf8("radioButtonInterpolationConstant"));

        horizontalLayout_6->addWidget(radioButtonInterpolationConstant);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_6);

        widgetColumnSelection = new QWidget(SVTimeSeriesPreviewDialog);
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


        verticalLayout->addWidget(widgetColumnSelection);


        horizontalLayout->addLayout(verticalLayout);

        widgetTimeSeriesPreview = new SVTimeSeriesPreviewWidget(SVTimeSeriesPreviewDialog);
        widgetTimeSeriesPreview->setObjectName(QString::fromUtf8("widgetTimeSeriesPreview"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetTimeSeriesPreview->sizePolicy().hasHeightForWidth());
        widgetTimeSeriesPreview->setSizePolicy(sizePolicy1);
        widgetTimeSeriesPreview->setMinimumSize(QSize(200, 200));

        horizontalLayout->addWidget(widgetTimeSeriesPreview);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SVTimeSeriesPreviewDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SVTimeSeriesPreviewDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVTimeSeriesPreviewDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVTimeSeriesPreviewDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVTimeSeriesPreviewDialog);
    } // setupUi

    void retranslateUi(QDialog *SVTimeSeriesPreviewDialog)
    {
        SVTimeSeriesPreviewDialog->setWindowTitle(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Dialog", nullptr));
        labelFileNameReference->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Reference:", nullptr));
        radioButtonAbsoluteFilePath->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Reference with absolute file path", nullptr));
        label_9->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Data file:", nullptr));
        pushButtonEditAnnualDataInTexteditor->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Edit...", nullptr));
        radioButtonRelativeFilePath->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Reference with relative file path", nullptr));
        label_3->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Interpolation:", nullptr));
        radioButtonInterpolationLinear->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "linear", nullptr));
        radioButtonInterpolationConstant->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "constant", nullptr));
        labelColumnSelection->setText(QCoreApplication::translate("SVTimeSeriesPreviewDialog", "Select column in data file:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVTimeSeriesPreviewDialog: public Ui_SVTimeSeriesPreviewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVTIMESERIESPREVIEWDIALOG_H
