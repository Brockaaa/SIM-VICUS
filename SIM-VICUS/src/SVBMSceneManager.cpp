/*	BSD 3-Clause License

    This file is part of the BlockMod Library.

    Copyright (c) 2019, Andreas Nicolai
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "SVBMSceneManager.h"

#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QDebug>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include <iostream>

#include "VICUS_BMNetwork.h"
#include "VICUS_BMSocket.h"
#include "SVBMConnectorSegmentItem.h"
#include "SVBMConnectorBlockItem.h"
#include "SVBMBlockItem.h"
#include "VICUS_BMGlobals.h"
#include "VICUS_BMConstants.h"
#include "SVBMZoomMeshGraphicsView.h"

SVBMSceneManager::SVBMSceneManager(QObject *parent) :
    QGraphicsScene(parent),
    m_network(new VICUS::BMNetwork)
{
    setupNetwork();
}


SVBMSceneManager::~SVBMSceneManager() {
    delete m_network;
}


void SVBMSceneManager::setNetwork(const VICUS::BMNetwork & network) {
    *m_network = network;

    qDeleteAll(m_blockItems);
    m_blockItems.clear();
    qDeleteAll(m_connectorSegmentItems);
    m_connectorSegmentItems.clear();
    m_connectorBlockItems.clear();
    m_nodeIdCounter = 0;

    // clear block connector map
    m_blockConnectorMap.clear();

    // create new graphics items
    for (VICUS::BMBlock  & b : m_network->m_blocks) {
        if(b.m_sockets[0].m_id > m_nodeIdCounter) m_nodeIdCounter = b.m_sockets[0].m_id;
        if(b.m_name.contains(CONNECTORBLOCK_NAME)){
            for(int i = 0; i < b.m_sockets.size() ; i++){
                b.m_sockets[i].m_connectorSocket = true;
            }
            SVBMConnectorBlockItem * item = new SVBMConnectorBlockItem(&b);

            addItem(item);
            m_blockItems.append(item);
            m_connectorBlockItems.append(item);

        }
        else{
            SVBMBlockItem * item = createBlockItem( b );
            addItem(item);
            m_blockItems.append(item);
        }
    }

    // create new graphics items for connectors
    for (VICUS::BMConnector & c : m_network->m_connectors) {
        QList<SVBMConnectorSegmentItem *> newConns = createConnectorItems(c);
        for( SVBMConnectorSegmentItem * item : qAsConst(newConns)) {
            addItem(item);
            m_connectorSegmentItems.append(item);
        }
    }

    // initially, we are not in connection mode
    m_currentlyConnecting = false;
}

void SVBMSceneManager::openNetwork(QString fname)
{
    VICUS::BMNetwork n;
    try {
        n.readXML(fname);
        n.checkNames();
        std::list<VICUS::BMConnector> checkedCons;
        // remove invalid connections and fix any connectors that might miss a bit
        for (VICUS::BMConnector & con : n.m_connectors) {
            try {
                n.adjustConnector(con);
                checkedCons.push_back(con);
            }
            catch (...) {}
        }
        n.m_connectors.swap(checkedCons);
        setNetwork(n); // network is copied
    } catch (std::runtime_error & e) {
        QString errormsg(e.what());
        qDebug() << errormsg;
    }
    m_blockCounter = 0;
    bool isInt;
    for(VICUS::BMBlock  block : m_network->m_blocks){
        block.m_name.toInt(&isInt);
        if(isInt) m_blockCounter++;
    }
    qDebug() << "Block Count: " << QString::number(m_blockCounter);
}


const VICUS::BMNetwork & SVBMSceneManager::network() const {
    return *m_network;
}


QPixmap SVBMSceneManager::generatePixmap(QSize targetSize) {
    // compute current scene rect
    QRectF r = itemsBoundingRect();

    double eps = 1.01;
    int borderSize = 10;
    int m;

    int w = targetSize.width();
    int h = targetSize.height();

    QRectF sourceRect;

    // the bigger of the scales determines the layout
    // if the scene rect is more wide than high, we use
    // x as scale, otherwise the height.
    if (r.width() > r.height()) {
        m = r.width();
        // also, we adjust the target height to the aspect ratio
        targetSize.setHeight( r.height()/r.width()*w + 2*borderSize);
        h = targetSize.height() + 2*borderSize;

        sourceRect = QRectF(r.center().x() - 0.5*m*eps,
                          r.center().y() - 0.5*r.height()*eps,
                          eps*m, eps*r.height());
    }
    else {
        m = r.height();
        sourceRect = QRectF(r.center().x() - 0.5*m*eps,
                              r.center().y() - 0.5*m*eps,
                              eps*m, eps*m);
    }

    // set the target rectangle within the thumbnail pixmap
    QRectF targetRect(borderSize, borderSize,
                      w-2*borderSize, h-2*borderSize);

    // Define source rectangle and enlarge source rect a little to include boundary lines which
    // would otherwise be clipped during pixel based rendering

    QPixmap pm(targetSize);
    pm.fill(Qt::white);

    QPainter painter(&pm);
    this->render(&painter, targetRect, sourceRect);

    return pm;
}


const SVBMBlockItem * SVBMSceneManager::blockItemByName(const QString & blockName) const {
    for (SVBMBlockItem* item : m_blockItems) {
        if (item->m_block->m_name == blockName)
            return item;
    }
    return nullptr;
}


void SVBMSceneManager::blockMoved(const VICUS::BMBlock * block, const QPointF /*oldPos*/) {
    // lookup connected connectors
    QSet<VICUS::BMConnector *> & cons = m_blockConnectorMap[block];
    // adjust connectors to new block positions
    for (VICUS::BMConnector * con : cons) {
        m_network->adjustConnector(*con);
        // update corresponding connectorItems (maybe remove/add items)
        updateConnectorSegmentItems(*con, nullptr);
    }

    // Mind the following problem:
    // - this function is called from within BlockItem::itemChange() event handler
    // - when you set a new network in the scene manager, for example in the slot connected
    //	to networkGeometryChanged(), this will delete all existing block items and create new ones
    // - when the execution returns from this function, it accesses now invalid memory --> boom!

    // Rule: never ever call setNetwork() when processing this signal!

    emit networkGeometryChanged(); /// \todo add old position to signal
}


void SVBMSceneManager::blockSelected(const VICUS::BMBlock * block) {
    emit newBlockSelected(block->m_name);
}


void SVBMSceneManager::connectorSegmentMoved(SVBMConnectorSegmentItem * currentItem) {
    // update corresponding connectorItems (maybe remove/add items)
    updateConnectorSegmentItems(*currentItem->m_connector, currentItem);
    emit networkGeometryChanged();
}


