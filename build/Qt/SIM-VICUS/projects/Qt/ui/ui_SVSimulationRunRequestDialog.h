/********************************************************************************
** Form generated from reading UI file 'SVSimulationRunRequestDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONRUNREQUESTDIALOG_H
#define UI_SVSIMULATIONRUNREQUESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationRunRequestDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_3;
    QCheckBox *checkBoxClearResultDir;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QFrame *frame;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonContinue;

    void setupUi(QDialog *SVSimulationRunRequestDialog)
    {
        if (SVSimulationRunRequestDialog->objectName().isEmpty())
            SVSimulationRunRequestDialog->setObjectName(QString::fromUtf8("SVSimulationRunRequestDialog"));
        SVSimulationRunRequestDialog->resize(629, 234);
        gridLayout = new QGridLayout(SVSimulationRunRequestDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(SVSimulationRunRequestDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setWordWrap(true);

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        checkBoxClearResultDir = new QCheckBox(SVSimulationRunRequestDialog);
        checkBoxClearResultDir->setObjectName(QString::fromUtf8("checkBoxClearResultDir"));
        checkBoxClearResultDir->setChecked(true);

        gridLayout->addWidget(checkBoxClearResultDir, 3, 1, 1, 1);

        buttonBox = new QDialogButtonBox(SVSimulationRunRequestDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        gridLayout->addWidget(buttonBox, 7, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label_2 = new QLabel(SVSimulationRunRequestDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        label = new QLabel(SVSimulationRunRequestDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        frame = new QFrame(SVSimulationRunRequestDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 4, 0, 1, 2);

        pushButtonStart = new QPushButton(SVSimulationRunRequestDialog);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStart->setIcon(icon);
        pushButtonStart->setIconSize(QSize(32, 32));

        gridLayout->addWidget(pushButtonStart, 2, 0, 1, 1);

        pushButtonContinue = new QPushButton(SVSimulationRunRequestDialog);
        pushButtonContinue->setObjectName(QString::fromUtf8("pushButtonContinue"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/32x32/sim_start.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonContinue->setIcon(icon1);
        pushButtonContinue->setIconSize(QSize(32, 32));

        gridLayout->addWidget(pushButtonContinue, 5, 0, 1, 1);

        QWidget::setTabOrder(pushButtonStart, checkBoxClearResultDir);
        QWidget::setTabOrder(checkBoxClearResultDir, pushButtonContinue);

        retranslateUi(SVSimulationRunRequestDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), SVSimulationRunRequestDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVSimulationRunRequestDialog);
    } // setupUi

    void retranslateUi(QDialog *SVSimulationRunRequestDialog)
    {
        SVSimulationRunRequestDialog->setWindowTitle(QCoreApplication::translate("SVSimulationRunRequestDialog", "Start Solver", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationRunRequestDialog", "Continue simulation from last output time point.", nullptr));
        checkBoxClearResultDir->setText(QCoreApplication::translate("SVSimulationRunRequestDialog", "Clear result directory before starting simulation", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationRunRequestDialog", "Restart simulation from begin, overwriting existing files.", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationRunRequestDialog", "The working/output directory for this project exists already.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationRunRequestDialog: public Ui_SVSimulationRunRequestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONRUNREQUESTDIALOG_H
