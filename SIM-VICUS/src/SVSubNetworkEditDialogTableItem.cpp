#include "SVSubNetworkEditDialogTableItem.h"
#include "ui_SVSubNetworkEditDialogTableItem.h"

#include "SVConstants.h"
#include "SVStyle.h"

#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>


SVSubNetworkEditDialogTableItem::SVSubNetworkEditDialogTableItem(QString filename, QString text, QString tooltip, int height, QWidget *parent, bool subCategory, bool inBuild) :
	QWidget(parent),
	ui(new Ui::SVSubNetworkEditDialogTableItem),
	m_inbuild(inBuild)
{
	ui->setupUi(this);
	if(!subCategory){
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
		layout->setSpacing(0);
		layout->setStretchFactor(iconLabel, 0);
		layout->setStretchFactor(textLabel, 1);
		setToolTip(tooltip);
		setLayout(layout);
	} else {
		QLabel *textLabel = new QLabel("        " + text, this);
		textLabel->setMinimumSize(0, 0);
		textLabel->setAlignment(Qt::AlignLeft| Qt::AlignVCenter); // This will center the text both horizontally and vertically
		textLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

		QHBoxLayout *layout = new QHBoxLayout(this);
		layout->addWidget(textLabel);
		layout->setContentsMargins(0,0,0,0);
		layout->setStretchFactor(textLabel, 0);
		setToolTip(tooltip);
		setLayout(layout);
	}

	setToolTip(QString("<p style='color: #000000; background-color: #ffffff; border: 1px solid black;'>%1</p>").arg(tooltip));

	this->setAutoFillBackground(true);

}

SVSubNetworkEditDialogTableItem::~SVSubNetworkEditDialogTableItem()
{
	delete ui;
}