void SVBMSceneManager::highlightConnectorSegments(const VICUS::BMConnector & con, bool highlighted) {
    for (SVBMConnectorSegmentItem* segmentItem : qAsConst(m_connectorSegmentItems)) {
        if (segmentItem->m_connector == &con) {
            segmentItem->m_isHighlighted = highlighted;
            segmentItem->update();
        }
    }
    this->update();
}


void SVBMSceneManager::selectConnectorSegments(const VICUS::BMConnector & con) {
    qDebug() << "SceneManager::selectConnectorSegments";
    for (SVBMConnectorSegmentItem* segmentItem : qAsConst(m_connectorSegmentItems)) {
        if (segmentItem->m_connector == &con) {
            if (!segmentItem->isSelected())
                segmentItem->setSelected(true);
            segmentItem->update();
        }
    }
    this->update();
}


void SVBMSceneManager::mergeConnectorSegments(VICUS::BMConnector & con) {
    // collect an ordered list of segment items
    QList<SVBMConnectorSegmentItem*> segmentItems;
    for (int i=0; i<con.m_segments.count(); ++i)
        segmentItems.append(nullptr);
    for (SVBMConnectorSegmentItem* segmentItem : qAsConst(m_connectorSegmentItems)) {
        if (segmentItem->m_connector == &con) {
            if (segmentItem->m_segmentIdx == -1 || segmentItem->m_segmentIdx == -2)
                continue;
            Q_ASSERT(segmentItem->m_segmentIdx < segmentItems.count());
            segmentItems[segmentItem->m_segmentIdx] = segmentItem;
        }
    }
    // now look for segments with near zero distance
    int i = 0;
    bool updateSegments = false;
    while (i<segmentItems.count()) {

        for (i=0; i<segmentItems.count(); ++i) {
            SVBMConnectorSegmentItem * segItem = segmentItems[i];
            Q_ASSERT(i == segItem->m_segmentIdx);
            VICUS::BMConnector::Segment & seg = con.m_segments[i];

            // if segment has the same orientation as the previous segment, we merge it such that the previous segment gets modified
            // and the current segment gets offset of zero
            if (i>0 && con.m_segments[i-1].m_direction == seg.m_direction) {
                con.m_segments[i-1].m_offset += seg.m_offset;
                seg.m_offset = 0;
                updateSegments = true;
            }

            if (VICUS::BMGlobals::nearZero(seg.m_offset)) {
                break;
            }
        }

        if (i == segmentItems.count())
            break; // none found, we are done

        // if i < segmentItems.count() we have found a zero length segment
        // if this is the first or last segment, we can simply remove it
        if (i == 0) {
            con.m_segments.removeFirst();
            SVBMConnectorSegmentItem * segItem = segmentItems.front();
            segmentItems.removeFirst();
            m_connectorSegmentItems.removeOne(segItem);
            delete segItem;
            // update segment indexes of remaining segments
            for (int j=0; j<segmentItems.count(); ++j)
                --segmentItems[j]->m_segmentIdx;
        }
        else if (i == segmentItems.count()-1) {
            con.m_segments.removeLast();
            SVBMConnectorSegmentItem * segItem = segmentItems.back();
            segmentItems.removeLast();
            m_connectorSegmentItems.removeOne(segItem);
            delete segItem;
            i = 0; // signal to try again
        }
        else {
            // segment is somewhere in the middle

            // remove the segment in question
            con.m_segments.removeAt(i);
            SVBMConnectorSegmentItem * segItem = segmentItems[i];
            segmentItems.removeAt(i);
            m_connectorSegmentItems.removeOne(segItem);
            delete segItem;
            // update segment indexes of remaining segments
            for (int j=i; j<segmentItems.count(); ++j)
                --segmentItems[j]->m_segmentIdx;

            // check if new neighbors have same orientation
            VICUS::BMConnector::Segment & previousSeg = con.m_segments[i-1];
            VICUS::BMConnector::Segment & nextSeg = con.m_segments[i];
            if (previousSeg.m_direction == nextSeg.m_direction) {
                // extend the previous segment
                previousSeg.m_offset += nextSeg.m_offset;
                // remove the next
                con.m_segments.removeAt(i);
                SVBMConnectorSegmentItem * segItem = segmentItems[i];
                segmentItems.removeAt(i);
                m_connectorSegmentItems.removeOne(segItem);
                delete segItem;
                // update segment indexes of remaining segments
                for (int j=i; j<segmentItems.count(); ++j)
                    --segmentItems[j]->m_segmentIdx;
                // update segments
                // remember to update the segment coordinates afterwards
                updateSegments = true;
            }

            i = 0; // signal to try again
        }
    }
    if (updateSegments)
        updateConnectorSegmentItems(con, nullptr);
    QApplication::restoreOverrideCursor();
}


bool SVBMSceneManager::isConnectedSocket(const VICUS::BMBlock * b, const VICUS::BMSocket * s) const {
    QMap<const VICUS::BMBlock*, QSet< VICUS::BMConnector*> >::const_iterator it = m_blockConnectorMap.find(b);
    if (it == m_blockConnectorMap.end())
        return false;
    // process all connectors and check, if they connect to the given socket
    for (const VICUS::BMConnector * c : it.value() ) {
        const VICUS::BMSocket * socket;
        const VICUS::BMBlock * block;
        m_network->lookupBlockAndSocket(c->m_sourceSocket, block, socket);
        if (s == socket)
            return true;
        m_network->lookupBlockAndSocket(c->m_targetSocket, block, socket);
        if (s == socket)
            return true;
    }
    return false;
}


