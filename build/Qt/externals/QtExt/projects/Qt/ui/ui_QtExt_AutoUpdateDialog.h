/********************************************************************************
** Form generated from reading UI file 'QtExt_AutoUpdateDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_AUTOUPDATEDIALOG_H
#define UI_QTEXT_AUTOUPDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AutoUpdateDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *labelNewVersion;
    QLabel *labelCurrentVersionNumber;
    QLabel *label;
    QLabel *labelCurrentVersion;
    QFrame *line;
    QLabel *labelNewVersionNumber;
    QPushButton *pushButtonDownload;
    QProgressBar *progressBarDownload;
    QTextEdit *textEditChangeLog;
    QPushButton *pushButtonSkipUpdate;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AutoUpdateDialog)
    {
        if (AutoUpdateDialog->objectName().isEmpty())
            AutoUpdateDialog->setObjectName(QString::fromUtf8("AutoUpdateDialog"));
        AutoUpdateDialog->resize(1008, 815);
        verticalLayout = new QVBoxLayout(AutoUpdateDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(AutoUpdateDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelNewVersion = new QLabel(groupBox);
        labelNewVersion->setObjectName(QString::fromUtf8("labelNewVersion"));

        gridLayout->addWidget(labelNewVersion, 1, 0, 1, 1);

        labelCurrentVersionNumber = new QLabel(groupBox);
        labelCurrentVersionNumber->setObjectName(QString::fromUtf8("labelCurrentVersionNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelCurrentVersionNumber->sizePolicy().hasHeightForWidth());
        labelCurrentVersionNumber->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        labelCurrentVersionNumber->setFont(font);

        gridLayout->addWidget(labelCurrentVersionNumber, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 2);

        labelCurrentVersion = new QLabel(groupBox);
        labelCurrentVersion->setObjectName(QString::fromUtf8("labelCurrentVersion"));

        gridLayout->addWidget(labelCurrentVersion, 0, 0, 1, 1);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 3);

        labelNewVersionNumber = new QLabel(groupBox);
        labelNewVersionNumber->setObjectName(QString::fromUtf8("labelNewVersionNumber"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        labelNewVersionNumber->setFont(font1);

        gridLayout->addWidget(labelNewVersionNumber, 1, 1, 1, 1);

        pushButtonDownload = new QPushButton(groupBox);
        pushButtonDownload->setObjectName(QString::fromUtf8("pushButtonDownload"));

        gridLayout->addWidget(pushButtonDownload, 0, 2, 1, 1);

        progressBarDownload = new QProgressBar(groupBox);
        progressBarDownload->setObjectName(QString::fromUtf8("progressBarDownload"));
        progressBarDownload->setValue(24);

        gridLayout->addWidget(progressBarDownload, 6, 0, 1, 3);

        textEditChangeLog = new QTextEdit(groupBox);
        textEditChangeLog->setObjectName(QString::fromUtf8("textEditChangeLog"));
        textEditChangeLog->setMinimumSize(QSize(800, 500));

        gridLayout->addWidget(textEditChangeLog, 5, 0, 1, 3);

        pushButtonSkipUpdate = new QPushButton(groupBox);
        pushButtonSkipUpdate->setObjectName(QString::fromUtf8("pushButtonSkipUpdate"));

        gridLayout->addWidget(pushButtonSkipUpdate, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(AutoUpdateDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AutoUpdateDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AutoUpdateDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AutoUpdateDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AutoUpdateDialog);
    } // setupUi

    void retranslateUi(QDialog *AutoUpdateDialog)
    {
        AutoUpdateDialog->setWindowTitle(QCoreApplication::translate("AutoUpdateDialog", "Software update", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AutoUpdateDialog", "A new software version is available", nullptr));
        labelNewVersion->setText(QCoreApplication::translate("AutoUpdateDialog", "New version:", nullptr));
        labelCurrentVersionNumber->setText(QCoreApplication::translate("AutoUpdateDialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("AutoUpdateDialog", "Changes:", nullptr));
        labelCurrentVersion->setText(QCoreApplication::translate("AutoUpdateDialog", "Current version:", nullptr));
        labelNewVersionNumber->setText(QCoreApplication::translate("AutoUpdateDialog", "TextLabel", nullptr));
        pushButtonDownload->setText(QCoreApplication::translate("AutoUpdateDialog", "Download update", nullptr));
        pushButtonSkipUpdate->setText(QCoreApplication::translate("AutoUpdateDialog", "Skip update...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoUpdateDialog: public Ui_AutoUpdateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEXT_AUTOUPDATEDIALOG_H
