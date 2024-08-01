#include "SVImportPDFDialogGraphicsView.h"

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QApplication>

#include <QDebug>

SVImportPDFDialogGraphicsView::SVImportPDFDialogGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	m_scene = new QGraphicsScene(this);
	setScene(m_scene);
	setRenderHint(QPainter::Antialiasing);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setBackgroundBrush(QBrush(Qt::lightGray));
}


void SVImportPDFDialogGraphicsView::setImage(const QImage &image)
{
	m_zoomLevel = 0;
	resetTransform();
	m_points.clear();
	m_image = image;
	m_scene->clear();

	QPixmap pixmap = QPixmap::fromImage(image);
	double ratio = (double)pixmap.rect().width() / (double)rect().width();
	double inverseRatio = (double)rect().width() / (double)pixmap.rect().width();
	m_scene->setSceneRect(QRect(0, 0, rect().width() * ratio, rect().height() * ratio));
	scale(inverseRatio, inverseRatio);

	QGraphicsPixmapItem *item = m_scene->addPixmap(pixmap);
}

void SVImportPDFDialogGraphicsView::setTwoPointMode(bool twoPointMode)
{
	if(!twoPointMode)
		removePointsFromScene();
	m_twoPointMode = twoPointMode;
}

void SVImportPDFDialogGraphicsView::zoomIn()
{
	if (m_zoomLevel < 35) {
		scale(1.2, 1.2);
		updatePointsAndLines();
		m_zoomLevel++;
	}
}

void SVImportPDFDialogGraphicsView::zoomOut()
{
	if (m_zoomLevel > 0) {
		scale(1/1.2, 1/1.2);
		updatePointsAndLines();
		m_zoomLevel--;
	}
}

void SVImportPDFDialogGraphicsView::mousePressEvent(QMouseEvent * event)
{
	m_isDragging = false;
	m_startPos = event->pos();
	QGraphicsView::mousePressEvent(event);
}

void SVImportPDFDialogGraphicsView::mouseMoveEvent(QMouseEvent * event)
{
	if (m_startPos.isNull()) {
		return;
	}

	int distance = (event->pos() - m_startPos).manhattanLength();
	if (distance >= m_dragThreshold) {
		if(!m_isDragging && m_twoPointMode)
			QApplication::restoreOverrideCursor();
		m_isDragging = true;
	}

	QGraphicsView::mouseMoveEvent(event);
}

void SVImportPDFDialogGraphicsView::mouseReleaseEvent(QMouseEvent * event)
{
	if(!m_isDragging && m_twoPointMode){
		QPointF scenePos = mapToScene(event->pos());
		if (m_points.size() < 2)
		{
			m_points.push_back(scenePos);
			qDebug() << "point placed: " << scenePos;
			drawPoint(scenePos);
			if (m_points.size() == 2)
			{
				drawLine();
			}
			emit pointCountChanged(m_points.size());
		}
		else
			removePointsFromScene();
	}
	if(m_isDragging && m_twoPointMode)
		QApplication::setOverrideCursor(Qt::CrossCursor);
	m_isDragging = false;
	m_startPos = QPointF(0,0);
}

void SVImportPDFDialogGraphicsView::wheelEvent(QWheelEvent * event)
{
	if (event->angleDelta().y() < 0) {
		zoomOut();
	}
	else {
		zoomIn();
	}
	event->accept();
}

void SVImportPDFDialogGraphicsView::enterEvent(QEvent * event)
{
	if(m_twoPointMode)
		QApplication::setOverrideCursor(Qt::CrossCursor);
	QGraphicsView::enterEvent(event);
}

void SVImportPDFDialogGraphicsView::leaveEvent(QEvent * event)
{
	if(m_twoPointMode)
		QApplication::restoreOverrideCursor();
	QGraphicsView::enterEvent(event);
}

void SVImportPDFDialogGraphicsView::drawPoint(const QPointF & pos)
{
	QPen pen(Qt::red);
	pen.setCosmetic(true);  // This ensures constant pixel width
	pen.setWidth(3);

	QGraphicsEllipseItem* point = m_scene->addEllipse(0, 0, 4, 4, pen, QBrush(Qt::red));
	point->setPos(pos - QPointF(2, 2));  // Center the point on the given position
	point->setFlags(QGraphicsItem::ItemIgnoresTransformations);  // Keep constant size
}

void SVImportPDFDialogGraphicsView::drawLine()
{
	QPen pen(Qt::blue);
	pen.setCosmetic(true);  // This ensures constant pixel width
	pen.setWidth(2);

	QGraphicsLineItem* line = m_scene->addLine(QLineF(m_points[0] - QPointF(1.75, 1.75), m_points[1] - QPointF(1.75, 1.75)), pen);
	//line->setFlags(QGraphicsItem::ItemIgnoresTransformations);  // Keep constant width
}

void SVImportPDFDialogGraphicsView::updatePointsAndLines()
{
	// Remove existing points and lines
	for (auto item : m_scene->items()) {
		if (item->type() == QGraphicsEllipseItem::Type || item->type() == QGraphicsLineItem::Type) {
			m_scene->removeItem(item);
			delete item;
		}
	}

	if (m_points.size() == 2) {
		drawLine();
	}
	// Redraw points and lines
	for (const QPointF &point : m_points) {
		drawPoint(point);
	}
}

void SVImportPDFDialogGraphicsView::removePointsFromScene()
{
	m_points.clear();
	m_scene->clear();
	m_scene->addPixmap(QPixmap::fromImage(m_image));
	emit pointCountChanged(m_points.size());
}
