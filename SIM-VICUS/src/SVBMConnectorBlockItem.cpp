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

void SVBMConnectorBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient grad(QPointF(0,0), QPointF(rect().width(),0));
    bool selected = (option->state & QStyle::State_Selected);
    if (selected) {
        painter->setPen(QPen(QBrush(QColor(0,128,0)), 1.5));
        grad.setColorAt(0, QColor(230,255,230));
        grad.setColorAt(1, QColor(200,240,180));
    }
    else {
        grad.setColorAt(0, QColor(196,196,255));
        grad.setColorAt(1, QColor(220,220,255));
    }
    painter->setBrush(grad);

    QPen p;

    if(!selected){
        p.setStyle(Qt::SolidLine);
        p.setColor(Qt::black);
    } else
    {
        p.setColor(QColor(192,0,0));
        p.setStyle(Qt::DashLine);
    }
    if(m_isHighlighted){
        p.setWidthF(1.6);
    }
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
