#include "SVBMConnectorBlockItem.h"

#include "VICUS_BMBlock.h"
#include "SVBMSceneManager.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>

SVBMConnectorBlockItem::SVBMConnectorBlockItem(VICUS::BMBlock *b) : SVBMBlockItem(b)
{
    setAcceptHoverEvents(true);
    setRect(0,0,b->m_size.width(), b->m_size.height());
    setPos(b->m_pos);
}
void SVBMConnectorBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    bool selected = (option->state & QStyle::State_Selected);

    QPen p;

    if(selected) {
        painter->setPen(QPen(QBrush(QColor(0,128,0)), 1.5));
        p.setColor(QColor(192,0,0));
        p.setStyle(Qt::DashLine);
    }
    else {
        p.setStyle(Qt::SolidLine);
        p.setColor(Qt::black);
    }

    if(m_isHighlighted) {
        p.setWidthF(1.6);
    }

    // Set brush to solid black
    painter->setBrush(QColor(Qt::black));

    painter->setPen(p);
    painter->drawEllipse(rect());
    painter->restore();
}


void SVBMConnectorBlockItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event){
    QGraphicsItem::hoverEnterEvent(event);
    SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
    sceneManager->setHighlightallConnectorsOfBlock(block(), true);
    m_isHighlighted = true;
}

void SVBMConnectorBlockItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event){
    QGraphicsItem::hoverLeaveEvent(event);
    SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
    sceneManager->setHighlightallConnectorsOfBlock(block(), false);
    m_isHighlighted = false;
}

