/********************************************************************************
** Form generated from reading UI file 'QtExt_CoordinateIndexEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_COORDINATEINDEXEDIT_H
#define UI_QTEXT_COORDINATEINDEXEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "QtExt_ValidatingLineEdit.h"

namespace QtExt {

class Ui_CoordinateIndexEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox;
    QtExt::ValidatingLineEdit *lineEdit;

    void setupUi(QWidget *QtExt__CoordinateIndexEdit)
    {
        if (QtExt__CoordinateIndexEdit->objectName().isEmpty())
            QtExt__CoordinateIndexEdit->setObjectName(QString::fromUtf8("QtExt__CoordinateIndexEdit"));
        QtExt__CoordinateIndexEdit->resize(331, 22);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtExt__CoordinateIndexEdit->sizePolicy().hasHeightForWidth());
        QtExt__CoordinateIndexEdit->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(QtExt__CoordinateIndexEdit);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spinBox = new QSpinBox(QtExt__CoordinateIndexEdit);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(0, 22));
        spinBox->setMaximumSize(QSize(16777215, 22));

        horizontalLayout->addWidget(spinBox);

        lineEdit = new QtExt::ValidatingLineEdit(QtExt__CoordinateIndexEdit);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(QtExt__CoordinateIndexEdit);

        QMetaObject::connectSlotsByName(QtExt__CoordinateIndexEdit);
    } // setupUi

    void retranslateUi(QWidget *QtExt__CoordinateIndexEdit)
    {
        QtExt__CoordinateIndexEdit->setWindowTitle(QCoreApplication::translate("QtExt::CoordinateIndexEdit", "Form", nullptr));
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class CoordinateIndexEdit: public Ui_CoordinateIndexEdit {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_COORDINATEINDEXEDIT_H
