/********************************************************************************
** Form generated from reading UI file 'SVPluginManager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVPLUGINMANAGER_H
#define UI_SVPLUGINMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVPluginManager
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolInstalledPlugins;
    QToolButton *toolAvailablePlugins;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVPluginManager)
    {
        if (SVPluginManager->objectName().isEmpty())
            SVPluginManager->setObjectName(QString::fromUtf8("SVPluginManager"));
        SVPluginManager->resize(1162, 698);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        SVPluginManager->setPalette(palette);
        SVPluginManager->setAutoFillBackground(true);
        gridLayout = new QGridLayout(SVPluginManager);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(SVPluginManager);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setOpenLinks(false);

        gridLayout->addWidget(textBrowser, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(14, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolInstalledPlugins = new QToolButton(SVPluginManager);
        toolInstalledPlugins->setObjectName(QString::fromUtf8("toolInstalledPlugins"));
        toolInstalledPlugins->setMinimumSize(QSize(0, 34));
        toolInstalledPlugins->setIconSize(QSize(32, 32));
        toolInstalledPlugins->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(toolInstalledPlugins);

        toolAvailablePlugins = new QToolButton(SVPluginManager);
        toolAvailablePlugins->setObjectName(QString::fromUtf8("toolAvailablePlugins"));
        toolAvailablePlugins->setMinimumSize(QSize(0, 34));
        toolAvailablePlugins->setIconSize(QSize(32, 32));
        toolAvailablePlugins->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(toolAvailablePlugins);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);


        retranslateUi(SVPluginManager);

        QMetaObject::connectSlotsByName(SVPluginManager);
    } // setupUi

    void retranslateUi(QWidget *SVPluginManager)
    {
        SVPluginManager->setWindowTitle(QCoreApplication::translate("SVPluginManager", "Form", nullptr));
        toolInstalledPlugins->setText(QCoreApplication::translate("SVPluginManager", "Installed", nullptr));
        toolAvailablePlugins->setText(QCoreApplication::translate("SVPluginManager", "Available", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVPluginManager: public Ui_SVPluginManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVPLUGINMANAGER_H
