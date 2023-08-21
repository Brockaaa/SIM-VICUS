#include "SVSubNetworkEditDialogTable.h"
#include "ui_SVSubNetworkEditDialogTable.h"

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

#include "SVConstants.h"
#include "SVStyle.h"

SVSubNetworkEditDialogTable::SVSubNetworkEditDialogTable(QWidget *parent) :
    QTableWidget(parent),
    ui(new Ui::SVSubNetworkEditDialogTable)
{
    ui->setupUi(this);
    setFrameStyle(0);
    setShowGrid(false);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDefaultDropAction(Qt::CopyAction);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setColumnCount(1);

    BM_GraphicsView = (SVBMZoomMeshGraphicsView *)(dynamic_cast<SVSubNetworkEditDialog*>(parent)->zoomMeshGraphicsView());


    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, palette.color(QPalette::Base));
    setPalette(palette);

    QHeaderView *vheader = verticalHeader();
    vheader->setVisible(false);

    QHeaderView *hheader = horizontalHeader();
    hheader->setSectionResizeMode(0, QHeaderView::Stretch);
    hheader->setVisible(false);

    /*setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);*/

}

SVSubNetworkEditDialogTable::~SVSubNetworkEditDialogTable()
{
    delete ui;
}

void SVSubNetworkEditDialogTable::addElement(VICUS::NetworkComponent::ModelType type){
    SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::ModelTypeAttributes[type].fileName, VICUS::ModelTypeAttributes[type].typeName, VICUS::ModelTypeAttributes[type].toolTip, m_defaultRowHeight, this);
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
    SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::ModelTypeAttributes[component.m_modelType].fileName, QString::fromStdString(component.m_displayName.string("en")), VICUS::ModelTypeAttributes[component.m_modelType].toolTip, m_defaultRowHeight, this, true);
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
    if(selected.isEmpty()) return;

    int index = selected[0].row();

    QMimeData *mimeData = new QMimeData();
    mimeData->setText(m_elementList[index]);
    QDrag *drag = new QDrag(this);

    double scaleX = BM_GraphicsView->getScaleX();
    double scaleY = BM_GraphicsView->getScaleY();

    VICUS::NetworkComponent::ModelType type;

    if(m_elementList[index].startsWith("default:")){
        type = static_cast<VICUS::NetworkComponent::ModelType>(m_elementList[index].split(":")[1].toInt());
    }else if(m_elementList[index].startsWith("db:")){
        for(int i = index; i >= 0; i--){
            if(m_elementList[i].startsWith("default:")){
                type = static_cast<VICUS::NetworkComponent::ModelType>(m_elementList[i].split(":")[1].toInt());
                break;
            }
        }
    }

    QPixmap pixmap = QPixmap(VICUS::ModelTypeAttributes[type].fileName);
    drag->setPixmap(pixmap.scaled(m_defaultRowHeight * scaleX, m_defaultRowHeight * scaleY));
    drag->setHotSpot(QPoint(m_defaultRowHeight * scaleX / 2, m_defaultRowHeight * scaleY / 2));
    drag->setMimeData(mimeData);
    drag->exec(supportedActions, Qt::CopyAction);
}

void SVSubNetworkEditDialogTable::focusOutEvent(QFocusEvent */*event*/)
{
    setCurrentCell(-1, -1);
}


int SVSubNetworkEditDialogTable::rowSize() const
{
    return m_rowSize;
}