void SVBMSceneManager::startSocketConnection(const SVBMSocketItem & outletSocketItem, const QPointF & mousePos) {
    Q_ASSERT(!outletSocketItem.socket()->m_inlet);

    m_connectingSocket = outletSocketItem.socket();
    // deselect all blocks and connectors
    for (SVBMBlockItem * block : qAsConst(m_blockItems))
        block->setSelected(false);
    for (SVBMConnectorSegmentItem * segmentItem : qAsConst(m_connectorSegmentItems))
        segmentItem->setSelected(false);

    // determine block that this outlet socket item belongs to
    SVBMBlockItem * bitem = dynamic_cast<SVBMBlockItem *>(outletSocketItem.parentItem());
    Q_ASSERT(bitem != nullptr);
    const VICUS::BMBlock * sourceBlock = bitem->block();
    const VICUS::BMSocket * sourceSocket = outletSocketItem.socket();
    // compose connector start name
    QString startSocketName = sourceBlock->m_name + "." + sourceSocket->m_name;

    // create a dummy block
    VICUS::BMBlock dummyBlock;
    dummyBlock.m_pos = mousePos;
    dummyBlock.m_size = QSizeF(20,20);
    dummyBlock.m_name = VICUS::BMGlobals::InvisibleLabel; // "Mich gibt's gar nicht";
    dummyBlock.m_connectionHelperBlock = true;
    VICUS::BMSocket dummySocket;
    dummySocket.m_name = VICUS::BMGlobals::InvisibleLabel; // "Mich gibt's auch nicht";
    dummySocket.m_inlet = true;
    dummySocket.m_orientation = Qt::Horizontal;
    dummySocket.m_pos = QPointF(0,0);
    dummyBlock.m_sockets.append(dummySocket);

    m_network->m_blocks.push_back(dummyBlock); // does not invalidate block pointers!

    QString targetSocketName = dummyBlock.m_name + "." + dummySocket.m_name;

    // create and add the connector
    VICUS::BMConnector con;
    con.m_name = VICUS::BMGlobals::InvisibleLabel; // "Mich gibt's erst recht nicht";
    con.m_sourceSocket = startSocketName;
    con.m_targetSocket = targetSocketName;
    m_network->m_connectors.push_back(con);

    // now create block item and connector items
    SVBMBlockItem * bi = createBlockItem(m_network->m_blocks.back()); // Mind: always pass the object in the m_block list
    bi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    bi->setPos(dummyBlock.m_pos);
    m_blockItems.append(bi);

    bi->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    bi->setPos(dummyBlock.m_pos);

    addItem(bi);

    QList<SVBMConnectorSegmentItem*> newConns = createConnectorItems(m_network->m_connectors.back());  // Mind: always pass the object in the m_connectors list
    for( SVBMConnectorSegmentItem * item : qAsConst(newConns)) {
        addItem(item);
        m_connectorSegmentItems.append(item);
    }

    m_currentlyConnecting = true;
}


void SVBMSceneManager::finishConnection() {

    // remove our artifical block and block item, if it exists
    if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
        removeBlock(m_network->m_blocks.size()-1);

    m_connectingSocket = nullptr;
    m_currentlyConnecting = false;
}


QList<const VICUS::BMBlock*> SVBMSceneManager::selectedBlocks() const {
    QList<QGraphicsItem*> selected = selectedItems();
    QList<const VICUS::BMBlock *> selectedBlocks;
    for (QGraphicsItem * item : qAsConst(selected)) {
        SVBMBlockItem * bi = dynamic_cast<SVBMBlockItem *>(item);
        if (bi != nullptr)
            selectedBlocks.append(bi->block());
    }
    return selectedBlocks;
}


const VICUS::BMConnector * SVBMSceneManager::selectedConnector() const {
    QList<QGraphicsItem*> selected = selectedItems();
    // find selected connector
    for (QGraphicsItem * item : qAsConst(selected)) {
        SVBMConnectorSegmentItem * segi = dynamic_cast<SVBMConnectorSegmentItem *>(item);
        if (segi != nullptr) {
            return segi->m_connector;
        }
    }
    return nullptr;
}


void SVBMSceneManager::addBlock(const VICUS::BMBlock & block) {
    m_network->m_blocks.push_back(block);
    SVBMBlockItem * item = createBlockItem( m_network->m_blocks.back() );
    addItem(item);
    m_blockItems.append(item);
    m_blockCounter++;
}

void SVBMSceneManager::addBlock(VICUS::NetworkComponent::ModelType type, QPoint point)
{
    VICUS::BMBlock b;

    VICUS::BMSocket s1;
    s1.m_inlet = true;
    s1.m_orientation = Qt::Horizontal;
    s1.m_pos = QPointF(0, BLOCK_HEIGHT / 2);
    s1.m_name = "inlet";

    VICUS::BMSocket s2;
    s2.m_inlet = false;
    s2.m_orientation = Qt::Horizontal;
    s2.m_pos = QPointF(BLOCK_WIDTH, BLOCK_HEIGHT / 2);
    s2.m_name = "outlet";

    SVBMZoomMeshGraphicsView *view = qobject_cast<SVBMZoomMeshGraphicsView *>(parent());
    QPointF pos = view->mapToScene(point - QPoint(BLOCK_WIDTH * view->getScaleX() / 2, BLOCK_HEIGHT * view->getScaleY() / 2));
    b.m_size = QSizeF(BLOCK_WIDTH, BLOCK_HEIGHT);
    b.m_pos = pos;
    b.m_elementID = VICUS::ModelTypeAttributes[type].uniqueID;
    b.m_name = QString::number(m_blockCounter);
    b.m_sockets.append(s1);
    b.m_sockets.append(s2);
    b.m_properties["ShowPixmap"] = true;
    b.m_properties["Pixmap"] = QPixmap(VICUS::ModelTypeAttributes[type].fileName).scaled(256,256);
    b.m_displayName = VICUS::ModelTypeAttributes[type].typeName;

    addBlock(b);
}

void SVBMSceneManager::addConnectorBlock(const VICUS::BMBlock & block){
    m_network->m_blocks.push_back(block);
    SVBMConnectorBlockItem * item = new SVBMConnectorBlockItem(&(m_network->m_blocks.back()));
    addItem(item);
    m_blockItems.append(item);
    m_connectorBlockItems.append(item);
}

void SVBMSceneManager::addConnectorBlock(SVBMConnectorBlockItem blockItem){
    m_network->m_blocks.push_back(*(blockItem.block()));
    addItem(&blockItem);
    m_blockItems.append(&blockItem);
}

void SVBMSceneManager::addConnector(const VICUS::BMConnector & con) {
    // first check, that indeed the source/target connectors are valid
    const VICUS::BMBlock * b1, * b2;
    const VICUS::BMSocket * s1, * s2;
    qDebug() << "addConnector" << con.m_name << con.m_sourceSocket << con.m_targetSocket;
    try {
        m_network->lookupBlockAndSocket(con.m_sourceSocket, b1, s1);
    } catch (...) {
        throw std::runtime_error("[SceneManager::addConnector] Invalid source socket identifyer.");
    }
    try {
        m_network->lookupBlockAndSocket(con.m_targetSocket, b2, s2);
    } catch (...) {
        throw std::runtime_error("[SceneManager::addConnector] Invalid target socket identifyer.");
    }
    if (s1->m_inlet)
        throw std::runtime_error("[SceneManager::addConnector] Invalid source socket (must be an outlet socket).");
    if (!s2->m_inlet)
        throw std::runtime_error("[SceneManager::addConnector] Invalid target socket (must be an inlet socket).");
    // check, if inlet socket is already connected to
    if (isConnectedSocket(b2, s2)) qDebug() << "already connected";
        /* throw std::runtime_error("[SceneManager::addConnector] Invalid target socket (has already an incoming connection)."); */
    m_network->m_connectors.push_back(con);
    m_network->adjustConnector(m_network->m_connectors.back());
}


