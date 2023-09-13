#ifndef SVSUBNETWORKEDITDIALOGTABLE_H
#define SVSUBNETWORKEDITDIALOGTABLE_H

#include <QWidget>
#include <QTableWidget>

#include <VICUS_BMGlobals.h>
#include "VICUS_NetworkComponent.h"

class SVBMZoomMeshGraphicsView;

namespace Ui {
class SVSubNetworkEditDialogTable;
}

namespace VICUS{
class NetworkController;
}

class SVSubNetworkEditDialogTable : public QTableWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkEditDialogTable(QWidget *parent = nullptr);
	~SVSubNetworkEditDialogTable();
	int rowSize() const;
	/* adds Default Element to Table, includes QPixmap */
	void addElement(VICUS::NetworkComponent::ModelType type);
	/* adds Element to Table */
	void addElement(VICUS::NetworkComponent &controller);
	/* removes all Elements from Table */
	void clear();
	std::vector<QString> m_elementList;

private:
	Ui::SVSubNetworkEditDialogTable *ui;

	int m_rowSize = 0;
	int m_defaultRowHeight = VICUS::BLOCK_HEIGHT;

	void startDrag(Qt::DropActions supportedActions) override;
	void focusOutEvent(QFocusEvent *event) override;

	/* Pointer to ZoomMeshGraphicsView, needed to determine position of Dragged Element */
	SVBMZoomMeshGraphicsView *                      m_zoomMeshGraphicsView = nullptr;


};

#endif // SVSUBNETWORKEDITDIALOGTABLE_H
