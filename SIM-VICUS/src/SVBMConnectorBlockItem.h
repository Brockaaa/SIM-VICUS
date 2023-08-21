#ifndef SVBMCONNECTORBLOCKITEM_H
#define SVBMCONNECTORBLOCKITEM_H

#include "SVBMBlockItem.h"
namespace VICUS{
class BMBlock;
}

class SVBMConnectorBlockItem : public SVBMBlockItem
{
public:
    SVBMConnectorBlockItem(VICUS::BMBlock *b);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    SVBMSceneManager* m_sceneManager;

protected:
    /*! Re-implemented to highlight the entire connectorBlock + connectorlines when hovered. */
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override;
    /*! Re-implemented to turn off highlighting of the entire connectorBlock + connectorlines when hovered. */
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override;

private:

    bool m_isHighlighted = false;

};



#endif // SVBMCONNECTORBLOCKITEM_H
