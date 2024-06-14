/********************************************************************************
** Form generated from reading UI file 'QtExt_LanguageStringEditWidget1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_LANGUAGESTRINGEDITWIDGET1_H
#define UI_QTEXT_LANGUAGESTRINGEDITWIDGET1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

namespace QtExt {

class Ui_LanguageStringEditWidget1
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QToolButton *toolButton;

    void setupUi(QWidget *QtExt__LanguageStringEditWidget1)
    {
        if (QtExt__LanguageStringEditWidget1->objectName().isEmpty())
            QtExt__LanguageStringEditWidget1->setObjectName(QString::fromUtf8("QtExt__LanguageStringEditWidget1"));
        QtExt__LanguageStringEditWidget1->resize(394, 22);
        horizontalLayout = new QHBoxLayout(QtExt__LanguageStringEditWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(QtExt__LanguageStringEditWidget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        toolButton = new QToolButton(QtExt__LanguageStringEditWidget1);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);


        retranslateUi(QtExt__LanguageStringEditWidget1);

        QMetaObject::connectSlotsByName(QtExt__LanguageStringEditWidget1);
    } // setupUi

    void retranslateUi(QWidget *QtExt__LanguageStringEditWidget1)
    {
        QtExt__LanguageStringEditWidget1->setWindowTitle(QCoreApplication::translate("QtExt::LanguageStringEditWidget1", "Form", nullptr));
        toolButton->setText(QCoreApplication::translate("QtExt::LanguageStringEditWidget1", "...", nullptr));
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class LanguageStringEditWidget1: public Ui_LanguageStringEditWidget1 {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_LANGUAGESTRINGEDITWIDGET1_H
