#ifndef BM_CONNECTORBLOCKITEM_H
#define BM_CONNECTORBLOCKITEM_H

#include "BM_BlockItem.h"

namespace BLOCKMOD {

class ConnectorBlockItem : public BLOCKMOD::BlockItem
{
public:
    ConnectorBlockItem(Block *b);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool m_isHighlighted = false;

    SceneManager* m_sceneManager;

protected:
    /*! Re-implemented to highlight the entire connectorBlock + connectorlines when hovered. */
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;
    /*! Re-implemented to turn off highlighting of the entire connectorBlock + connectorlines when hovered. */
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override;

};



} // namespace BLOCKMOD

#endif // BM_CONNECTORBLOCKITEM_H
