#include "QtExt_SubNetworkHoverToSelect.h"

#include <QVBoxLayout>
#include <QColor>
#include <QDebug>
#include <QPainter>

QtExt_SubNetworkHoverToSelect::QtExt_SubNetworkHoverToSelect(QWidget *parent)
	: QWidget(parent)
{
	label = new QLabel(this);

	//set size to expanding
	label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	label->setMinimumSize(835, 500);
	label->setMaximumSize(835, 500);
	// no padding or margins
	label->setStyleSheet("QLabel { background-color: white; border: 0px; padding: 0px; margin: 0px; }");

	//add to parent
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);

	setLayout(layout);


}

void QtExt_SubNetworkHoverToSelect::setThumbnail(const QPixmap &thumbnail)
{
	m_thumbNail = new QPixmap(thumbnail);
	QPixmap newPixmap(QSize(this->width(), this->height()));
	newPixmap.fill(Qt::transparent);
	// Create a painter to draw on the pixmap
	QPainter painter(&newPixmap);
	// Draw the original pixmap
	painter.drawPixmap(0, this->height() / 2 - m_thumbNail->height() / 2, *m_thumbNail);
	label->setPixmap(newPixmap);
	label->setGeometry(0, 0, this->width(), this->height());
}

void QtExt_SubNetworkHoverToSelect::enterEvent(QEvent *event)
{
	if (!label || label->pixmap() == nullptr)
		return;

	// Get the size of this widget
	QSize size = QSize(this->width(), this->height());

	// Create a new QPixmap to draw on
	QPixmap newPixmap(size);
	newPixmap.fill(Qt::transparent); // Fill with transparent color

	// Create a painter to draw on the pixmap
	QPainter painter(&newPixmap);

	// Draw the original pixmap
	painter.drawPixmap(0, this->height() / 2 - m_thumbNail->height() / 2, *m_thumbNail);

	// Create a gradient
	QRectF sceneRect = QRectF(0, 0, size.width(), size.height());
	QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());

	QColor col1("#4a8522");
	col1.setAlpha(200);
	QColor col2("#ffffff");
	col2.setAlpha(0);

	gradient.setColorAt(0, col2);  // Starting color
	gradient.setColorAt(1, col1);  // Ending color

	// Set the brush for the painter
	painter.setBrush(QBrush(gradient));
	painter.setCompositionMode(QPainter::CompositionMode_Darken);

	// Draw the rectangle with the gradient
	painter.fillRect(sceneRect, QBrush(gradient));

	// now draw the edit icon
	painter.drawPixmap(this->width() / 2 - m_icon->width() / 2, this->height() / 2 - m_icon->height() / 2, *m_icon);

	// Set the new pixmap as the label's background
	label->setPixmap(newPixmap);
	// position the pixmap to the left top corner
	label->setGeometry(0, 0, this->width(), this->height());

	QWidget::enterEvent(event); // Call base class implementation
}

void QtExt_SubNetworkHoverToSelect::leaveEvent(QEvent *event)
{
	QPixmap newPixmap(QSize(this->width(), this->height()));
	newPixmap.fill(Qt::transparent);
	// Create a painter to draw on the pixmap
	QPainter painter(&newPixmap);
	// Draw the original pixmap
	painter.drawPixmap(0, this->height() / 2 - m_thumbNail->height() / 2, *m_thumbNail);
	label->setPixmap(newPixmap);
	label->setGeometry(0, 0, this->width(), this->height());
}

void QtExt_SubNetworkHoverToSelect::mouseReleaseEvent(QMouseEvent *event)
{
	emit thumbNailClicked();
}
