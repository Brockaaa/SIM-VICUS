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
	m_image = image;
	m_scene->clear();
	QPixmap pixmap = QPixmap::fromImage(image);
	QGraphicsPixmapItem *item = m_scene->addPixmap(pixmap);
	qDebug() << "Pixmap rect: " << pixmap.rect();
	qDebug() << "Scene rect: " << rect();
	m_scene->setSceneRect(rect());
	double ratio = (double)rect().width() / (double)pixmap.rect().width();
	scale(ratio, ratio);
}

void SVImportPDFDialogGraphicsView::setTwoPointMode(bool twoPointMode)
{
	if(!twoPointMode)
		removePointsFromScene();
	m_twoPointMode = twoPointMode;
}

void SVImportPDFDialogGraphicsView::zoomIn()
{
	scale(1.2, 1.2);
	m_zoomLevel++;
}

void SVImportPDFDialogGraphicsView::zoomOut()
{
	if(m_zoomLevel > 0){
		scale(1/1.2, 1/1.2);
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
	pen.setWidth(3);
	m_scene->addEllipse(pos.x() - 2, pos.y() - 2, 4, 4, pen, QBrush(Qt::red));
}

void SVImportPDFDialogGraphicsView::drawLine()
{
	QPen pen(Qt::blue);
	pen.setWidth(2);
	m_scene->addLine(QLineF(m_points[0], m_points[1]), pen);
}

void SVImportPDFDialogGraphicsView::removePointsFromScene()
{
	m_points.clear();
	m_scene->clear();
	m_scene->addPixmap(QPixmap::fromImage(m_image));
	emit pointCountChanged(m_points.size());
}