void SVBMSceneManager::removeBlock(const VICUS::BMBlock * block) {
    size_t idx = 0;
    for (auto bit = m_network->m_blocks.begin(); bit != m_network->m_blocks.end(); ++bit, ++idx)
        if (block == &(*bit))
            break;
    if (idx == m_network->m_blocks.size())
        throw std::runtime_error("[SceneManager::removeBlock] Invalid pointer (not in managed network)");
    removeBlock(idx);
}


void SVBMSceneManager::removeBlock(unsigned int blockIndex) {
    Q_ASSERT(m_network->m_blocks.size() > blockIndex);
    Q_ASSERT(m_blockItems.count() > (int)blockIndex);

    auto bit = m_network->m_blocks.begin(); std::advance(bit, blockIndex);
    const VICUS::BMBlock * blockToBeRemoved = &(*bit);
    if(blockToBeRemoved->m_name.contains(CONNECTORBLOCK_NAME)){
        removeConnectorBlock(blockToBeRemoved);
        return;
    }
    if(blockToBeRemoved->m_name == ENTRANCE_NAME || blockToBeRemoved->m_name == EXIT_NAME) return;

    SVBMBlockItem * bi = m_blockItems[(int)blockIndex];

    // find connectors that connect to this block
    QSet<VICUS::BMConnector*> connectors = m_blockConnectorMap[blockToBeRemoved];
    // save all ConnectorBlocks that should be deleted
    QSet<const VICUS::BMBlock*> connectorBlocksToBeDeleted;
    for (VICUS::BMConnector * con : connectors) {
        // find connector to be removed from list
        for (auto cit = m_network->m_connectors.begin(); cit != m_network->m_connectors.end(); ++cit) {
            if (&(*cit) == con) {
                VICUS::BMSocket* sourceSocket = nullptr;
                VICUS::BMBlock* sourceBlock = nullptr;
                VICUS::BMSocket* targetSocket = nullptr;
                VICUS::BMBlock* targetBlock = nullptr;

                m_network->lookupBlockAndSocket(cit->m_targetSocket,  const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));
                m_network->lookupBlockAndSocket(cit->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));

                if(m_blockConnectorMap[targetBlock].count() == 1 && targetBlock->m_name != EXIT_NAME) {
                    targetSocket->m_id = -1;
                }
                if(targetBlock->m_name.contains(CONNECTORBLOCK_NAME) && sourceBlock->m_name != VICUS::BMGlobals::InvisibleLabel && targetBlock != blockToBeRemoved){
                    if(m_blockConnectorMap[targetBlock].count() <= 2){
                        connectorBlocksToBeDeleted.insert(targetBlock);
                        m_network->m_connectors.erase(cit);
                        break;
                    }
                }

                //check if the block on the other side is connected with another block. If not, reset m_id
                if(m_blockConnectorMap[sourceBlock].count() == 1 && sourceBlock->m_name != ENTRANCE_NAME) {
                    sourceSocket->m_id = -1;
                }
                if(sourceBlock->m_name.contains(CONNECTORBLOCK_NAME) && targetBlock->m_name != VICUS::BMGlobals::InvisibleLabel && sourceBlock != blockToBeRemoved){
                    if(m_blockConnectorMap[sourceBlock].count() <= 2){
                        connectorBlocksToBeDeleted.insert(sourceBlock);
                        m_network->m_connectors.erase(cit);
                        break;
                    }
                }

                m_network->m_connectors.erase(cit);
                break;
            }
        }
    }

    // now remove the block itself
    m_blockItems.removeOne(bi);
    delete bi;

    // finally remove block itself from list
    m_network->m_blocks.erase(bit);

    // and update all connector items; first remove all, then recreate as needed
    qDeleteAll(m_connectorSegmentItems); // will be recreated
    m_connectorSegmentItems.clear();
    m_blockConnectorMap.clear(); // will be recreated
    for (VICUS::BMConnector & con : m_network->m_connectors) {
        updateConnectorSegmentItems(con, nullptr);
    }
    for(const VICUS::BMBlock* block : connectorBlocksToBeDeleted){
        removeConnectorBlock(block);
    }
}

void SVBMSceneManager::removeSelectedBlocks()
{
    QList<const VICUS::BMBlock *> qlist = selectedBlocks();

    for(const VICUS::BMBlock * tmpBlock : qlist){
        removeBlock(tmpBlock);
    }
}

void SVBMSceneManager::removeConnectorBlock(const VICUS::BMBlock * block){

    size_t blockIndex = 0;
    for (auto bit = m_network->m_blocks.begin(); bit != m_network->m_blocks.end(); ++bit, ++blockIndex)
        if (block == &(*bit))
            break;
    if (blockIndex == m_network->m_blocks.size())
        throw std::runtime_error("[SceneManager::removeBlock] Invalid pointer (not in managed network)");

    Q_ASSERT(m_network->m_blocks.size() > blockIndex);
    //Q_ASSERT(m_blockItems.count() > (int)blockIndex);

    auto bit = m_network->m_blocks.begin(); std::advance(bit, blockIndex);
    VICUS::BMBlock * blockToBeRemoved = &(*bit);
    qDebug() << "start removeConnectorBlock: " << block->m_name;
    // find connectors that connect to this block
    QSet< VICUS::BMConnector*> connectors = m_blockConnectorMap[blockToBeRemoved];
    std::vector<QString> removedConnectors;
    for (VICUS::BMConnector * con : connectors) {
        // find connector to be removed from list
        for (auto cit = m_network->m_connectors.begin(); cit != m_network->m_connectors.end(); ++cit) {
            if (&(*cit) == con) {
                /*qDebug() << "Con: source: "<< con->m_sourceSocket << " - target: " << con->m_targetSocket;
                if(!con->m_sourceSocket.contains("connector")) removedConnectors.insert(con->m_sourceSocket);
                if(!con->m_targetSocket.contains("connector")) removedConnectors.insert(con->m_sourceSocket);*/

                VICUS::BMSocket* sourceSocket = nullptr;
                VICUS::BMBlock* sourceBlock = nullptr;
                VICUS::BMSocket* targetSocket = nullptr;
                VICUS::BMBlock* targetBlock = nullptr;

                //check if the block on the other side is connected with another block. If not, reset m_id

                m_network->lookupBlockAndSocket(cit->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));
                if(sourceBlock && sourceSocket != nullptr && sourceBlock->m_name != ENTRANCE_NAME){
                        sourceSocket->m_id = -1;
                }

                m_network->lookupBlockAndSocket(cit->m_targetSocket,  const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));
                if(targetBlock && targetSocket != nullptr && targetBlock->m_name != "Exit"){
                        targetSocket->m_id = -1;
                }


                m_network->m_connectors.erase(cit);
                break;
            }
        }
    }

    // now remove the block itself
    SVBMBlockItem * bi = m_blockItems[(int)blockIndex];
    m_blockItems.removeAt((int)blockIndex);
    delete bi;
    m_connectorBlockItems.erase(
        std::remove_if(m_connectorBlockItems.begin(), m_connectorBlockItems.end(),
                       [&](SVBMConnectorBlockItem* cbi) { return cbi->m_block == &(*bit); }),
        m_connectorBlockItems.end()
        );
    // finally remove block itself from list
    m_network->m_blocks.erase(bit);

    // and update all connector items; first remove all, then recreate as needed
    qDeleteAll(m_connectorSegmentItems); // will be recreated
    m_connectorSegmentItems.clear();
    m_blockConnectorMap.clear(); // will be recreated
    for (VICUS::BMConnector & con : m_network->m_connectors) {
        updateConnectorSegmentItems(con, nullptr);
    }
}

