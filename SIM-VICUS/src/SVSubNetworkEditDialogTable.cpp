#include "SVSubNetworkEditDialogTable.h"
#include "ui_SVSubNetworkEditDialogTable.h"


// TODO Maik: richtige Klammern

#include "SVSubNetworkEditDialogTableItem.h"

#include <QDebug>
#include <QHeaderView>
#include <QLayout>
#include <QLabel>
#include <QPalette>
#include <QMimeData>
#include <QDrag>

#include "SVSubNetworkEditDialog.h"
#include <SVBMZoomMeshGraphicsView.h>

#include <VICUS_NetworkController.h>
#include <VICUS_KeywordListQt.h>

#include "SVConstants.h"
#include "SVStyle.h"


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
	SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(getIconFileFromModelType(type), VICUS::KeywordListQt::Keyword("NetworkComponent::ModelType", type), VICUS::KeywordListQt::Description("NetworkComponent::ModelType", type), m_defaultRowHeight, this);
	setFixedHeight(height() + m_defaultRowHeight);
	insertRow(m_rowSize);
	setCellWidget(m_rowSize, 0, bmItem1);
	setRowHeight(m_rowSize, m_defaultRowHeight);
	QString elementString = QString("default:") + QString::number(type);
	m_elementList.push_back(elementString);
	m_rowSize++;
}

void SVSubNetworkEditDialogTable::addElement(VICUS::NetworkComponent &component){
	const int rowHeight = 35;
	SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::getIconFileFromModelType(component.m_modelType),  QString::fromStdString(component.m_displayName.string("en")), VICUS::KeywordListQt::Description("NetworkComponent::ModelType", component.m_modelType), m_defaultRowHeight, this, true);
	setFixedHeight(height() + rowHeight);
	insertRow(m_rowSize);
	setCellWidget(m_rowSize, 0, bmItem1);
	setRowHeight(m_rowSize, rowHeight);
	QString elementString = QString("db:") + QString::number(static_cast<int>(component.m_modelType)) + QString(":") + QString::number(component.m_id);
	m_elementList.push_back(elementString);
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

//	QMimeData *mimeData = new QMimeData();
//	mimeData->setText(m_elementList[index]);

//	QDrag *drag = new QDrag(this);

//	double scaleX = m_zoomMeshGraphicsView->getScaleX();
//	double scaleY = m_zoomMeshGraphicsView->getScaleY();

//	VICUS::NetworkComponent::ModelType type;

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

//	QPixmap pixmap = QPixmap(VICUS::getIconFileFromModelType(type));
//	drag->setPixmap(pixmap.scaled(m_defaultRowHeight * scaleX, m_defaultRowHeight * scaleY));
//	drag->setHotSpot(QPoint(m_defaultRowHeight * scaleX / 2, m_defaultRowHeight * scaleY / 2));
//	drag->setMimeData(mimeData);
//	drag->exec(supportedActions, Qt::CopyAction);
}

void SVSubNetworkEditDialogTable::focusOutEvent(QFocusEvent */*event*/)
{
	setCurrentCell(-1, -1);
}


