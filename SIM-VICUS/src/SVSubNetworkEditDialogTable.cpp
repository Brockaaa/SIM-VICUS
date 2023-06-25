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
    setColumnCount(1);

    BM_GraphicsView = (SVBMZoomMeshGraphicsView *)(dynamic_cast<SVSubNetworkEditDialog*>(parent)->zoomMeshGraphicsView());


    QPalette palette = this->palette();
    palette.setColor(QPalette::Highlight, palette.color(QPalette::Base));
    setPalette(palette);

    QHeaderView *vheader = verticalHeader();
    vheader->setVisible(false);
    vheader->setDefaultSectionSize(m_defaultRowHeight);

    QHeaderView *hheader = horizontalHeader();
    hheader->setSectionResizeMode(0, QHeaderView::Stretch);
    hheader->setVisible(false);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

SVSubNetworkEditDialogTable::~SVSubNetworkEditDialogTable()
{
    delete ui;
}

void SVSubNetworkEditDialogTable::addElement(VICUS::NetworkComponent::ModelType type){

    qDebug() << VICUS::ModelTypeAttributes[type].fileName;
    SVSubNetworkEditDialogTableItem *bmItem1 = new SVSubNetworkEditDialogTableItem(VICUS::ModelTypeAttributes[type].fileName, VICUS::ModelTypeAttributes[type].typeName, VICUS::ModelTypeAttributes[type].toolTip, m_defaultRowHeight);
    setFixedHeight(height() + m_defaultRowHeight);
    insertRow(m_rowSize);
    setCellWidget(m_rowSize, 0, bmItem1);

    elementList.push_back(type);
    m_rowSize++;
}


void SVSubNetworkEditDialogTable::startDrag(Qt::DropActions supportedActions){

    QModelIndexList selected = selectedIndexes();
    if(selected.isEmpty()) return;

    int typeID = VICUS::ModelTypeAttributes[elementList[selected[0].row()]].uniqueID;
    VICUS::NetworkComponent::ModelType type = VICUS::ModelTypeLookup(typeID);


    QMimeData *mimeData = new QMimeData();
    mimeData->setText(QString::number(typeID));
    QDrag *drag = new QDrag(this);

    double scaleX = BM_GraphicsView->getScaleX();
    double scaleY = BM_GraphicsView->getScaleY();

    QPixmap pixmap = QPixmap(VICUS::ModelTypeAttributes[type].fileName);

    drag->setPixmap(pixmap.scaled(m_defaultRowHeight * scaleX, m_defaultRowHeight * scaleY));
    drag->setHotSpot(QPoint(m_defaultRowHeight * scaleX / 2, m_defaultRowHeight * scaleY / 2));

    drag->setMimeData(mimeData);

    drag->exec(supportedActions, Qt::CopyAction);
}


int SVSubNetworkEditDialogTable::rowSize() const
{
    return m_rowSize;
}
