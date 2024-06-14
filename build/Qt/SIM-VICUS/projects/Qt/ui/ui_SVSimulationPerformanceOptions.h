/********************************************************************************
** Form generated from reading UI file 'SVSimulationPerformanceOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVSIMULATIONPERFORMANCEOPTIONS_H
#define UI_SVSIMULATIONPERFORMANCEOPTIONS_H

#include <QtCore/QVariant>
#include <QtExt_ParameterEdit.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVSimulationPerformanceOptions
{
public:
    QGridLayout *gridLayout;
    QtExt::ParameterEdit *lineEditMinDT;
    QtExt::ValidatingLineEdit *lineEditNonLin;
    QLabel *labelRelTol;
    QLabel *label_2;
    QLabel *labelInitialDT;
    QLabel *label;
    QLabel *label_4;
    QComboBox *comboBoxMinDT;
    QLabel *labelMaxOrder;
    QtExt::ParameterEdit *lineEditRelTol;
    QComboBox *comboBoxIntegrator;
    QtExt::ValidatingLineEdit *lineEditMaxKry;
    QLabel *labelPreILU;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelNonLin;
    QComboBox *comboBoxPreCond;
    QLabel *labelPreCond;
    QtExt::ValidatingLineEdit *lineEditPreILU;
    QComboBox *comboBoxLesSolver;
    QLabel *label_3;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *labelMinDT;
    QLabel *labelLesSolver;
    QtExt::ValidatingLineEdit *lineEditMaxOrder;
    QLabel *labelIntegrator;
    QSpacerItem *verticalSpacer;
    QFrame *line_4;
    QComboBox *comboBoxInitialDT;
    QtExt::ValidatingLineEdit *lineEditIterative;
    QtExt::ParameterEdit *lineEditInitialDT;
    QFrame *line_6;
    QSpacerItem *verticalSpacer_3;
    QLabel *labelIterative;
    QLabel *labelMaxKry;
    QFrame *line_5;

    void setupUi(QWidget *SVSimulationPerformanceOptions)
    {
        if (SVSimulationPerformanceOptions->objectName().isEmpty())
            SVSimulationPerformanceOptions->setObjectName(QString::fromUtf8("SVSimulationPerformanceOptions"));
        SVSimulationPerformanceOptions->resize(1110, 751);
        gridLayout = new QGridLayout(SVSimulationPerformanceOptions);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditMinDT = new QtExt::ParameterEdit(SVSimulationPerformanceOptions);
        lineEditMinDT->setObjectName(QString::fromUtf8("lineEditMinDT"));
        lineEditMinDT->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditMinDT, 22, 1, 1, 1);

        lineEditNonLin = new QtExt::ValidatingLineEdit(SVSimulationPerformanceOptions);
        lineEditNonLin->setObjectName(QString::fromUtf8("lineEditNonLin"));
        lineEditNonLin->setMinimumSize(QSize(0, 0));
        lineEditNonLin->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditNonLin, 5, 1, 1, 1);

        labelRelTol = new QLabel(SVSimulationPerformanceOptions);
        labelRelTol->setObjectName(QString::fromUtf8("labelRelTol"));

        gridLayout->addWidget(labelRelTol, 23, 0, 1, 1);

        label_2 = new QLabel(SVSimulationPerformanceOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        labelInitialDT = new QLabel(SVSimulationPerformanceOptions);
        labelInitialDT->setObjectName(QString::fromUtf8("labelInitialDT"));
        labelInitialDT->setMaximumSize(QSize(500, 16777215));

        gridLayout->addWidget(labelInitialDT, 21, 0, 1, 1);

        label = new QLabel(SVSimulationPerformanceOptions);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(SVSimulationPerformanceOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 18, 0, 1, 1);

        comboBoxMinDT = new QComboBox(SVSimulationPerformanceOptions);
        comboBoxMinDT->setObjectName(QString::fromUtf8("comboBoxMinDT"));
        comboBoxMinDT->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(comboBoxMinDT, 22, 2, 1, 1);

        labelMaxOrder = new QLabel(SVSimulationPerformanceOptions);
        labelMaxOrder->setObjectName(QString::fromUtf8("labelMaxOrder"));

        gridLayout->addWidget(labelMaxOrder, 4, 0, 1, 1);

        lineEditRelTol = new QtExt::ParameterEdit(SVSimulationPerformanceOptions);
        lineEditRelTol->setObjectName(QString::fromUtf8("lineEditRelTol"));
        lineEditRelTol->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditRelTol, 23, 1, 1, 1);

        comboBoxIntegrator = new QComboBox(SVSimulationPerformanceOptions);
        comboBoxIntegrator->setObjectName(QString::fromUtf8("comboBoxIntegrator"));
        comboBoxIntegrator->setMinimumSize(QSize(0, 0));
        comboBoxIntegrator->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(comboBoxIntegrator, 2, 1, 1, 1);

        lineEditMaxKry = new QtExt::ValidatingLineEdit(SVSimulationPerformanceOptions);
        lineEditMaxKry->setObjectName(QString::fromUtf8("lineEditMaxKry"));
        lineEditMaxKry->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditMaxKry, 10, 1, 1, 1);

        labelPreILU = new QLabel(SVSimulationPerformanceOptions);
        labelPreILU->setObjectName(QString::fromUtf8("labelPreILU"));

        gridLayout->addWidget(labelPreILU, 16, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_2, 6, 0, 1, 1);

        labelNonLin = new QLabel(SVSimulationPerformanceOptions);
        labelNonLin->setObjectName(QString::fromUtf8("labelNonLin"));

        gridLayout->addWidget(labelNonLin, 5, 0, 1, 1);

        comboBoxPreCond = new QComboBox(SVSimulationPerformanceOptions);
        comboBoxPreCond->setObjectName(QString::fromUtf8("comboBoxPreCond"));
        comboBoxPreCond->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(comboBoxPreCond, 15, 1, 1, 1);

        labelPreCond = new QLabel(SVSimulationPerformanceOptions);
        labelPreCond->setObjectName(QString::fromUtf8("labelPreCond"));
        labelPreCond->setMaximumSize(QSize(500, 16777215));

        gridLayout->addWidget(labelPreCond, 15, 0, 1, 1);

        lineEditPreILU = new QtExt::ValidatingLineEdit(SVSimulationPerformanceOptions);
        lineEditPreILU->setObjectName(QString::fromUtf8("lineEditPreILU"));
        lineEditPreILU->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditPreILU, 16, 1, 1, 1);

        comboBoxLesSolver = new QComboBox(SVSimulationPerformanceOptions);
        comboBoxLesSolver->setObjectName(QString::fromUtf8("comboBoxLesSolver"));
        comboBoxLesSolver->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(comboBoxLesSolver, 9, 1, 1, 1);

        label_3 = new QLabel(SVSimulationPerformanceOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 13, 0, 1, 1);

        line_2 = new QFrame(SVSimulationPerformanceOptions);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 9);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_4, 17, 0, 1, 1);

        labelMinDT = new QLabel(SVSimulationPerformanceOptions);
        labelMinDT->setObjectName(QString::fromUtf8("labelMinDT"));

        gridLayout->addWidget(labelMinDT, 22, 0, 1, 1);

        labelLesSolver = new QLabel(SVSimulationPerformanceOptions);
        labelLesSolver->setObjectName(QString::fromUtf8("labelLesSolver"));
        labelLesSolver->setMaximumSize(QSize(500, 16777215));

        gridLayout->addWidget(labelLesSolver, 9, 0, 1, 1);

        lineEditMaxOrder = new QtExt::ValidatingLineEdit(SVSimulationPerformanceOptions);
        lineEditMaxOrder->setObjectName(QString::fromUtf8("lineEditMaxOrder"));
        lineEditMaxOrder->setMinimumSize(QSize(0, 0));
        lineEditMaxOrder->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditMaxOrder, 4, 1, 1, 1);

        labelIntegrator = new QLabel(SVSimulationPerformanceOptions);
        labelIntegrator->setObjectName(QString::fromUtf8("labelIntegrator"));
        labelIntegrator->setMaximumSize(QSize(500, 16777215));

        gridLayout->addWidget(labelIntegrator, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 24, 0, 1, 1);

        line_4 = new QFrame(SVSimulationPerformanceOptions);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 14, 0, 1, 9);

        comboBoxInitialDT = new QComboBox(SVSimulationPerformanceOptions);
        comboBoxInitialDT->setObjectName(QString::fromUtf8("comboBoxInitialDT"));
        comboBoxInitialDT->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(comboBoxInitialDT, 21, 2, 1, 1);

        lineEditIterative = new QtExt::ValidatingLineEdit(SVSimulationPerformanceOptions);
        lineEditIterative->setObjectName(QString::fromUtf8("lineEditIterative"));
        lineEditIterative->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditIterative, 11, 1, 1, 1);

        lineEditInitialDT = new QtExt::ParameterEdit(SVSimulationPerformanceOptions);
        lineEditInitialDT->setObjectName(QString::fromUtf8("lineEditInitialDT"));
        lineEditInitialDT->setMaximumSize(QSize(400, 16777215));

        gridLayout->addWidget(lineEditInitialDT, 21, 1, 1, 1);

        line_6 = new QFrame(SVSimulationPerformanceOptions);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_6, 8, 0, 1, 9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_3, 12, 0, 1, 1);

        labelIterative = new QLabel(SVSimulationPerformanceOptions);
        labelIterative->setObjectName(QString::fromUtf8("labelIterative"));

        gridLayout->addWidget(labelIterative, 11, 0, 1, 1);

        labelMaxKry = new QLabel(SVSimulationPerformanceOptions);
        labelMaxKry->setObjectName(QString::fromUtf8("labelMaxKry"));

        gridLayout->addWidget(labelMaxKry, 10, 0, 1, 1);

        line_5 = new QFrame(SVSimulationPerformanceOptions);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 19, 0, 2, 9);


        retranslateUi(SVSimulationPerformanceOptions);

        QMetaObject::connectSlotsByName(SVSimulationPerformanceOptions);
    } // setupUi

    void retranslateUi(QWidget *SVSimulationPerformanceOptions)
    {
        SVSimulationPerformanceOptions->setWindowTitle(QCoreApplication::translate("SVSimulationPerformanceOptions", "Form", nullptr));
        labelRelTol->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Relative Tolerance:", nullptr));
        label_2->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Linear equation system solver", nullptr));
        labelInitialDT->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Initial time step:", nullptr));
        label->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Time integration method", nullptr));
        label_4->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "General options", nullptr));
        labelMaxOrder->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Maximum Method Order (1-5):", nullptr));
        labelPreILU->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Level of fill-in (ILU):", nullptr));
        labelNonLin->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Non-linear Iteration Convergence Coefficient:", nullptr));
        labelPreCond->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Preconditioner:", nullptr));
        label_3->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Preconditioner for iterative equation system solvers", nullptr));
        labelMinDT->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Time step size limit (model consistency):", nullptr));
        labelLesSolver->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Linear Equation System Solver:", nullptr));
        labelIntegrator->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Integrator:", nullptr));
        labelIterative->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Linear Iteration Convergence Coefficient:", nullptr));
        labelMaxKry->setText(QCoreApplication::translate("SVSimulationPerformanceOptions", "Maximum Dimension for Krylov Subspace:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVSimulationPerformanceOptions: public Ui_SVSimulationPerformanceOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVSIMULATIONPERFORMANCEOPTIONS_H
