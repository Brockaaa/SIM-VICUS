/********************************************************************************
** Form generated from reading UI file 'SVAcousticConstraintsCheckWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVACOUSTICCONSTRAINTSCHECKWIDGET_H
#define UI_SVACOUSTICCONSTRAINTSCHECKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVAcousticConstraintsCheckWidget
{
public:
    QGridLayout *gridLayoutMaster;
    QTabWidget *tabWidget;
    QWidget *tabImpatSound;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelImpactSoundIcon;
    QLabel *labelImpactSound;
    QCheckBox *checkBoxHideImpactSound;
    QTableWidget *tableWidgetImpactSound;
    QWidget *resistance;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *labelAirBourneSoundIcon;
    QLabel *labelAirBourneSound;
    QCheckBox *checkBoxHideAirBourneSound;
    QTableWidget *tableWidgetAirBorneSound;
    QWidget *reverberation;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelReverberationIcon;
    QLabel *labelReverberation;
    QTableWidget *tableWidgetReverberation;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonCheckConstraints;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SVAcousticConstraintsCheckWidget)
    {
        if (SVAcousticConstraintsCheckWidget->objectName().isEmpty())
            SVAcousticConstraintsCheckWidget->setObjectName(QString::fromUtf8("SVAcousticConstraintsCheckWidget"));
        SVAcousticConstraintsCheckWidget->resize(1143, 647);
        gridLayoutMaster = new QGridLayout(SVAcousticConstraintsCheckWidget);
        gridLayoutMaster->setObjectName(QString::fromUtf8("gridLayoutMaster"));
        gridLayoutMaster->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(SVAcousticConstraintsCheckWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(1000, 0));
        tabImpatSound = new QWidget();
        tabImpatSound->setObjectName(QString::fromUtf8("tabImpatSound"));
        verticalLayout_4 = new QVBoxLayout(tabImpatSound);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelImpactSoundIcon = new QLabel(tabImpatSound);
        labelImpactSoundIcon->setObjectName(QString::fromUtf8("labelImpactSoundIcon"));
        labelImpactSoundIcon->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(labelImpactSoundIcon);

        labelImpactSound = new QLabel(tabImpatSound);
        labelImpactSound->setObjectName(QString::fromUtf8("labelImpactSound"));

        horizontalLayout_2->addWidget(labelImpactSound);


        verticalLayout_4->addLayout(horizontalLayout_2);

        checkBoxHideImpactSound = new QCheckBox(tabImpatSound);
        checkBoxHideImpactSound->setObjectName(QString::fromUtf8("checkBoxHideImpactSound"));
        checkBoxHideImpactSound->setChecked(true);

        verticalLayout_4->addWidget(checkBoxHideImpactSound);

        tableWidgetImpactSound = new QTableWidget(tabImpatSound);
        tableWidgetImpactSound->setObjectName(QString::fromUtf8("tableWidgetImpactSound"));

        verticalLayout_4->addWidget(tableWidgetImpactSound);

        tabWidget->addTab(tabImpatSound, QString());
        resistance = new QWidget();
        resistance->setObjectName(QString::fromUtf8("resistance"));
        verticalLayout_3 = new QVBoxLayout(resistance);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelAirBourneSoundIcon = new QLabel(resistance);
        labelAirBourneSoundIcon->setObjectName(QString::fromUtf8("labelAirBourneSoundIcon"));
        labelAirBourneSoundIcon->setMaximumSize(QSize(20, 16777215));

        horizontalLayout->addWidget(labelAirBourneSoundIcon);

        labelAirBourneSound = new QLabel(resistance);
        labelAirBourneSound->setObjectName(QString::fromUtf8("labelAirBourneSound"));

        horizontalLayout->addWidget(labelAirBourneSound);


        verticalLayout_3->addLayout(horizontalLayout);

        checkBoxHideAirBourneSound = new QCheckBox(resistance);
        checkBoxHideAirBourneSound->setObjectName(QString::fromUtf8("checkBoxHideAirBourneSound"));
        checkBoxHideAirBourneSound->setChecked(true);
        checkBoxHideAirBourneSound->setTristate(false);

        verticalLayout_3->addWidget(checkBoxHideAirBourneSound);

        tableWidgetAirBorneSound = new QTableWidget(resistance);
        tableWidgetAirBorneSound->setObjectName(QString::fromUtf8("tableWidgetAirBorneSound"));

        verticalLayout_3->addWidget(tableWidgetAirBorneSound);

        tabWidget->addTab(resistance, QString());
        reverberation = new QWidget();
        reverberation->setObjectName(QString::fromUtf8("reverberation"));
        verticalLayout = new QVBoxLayout(reverberation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelReverberationIcon = new QLabel(reverberation);
        labelReverberationIcon->setObjectName(QString::fromUtf8("labelReverberationIcon"));
        labelReverberationIcon->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_4->addWidget(labelReverberationIcon);

        labelReverberation = new QLabel(reverberation);
        labelReverberation->setObjectName(QString::fromUtf8("labelReverberation"));

        horizontalLayout_4->addWidget(labelReverberation);


        verticalLayout->addLayout(horizontalLayout_4);

        tableWidgetReverberation = new QTableWidget(reverberation);
        tableWidgetReverberation->setObjectName(QString::fromUtf8("tableWidgetReverberation"));

        verticalLayout->addWidget(tableWidgetReverberation);

        tabWidget->addTab(reverberation, QString());

        gridLayoutMaster->addWidget(tabWidget, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonCheckConstraints = new QPushButton(SVAcousticConstraintsCheckWidget);
        pushButtonCheckConstraints->setObjectName(QString::fromUtf8("pushButtonCheckConstraints"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        pushButtonCheckConstraints->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gfx/actions/play-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCheckConstraints->setIcon(icon);

        horizontalLayout_3->addWidget(pushButtonCheckConstraints);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayoutMaster->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(SVAcousticConstraintsCheckWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SVAcousticConstraintsCheckWidget);
    } // setupUi

    void retranslateUi(QWidget *SVAcousticConstraintsCheckWidget)
    {
        SVAcousticConstraintsCheckWidget->setWindowTitle(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Dialog", nullptr));
        labelImpactSoundIcon->setText(QString());
        labelImpactSound->setText(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "No acoustic check has been done.", nullptr));
        checkBoxHideImpactSound->setText(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Hide valid components", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabImpatSound), QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Impact sound", nullptr));
        labelAirBourneSoundIcon->setText(QString());
        labelAirBourneSound->setText(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "No acoustic check has been done.", nullptr));
        checkBoxHideAirBourneSound->setText(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Hide valid components", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(resistance), QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Air bourne sound", nullptr));
        labelReverberationIcon->setText(QString());
        labelReverberation->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(reverberation), QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Reverberation time", nullptr));
        pushButtonCheckConstraints->setText(QCoreApplication::translate("SVAcousticConstraintsCheckWidget", "Run acoustic evaluation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVAcousticConstraintsCheckWidget: public Ui_SVAcousticConstraintsCheckWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVACOUSTICCONSTRAINTSCHECKWIDGET_H