void SVBMSceneManager::setHighlightallConnectorsOfBlock(const VICUS::BMBlock *block, bool highlighted)
{
    for (VICUS::BMConnector & con : m_network->m_connectors) {
        if(con.m_sourceSocket.contains(block->m_name) || con.m_targetSocket.contains(block->m_name)){
            for (auto cit = m_connectorSegmentItems.begin(); cit != m_connectorSegmentItems.end(); ++cit) {
                if ((*cit)->m_connector == &con) {
                    (*cit)->m_isHighlighted = highlighted;
                }
            }
        }
    }
}

void SVBMSceneManager::removeConnector(const VICUS::BMConnector * con) {
    size_t idx = 0;
    for (auto cit = m_network->m_connectors.begin(); cit != m_network->m_connectors.end(); ++cit, ++idx)
        if (con == &(*cit))
            break;
    if (idx == m_network->m_connectors.size())
        return;
    removeConnector(idx);
}


void SVBMSceneManager::removeConnector(unsigned int connectorIndex) {
    Q_ASSERT(m_network->m_connectors.size() > connectorIndex);

    auto cit = m_network->m_connectors.begin(); std::advance(cit, connectorIndex);
    VICUS::BMConnector * conToBeRemoved = &(*cit);
    VICUS::BMSocket* sourceSocket = nullptr;
    VICUS::BMBlock* sourceBlock = nullptr;
    VICUS::BMSocket* targetSocket = nullptr;
    VICUS::BMBlock* targetBlock = nullptr;
    m_network->lookupBlockAndSocket(conToBeRemoved->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));
    m_network->lookupBlockAndSocket(conToBeRemoved->m_targetSocket, const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));

    if(m_blockConnectorMap[sourceBlock].count() <= 1) {
        sourceSocket->m_id = -1;
    }
    if(m_blockConnectorMap[targetBlock].count() <= 1) {
        targetSocket->m_id = -1;
    }

    // find corresponding connector items

    int i=0;
    while (i<m_connectorSegmentItems.count()) {
        if (m_connectorSegmentItems[i]->m_connector == conToBeRemoved) {
            delete m_connectorSegmentItems[i];
            m_connectorSegmentItems.removeAt(i);
            continue;
        }
        ++i;
    }

    // remove connector associations in block-connector-map
    for (QMap<const VICUS::BMBlock*, QSet< VICUS::BMConnector*> >::iterator it = m_blockConnectorMap.begin(); it != m_blockConnectorMap.end(); ++it) {
        QSet< VICUS::BMConnector*> & conList = it.value();
        conList.remove(conToBeRemoved);
    }

    // finally remove connector at given index
    m_network->m_connectors.erase(cit);

    QSet< VICUS::BMConnector*> *connectorList = &m_blockConnectorMap[sourceBlock];
    for(VICUS::BMConnector *tmpConn : *connectorList){
        if(tmpConn->m_sourceSocket.contains(sourceSocket->m_name)) qDebug() << "fucking hit!";
    }

}


// ** protected functions **


void SVBMSceneManager::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//	if (mouseEvent->button() == Qt::RightButton) {
//		disableConnectionMode();
//	}
    // in case of click on socket while in connection mode, the next call will
    // result in a call to startSocketConnection(), which creates a new block and connection
    // we need to detect this and fire a mouse event again afterwards, which will cause
    // the newly created block to go into drag-move mode
    bool alreadyInConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_name == VICUS::BMGlobals::InvisibleLabel);
    QGraphicsScene::mousePressEvent(mouseEvent);
    bool inConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_name == VICUS::BMGlobals::InvisibleLabel);
    if (!alreadyInConnectionProcess && inConnectionProcess) {
        // make the last item the mouse grabber objects
        m_blockItems.back()->grabMouse();
    }
}


