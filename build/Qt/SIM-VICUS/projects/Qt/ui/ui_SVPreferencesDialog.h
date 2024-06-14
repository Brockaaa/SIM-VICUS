/********************************************************************************
** Form generated from reading UI file 'SVPreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPREFERENCESDIALOG_H
#define UI_SVPREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *SVPreferencesDialog)
    {
        if (SVPreferencesDialog->objectName().isEmpty())
            SVPreferencesDialog->setObjectName(QString::fromUtf8("SVPreferencesDialog"));
        SVPreferencesDialog->setWindowModality(Qt::WindowModal);
        SVPreferencesDialog->resize(618, 188);
        verticalLayout = new QVBoxLayout(SVPreferencesDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SVPreferencesDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SVPreferencesDialog);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SVPreferencesDialog);
    } // setupUi

    void retranslateUi(QWidget *SVPreferencesDialog)
    {
        SVPreferencesDialog->setWindowTitle(QCoreApplication::translate("SVPreferencesDialog", "Preferences", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPreferencesDialog: public Ui_SVPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPREFERENCESDIALOG_H
