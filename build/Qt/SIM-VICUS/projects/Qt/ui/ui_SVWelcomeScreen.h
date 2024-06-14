/********************************************************************************
** Form generated from reading UI file 'SVWelcomeScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVWELCOMESCREEN_H
#define UI_SVWELCOMESCREEN_H

#include <QtCore/QVariant>
#include <QtExt_ClickableLabel.h>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVWelcomeScreen
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButtonNewProject;
    QToolButton *toolButtonOpenProject;
    QSpacerItem *horizontalSpacer;
    QLabel *labelLogo;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowserNews;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QtExt::ClickableLabel *labelRecent;
    QSpacerItem *horizontalSpacer_4;
    QtExt::ClickableLabel *labelExample;
    QSpacerItem *horizontalSpacer_3;
    QTextBrowser *textBrowserMain;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QFrame *line;

    void setupUi(QWidget *SVWelcomeScreen)
    {
        if (SVWelcomeScreen->objectName().isEmpty())
            SVWelcomeScreen->setObjectName(QString::fromUtf8("SVWelcomeScreen"));
        SVWelcomeScreen->resize(1162, 698);
        QPalette palette;
        SVWelcomeScreen->setPalette(palette);
        SVWelcomeScreen->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(SVWelcomeScreen);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButtonNewProject = new QToolButton(SVWelcomeScreen);
        toolButtonNewProject->setObjectName(QString::fromUtf8("toolButtonNewProject"));
        toolButtonNewProject->setMinimumSize(QSize(0, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/icons8/icons8-new-file-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonNewProject->setIcon(icon);
        toolButtonNewProject->setIconSize(QSize(32, 32));
        toolButtonNewProject->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(toolButtonNewProject);

        toolButtonOpenProject = new QToolButton(SVWelcomeScreen);
        toolButtonOpenProject->setObjectName(QString::fromUtf8("toolButtonOpenProject"));
        toolButtonOpenProject->setMinimumSize(QSize(0, 34));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/icons8/icons8-ordner-oeffnen-80.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonOpenProject->setIcon(icon1);
        toolButtonOpenProject->setIconSize(QSize(32, 32));
        toolButtonOpenProject->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(toolButtonOpenProject);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelLogo = new QLabel(SVWelcomeScreen);
        labelLogo->setObjectName(QString::fromUtf8("labelLogo"));
        labelLogo->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelLogo);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowserNews = new QTextBrowser(SVWelcomeScreen);
        textBrowserNews->setObjectName(QString::fromUtf8("textBrowserNews"));
        textBrowserNews->setMaximumSize(QSize(300, 16777215));
        textBrowserNews->setFrameShape(QFrame::NoFrame);
        textBrowserNews->setOpenLinks(false);

        gridLayout->addWidget(textBrowserNews, 4, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        labelRecent = new QtExt::ClickableLabel(SVWelcomeScreen);
        labelRecent->setObjectName(QString::fromUtf8("labelRecent"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelRecent->sizePolicy().hasHeightForWidth());
        labelRecent->setSizePolicy(sizePolicy);
        labelRecent->setMinimumSize(QSize(160, 0));
        labelRecent->setMaximumSize(QSize(140, 16777215));
        QFont font;
        font.setPointSize(12);
        labelRecent->setFont(font);
        labelRecent->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(labelRecent);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        labelExample = new QtExt::ClickableLabel(SVWelcomeScreen);
        labelExample->setObjectName(QString::fromUtf8("labelExample"));
        sizePolicy.setHeightForWidth(labelExample->sizePolicy().hasHeightForWidth());
        labelExample->setSizePolicy(sizePolicy);
        labelExample->setMinimumSize(QSize(100, 0));
        labelExample->setMaximumSize(QSize(100, 16777215));
        labelExample->setFont(font);
        labelExample->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(labelExample);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 0, 1, 1, 2);

        textBrowserMain = new QTextBrowser(SVWelcomeScreen);
        textBrowserMain->setObjectName(QString::fromUtf8("textBrowserMain"));
        textBrowserMain->setFrameShape(QFrame::NoFrame);
        textBrowserMain->setLineWidth(0);
        textBrowserMain->setOpenLinks(false);

        gridLayout->addWidget(textBrowserMain, 4, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_7 = new QSpacerItem(15, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        line = new QFrame(SVWelcomeScreen);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 2);


        gridLayout_2->addLayout(gridLayout, 3, 0, 1, 1);


        retranslateUi(SVWelcomeScreen);

        QMetaObject::connectSlotsByName(SVWelcomeScreen);
    } // setupUi

    void retranslateUi(QWidget *SVWelcomeScreen)
    {
        SVWelcomeScreen->setWindowTitle(QCoreApplication::translate("SVWelcomeScreen", "Form", nullptr));
        toolButtonNewProject->setText(QCoreApplication::translate("SVWelcomeScreen", "Create project...", nullptr));
        toolButtonOpenProject->setText(QCoreApplication::translate("SVWelcomeScreen", "Open project...", nullptr));
        labelLogo->setText(QString());
        labelRecent->setText(QCoreApplication::translate("SVWelcomeScreen", "Recent projects", nullptr));
        labelExample->setText(QCoreApplication::translate("SVWelcomeScreen", "Examples", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVWelcomeScreen: public Ui_SVWelcomeScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVWELCOMESCREEN_H
