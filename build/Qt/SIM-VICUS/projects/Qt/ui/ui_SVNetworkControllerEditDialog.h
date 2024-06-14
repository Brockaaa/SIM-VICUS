/********************************************************************************
** Form generated from reading UI file 'SVNetworkControllerEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVNETWORKCONTROLLEREDITDIALOG_H
#define UI_SVNETWORKCONTROLLEREDITDIALOG_H

#include <QtCore/QVariant>
#include <QtExt_ValidatingLineEdit.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVNetworkControllerEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutName;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QGroupBox *groupBoxProperty;
    QGridLayout *gridLayout;
    QComboBox *comboBoxProperty;
    QLineEdit *lineEditSchedule;
    QtExt::ValidatingLineEdit *lineEditSetpoint;
    QToolButton *toolButtonSchedule;
    QRadioButton *radioButtonFixedSetPoint;
    QLabel *label_2;
    QRadioButton *radioButtonSchedule;
    QToolButton *toolButtonRemoveSchedule;
    QGroupBox *groupBoxType;
    QFormLayout *formLayout;
    QLabel *labelType;
    QComboBox *comboBoxControllerType;
    QLabel *labelKp;
    QtExt::ValidatingLineEdit *lineEditKp;
    QLabel *labelKi;
    QtExt::ValidatingLineEdit *lineEditKi;
    QGroupBox *groupBoxMaximumOutput;
    QFormLayout *formLayout_2;
    QLabel *labelyMax;
    QtExt::ValidatingLineEdit *lineEditMaxControllerResultValue;
    QLabel *label_8;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVNetworkControllerEditDialog)
    {
        if (SVNetworkControllerEditDialog->objectName().isEmpty())
            SVNetworkControllerEditDialog->setObjectName(QString::fromUtf8("SVNetworkControllerEditDialog"));
        SVNetworkControllerEditDialog->resize(470, 471);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVNetworkControllerEditDialog->sizePolicy().hasHeightForWidth());
        SVNetworkControllerEditDialog->setSizePolicy(sizePolicy);
        SVNetworkControllerEditDialog->setModal(true);
        verticalLayout = new QVBoxLayout(SVNetworkControllerEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayoutName = new QHBoxLayout();
        horizontalLayoutName->setObjectName(QString::fromUtf8("horizontalLayoutName"));
        labelName = new QLabel(SVNetworkControllerEditDialog);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        horizontalLayoutName->addWidget(labelName);

        lineEditName = new QLineEdit(SVNetworkControllerEditDialog);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayoutName->addWidget(lineEditName);


        verticalLayout->addLayout(horizontalLayoutName);

        groupBoxProperty = new QGroupBox(SVNetworkControllerEditDialog);
        groupBoxProperty->setObjectName(QString::fromUtf8("groupBoxProperty"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxProperty->sizePolicy().hasHeightForWidth());
        groupBoxProperty->setSizePolicy(sizePolicy1);
        groupBoxProperty->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(groupBoxProperty);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxProperty = new QComboBox(groupBoxProperty);
        comboBoxProperty->setObjectName(QString::fromUtf8("comboBoxProperty"));

        gridLayout->addWidget(comboBoxProperty, 0, 1, 1, 2);

        lineEditSchedule = new QLineEdit(groupBoxProperty);
        lineEditSchedule->setObjectName(QString::fromUtf8("lineEditSchedule"));
        lineEditSchedule->setReadOnly(true);

        gridLayout->addWidget(lineEditSchedule, 2, 2, 1, 1);

        lineEditSetpoint = new QtExt::ValidatingLineEdit(groupBoxProperty);
        lineEditSetpoint->setObjectName(QString::fromUtf8("lineEditSetpoint"));

        gridLayout->addWidget(lineEditSetpoint, 1, 2, 1, 1);

        toolButtonSchedule = new QToolButton(groupBoxProperty);
        toolButtonSchedule->setObjectName(QString::fromUtf8("toolButtonSchedule"));

        gridLayout->addWidget(toolButtonSchedule, 2, 3, 1, 1);

        radioButtonFixedSetPoint = new QRadioButton(groupBoxProperty);
        radioButtonFixedSetPoint->setObjectName(QString::fromUtf8("radioButtonFixedSetPoint"));

        gridLayout->addWidget(radioButtonFixedSetPoint, 1, 0, 1, 2);

        label_2 = new QLabel(groupBoxProperty);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        radioButtonSchedule = new QRadioButton(groupBoxProperty);
        radioButtonSchedule->setObjectName(QString::fromUtf8("radioButtonSchedule"));

        gridLayout->addWidget(radioButtonSchedule, 2, 0, 1, 2);

        toolButtonRemoveSchedule = new QToolButton(groupBoxProperty);
        toolButtonRemoveSchedule->setObjectName(QString::fromUtf8("toolButtonRemoveSchedule"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemoveSchedule->setIcon(icon);

        gridLayout->addWidget(toolButtonRemoveSchedule, 2, 4, 1, 1);


        verticalLayout->addWidget(groupBoxProperty);

        groupBoxType = new QGroupBox(SVNetworkControllerEditDialog);
        groupBoxType->setObjectName(QString::fromUtf8("groupBoxType"));
        groupBoxType->setMaximumSize(QSize(16777215, 16777215));
        formLayout = new QFormLayout(groupBoxType);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelType = new QLabel(groupBoxType);
        labelType->setObjectName(QString::fromUtf8("labelType"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelType);

        comboBoxControllerType = new QComboBox(groupBoxType);
        comboBoxControllerType->setObjectName(QString::fromUtf8("comboBoxControllerType"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBoxControllerType);

        labelKp = new QLabel(groupBoxType);
        labelKp->setObjectName(QString::fromUtf8("labelKp"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelKp);

        lineEditKp = new QtExt::ValidatingLineEdit(groupBoxType);
        lineEditKp->setObjectName(QString::fromUtf8("lineEditKp"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditKp);

        labelKi = new QLabel(groupBoxType);
        labelKi->setObjectName(QString::fromUtf8("labelKi"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelKi);

        lineEditKi = new QtExt::ValidatingLineEdit(groupBoxType);
        lineEditKi->setObjectName(QString::fromUtf8("lineEditKi"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditKi);


        verticalLayout->addWidget(groupBoxType);

        groupBoxMaximumOutput = new QGroupBox(SVNetworkControllerEditDialog);
        groupBoxMaximumOutput->setObjectName(QString::fromUtf8("groupBoxMaximumOutput"));
        groupBoxMaximumOutput->setMaximumSize(QSize(16777215, 16777215));
        formLayout_2 = new QFormLayout(groupBoxMaximumOutput);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        labelyMax = new QLabel(groupBoxMaximumOutput);
        labelyMax->setObjectName(QString::fromUtf8("labelyMax"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelyMax);

        lineEditMaxControllerResultValue = new QtExt::ValidatingLineEdit(groupBoxMaximumOutput);
        lineEditMaxControllerResultValue->setObjectName(QString::fromUtf8("lineEditMaxControllerResultValue"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditMaxControllerResultValue);

        label_8 = new QLabel(groupBoxMaximumOutput);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font;
        font.setItalic(true);
        label_8->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, label_8);

        label_5 = new QLabel(groupBoxMaximumOutput);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, label_5);


        verticalLayout->addWidget(groupBoxMaximumOutput);

        buttonBox = new QDialogButtonBox(SVNetworkControllerEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);

        retranslateUi(SVNetworkControllerEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVNetworkControllerEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVNetworkControllerEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVNetworkControllerEditDialog);
    } // setupUi

    void retranslateUi(QDialog *SVNetworkControllerEditDialog)
    {
        SVNetworkControllerEditDialog->setWindowTitle(QCoreApplication::translate("SVNetworkControllerEditDialog", "Edit Controller", nullptr));
        labelName->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Name:", nullptr));
        groupBoxProperty->setTitle(QCoreApplication::translate("SVNetworkControllerEditDialog", "Controlled Property", nullptr));
        toolButtonSchedule->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "...", nullptr));
        radioButtonFixedSetPoint->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Fixed Set Point", nullptr));
        label_2->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Property", nullptr));
        radioButtonSchedule->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Schedule", nullptr));
        toolButtonRemoveSchedule->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "...", nullptr));
        groupBoxType->setTitle(QCoreApplication::translate("SVNetworkControllerEditDialog", "Controller Type", nullptr));
        labelType->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Type", nullptr));
        labelKp->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Kp", nullptr));
        labelKi->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "Ki", nullptr));
        groupBoxMaximumOutput->setTitle(QCoreApplication::translate("SVNetworkControllerEditDialog", "Maximum Controller Output ", nullptr));
        labelyMax->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "yMax", nullptr));
        label_8->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "this is the maximum zeta-value for valves, heat exchangers", nullptr));
        label_5->setText(QCoreApplication::translate("SVNetworkControllerEditDialog", "set this value to \"0\" to disable clipping", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVNetworkControllerEditDialog: public Ui_SVNetworkControllerEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVNETWORKCONTROLLEREDITDIALOG_H
