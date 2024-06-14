/********************************************************************************
** Form generated from reading UI file 'SVDBDialogAddDependentElements.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVDBDIALOGADDDEPENDENTELEMENTS_H
#define UI_SVDBDIALOGADDDEPENDENTELEMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SVDBDialogAddDependentElements
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTextCaption;
    QListWidget *listWidget;
    QLabel *labelTextQuestion;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SVDBDialogAddDependentElements)
    {
        if (SVDBDialogAddDependentElements->objectName().isEmpty())
            SVDBDialogAddDependentElements->setObjectName(QString::fromUtf8("SVDBDialogAddDependentElements"));
        SVDBDialogAddDependentElements->resize(548, 240);
        verticalLayout = new QVBoxLayout(SVDBDialogAddDependentElements);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTextCaption = new QLabel(SVDBDialogAddDependentElements);
        labelTextCaption->setObjectName(QString::fromUtf8("labelTextCaption"));

        verticalLayout->addWidget(labelTextCaption);

        listWidget = new QListWidget(SVDBDialogAddDependentElements);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        labelTextQuestion = new QLabel(SVDBDialogAddDependentElements);
        labelTextQuestion->setObjectName(QString::fromUtf8("labelTextQuestion"));

        verticalLayout->addWidget(labelTextQuestion);

        buttonBox = new QDialogButtonBox(SVDBDialogAddDependentElements);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SVDBDialogAddDependentElements);
        QObject::connect(buttonBox, SIGNAL(accepted()), SVDBDialogAddDependentElements, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SVDBDialogAddDependentElements, SLOT(reject()));

        QMetaObject::connectSlotsByName(SVDBDialogAddDependentElements);
    } // setupUi

    void retranslateUi(QDialog *SVDBDialogAddDependentElements)
    {
        SVDBDialogAddDependentElements->setWindowTitle(QCoreApplication::translate("SVDBDialogAddDependentElements", "Add elements to user database", nullptr));
        labelTextCaption->setText(QCoreApplication::translate("SVDBDialogAddDependentElements", "The following local elements are referenced from the DB element:", nullptr));
        labelTextQuestion->setText(QCoreApplication::translate("SVDBDialogAddDependentElements", "Do you want to add these elements to the user database as well?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVDBDialogAddDependentElements: public Ui_SVDBDialogAddDependentElements {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVDBDIALOGADDDEPENDENTELEMENTS_H
