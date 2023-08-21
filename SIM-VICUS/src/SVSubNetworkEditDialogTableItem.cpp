#include "SVSubNetworkEditDialogTableItem.h"
#include "ui_SVSubNetworkEditDialogTableItem.h"
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include "SVConstants.h"
#include "SVStyle.h"

SVSubNetworkEditDialogTableItem::SVSubNetworkEditDialogTableItem(QString filename, QString text, QString tooltip, int height, QWidget *parent, bool subCategory) :
    QWidget(parent),
    ui(new Ui::SVSubNetworkEditDialogTableItem)
{
    ui->setupUi(this);
    if(!subCategory){
        QLabel *iconLabel = new QLabel(this);
        QLabel *textLabel = new QLabel(text, this);
        QHBoxLayout *layout = new QHBoxLayout(this);

        //TODO : pixmap takes long, only supports very limited number of images
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
    } else {
        const int LEFT_PADDING = 30; // Adjust this constant for desired left padding

        QLabel *textLabel = new QLabel(text, this);
        textLabel->setMinimumSize(0, 0);
        textLabel->setAlignment(Qt::AlignLeft); // This will center the text both horizontally and vertically
        textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addSpacing(LEFT_PADDING); // Add padding to the left
        layout->addWidget(textLabel);
        layout->setStretchFactor(textLabel, 1);
        setToolTip(tooltip);
        setLayout(layout);
    }

}

SVSubNetworkEditDialogTableItem::~SVSubNetworkEditDialogTableItem()
{
    delete ui;
}
