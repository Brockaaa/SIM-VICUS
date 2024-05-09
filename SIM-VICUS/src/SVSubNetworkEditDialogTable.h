#ifndef SVSUBNETWORKEDITDIALOGTABLE_H
#define SVSUBNETWORKEDITDIALOGTABLE_H

#include <QWidget>
#include <QTableWidget>

#include <VICUS_BMGlobals.h>
#include <VICUS_NetworkComponent.h>
#include <VICUS_KeywordListQt.h>

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
	struct SubNetworkEditDialogTableEntry {

		SubNetworkEditDialogTableEntry(){}

		SubNetworkEditDialogTableEntry(QString &text) {
			QString modelType = text.split(":")[0];
			m_modelType = VICUS::NetworkComponent::ModelType( VICUS::KeywordList::Enumeration("NetworkComponent::ModelType", modelType.toStdString()) );
			m_id = text.split(":")[1].toUInt();
		}
		/*! id of database element, INVALID_ID means it is a new component */
		unsigned int							m_id;
		VICUS::NetworkComponent::ModelType		m_modelType;

		QString toText() {
			return QString("%1:%2")
					.arg( VICUS::KeywordList::Keyword("NetworkComponent::ModelType", m_modelType) )
					.arg(m_id);
		}
	};

	explicit SVSubNetworkEditDialogTable(QWidget *parent = nullptr);
	~SVSubNetworkEditDialogTable();
	int rowSize() const;
	/* adds Default Element to Table, includes QPixmap */
	void addElement(VICUS::NetworkComponent::ModelType type);
	/* adds Element to Table */
	void addElement(VICUS::NetworkComponent &controller);
	/* removes all Elements from Table */
	void clear();

private:

	void startDrag(Qt::DropActions supportedActions) override;

	void focusOutEvent(QFocusEvent *event) override;
	/* sets proper marking color when item selected */
	void on_itemSelectionChanged();

	void on_styleChanged();

public:

	Ui::SVSubNetworkEditDialogTable		*m_ui;

	/*! */
	std::vector<SubNetworkEditDialogTableEntry>			m_elementList;

	int													m_rowSize = 0;

	int													m_defaultRowHeight = int(VICUS::BLOCK_HEIGHT / 1.5);

	/* Pointer to ZoomMeshGraphicsView, needed to determine position of Dragged Element */
	SVBMZoomMeshGraphicsView							*m_zoomMeshGraphicsView = nullptr;

};

#endif // SVSUBNETWORKEDITDIALOGTABLE_H
