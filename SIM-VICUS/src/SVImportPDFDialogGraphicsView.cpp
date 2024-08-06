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


void SVImportPDFDialogGraphicsView::setImage(const QImage &image) {
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

	m_pixmapItem = m_scene->addPixmap(pixmap);
}

void SVImportPDFDialogGraphicsView::setTwoPointMode(bool twoPointMode) {
	if (!twoPointMode) {
		removePointsFromScene();
		emit pointCountChanged(0);
	}
	m_twoPointMode = twoPointMode;
}

void SVImportPDFDialogGraphicsView::zoomIn() {
	if (m_zoomLevel < 35) {
		scale(1.2, 1.2);
		m_zoomLevel++;
	}
}

void SVImportPDFDialogGraphicsView::zoomOut() {
	if (m_zoomLevel > 0) {
		scale(1/1.2, 1/1.2);
		m_zoomLevel--;
	}
}

void SVImportPDFDialogGraphicsView::mousePressEvent(QMouseEvent * event) {
	m_isDragging = false;
	m_startPos = event->pos();
	QGraphicsView::mousePressEvent(event);
}

void SVImportPDFDialogGraphicsView::mouseMoveEvent(QMouseEvent * event) {
	if (m_startPos.isNull()) {
		return;
	}

	int distance = (event->pos() - m_startPos).manhattanLength();
	if (distance >= m_dragThreshold) {
		if (!m_isDragging && m_twoPointMode)
			QApplication::restoreOverrideCursor();
		m_isDragging = true;
	}

	QGraphicsView::mouseMoveEvent(event);
}

void SVImportPDFDialogGraphicsView::mouseReleaseEvent(QMouseEvent * event) {
	if (!m_isDragging && m_twoPointMode){
		QPointF scenePos = mapToScene(event->pos());
		if (m_points.size() < 2)
		{
			m_points.push_back(scenePos);
			updatePointsAndLines();
		}
		else
			removePointsFromScene();
		emit pointCountChanged(m_points.size());
	}
	if (m_isDragging && m_twoPointMode)
		QApplication::setOverrideCursor(Qt::CrossCursor);
	m_isDragging = false;
	m_startPos = QPointF(0,0);
}

void SVImportPDFDialogGraphicsView::wheelEvent(QWheelEvent * event) {
	if (event->angleDelta().y() < 0) {
		zoomOut();
	}
	else {
		zoomIn();
	}
	event->accept();
}

void SVImportPDFDialogGraphicsView::enterEvent(QEvent * event) {
	if (m_twoPointMode)
		QApplication::setOverrideCursor(Qt::CrossCursor);
	QGraphicsView::enterEvent(event);
}

void SVImportPDFDialogGraphicsView::leaveEvent(QEvent * event) {
	if (m_twoPointMode)
		QApplication::restoreOverrideCursor();
	QGraphicsView::enterEvent(event);
}

void SVImportPDFDialogGraphicsView::drawPoint(const QPointF &pos) {
	QPen pen(Qt::red);
	pen.setCosmetic(true);
	pen.setWidth(4);

	QGraphicsEllipseItem* point = new QGraphicsEllipseItem(-1, -1, 2, 2);
	point->setPen(pen);
	point->setBrush(Qt::red);
	point->setPos(pos);
	point->setFlags(QGraphicsItem::ItemIgnoresTransformations);
	m_scene->addItem(point);
}

void SVImportPDFDialogGraphicsView::drawLine() {
	QPen pen(Qt::red);
	pen.setCosmetic(true);
	pen.setWidth(2);

	QLineF line(m_points[0], m_points[1]);
	QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);
	lineItem->setPen(pen);
	m_scene->addItem(lineItem);
}

void SVImportPDFDialogGraphicsView::updatePointsAndLines() {
	if (m_points.size() == 2) {
		drawLine();
	}

	for (QPointF &point : m_points) {
		drawPoint(point);
	}
}

void SVImportPDFDialogGraphicsView::removePointsFromScene() {
	m_points.clear();
	m_scene->clear();
	m_scene->addPixmap(QPixmap::fromImage(m_image));
}