void SVBMSceneManager::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    // check if in connection mode and if connection-block position is over an inlet socket that
    // is not yet connected - if so, mark the socket as "hovered" and update it

    if (m_currentlyConnecting) {
        if (!m_blockItems.isEmpty() && m_blockItems.back()->block()->m_name == VICUS::BMGlobals::InvisibleLabel) {
            QPointF p = m_blockItems.back()->pos();
            for (SVBMBlockItem  * bi : qAsConst(m_blockItems)) {
                if (bi->block()->m_name == VICUS::BMGlobals::InvisibleLabel)
                    continue;
                // first un-hover all sockets
                for (SVBMSocketItem * si : qAsConst(bi->m_socketItems)) {
                    si->m_hovered = false;
                    si->update();
                }

                // now search for sockets that may be hovered
                SVBMSocketItem * si = bi->inletSocketAcceptingConnection(p);
                if (si != nullptr) {
                        si->m_hovered = true;
                        si->update();
                }
            }
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}


void SVBMSceneManager::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    if (mouseEvent->button() & Qt::LeftButton) {
        QString startSocket;
        QString targetSocket;

        // check if we have dropped onto a connectable socket
        if (m_currentlyConnecting) {
            if (!m_blockItems.isEmpty() && m_blockItems.back()->block()->m_name == VICUS::BMGlobals::InvisibleLabel) {
                QPointF p = m_blockItems.back()->pos();
                bool connectionFound = false;
                for (SVBMBlockItem  * bi : qAsConst(m_blockItems)) {
                    if (bi->block()->m_name == VICUS::BMGlobals::InvisibleLabel)
                        continue;

                    // now search for sockets that may be hovered
                    SVBMSocketItem * si = bi->inletSocketAcceptingConnection(p);
                    if (si != nullptr) {
                        connectionFound = true;
                        // found one - remember this socket and the starting socket for our connection
                        startSocket = m_network->m_connectors.back().m_sourceSocket;
                        targetSocket = bi->block()->m_name + "." + si->socket()->m_name;
                        VICUS::BMBlock* startBlock = nullptr;
                        VICUS::BMBlock* targetBlock = nullptr;
                        VICUS::BMSocket* startSocketP = nullptr;
                        VICUS::BMSocket* targetSocketP = nullptr;
                        m_network->lookupBlockAndSocket(startSocket, const_cast<const VICUS::BMBlock *&>(startBlock), const_cast<const VICUS::BMSocket*&>(startSocketP));
                        m_network->lookupBlockAndSocket(targetSocket,const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocketP));
                        qDebug() << "String startSocket: " << startSocket;
                        qDebug() << "String targetSocket: " << targetSocket;
                        qDebug() << "Name start Block: " << startBlock->m_name << " Socket: " << startSocketP->m_name;
                        qDebug() << "Name target Block: " << targetBlock->m_name << " Socket: " << targetSocketP->m_name;

                        // if sourceBlock not connected and targetBlock is connected
                        if(m_connectingSocket->m_id == -1 && si->socket()->m_id != -1){
                            if(targetBlock->m_name == EXIT_NAME){
                                qDebug() << "Exit found";
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);
                                SVBMConnectorBlockItem* conn = nullptr;
                                for(SVBMConnectorBlockItem* connSoc : m_connectorBlockItems){
                                    if(connSoc->block()->m_name == CONNECTORBLOCK_NAME + QString::number(EXIT_ID)){
                                        conn = connSoc;
                                        qDebug() << "Found: " << connSoc->block()->m_name;
                                    }
                                }
                                if(conn == nullptr){
                                    addConnectorBlockAndSocket(startBlock, targetBlock, startSocketP, targetSocketP, EXIT_ID);
                                } else {
                                    VICUS::BMConnector con;
                                    con.m_name = "con";
                                    con.m_sourceSocket = startSocket;
                                    con.m_targetSocket = CONNECTORBLOCK_NAME + QString::number(EXIT_ID) + "." + INLET_NAME;
                                    m_network->m_connectors.push_back(con);
                                    m_network->adjustConnector(m_network->m_connectors.back());
                                    updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
                                }
                            }
                             // if targetBlock is a ConnectorBlock
                            else if(targetBlock->m_name.contains("connector")){
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);
                                VICUS::BMConnector con;
                                con.m_name = "con";
                                con.m_sourceSocket = startSocket;
                                con.m_targetSocket = targetSocket;
                                m_network->m_connectors.push_back(con);
                                m_network->adjustConnector(m_network->m_connectors.back());
                                updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);

                            // if targetBlock is not a ConnectorBlock, find the appropriate connectorBlock and connect sourceBlock with the connectorBlock
                            } else {
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);
                                QString blockname = "connector" + QString::number(si->socket()->m_id);
                                for(const SVBMConnectorBlockItem* tmpBlock : m_connectorBlockItems){
                                    if(tmpBlock->block()->m_name == blockname){
                                        targetSocket = tmpBlock->block()->m_name + "." + tmpBlock->block()->m_sockets[0].m_name;
                                        break;
                                    }
                                }
                                VICUS::BMConnector con;
                                con.m_name = "con";
                                con.m_sourceSocket = startSocket;
                                con.m_targetSocket = targetSocket;
                                m_network->m_connectors.push_back(con);
                                m_network->adjustConnector(m_network->m_connectors.back());
                                updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
                            }
                            startSocketP->m_id = targetSocketP->m_id;
                        }

                        // if sourceBlock is connected and targetBlock is not connected
                        else if(m_connectingSocket->m_id != -1 && si->socket()->m_id == -1){
                            if(startBlock->m_name == ENTRANCE_NAME){
                                qDebug() << "Entrance found";
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);
                                SVBMConnectorBlockItem* conn = nullptr;
                                for(SVBMConnectorBlockItem* connSoc : m_connectorBlockItems){
                                    if(connSoc->block()->m_name == "connector" + QString::number(ENTRANCE_ID)){
                                        conn = connSoc;
                                        qDebug() << "Found: " << connSoc->block()->m_name;
                                    }
                                }
                                if(conn == nullptr){
                                    addConnectorBlockAndSocket(startBlock, targetBlock, startSocketP, targetSocketP, ENTRANCE_ID);

                                } else {
                                    VICUS::BMConnector con;
                                    con.m_name = CONNECTOR_NAME;
                                    con.m_sourceSocket = "connector" + QString::number(ENTRANCE_ID) + "." + OUTLET_NAME;
                                    con.m_targetSocket = targetSocket;
                                    m_network->m_connectors.push_back(con);
                                    m_network->adjustConnector(m_network->m_connectors.back());
                                    updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
                                }
                            }
                            else if(startBlock->m_name.contains("connector")){
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);

                                VICUS::BMConnector con;
                                con.m_name = CONNECTOR_NAME;
                                con.m_sourceSocket = startSocket;
                                con.m_targetSocket = targetSocket;
                                m_network->m_connectors.push_back(con);
                                m_network->adjustConnector(m_network->m_connectors.back());
                                updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
                            } else {
                                if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                    removeBlock(m_network->m_blocks.size() - 1);
                                QString blockname = "connector" + QString::number(m_connectingSocket->m_id);
                                for(const SVBMConnectorBlockItem* tmpBlock : m_connectorBlockItems){
                                    if(tmpBlock->block()->m_name == blockname){
                                        startSocket = tmpBlock->block()->m_name + "." + tmpBlock->block()->m_sockets[1].m_name;
                                        break;
                                    }
                                }
                                VICUS::BMConnector con;
                                con.m_name = CONNECTOR_NAME;
                                con.m_sourceSocket = startSocket;
                                con.m_targetSocket = targetSocket;
                                m_network->m_connectors.push_back(con);
                                m_network->adjustConnector(m_network->m_connectors.back());
                                updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
                            }
                            si->socket()->m_id = m_connectingSocket->m_id;
                        }

                        else if (m_connectingSocket->m_id != -1 && si->socket()->m_id != -1){
                            if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                removeBlock(m_network->m_blocks.size() - 1);
                            m_connectingSocket = nullptr;
                            m_currentlyConnecting = false;
                            QApplication::restoreOverrideCursor();
                            return;
                        }

                        // if no connectorBlock
                        else {
                            //remove artificial Block and block item
                            if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                                removeBlock(m_network->m_blocks.size() - 1);

                            addConnectorBlockAndSocket(startBlock, targetBlock, startSocketP, targetSocketP, m_nodeIdCounter);
                            m_nodeIdCounter++;
                        }
                        emit newConnectionAdded();
                        break;
                    }
                }
                if(!connectionFound){
                    if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_name  == VICUS::BMGlobals::InvisibleLabel)
                        removeBlock(m_network->m_blocks.size() - 1);
                }
            }
            m_connectingSocket = nullptr;
            m_currentlyConnecting = false;
            QApplication::restoreOverrideCursor();
        }
        // check if any block or connector has been selected
        else{
            bool blockOrConnectorSelected = false;
            for (const SVBMBlockItem *item: qAsConst(m_blockItems)) {
                if (item->isSelected()) {
                    blockOrConnectorSelected = true;
                    break;
                }
            }
            for (const SVBMConnectorSegmentItem *item: qAsConst(m_connectorSegmentItems)) {
                if (item->isSelected()) {
                    blockOrConnectorSelected = true;
                    break;
                }
            }
            if (!blockOrConnectorSelected)
                emit selectionCleared();
        }
    }
}


