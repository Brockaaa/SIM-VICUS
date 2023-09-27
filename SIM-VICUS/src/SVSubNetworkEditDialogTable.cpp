#include "SVSubNetworkEditDialogTable.h"
#include "ui_SVSubNetworkEditDialogTable.h"

#include "SVSubNetworkEditDialogTableItem.h"
#include "SVSubNetworkEditDialog.h"
#include "SVBMZoomMeshGraphicsView.h"

#include <QDebug>
#include <QHeaderView>
#include <QPalette>
#include <QMimeData>
#include <QDrag>

#include <VICUS_NetworkController.h>
#include <VICUS_KeywordListQt.h>


SVSubNetworkEditDialogTable::SVSubNetworkEditDialogTable(QWidget *parent) :
	QTableWidget(parent),
	m_ui(new Ui::SVSubNetworkEditDialogTable)
{
	m_ui->setupUi(this);
	setFrameStyle(0);
	setShowGrid(false);
	setDragEnabled(true);
	setDropIndicatorShown(true);
	setDefaultDropAction(Qt::CopyAction);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectItems);
	setColumnCount(1);

	m_zoomMeshGraphicsView = dynamic_cast<SVSubNetworkEditDialog*>(parent)->zoomMeshGraphicsView();

	QPalette palette = this->palette();
	palette.setColor(QPalette::Highlight, palette.color(QPalette::Base));
	setPalette(palette);

	QHeaderView *vheader = verticalHeader();
	vheader->setVisible(false);

	QHeaderView *hheader = horizontalHeader();
	hheader->setSectionResizeMode(0, QHeaderView::Stretch);
	hheader->setVisible(false);
}

SVSubNetworkEditDialogTable::~SVSubNetworkEditDialogTable()
{
	delete m_ui;
}

void SVSubNetworkEditDialogTable::addElement(VICUS::NetworkComponent::ModelType type){
	SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::NetworkComponent::iconFileFromModelType(type), VICUS::KeywordListQt::Keyword("NetworkComponent::ModelType", type), VICUS::KeywordListQt::Description("NetworkComponent::ModelType", type), m_defaultRowHeight, this);
	setFixedHeight(height() + m_defaultRowHeight);
	insertRow(m_rowSize);
	setCellWidget(m_rowSize, 0, bmItem1);
	setRowHeight(m_rowSize, m_defaultRowHeight);
	SubNetworkEditDialogTableEntry entry;
	entry.m_modelType = type;
	entry.m_id = VICUS::INVALID_ID;
	QString generatedString = entry.toText();
	m_elementList.push_back(generatedString);
	m_rowSize++;
}

void SVSubNetworkEditDialogTable::addElement(VICUS::NetworkComponent &component){
	const int rowHeight = 35;
	SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::NetworkComponent::iconFileFromModelType(component.m_modelType),  QString::fromStdString(component.m_displayName.string("en")), VICUS::KeywordListQt::Description("NetworkComponent::ModelType", component.m_modelType), m_defaultRowHeight, this, true);
	if(!component.m_builtIn){
		bmItem1->setStyleSheet("background-color: #ADD8E6;");
	}
	setFixedHeight(height() + rowHeight);
	insertRow(m_rowSize);
	setCellWidget(m_rowSize, 0, bmItem1);
	setRowHeight(m_rowSize, rowHeight);
	SubNetworkEditDialogTableEntry entry;
	entry.m_modelType = component.m_modelType;
	entry.m_id = component.m_id;
	QString generatedString = entry.toText();
	m_elementList.push_back(generatedString);
	m_rowSize++;
}

void SVSubNetworkEditDialogTable::clear()
{
	QTableWidget::clear();
	m_elementList.clear();
	for (int i = rowCount() - 1; i >= 0; i--) {
		removeRow(i);
	}
	m_rowSize = 0;
	setFixedHeight(0);
}


void SVSubNetworkEditDialogTable::startDrag(Qt::DropActions supportedActions){

	QModelIndexList selected = selectedIndexes();
	if(selected.isEmpty())
		return;

	int index = selected[0].row();

	QMimeData *mimeData = new QMimeData();
	mimeData->setText(m_elementList[index].toText());

	QDrag *drag = new QDrag(this);

	double scaleX = m_zoomMeshGraphicsView->getScaleX();
	double scaleY = m_zoomMeshGraphicsView->getScaleY();

	VICUS::NetworkComponent::ModelType type = m_elementList[index].m_modelType;

//	if(m_elementList[index].startsWith("default:")){
//		type = static_cast<VICUS::NetworkComponent::ModelType>(m_elementList[index].split(":")[1].toInt());
//	}
//	else if (m_elementList[index].startsWith("db:")){
//		for(int i = index; i >= 0; i--){
//			if(m_elementList[i].startsWith("default:")){
//				type = static_cast<VICUS::NetworkComponent::ModelType>(m_elementList[i].split(":")[1].toInt());
//				break;
//			}
//		}
//	}

	QPixmap pixmap = QPixmap(VICUS::NetworkComponent::iconFileFromModelType(type));
	drag->setPixmap(pixmap.scaled(m_defaultRowHeight * scaleX, m_defaultRowHeight * scaleY));
	drag->setHotSpot(QPoint(m_defaultRowHeight * scaleX / 2, m_defaultRowHeight * scaleY / 2));
	drag->setMimeData(mimeData);
	drag->exec(supportedActions, Qt::CopyAction);
}

void SVSubNetworkEditDialogTable::focusOutEvent(QFocusEvent */*event*/)
{
	setCurrentCell(-1, -1);
}


