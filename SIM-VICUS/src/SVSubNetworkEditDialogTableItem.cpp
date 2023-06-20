#include "SVSubNetworkEditDialogTableItem.h"
#include "ui_SVSubNetworkEditDialogTableItem.h"
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include "SVConstants.h"
#include "SVStyle.h"

SVSubNetworkEditDialogTableItem::SVSubNetworkEditDialogTableItem(QString filename, QString text, QString tooltip, int height, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SVSubNetworkEditDialogTableItem)
{
    ui->setupUi(this);
    QLabel *iconLabel = new QLabel(this);
    QLabel *textLabel = new QLabel(text, this);
    QHBoxLayout *layout = new QHBoxLayout(this);

    QPixmap pixmap(filename);
    iconLabel->setPixmap(pixmap.scaled(height, height));
    iconLabel->setMinimumSize(height, height);
    iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    textLabel->setMinimumSize(0, 0);
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(5);
    layout->setStretchFactor(iconLabel, 0);
    layout->setStretchFactor(textLabel, 1);
    setToolTip(tooltip);
    setLayout(layout);
}


SVSubNetworkEditDialogTableItem::~SVSubNetworkEditDialogTableItem()
{
    delete ui;
}
