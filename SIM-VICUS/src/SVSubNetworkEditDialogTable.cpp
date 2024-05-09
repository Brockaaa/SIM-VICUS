#include "SVSubNetworkEditDialogTable.h"
#include "ui_SVSubNetworkEditDialogTable.h"

#include "SVSubNetworkEditDialogTableItem.h"
#include "SVSubNetworkEditDialog.h"
#include "SVBMZoomMeshGraphicsView.h"
#include "SVStyle.h"

#include <QDebug>
#include <QHeaderView>
#include <QPalette>
#include <QMimeData>
#include <QDrag>
#include <QSvgRenderer>

#include <QtExt_Style.h>

#include <VICUS_NetworkController.h>
#include <VICUS_KeywordListQt.h>

#include "SVMainWindow.h"
#include "SVPreferencesDialog.h"
#include "SVPreferencesPageStyle.h"
#include "SVSettings.h"


SVSubNetworkEditDialogTable::SVSubNetworkEditDialogTable(QWidget *parent) :
	QTableWidget(parent),
	m_ui(new Ui::SVSubNetworkEditDialogTable)
{
	m_ui->setupUi(this);
	setFrameStyle(QFrame::NoFrame);
	setShowGrid(false);
	setDragEnabled(true);
	setDropIndicatorShown(true);
	setDefaultDropAction(Qt::CopyAction);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setSelectionBehavior(QAbstractItemView::SelectItems);
	setColumnCount(1);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_zoomMeshGraphicsView = dynamic_cast<SVSubNetworkEditDialog*>(parent)->zoomMeshGraphicsView();

	QPalette palette = this->palette();
	palette.setColor(QPalette::Highlight, palette.color(QPalette::Dark));
	setPalette(palette);

	QHeaderView *vheader = verticalHeader();
	vheader->setVisible(false);

	QHeaderView *hheader = horizontalHeader();
	hheader->setSectionResizeMode(0, QHeaderView::Stretch);
	hheader->setVisible(false);
	connect(this, &SVSubNetworkEditDialogTable::itemSelectionChanged, this, &SVSubNetworkEditDialogTable::on_itemSelectionChanged);
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
	SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::NetworkComponent::iconFileFromModelType(component.m_modelType),
		QString::fromStdString(component.m_displayName.string("en")), VICUS::KeywordListQt::Description("NetworkComponent::ModelType", component.m_modelType),
		m_defaultRowHeight, this, true, component.m_builtIn);
	if (!component.m_local)
		bmItem1->setStyleSheet(QString("background-color: %1;").arg(SVStyle::instance().m_userDBBackgroundDark.name()));
	else if (component.m_builtIn)
		bmItem1->setStyleSheet(QString("background-color: %1;").arg(SVStyle::instance().m_alternativeBackgroundDark.name()));
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
	if(SVSettings::instance().m_theme == SVSettings::TT_Dark)
		setFixedHeight(6);
	else
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

	QSvgRenderer renderer(VICUS::NetworkComponent::iconFileFromModelType(type));
	QPixmap pixmap = QPixmap(m_defaultRowHeight * scaleX, m_defaultRowHeight * scaleX);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	renderer.render(&painter);
	painter.end();

	drag->setPixmap(pixmap);
	drag->setHotSpot(QPoint(m_defaultRowHeight * scaleX / 2, m_defaultRowHeight * scaleY / 2));
	drag->setMimeData(mimeData);
	drag->exec(supportedActions, Qt::CopyAction);
}

void SVSubNetworkEditDialogTable::focusOutEvent(QFocusEvent */*event*/)
{
	setCurrentCell(-1, -1);
}

void SVSubNetworkEditDialogTable::on_itemSelectionChanged()
{

	for(int i = 0; i < rowCount(); i++){
		SVSubNetworkEditDialogTableItem *item = dynamic_cast<SVSubNetworkEditDialogTableItem*>(cellWidget(i, 0));
		if(item->m_inbuild){
			item->setStyleSheet(QString("background-color: %1; ").arg(QtExt::Style::ToolBoxPageBackground));
		} else{
			item->setStyleSheet(QString("background-color: %1; ").arg(SVStyle::instance().m_userDBBackgroundDark.name()));
		}
	}
	QModelIndexList selected = selectedIndexes();
	for(auto index : selected){
		SVSubNetworkEditDialogTableItem *item = dynamic_cast<SVSubNetworkEditDialogTableItem*>(cellWidget(index.row(), 0));
		item->setStyleSheet(QString("background-color: %1; QToolTip { color: #000000; background-color: #ffffff; border: 1px solid black; }").arg(SVStyle::instance().m_alternativeBackgroundDark.name()));
	}
}