SVBMBlockItem * SVBMSceneManager::createBlockItem(VICUS::BMBlock  & b) {
    SVBMBlockItem * item = new SVBMBlockItem(&b);
    item->setRect(0,0,b.m_size.width(), b.m_size.height());
    item->setPos(b.m_pos);
    return item;
}


SVBMConnectorSegmentItem * SVBMSceneManager::createConnectorItem(VICUS::BMConnector & con) {
    SVBMConnectorSegmentItem * item = new SVBMConnectorSegmentItem(&con);
    return item;
}


QList<SVBMConnectorSegmentItem *> SVBMSceneManager::createConnectorItems(VICUS::BMConnector & con) {
    QList<SVBMConnectorSegmentItem *> newConns;
    // we need to create two segment items for the start and end line segments, and give
    // them the properties to be painted appropriately

    try {
        const VICUS::BMSocket * socket;
        const VICUS::BMBlock * block;
        m_network->lookupBlockAndSocket(con.m_sourceSocket, block, socket);
        m_blockConnectorMap[block].insert(&con); // remember association
        // get start line coordinates: first point is the socket's center, second point is the connection point outside the socket
        QLineF startLine = block->socketStartLine(socket);
        // get end line coordinates: first point is the socket's center, second point is the connection point outside the socket
        m_network->lookupBlockAndSocket(con.m_targetSocket, block, socket);
        m_blockConnectorMap[block].insert(&con); // remember association
        QLineF endLine = block->socketStartLine(socket);

        SVBMConnectorSegmentItem * item = createConnectorItem(con);
        item->setLine(startLine);
        item->setFlags(QGraphicsItem::ItemIsSelectable);
        item->m_segmentIdx = -1; // start line
        newConns.append(item);

        item = createConnectorItem(con);
        item->setLine(endLine);
        item->setFlags(QGraphicsItem::ItemIsSelectable);
        item->m_segmentIdx = -2; // end line
        newConns.append(item);

        QPointF start = startLine.p2();
        for (int i=0; i<con.m_segments.count(); ++i) {
            const VICUS::BMConnector::Segment & seg = con.m_segments[i];
            item = createConnectorItem(con);
            QPointF next(start);
            if (seg.m_direction == Qt::Horizontal)
                next += QPointF(seg.m_offset, 0);
            else
                next += QPointF(0, seg.m_offset);
            item->setLine(QLineF(start, next));
            item->m_segmentIdx = i; // regular line segment
            newConns.append(item);
            start = next;
        }

    }
    catch (std::runtime_error & e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Error creating connector items - invalid network data?" << std::endl;
        qDeleteAll(newConns);
        newConns.clear();
    }

    return newConns;
}


void SVBMSceneManager::onSelectionChanged() {
    // get newly selected items, and if a connector is part of the selection, select *all* segments of the same collector,
    // but deselect all others

    // if the selection was cleared, signal so
    QList<QGraphicsItem *> items = QGraphicsScene::selectedItems();
    if (items.isEmpty()) {
        emit selectionCleared();
        return;
    }

    // search for selected connector items
    QList< VICUS::BMConnector*> selectedCons;
    for (QGraphicsItem * item : qAsConst(items)) {
        SVBMConnectorSegmentItem * segItem = dynamic_cast<SVBMConnectorSegmentItem*>(item);
        if (segItem == nullptr)
            continue;
        if (selectedCons.count(segItem->m_connector) == 0)
            selectedCons.append(segItem->m_connector);
    }

    // if a connector segment was selected, de-select only the last connector and all segments of the same
    if (!selectedCons.isEmpty()) {
//		disconnect(this, &SceneManager::selectionChanged, this, &SceneManager::onSelectionChanged);
        clearSelection();
        // now select all items that belong to the connector
        for (SVBMConnectorSegmentItem * item : m_connectorSegmentItems) {
            if (item->m_connector == selectedCons.back())
                item->setSelected(true);
        }
//		connect(this, &SceneManager::selectionChanged, this, &SceneManager::onSelectionChanged);
        // signal that our connection was selected
        emit newConnectorSelected(selectedCons[0]->m_sourceSocket, selectedCons[0]->m_targetSocket);
    }
}


void SVBMSceneManager::blockDoubleClicked(const SVBMBlockItem * blockItem) {
    emit blockActionTriggered(blockItem);
}


void SVBMSceneManager::updateConnectorSegmentItems(const VICUS::BMConnector & con, SVBMConnectorSegmentItem * currentItem) {
    // lookup corresponding connectorItems
    SVBMConnectorSegmentItem*	startSegment = nullptr;
    SVBMConnectorSegmentItem*	endSegment = nullptr;
    QList<SVBMConnectorSegmentItem*> segmentItems;
    for (SVBMConnectorSegmentItem* segmentItem : qAsConst(m_connectorSegmentItems)) {
        if (segmentItem->m_connector == &con) {
            if (segmentItem->m_segmentIdx == -1)
                startSegment = segmentItem;
            else if (segmentItem->m_segmentIdx == -2)
                endSegment = segmentItem;
            else {
                if (currentItem == nullptr || segmentItem != currentItem)
                    segmentItems.append(segmentItem);
            }
        }
    }
    // re-create entire connector if all pointers are emtpy
    if (startSegment == nullptr && endSegment == nullptr && segmentItems.isEmpty()) {
        QList<SVBMConnectorSegmentItem *> newConns = createConnectorItems(const_cast<VICUS::BMConnector &>(con)); // const-cast is safe here, since we only expect connector objects that we own ourselves
        for( SVBMConnectorSegmentItem * item : qAsConst(newConns)) {
            addItem(item);
            m_connectorSegmentItems.append(item);
//			qDebug() << item << " : " << item->m_connector << " : " << item->m_segmentIdx << " : " << item->line();
        }
        return;
    }
    Q_ASSERT(startSegment != nullptr);
    Q_ASSERT(endSegment != nullptr);
    // segmentItems now contains all segment items matching this connected, except the currentItem
    int itemsNeeded = con.m_segments.count();
    if (currentItem != nullptr)
        --itemsNeeded;

    // remove any superfluous segment items
    while (segmentItems.count() > itemsNeeded) {
        SVBMConnectorSegmentItem* segmentItem = segmentItems.back();
        m_connectorSegmentItems.removeOne(segmentItem);
        delete segmentItem;
        segmentItems.pop_back();
    }

    bool highlighted = false;
    if (currentItem != nullptr)
        highlighted = currentItem->m_isHighlighted;
    else if (!segmentItems.isEmpty())
        highlighted = segmentItems.front()->m_isHighlighted;

    // add missing items
    for (int i=segmentItems.count(); i<itemsNeeded; ++i) {
        SVBMConnectorSegmentItem * item = createConnectorItem(const_cast<VICUS::BMConnector&>(con)); // need to get write access for connector in newly created item
        item->m_isHighlighted = highlighted;
        addItem(item);
        m_connectorSegmentItems.append(item);
        segmentItems.append(item);
    }

    // insert current item at correct index position
    if (currentItem != nullptr) {
        Q_ASSERT(currentItem->m_segmentIdx < segmentItems.count());
        segmentItems.insert(currentItem->m_segmentIdx, currentItem);
    }

    Q_ASSERT(segmentItems.count() == con.m_segments.count());

    // now process all segment items
    try {
        // first start and end segments
        const VICUS::BMSocket * socket;
        const VICUS::BMBlock * block;
        m_network->lookupBlockAndSocket(con.m_sourceSocket, block, socket);
        // get start line coordinates: first point is the socket's center, second point is the connection point outside the socket
        QLineF startLine = block->socketStartLine(socket);
        QPointF pos = startSegment->pos();
        startLine.translate(-pos);
        startSegment->setLine(startLine);
        // get end line coordinates: first point is the socket's center, second point is the connection point outside the socket
        m_network->lookupBlockAndSocket(con.m_targetSocket, block, socket);
        QLineF endLine = block->socketStartLine(socket);
        pos = endSegment->pos();
        endLine.translate(-pos);
        endSegment->setLine(endLine);

        // now all others
        QPointF start = startLine.p2();
        for (int i=0; i<con.m_segments.count(); ++i) {
            const VICUS::BMConnector::Segment & seg = con.m_segments[i];
            // create new segment items if new ones have been added in the meantime
            SVBMConnectorSegmentItem* item = segmentItems[i];
            Q_ASSERT(item != nullptr);
            QPointF next(start);
            if (seg.m_direction == Qt::Horizontal)
                next += QPointF(seg.m_offset, 0);
            else
                next += QPointF(0, seg.m_offset);
            QLineF newLine(start, next);
            pos = item->pos();
            newLine.translate(-pos);
            item->setLine(newLine);
            item->m_segmentIdx = i; // regular line segment
            start = next;
        }
    } catch (...) {
        // error handling
    }
}

void SVBMSceneManager::addConnectorBlockAndSocket(VICUS::BMBlock  *startBlock, VICUS::BMBlock *targetBlock, VICUS::BMSocket *startSocket, VICUS::BMSocket *targetSocket, int id){
    //Create connector block and give
    VICUS::BMBlock connectorBlock(CONNECTORBLOCK_NAME + QString::number(id), ((startBlock->m_pos.x() + startSocket->m_pos.x() + targetBlock->m_pos.x() + targetSocket->m_pos.x()) / 2) - 16, ((startBlock->m_pos.y() + startSocket->m_pos.y() + targetBlock->m_pos.y() + targetSocket->m_pos.y()) / 2) - 20);

    connectorBlock.m_size = QSizeF(CONNECTORBLOCK_WIDTH, CONNECTORBLOCK_HEIGHT);
    VICUS::BMSocket inlet(INLET_NAME, QPointF(0, connectorBlock.m_size.height() / 2), Qt::Horizontal, true);
    inlet.m_id = id;
    inlet.m_connectorSocket = true;
    VICUS::BMSocket outlet(OUTLET_NAME, QPointF(connectorBlock.m_size.width() / 2, connectorBlock.m_size.height() / 2), Qt::Horizontal, false);
    outlet.m_id = id;
    outlet.m_connectorSocket = true;
    connectorBlock.m_sockets.append(inlet);
    connectorBlock.m_sockets.append(outlet);
    qDebug() << connectorBlock.m_name << inlet.m_name;
    addConnectorBlock(connectorBlock);

    VICUS::BMConnector consource;
    consource.m_name = CONNECTOR_NAME;
    consource.m_sourceSocket = startBlock->m_name + "." + startSocket->m_name;
    qDebug() << consource.m_sourceSocket;
    consource.m_targetSocket = connectorBlock.m_name + "." + inlet.m_name;
    m_network->m_connectors.push_back(consource);
    m_network->adjustConnector(m_network->m_connectors.back());
    updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);

    VICUS::BMConnector contarget;
    contarget.m_name = CONNECTOR_NAME;
    contarget.m_sourceSocket = connectorBlock.m_name + "." + outlet.m_name;
    contarget.m_targetSocket = targetBlock->m_name + "." + targetSocket->m_name;
    m_network->m_connectors.push_back(contarget);
    m_network->adjustConnector(m_network->m_connectors.back());
    updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
    startSocket->m_id = targetSocket->m_id = id;
}

void SVBMSceneManager::setupNetwork(){

    VICUS::BMNetwork n = VICUS::BMNetwork();
    setNetwork(n);
    setSceneRect(0,0,1152,828);

    VICUS::BMBlock bentry, bexit;

    bentry.m_name = ENTRANCE_NAME;
    bentry.m_size = QSizeF(ENTRANCEEXITBLOCK_WIDTH,ENTRANCEEXITBLOCK_HEIGHT);
    bentry.m_pos = QPointF(0,400);
    bentry.m_displayName = tr("Entrance");

    bexit.m_name = EXIT_NAME;
    bexit.m_size = QSizeF(ENTRANCEEXITBLOCK_WIDTH,ENTRANCEEXITBLOCK_HEIGHT);
    bexit.m_pos = QPointF(1102,400);
    bexit.m_displayName = tr("Exit");


    VICUS::BMSocket outlet, inlet;
    outlet.m_name = OUTLET_NAME;
    outlet.m_inlet = false;
    outlet.m_id = ENTRANCE_ID;
    outlet.m_orientation = Qt::Horizontal;
    outlet.m_pos = QPointF(ENTRANCEEXITBLOCK_WIDTH,ENTRANCEEXITBLOCK_HEIGHT / 2);
    bentry.m_sockets.append(outlet);

    inlet.m_name = INLET_NAME;
    inlet.m_inlet = true;
    inlet.m_id = EXIT_ID;
    inlet.m_orientation = Qt::Horizontal;
    inlet.m_pos = QPointF(0,ENTRANCEEXITBLOCK_HEIGHT / 2);
    bexit.m_sockets.append(inlet);

    addBlock(bentry);
    addBlock(bexit);
}
