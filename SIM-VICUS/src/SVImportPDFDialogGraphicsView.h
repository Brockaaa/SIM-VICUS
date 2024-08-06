#ifndef SVIMPORTPDFDIALOGGRAPHICSVIEW_H
#define SVIMPORTPDFDIALOGGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>

class QGraphicsPixmapItem;

class SVImportPDFDialogGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit SVImportPDFDialogGraphicsView(QWidget *parent = nullptr);

	void setImage(const QImage &image);

	float scaling(){ return m_scale; }

	void setTwoPointMode(bool twoPointMode);

	bool twoPointMode(){ return m_twoPointMode; }

public slots:
	/*! Increases zoom level. */
	void zoomIn();

	/*! Decreases zoom level. */
	void zoomOut();

protected:
	void mousePressEvent(QMouseEvent *event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

	void wheelEvent(QWheelEvent *event) override;

	/*! Overloaded to set cross/arrow cursor */
	void enterEvent(QEvent *event) override;

	/*! Overloaded to set arrow cursor. */
	void leaveEvent(QEvent *event) override;
signals:
	void pointCountChanged(int numberOfPointsInScene);

private:
	void drawPoint(const QPointF &pos);

	void drawLine();

	void updatePointsAndLines();

	void removePointsFromScene();

	int						m_dragThreshold = 5;

	QPointF					m_startPos;

	bool					m_isDragging = false;

	bool					m_twoPointMode = false;

	std::vector<QPointF>	m_points;

	QGraphicsScene			*m_scene = nullptr;

	float					m_scale = 1;

	int						m_zoomLevel = 0;

	QImage					m_image;

	QGraphicsPixmapItem		*m_pixmapItem;

	friend class SVImportPDFDialog;
};

#endif // SVIMPORTPDFDIALOGGRAPHICSVIEW_H
