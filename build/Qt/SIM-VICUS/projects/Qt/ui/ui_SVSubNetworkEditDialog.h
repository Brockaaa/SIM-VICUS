/********************************************************************************
** Form generated from reading UI file 'SVSubNetworkEditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSUBNETWORKEDITDIALOG_H
#define UI_SVSUBNETWORKEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtExt_ToolBox.h"
#include "SVBMZoomMeshGraphicsView.h"
#include "SVNetworkComponentEditWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SVSubNetworkEditDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *scrollAreaLayout;
    QVBoxLayout *wrapperLayout;
    QtExt::ToolBox *tbox;
    QSpacerItem *verticalSpacerInsideWrapper;
    QWidget *layoutViewWidget;
    QVBoxLayout *verticalLayoutViewWidget;
    SVBMZoomMeshGraphicsView *viewWidget;
    QHBoxLayout *buttonsLayout;
    QToolButton *addToUserDBButton;
    QToolButton *copyBlockButton;
    QToolButton *removeButton;
    QToolButton *toolButtonRename;
    QSpacerItem *horizontalSpacerButtonBox;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QVBoxLayout *verticalLayoutPage1;
    QWidget *page2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *leftPaddingLayout;
    QGroupBox *groupBoxName;
    QGridLayout *gridLayout;
    QLineEdit *nameLineEdit;
    QLabel *nameLabel;
    QStackedWidget *stackedWidgetNetworkComponent;
    QWidget *page_5;
    QVBoxLayout *verticalLayoutPage11;
    SVNetworkComponentEditWidget *networkComponentEditWidget;
    QWidget *page_6;
    QVBoxLayout *verticalLayoutPage12;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *SVSubNetworkEditDialog)
    {
        if (SVSubNetworkEditDialog->objectName().isEmpty())
            SVSubNetworkEditDialog->setObjectName(QString::fromUtf8("SVSubNetworkEditDialog"));
        SVSubNetworkEditDialog->setProperty("modal", QVariant(false));
        SVSubNetworkEditDialog->setWindowModality(Qt::WindowModal);
        SVSubNetworkEditDialog->resize(1156, 593);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SVSubNetworkEditDialog->sizePolicy().hasHeightForWidth());
        SVSubNetworkEditDialog->setSizePolicy(sizePolicy);
        SVSubNetworkEditDialog->setAcceptDrops(true);
        horizontalLayout = new QHBoxLayout(SVSubNetworkEditDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(SVSubNetworkEditDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setAcceptDrops(true);
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(layoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 171, 573));
        scrollAreaLayout = new QVBoxLayout(scrollAreaWidgetContents);
        scrollAreaLayout->setSpacing(0);
        scrollAreaLayout->setObjectName(QString::fromUtf8("scrollAreaLayout"));
        scrollAreaLayout->setContentsMargins(0, 0, 0, 0);
        wrapperLayout = new QVBoxLayout();
        wrapperLayout->setObjectName(QString::fromUtf8("wrapperLayout"));
        tbox = new QtExt::ToolBox(scrollAreaWidgetContents);
        tbox->setObjectName(QString::fromUtf8("tbox"));
        tbox->setMinimumSize(QSize(0, 0));
        tbox->setMaximumSize(QSize(600, 16777215));

        wrapperLayout->addWidget(tbox);

        verticalSpacerInsideWrapper = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        wrapperLayout->addItem(verticalSpacerInsideWrapper);


        scrollAreaLayout->addLayout(wrapperLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);

        verticalLayout_6->setStretch(0, 1);
        splitter->addWidget(layoutWidget);
        layoutViewWidget = new QWidget(splitter);
        layoutViewWidget->setObjectName(QString::fromUtf8("layoutViewWidget"));
        verticalLayoutViewWidget = new QVBoxLayout(layoutViewWidget);
        verticalLayoutViewWidget->setObjectName(QString::fromUtf8("verticalLayoutViewWidget"));
        verticalLayoutViewWidget->setContentsMargins(0, 0, 0, 0);
        viewWidget = new SVBMZoomMeshGraphicsView(layoutViewWidget);
        viewWidget->setObjectName(QString::fromUtf8("viewWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(viewWidget->sizePolicy().hasHeightForWidth());
        viewWidget->setSizePolicy(sizePolicy1);
        viewWidget->setBaseSize(QSize(500, 0));
        viewWidget->setAcceptDrops(true);

        verticalLayoutViewWidget->addWidget(viewWidget);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName(QString::fromUtf8("buttonsLayout"));
        addToUserDBButton = new QToolButton(layoutViewWidget);
        addToUserDBButton->setObjectName(QString::fromUtf8("addToUserDBButton"));
        addToUserDBButton->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/24x24/toDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        addToUserDBButton->setIcon(icon);
        addToUserDBButton->setIconSize(QSize(24, 24));

        buttonsLayout->addWidget(addToUserDBButton);

        copyBlockButton = new QToolButton(layoutViewWidget);
        copyBlockButton->setObjectName(QString::fromUtf8("copyBlockButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/gfx/actions/24x24/editcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyBlockButton->setIcon(icon1);
        copyBlockButton->setIconSize(QSize(24, 24));

        buttonsLayout->addWidget(copyBlockButton);

        removeButton = new QToolButton(layoutViewWidget);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon2);
        removeButton->setIconSize(QSize(24, 24));

        buttonsLayout->addWidget(removeButton);

        toolButtonRename = new QToolButton(layoutViewWidget);
        toolButtonRename->setObjectName(QString::fromUtf8("toolButtonRename"));
        toolButtonRename->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/gfx/actions/24x24/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRename->setIcon(icon3);
        toolButtonRename->setIconSize(QSize(24, 24));

        buttonsLayout->addWidget(toolButtonRename);

        horizontalSpacerButtonBox = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonsLayout->addItem(horizontalSpacerButtonBox);


        verticalLayoutViewWidget->addLayout(buttonsLayout);

        verticalLayoutViewWidget->setStretch(0, 1);
        splitter->addWidget(layoutViewWidget);

        horizontalLayout->addWidget(splitter);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, 0, -1);
        stackedWidget = new QStackedWidget(SVSubNetworkEditDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMinimumSize(QSize(473, 0));
        stackedWidget->setMaximumSize(QSize(473, 16777215));
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        sizePolicy2.setHeightForWidth(page1->sizePolicy().hasHeightForWidth());
        page1->setSizePolicy(sizePolicy2);
        verticalLayoutPage1 = new QVBoxLayout(page1);
        verticalLayoutPage1->setSpacing(0);
        verticalLayoutPage1->setObjectName(QString::fromUtf8("verticalLayoutPage1"));
        verticalLayoutPage1->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        sizePolicy2.setHeightForWidth(page2->sizePolicy().hasHeightForWidth());
        page2->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(page2);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        leftPaddingLayout = new QVBoxLayout();
        leftPaddingLayout->setSpacing(0);
        leftPaddingLayout->setObjectName(QString::fromUtf8("leftPaddingLayout"));
        leftPaddingLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxName = new QGroupBox(page2);
        groupBoxName->setObjectName(QString::fromUtf8("groupBoxName"));
        groupBoxName->setEnabled(false);
        groupBoxName->setMaximumSize(QSize(473, 16777215));
        gridLayout = new QGridLayout(groupBoxName);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nameLineEdit = new QLineEdit(groupBoxName);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setMinimumSize(QSize(0, 0));
        nameLineEdit->setMaximumSize(QSize(372, 16777215));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 2);

        nameLabel = new QLabel(groupBoxName);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 0, 0, 1, 1);


        leftPaddingLayout->addWidget(groupBoxName);

        stackedWidgetNetworkComponent = new QStackedWidget(page2);
        stackedWidgetNetworkComponent->setObjectName(QString::fromUtf8("stackedWidgetNetworkComponent"));
        sizePolicy2.setHeightForWidth(stackedWidgetNetworkComponent->sizePolicy().hasHeightForWidth());
        stackedWidgetNetworkComponent->setSizePolicy(sizePolicy2);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        sizePolicy2.setHeightForWidth(page_5->sizePolicy().hasHeightForWidth());
        page_5->setSizePolicy(sizePolicy2);
        page_5->setMinimumSize(QSize(473, 100));
        verticalLayoutPage11 = new QVBoxLayout(page_5);
        verticalLayoutPage11->setSpacing(0);
        verticalLayoutPage11->setObjectName(QString::fromUtf8("verticalLayoutPage11"));
        verticalLayoutPage11->setContentsMargins(0, 0, 0, 0);
        networkComponentEditWidget = new SVNetworkComponentEditWidget(page_5);
        networkComponentEditWidget->setObjectName(QString::fromUtf8("networkComponentEditWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(networkComponentEditWidget->sizePolicy().hasHeightForWidth());
        networkComponentEditWidget->setSizePolicy(sizePolicy3);
        networkComponentEditWidget->setMinimumSize(QSize(473, 0));
        networkComponentEditWidget->setMaximumSize(QSize(473, 16777215));

        verticalLayoutPage11->addWidget(networkComponentEditWidget);

        stackedWidgetNetworkComponent->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        sizePolicy2.setHeightForWidth(page_6->sizePolicy().hasHeightForWidth());
        page_6->setSizePolicy(sizePolicy2);
        verticalLayoutPage12 = new QVBoxLayout(page_6);
        verticalLayoutPage12->setSpacing(0);
        verticalLayoutPage12->setObjectName(QString::fromUtf8("verticalLayoutPage12"));
        verticalLayoutPage12->setContentsMargins(0, 0, 0, 0);
        stackedWidgetNetworkComponent->addWidget(page_6);

        leftPaddingLayout->addWidget(stackedWidgetNetworkComponent);

        leftPaddingLayout->setStretch(1, 1);

        verticalLayout->addLayout(leftPaddingLayout);

        stackedWidget->addWidget(page2);

        verticalLayout_2->addWidget(stackedWidget);

        buttonBox = new QDialogButtonBox(SVSubNetworkEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy4);
        buttonBox->setMinimumSize(QSize(473, 0));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);

        retranslateUi(SVSubNetworkEditDialog);

        stackedWidget->setCurrentIndex(1);
        stackedWidgetNetworkComponent->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVSubNetworkEditDialog);
    } // setupUi

    void retranslateUi(QWidget *SVSubNetworkEditDialog)
    {
        SVSubNetworkEditDialog->setWindowTitle(QCoreApplication::translate("SVSubNetworkEditDialog", "SubNetwork Editor", nullptr));
        groupBoxName->setTitle(QCoreApplication::translate("SVSubNetworkEditDialog", "Block Settings", nullptr));
        nameLabel->setText(QCoreApplication::translate("SVSubNetworkEditDialog", "Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSubNetworkEditDialog: public Ui_SVSubNetworkEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSUBNETWORKEDITDIALOG_H
