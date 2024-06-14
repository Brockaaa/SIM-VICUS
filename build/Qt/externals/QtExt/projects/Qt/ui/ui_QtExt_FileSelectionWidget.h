/********************************************************************************
** Form generated from reading UI file 'QtExt_FileSelectionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXT_FILESELECTIONWIDGET_H
#define UI_QTEXT_FILESELECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

namespace QtExt {

class Ui_FileSelectionWidget
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEditFilename;
    QTreeView *treeViewDirectories;
    QListView *listViewFiles;

    void setupUi(QWidget *QtExt__FileSelectionWidget)
    {
        if (QtExt__FileSelectionWidget->objectName().isEmpty())
            QtExt__FileSelectionWidget->setObjectName(QString::fromUtf8("QtExt__FileSelectionWidget"));
        QtExt__FileSelectionWidget->resize(496, 384);
        gridLayout = new QGridLayout(QtExt__FileSelectionWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(4);
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEditFilename = new QLineEdit(QtExt__FileSelectionWidget);
        lineEditFilename->setObjectName(QString::fromUtf8("lineEditFilename"));

        gridLayout->addWidget(lineEditFilename, 0, 0, 1, 2);

        treeViewDirectories = new QTreeView(QtExt__FileSelectionWidget);
        treeViewDirectories->setObjectName(QString::fromUtf8("treeViewDirectories"));

        gridLayout->addWidget(treeViewDirectories, 1, 0, 1, 1);

        listViewFiles = new QListView(QtExt__FileSelectionWidget);
        listViewFiles->setObjectName(QString::fromUtf8("listViewFiles"));

        gridLayout->addWidget(listViewFiles, 1, 1, 1, 1);


        retranslateUi(QtExt__FileSelectionWidget);

        QMetaObject::connectSlotsByName(QtExt__FileSelectionWidget);
    } // setupUi

    void retranslateUi(QWidget *QtExt__FileSelectionWidget)
    {
        QtExt__FileSelectionWidget->setWindowTitle(QCoreApplication::translate("QtExt::FileSelectionWidget", "Form", nullptr));
    } // retranslateUi

};

} // namespace QtExt

namespace QtExt {
namespace Ui {
    class FileSelectionWidget: public Ui_FileSelectionWidget {};
} // namespace Ui
} // namespace QtExt

#endif // UI_QTEXT_FILESELECTIONWIDGET_H
