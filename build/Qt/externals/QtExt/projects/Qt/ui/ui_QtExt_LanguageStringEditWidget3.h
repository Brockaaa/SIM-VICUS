/********************************************************************************
** Form generated from reading UI file 'QtExt_LanguageStringEditWidget3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_LANGUAGESTRINGEDITWIDGET3_H
#define UI_QTEXT_LANGUAGESTRINGEDITWIDGET3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

namespace QtExt {

class Ui_LanguageStringEditWidget3
{
public:
    QGridLayout *gridLayout;
    QLabel *labelLanguageSelection;
    QComboBox *comboBoxThirdLanguage;
    QFormLayout *formLayout;
    QLabel *labelEnglishLanguageCaption;
    QLineEdit *lineEditEnglish;
    QLabel *labelCurrentLanguageCaption;
    QLineEdit *lineEditCurrent;
    QLabel *labelThirdLanguageCaption;
    QLineEdit *lineEdit3rdLanguage;

    void setupUi(QWidget *QtExt__LanguageStringEditWidget3)
    {
        if (QtExt__LanguageStringEditWidget3->objectName().isEmpty())
            QtExt__LanguageStringEditWidget3->setObjectName(QString::fromUtf8("QtExt__LanguageStringEditWidget3"));
        QtExt__LanguageStringEditWidget3->resize(414, 120);
        gridLayout = new QGridLayout(QtExt__LanguageStringEditWidget3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelLanguageSelection = new QLabel(QtExt__LanguageStringEditWidget3);
        labelLanguageSelection->setObjectName(QString::fromUtf8("labelLanguageSelection"));

        gridLayout->addWidget(labelLanguageSelection, 0, 0, 1, 1);

        comboBoxThirdLanguage = new QComboBox(QtExt__LanguageStringEditWidget3);
        comboBoxThirdLanguage->setObjectName(QString::fromUtf8("comboBoxThirdLanguage"));

        gridLayout->addWidget(comboBoxThirdLanguage, 0, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelEnglishLanguageCaption = new QLabel(QtExt__LanguageStringEditWidget3);
        labelEnglishLanguageCaption->setObjectName(QString::fromUtf8("labelEnglishLanguageCaption"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelEnglishLanguageCaption);

        lineEditEnglish = new QLineEdit(QtExt__LanguageStringEditWidget3);
        lineEditEnglish->setObjectName(QString::fromUtf8("lineEditEnglish"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditEnglish);

        labelCurrentLanguageCaption = new QLabel(QtExt__LanguageStringEditWidget3);
        labelCurrentLanguageCaption->setObjectName(QString::fromUtf8("labelCurrentLanguageCaption"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelCurrentLanguageCaption);

        lineEditCurrent = new QLineEdit(QtExt__LanguageStringEditWidget3);
        lineEditCurrent->setObjectName(QString::fromUtf8("lineEditCurrent"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditCurrent);

        labelThirdLanguageCaption = new QLabel(QtExt__LanguageStringEditWidget3);
        labelThirdLanguageCaption->setObjectName(QString::fromUtf8("labelThirdLanguageCaption"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelThirdLanguageCaption);

        lineEdit3rdLanguage = new QLineEdit(QtExt__LanguageStringEditWidget3);
        lineEdit3rdLanguage->setObjectName(QString::fromUtf8("lineEdit3rdLanguage"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit3rdLanguage);


        gridLayout->addLayout(formLayout, 1, 0, 1, 2);

        gridLayout->setColumnStretch(1, 1);

        retranslateUi(QtExt__LanguageStringEditWidget3);

        QMetaObject::connectSlotsByName(QtExt__LanguageStringEditWidget3);
    } // setupUi

    void retranslateUi(QWidget *QtExt__LanguageStringEditWidget3)
    {
        QtExt__LanguageStringEditWidget3->setWindowTitle(QCoreApplication::translate("QtExt::LanguageStringEditWidget3", "Form", nullptr));
        labelLanguageSelection->setText(QCoreApplication::translate("QtExt::LanguageStringEditWidget3", "Third language:", nullptr));
        labelEnglishLanguageCaption->setText(QCoreApplication::translate("QtExt::LanguageStringEditWidget3", "en", nullptr));
        labelCurrentLanguageCaption->setText(QCoreApplication::translate("QtExt::LanguageStringEditWidget3", "de", nullptr));
        labelThirdLanguageCaption->setText(QCoreApplication::translate("QtExt::LanguageStringEditWidget3", "uu", nullptr));
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class LanguageStringEditWidget3: public Ui_LanguageStringEditWidget3 {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_LANGUAGESTRINGEDITWIDGET3_H
