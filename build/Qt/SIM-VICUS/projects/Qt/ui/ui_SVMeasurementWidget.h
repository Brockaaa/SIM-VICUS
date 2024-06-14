/********************************************************************************
** Form generated from reading UI file 'SVMeasurementWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVMEASUREMENTWIDGET_H
#define UI_SVMEASUREMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtExt_ColorButton.h>
#include <QtExt_ValidatingLineEdit.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SVMeasurementWidget
{
public:
    QGridLayout *gridLayout;
    QtExt::ValidatingLineEdit *lineEditStartZ;
    QtExt::ValidatingLineEdit *lineEditDistZ;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QtExt::ColorButton *pushButtonColor;
    QPushButton *pushButtonCopyInformation;
    QFrame *line;
    QLabel *labelStartPoint;
    QLabel *label_3;
    QtExt::ValidatingLineEdit *lineEditStartY;
    QtExt::ValidatingLineEdit *lineEditEndX;
    QtExt::ValidatingLineEdit *lineEditEndZ;
    QLabel *label;
    QtExt::ValidatingLineEdit *lineEditDistX;
    QtExt::ValidatingLineEdit *lineEditDistY;
    QtExt::ValidatingLineEdit *lineEditStartX;
    QLabel *labelStartPoint_2;
    QLabel *label_2;
    QtExt::ValidatingLineEdit *lineEditEndY;
    QCheckBox *checkBoxLocalMeasurement;
    QtExt::ValidatingLineEdit *lineEditDistance;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SVMeasurementWidget)
    {
        if (SVMeasurementWidget->objectName().isEmpty())
            SVMeasurementWidget->setObjectName(QString::fromUtf8("SVMeasurementWidget"));
        SVMeasurementWidget->setEnabled(true);
        SVMeasurementWidget->resize(439, 213);
        gridLayout = new QGridLayout(SVMeasurementWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditStartZ = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditStartZ->setObjectName(QString::fromUtf8("lineEditStartZ"));
        QFont font;
        font.setPointSize(9);
        lineEditStartZ->setFont(font);
        lineEditStartZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditStartZ->setReadOnly(true);

        gridLayout->addWidget(lineEditStartZ, 4, 3, 1, 1);

        lineEditDistZ = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditDistZ->setObjectName(QString::fromUtf8("lineEditDistZ"));
        lineEditDistZ->setFont(font);
        lineEditDistZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditDistZ->setReadOnly(true);

        gridLayout->addWidget(lineEditDistZ, 7, 3, 1, 1);

        line_2 = new QFrame(SVMeasurementWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 8, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 13, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonColor = new QtExt::ColorButton(SVMeasurementWidget);
        pushButtonColor->setObjectName(QString::fromUtf8("pushButtonColor"));

        horizontalLayout->addWidget(pushButtonColor);

        pushButtonCopyInformation = new QPushButton(SVMeasurementWidget);
        pushButtonCopyInformation->setObjectName(QString::fromUtf8("pushButtonCopyInformation"));

        horizontalLayout->addWidget(pushButtonCopyInformation);

        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 12, 1, 1, 3);

        line = new QFrame(SVMeasurementWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 6, 0, 1, 4);

        labelStartPoint = new QLabel(SVMeasurementWidget);
        labelStartPoint->setObjectName(QString::fromUtf8("labelStartPoint"));
        labelStartPoint->setFont(font);

        gridLayout->addWidget(labelStartPoint, 4, 0, 1, 1);

        label_3 = new QLabel(SVMeasurementWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        lineEditStartY = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditStartY->setObjectName(QString::fromUtf8("lineEditStartY"));
        lineEditStartY->setFont(font);
        lineEditStartY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditStartY->setReadOnly(true);

        gridLayout->addWidget(lineEditStartY, 4, 2, 1, 1);

        lineEditEndX = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditEndX->setObjectName(QString::fromUtf8("lineEditEndX"));
        lineEditEndX->setFont(font);
        lineEditEndX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditEndX->setReadOnly(true);

        gridLayout->addWidget(lineEditEndX, 5, 1, 1, 1);

        lineEditEndZ = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditEndZ->setObjectName(QString::fromUtf8("lineEditEndZ"));
        lineEditEndZ->setFont(font);
        lineEditEndZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditEndZ->setReadOnly(true);

        gridLayout->addWidget(lineEditEndZ, 5, 3, 1, 1);

        label = new QLabel(SVMeasurementWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditDistX = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditDistX->setObjectName(QString::fromUtf8("lineEditDistX"));
        lineEditDistX->setFont(font);
        lineEditDistX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditDistX->setReadOnly(true);

        gridLayout->addWidget(lineEditDistX, 7, 1, 1, 1);

        lineEditDistY = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditDistY->setObjectName(QString::fromUtf8("lineEditDistY"));
        lineEditDistY->setFont(font);
        lineEditDistY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditDistY->setReadOnly(true);

        gridLayout->addWidget(lineEditDistY, 7, 2, 1, 1);

        lineEditStartX = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditStartX->setObjectName(QString::fromUtf8("lineEditStartX"));
        lineEditStartX->setFont(font);
        lineEditStartX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditStartX->setReadOnly(true);

        gridLayout->addWidget(lineEditStartX, 4, 1, 1, 1);

        labelStartPoint_2 = new QLabel(SVMeasurementWidget);
        labelStartPoint_2->setObjectName(QString::fromUtf8("labelStartPoint_2"));
        labelStartPoint_2->setFont(font);

        gridLayout->addWidget(labelStartPoint_2, 5, 0, 1, 1);

        label_2 = new QLabel(SVMeasurementWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        lineEditEndY = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditEndY->setObjectName(QString::fromUtf8("lineEditEndY"));
        lineEditEndY->setFont(font);
        lineEditEndY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditEndY->setReadOnly(true);

        gridLayout->addWidget(lineEditEndY, 5, 2, 1, 1);

        checkBoxLocalMeasurement = new QCheckBox(SVMeasurementWidget);
        checkBoxLocalMeasurement->setObjectName(QString::fromUtf8("checkBoxLocalMeasurement"));

        gridLayout->addWidget(checkBoxLocalMeasurement, 12, 0, 1, 1);

        lineEditDistance = new QtExt::ValidatingLineEdit(SVMeasurementWidget);
        lineEditDistance->setObjectName(QString::fromUtf8("lineEditDistance"));
        lineEditDistance->setFont(font1);
        lineEditDistance->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditDistance->setReadOnly(true);

        gridLayout->addWidget(lineEditDistance, 1, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);


        retranslateUi(SVMeasurementWidget);

        QMetaObject::connectSlotsByName(SVMeasurementWidget);
    } // setupUi

    void retranslateUi(QWidget *SVMeasurementWidget)
    {
        SVMeasurementWidget->setWindowTitle(QCoreApplication::translate("SVMeasurementWidget", "Distance", nullptr));
        pushButtonColor->setText(QString());
        pushButtonCopyInformation->setText(QCoreApplication::translate("SVMeasurementWidget", "Copy Information", nullptr));
        labelStartPoint->setText(QCoreApplication::translate("SVMeasurementWidget", "Start point (X/Y/Z):", nullptr));
        label_3->setText(QCoreApplication::translate("SVMeasurementWidget", "m", nullptr));
        label->setText(QCoreApplication::translate("SVMeasurementWidget", "Distance:", nullptr));
        labelStartPoint_2->setText(QCoreApplication::translate("SVMeasurementWidget", "End point (X/Y/Z):", nullptr));
        label_2->setText(QCoreApplication::translate("SVMeasurementWidget", "Offsets (\316\224X/\316\224Y/\316\224Z) [m]:", nullptr));
        checkBoxLocalMeasurement->setText(QCoreApplication::translate("SVMeasurementWidget", "use local coordinate system", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SVMeasurementWidget: public Ui_SVMeasurementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVMEASUREMENTWIDGET_H
