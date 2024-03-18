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
#include <QSvgRenderer>

#include "SVBMConnectorSegmentItem.h"
#include "SVBMBlockItem.h"
#include "SVBMSocketItem.h"
#include "SVBMZoomMeshGraphicsView.h"

#include "VICUS_BMNetwork.h"
#include "VICUS_BMSocket.h"
#include "VICUS_BMGlobals.h"
#include "VICUS_KeywordListQt.h"


SVBMSceneManager::SVBMSceneManager(QObject *parent) :
	QGraphicsScene(parent),
	m_network(new VICUS::BMNetwork)
{
}


SVBMSceneManager::~SVBMSceneManager() {
	delete m_network;
}


void SVBMSceneManager::updateNetwork(VICUS::BMNetwork & network, std::vector<VICUS::NetworkComponent>& networkComponents) {
	// Assuming m_network is a member variable, we set its value.
	Q_ASSERT(m_network);
	*m_network = network;

	// Delete all items in m_blockItems and clear the list.
	qDeleteAll(m_blockItems);
	m_blockItems.clear();

	// Delete all items in m_connectorSegmentItems and clear the list.
	qDeleteAll(m_connectorSegmentItems);
	m_connectorSegmentItems.clear();

	// Clear the block connector map.
	m_blockConnectorMap.clear();

	// Create new graphics items for blocks.
	for (VICUS::BMBlock &b : m_network->m_blocks) {

		SVBMBlockItem *item;
		if(b.m_mode == VICUS::BMBlockType::NetworkComponentBlock){

			VICUS::NetworkComponent* component = VICUS::element(networkComponents, b.m_componentId);

			//create and set QPixmap
			QSvgRenderer renderer(VICUS::NetworkComponent::iconFileFromModelType(component->m_modelType));
			QPixmap pixmap(VICUS::BLOCK_WIDTH * 2, VICUS::BLOCK_HEIGHT * 2);
			pixmap.fill(Qt::transparent);

			QPainter painter(&pixmap);
			renderer.render(&painter);
			painter.end();

			b.m_properties["ShowPixmap"] = true;
			b.m_properties["Pixmap"] = pixmap;


			Q_ASSERT(component != nullptr);
			item = createBlockItem(b, component->m_modelType);
		} else {
			item = createBlockItem(b);
		}

		if (b.m_mode == VICUS::BMBlockType::ConnectorBlock) {
			// Set m_connectorSocket to true for all sockets in the block.
			for (int i = 0; i < b.m_sockets.size(); i++) {
				b.m_sockets[i].m_isSocketOfConnector = true;
			}
			item->setRect(0,0,VICUS::CONNECTORBLOCK_WIDTH, VICUS::CONNECTORBLOCK_HEIGHT);
			item->setPos(b.m_pos);

		}
		// Add BlockItem to the scene and list.

		addItem(item);
		m_blockItems.append(item);
	}

	// Create new graphics items for connectors.
	for (VICUS::BMConnector &c : m_network->m_connectors) {
		QList<SVBMConnectorSegmentItem *> newConns = createConnectorItems(c);
		for (SVBMConnectorSegmentItem *item : qAsConst(newConns)) {
			// Add connector items to the scene and list.
			addItem(item);
			m_connectorSegmentItems.append(item);
		}
	}

	triggerItemChange();

	// By default, the connection mode is off.
	m_currentlyConnecting = false;
}

const VICUS::BMNetwork & SVBMSceneManager::network() const {
	return *m_network;
}


QPixmap SVBMSceneManager::generatePixmap(QSize targetSize) {
	// compute current scene rect
	QRectF r = itemsBoundingRect();

	double eps = 1.01;
	int borderSize = 20;
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

			if (std::fabs(seg.m_offset) < 5) {
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
	Q_ASSERT(!outletSocketItem.socket()->m_isInlet);

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
	dummyBlock.m_mode = VICUS::BMBlockType::InvisibleBlock; // "Mich gibt's gar nicht";
	dummyBlock.m_connectionHelperBlock = true;
	VICUS::BMSocket dummySocket;
	dummySocket.m_name = VICUS::BMGlobals::InvisibleLabel; // "Mich gibt's auch nicht";
	dummySocket.m_isInlet = true;
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
	if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock)
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


void SVBMSceneManager::addBlock(const VICUS::BMBlock & block, VICUS::NetworkComponent::ModelType modelType) {
	m_network->m_blocks.push_back(block);
	SVBMBlockItem * item = createBlockItem(m_network->m_blocks.back(), modelType);
	addItem(item);
	m_blockItems.append(item);
}

void SVBMSceneManager::addBlock(VICUS::NetworkComponent::ModelType type, QPoint point, unsigned int componentID)
{
	VICUS::BMBlock b;

	VICUS::BMSocket s1;
	s1.m_isInlet = true;
	s1.m_orientation = Qt::Horizontal;
	s1.m_pos = QPointF(0, VICUS::BLOCK_HEIGHT / 2);
	s1.m_name = VICUS::INLET_NAME;

	VICUS::BMSocket s2;
	s2.m_isInlet = false;
	s2.m_orientation = Qt::Horizontal;
	s2.m_pos = QPointF(VICUS::BLOCK_WIDTH, VICUS::BLOCK_HEIGHT / 2);
	s2.m_name = VICUS::OUTLET_NAME;

	SVBMZoomMeshGraphicsView *view = qobject_cast<SVBMZoomMeshGraphicsView *>(parent());
	QPointF pos = view->mapToScene(point - QPoint(VICUS::BLOCK_WIDTH * view->getScaleX() / 2, VICUS::BLOCK_HEIGHT * view->getScaleY() / 2));
	b.m_size = QSizeF(VICUS::BLOCK_WIDTH, VICUS::BLOCK_HEIGHT);
	b.m_pos = pos;
	b.m_name = QString::number(newBlockId());
	b.m_mode = VICUS::BMBlockType::NetworkComponentBlock;
	b.m_sockets.append(s1);
	b.m_sockets.append(s2);

	//create and set QPixmap
	QSvgRenderer renderer(VICUS::NetworkComponent::iconFileFromModelType(type));
	QPixmap pixmap(VICUS::BLOCK_WIDTH * 2, VICUS::BLOCK_HEIGHT * 2);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	renderer.render(&painter);
	painter.end();

	b.m_properties["ShowPixmap"] = true;
	b.m_properties["Pixmap"] = pixmap;
	b.m_displayName = VICUS::KeywordListQt::Keyword("NetworkComponent::ModelType", type);

	// do we have a component from db?
	if(componentID != VICUS::INVALID_ID)
		b.m_componentId = componentID;
	else
		b.m_componentId = static_cast<unsigned int>(type);

	emit newBlockAdded(&b, componentID);

	addBlock(b, type);
}


void SVBMSceneManager::addConnectorBlock(VICUS::BMBlock & block){
	block.m_mode = VICUS::BMBlockType::ConnectorBlock;
	m_network->m_blocks.push_back(block);
	SVBMBlockItem * item = new SVBMBlockItem(&(m_network->m_blocks.back()), VICUS::NetworkComponent::NUM_MT);
	item->setRect(0,0,block.m_size.width(), block.m_size.height());
	item->setPos(block.m_pos);
	addItem(item);
	m_blockItems.append(item);
}

void SVBMSceneManager::setController(const VICUS::BMBlock * block, QString controllerName) {
	for(SVBMBlockItem * item : m_blockItems){
		if(item->m_block == block){
			item->m_controllerName = controllerName;
		}
	}
}


void SVBMSceneManager::createConnection(const VICUS::BMBlock * startBlock, const VICUS::BMBlock * targetBlock,
										const VICUS::BMSocket * startSocket, const VICUS::BMSocket * targetSocket) {
	Q_ASSERT(startBlock && targetBlock && startSocket && targetSocket);
	VICUS::BMConnector newConnector;
	newConnector.m_name = VICUS::CONNECTOR_NAME;
	newConnector.m_sourceSocket = startBlock->m_name + "." + startSocket->m_name;
	newConnector.m_targetSocket = targetBlock->m_name + "." + targetSocket->m_name;
	m_network->m_connectors.push_back(newConnector);
	m_network->adjustConnector(m_network->m_connectors.back());
	updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
}


void SVBMSceneManager::removeBlock(const VICUS::BMBlock * block) {
	unsigned int idx = 0;
	for (auto bit = m_network->m_blocks.begin(); bit != m_network->m_blocks.end(); ++bit, ++idx)
		if (block == &(*bit)) {
			removeBlock(idx);
			return;
		}
	throw std::runtime_error("[SceneManager::removeBlock] Invalid pointer (not in managed network)");
}


void SVBMSceneManager::removeBlock(unsigned int blockIndex) {
	Q_ASSERT(m_network->m_blocks.size() > blockIndex);
	Q_ASSERT(m_blockItems.count() > (int)blockIndex);

	auto bit = m_network->m_blocks.begin();
	std::advance(bit, blockIndex);
	const VICUS::BMBlock * blockToBeRemoved = &(*bit);

	// is connector block?
	if(blockToBeRemoved->m_mode == VICUS::BMBlockType::ConnectorBlock){
		removeConnectorBlock(blockToBeRemoved);
		return;
	}

	// is global inlet / outlet ?
	if (blockToBeRemoved->m_mode == VICUS::BMBlockType::GlobalInlet || blockToBeRemoved->m_mode == VICUS::BMBlockType::GlobalOutlet)
		return;

	// find connectors that connect to this block
	QSet<VICUS::BMConnector*> connectorsToBeDeleted = m_blockConnectorMap[blockToBeRemoved];
	// save all ConnectorBlocks that need to be checked for deletion. This is needed because the ConnectorBlock could have
	QSet<const VICUS::BMBlock*> connectorBlocksToBeChecked;

	for (VICUS::BMConnector * con : connectorsToBeDeleted) {
		// find connector to be removed from list
		for (auto cit = m_network->m_connectors.begin(); cit != m_network->m_connectors.end(); ++cit) {
			if (&(*cit) == con) {

				if(blockToBeRemoved->m_mode == VICUS::BMBlockType::InvisibleBlock){
					// if invisible label is removed, remove all connectors
					m_network->m_connectors.erase(cit);
					break;
				}
				VICUS::BMSocket* sourceSocket = nullptr;
				VICUS::BMBlock* sourceBlock = nullptr;
				VICUS::BMSocket* targetSocket = nullptr;
				VICUS::BMBlock* targetBlock = nullptr;

				m_network->lookupBlockAndSocket(cit->m_targetSocket,  const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));
				m_network->lookupBlockAndSocket(cit->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));


				// reset ID if it is not Entrance or Exit Block
				if(targetBlock->m_mode != VICUS::BMBlockType::GlobalOutlet ){
					targetSocket->m_id = VICUS::INVALID_ID;
				}
				if(sourceBlock->m_mode != VICUS::BMBlockType::GlobalInlet ){
					sourceSocket->m_id = VICUS::INVALID_ID;
				}

				// if ConnectorBlock on TARGET side of connector has no Connections on one side anymore, delete it
				if(targetBlock->m_mode == VICUS::BMBlockType::ConnectorBlock && targetBlock != blockToBeRemoved){
					connectorBlocksToBeChecked.insert(targetBlock);
				}

				// if ConnectorBlock on SOURCE side of connector has no Connections on one side anymore, delete it
				if(sourceBlock->m_mode == VICUS::BMBlockType::ConnectorBlock && sourceBlock != blockToBeRemoved){
					connectorBlocksToBeChecked.insert(sourceBlock);
				}

				// delete the connector
				m_network->m_connectors.erase(cit);
				break;
			}
		}
	}

	// now remove the block itself
	SVBMBlockItem * bi = m_blockItems[(int)blockIndex];
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

	// now check if all the saved connectorBlocks have more than one connection on each side
	for(const VICUS::BMBlock* block : connectorBlocksToBeChecked){
		if(!isConnectedSocket(block, &block->m_sockets[0]) || !isConnectedSocket(block, &block->m_sockets[1])){
			removeBlock(block);
		} else if(checkOneConnectionPerSocket(block)){
			VICUS::BMConnector newConnector;
			for(VICUS::BMConnector * con : m_blockConnectorMap[block]){
				if(!con->m_sourceSocket.contains(block->m_name)){
					if(con->m_sourceSocket.contains(".inlet"))
						newConnector.m_targetSocket = con->m_sourceSocket;
					else
						newConnector.m_sourceSocket = con->m_sourceSocket;
				} else if(!con->m_targetSocket.contains(block->m_name)){
					if(con->m_targetSocket.contains(".inlet"))
						newConnector.m_targetSocket = con->m_targetSocket;
					else
						newConnector.m_sourceSocket = con->m_targetSocket;
				}
			}

			QString blockName = block->m_name;
			unsigned int id = blockName.remove(0, VICUS::CONNECTORBLOCK_NAME.length()).toUInt();
			removeConnectorBlock(block);

			newConnector.m_name = VICUS::CONNECTOR_NAME;
			m_network->m_connectors.push_back(newConnector);
			m_network->adjustConnector(m_network->m_connectors.back());
			updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);

			emit newConnectionAdded();

			const VICUS::BMSocket * sourceSocket = nullptr;
			const VICUS::BMBlock * sourceBlock = nullptr;
			const VICUS::BMSocket * targetSocket = nullptr;
			const VICUS::BMBlock * targetBlock = nullptr;

			m_network->lookupBlockAndSocket(newConnector.m_sourceSocket, sourceBlock, sourceSocket);
			m_network->lookupBlockAndSocket(newConnector.m_targetSocket, targetBlock, targetSocket);

			if(targetBlock->m_mode != VICUS::BMBlockType::GlobalOutlet){
				const_cast<VICUS::BMSocket*>(targetSocket)->m_id = id;
			} else {
				const_cast<VICUS::BMSocket*>(targetSocket)->m_id = VICUS::EXIT_ID;
				const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = VICUS::EXIT_ID;
			}
			if(sourceBlock->m_mode != VICUS::BMBlockType::GlobalInlet){
				const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = id;
			} else {
				const_cast<VICUS::BMSocket*>(targetSocket)->m_id = VICUS::ENTRANCE_ID;
				const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = VICUS::ENTRANCE_ID;
			}
		}
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

	VICUS::BMBlock *blockToBeRemoved = nullptr;
	std::list<VICUS::BMBlock>::iterator bit = m_network->m_blocks.begin();
	for (; bit != m_network->m_blocks.end(); ++bit)
		if (block == &(*bit))
			blockToBeRemoved = &(*bit);

	Q_ASSERT(blockToBeRemoved != nullptr);

	// find connectors that connect to this block
	QSet< VICUS::BMConnector*> connectors = m_blockConnectorMap[blockToBeRemoved];
	std::vector<QString> removedConnectors;
	for (VICUS::BMConnector * con : connectors) {
		// find connector to be removed from list
		for (auto cit = m_network->m_connectors.begin(); cit != m_network->m_connectors.end(); ++cit) {
			if (&(*cit) == con) {

				VICUS::BMSocket* sourceSocket = nullptr;
				VICUS::BMBlock* sourceBlock = nullptr;
				VICUS::BMSocket* targetSocket = nullptr;
				VICUS::BMBlock* targetBlock = nullptr;

				//check if the block on the other side is connected with another block. If not, reset m_id

				m_network->lookupBlockAndSocket(cit->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));
				if(sourceBlock && sourceSocket != nullptr && sourceBlock->m_mode != VICUS::BMBlockType::GlobalInlet){
						sourceSocket->m_id = VICUS::INVALID_ID;
				}

				m_network->lookupBlockAndSocket(cit->m_targetSocket,  const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));
				if(targetBlock && targetSocket != nullptr && targetBlock->m_mode != VICUS::BMBlockType::GlobalOutlet){
						targetSocket->m_id = VICUS::INVALID_ID;
				}


				m_network->m_connectors.erase(cit);
				break;
			}
		}
	}

	// now remove the block itself
	QList<SVBMBlockItem*>::iterator it = m_blockItems.begin();
	while(it != m_blockItems.end()) {
		if((*it)->m_block == blockToBeRemoved) {
			delete *it;
			m_blockItems.erase(it);  // erase returns iterator to next item
			break;
		}
		it++;
	}

	for (auto bit = m_network->m_blocks.begin(); bit != m_network->m_blocks.end(); ++bit){
		if (&(*bit) == blockToBeRemoved) {
			m_network->m_blocks.erase(bit);
			break;
		}
	}

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

	if(!isConnectedSocket(sourceBlock, sourceSocket) && !(sourceBlock->m_mode == VICUS::BMBlockType::GlobalInlet)){
		sourceSocket->m_id = VICUS::INVALID_ID;
	}
	if(!isConnectedSocket(targetBlock, targetSocket) && !(targetBlock->m_mode == VICUS::BMBlockType::GlobalOutlet)){
		targetSocket->m_id = VICUS::INVALID_ID;
	}
}


void SVBMSceneManager::removeSelectedConnector()
{
	// first look up connector to be removed
	const VICUS::BMConnector * conToBeRemoved = selectedConnector();
	VICUS::BMSocket* sourceSocket = nullptr;
	VICUS::BMBlock* sourceBlock = nullptr;
	VICUS::BMSocket* targetSocket = nullptr;
	VICUS::BMBlock* targetBlock = nullptr;
	m_network->lookupBlockAndSocket(conToBeRemoved->m_sourceSocket, const_cast<const VICUS::BMBlock *&>(sourceBlock), const_cast<const VICUS::BMSocket*&>(sourceSocket));
	m_network->lookupBlockAndSocket(conToBeRemoved->m_targetSocket, const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));

	removeConnector(conToBeRemoved);

	VICUS::BMBlock *block;
	if(sourceBlock->m_mode == VICUS::BMBlockType::ConnectorBlock)
		block = sourceBlock;
	else if(targetBlock->m_mode == VICUS::BMBlockType::ConnectorBlock)
		block = targetBlock;
	else
		return;

	if(!isConnectedSocket(block, &block->m_sockets[0]) || !isConnectedSocket(block, &block->m_sockets[1])){
		removeBlock(block);
	}

	if(checkOneConnectionPerSocket(block)){
		VICUS::BMConnector newConnector;
		for(VICUS::BMConnector * con : m_blockConnectorMap[block]){
			if(con->m_sourceSocket.contains(block->m_name)){
				newConnector.m_targetSocket = con->m_targetSocket;
			} else {
				newConnector.m_sourceSocket = con->m_sourceSocket;
			}
		}
		removeConnectorBlock(block);

		unsigned int id = newConnector.m_sourceSocket.split(".")[1].toInt();

		newConnector.m_name = VICUS::CONNECTOR_NAME;
		m_network->m_connectors.push_back(newConnector);
		m_network->adjustConnector(m_network->m_connectors.back());
		updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);

		emit newConnectionAdded();

		const VICUS::BMSocket * sourceSocket = nullptr;
		const VICUS::BMBlock * sourceBlock = nullptr;
		const VICUS::BMSocket * targetSocket = nullptr;
		const VICUS::BMBlock * targetBlock = nullptr;

		m_network->lookupBlockAndSocket(newConnector.m_sourceSocket, sourceBlock, sourceSocket);
		m_network->lookupBlockAndSocket(newConnector.m_targetSocket, targetBlock, targetSocket);

		if(targetBlock->m_mode != VICUS::BMBlockType::GlobalOutlet){
			const_cast<VICUS::BMSocket*>(targetSocket)->m_id = id;
		} else {
			const_cast<VICUS::BMSocket*>(targetSocket)->m_id = VICUS::EXIT_ID;
			const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = VICUS::EXIT_ID;
			return;
		}
		if(sourceBlock->m_mode != VICUS::BMBlockType::GlobalInlet){
			const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = id;
		} else {
			const_cast<VICUS::BMSocket*>(targetSocket)->m_id = VICUS::ENTRANCE_ID;
			const_cast<VICUS::BMSocket*>(sourceSocket)->m_id = VICUS::ENTRANCE_ID;
		}
	}
}


// ** protected functions **


void SVBMSceneManager::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
	// in case of click on socket while in connection mode, the next call will
	// result in a call to startSocketConnection(), which creates a new block and connection
	// we need to detect this and fire a mouse event again afterwards, which will cause
	// the newly created block to go into drag-move mode
	bool alreadyInConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock);
	QGraphicsScene::mousePressEvent(mouseEvent);
	bool inConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock);
	if (!alreadyInConnectionProcess && inConnectionProcess) {
		// make the last item the mouse grabber objects
		m_blockItems.back()->grabMouse();
	}
}


void SVBMSceneManager::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {

	// check if in connection mode and if connection-block position is over an inlet socket that
	// is not yet connected - if so, mark the socket as "hovered" and update it

	if (m_currentlyConnecting) {
		if (!m_blockItems.isEmpty() && m_blockItems.back()->block()->m_mode == VICUS::BMBlockType::InvisibleBlock) {
			QPointF p = m_blockItems.back()->pos();
			for (SVBMBlockItem  * bi : qAsConst(m_blockItems)) {
				if (bi->block()->m_mode == VICUS::BMBlockType::InvisibleBlock)
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

void SVBMSceneManager::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
	// similar to mousePressEvent, reimplemented to allow doubleclicked connectorBlocks to create new Connection
	bool alreadyInConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock);
	QGraphicsScene::mouseDoubleClickEvent(event);
	bool inConnectionProcess = !m_network->m_blocks.empty() && (m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock);
	if (!alreadyInConnectionProcess && inConnectionProcess) {
		// make the last item the mouse grabber objects
		m_blockItems.back()->grabMouse();
	}

}


void SVBMSceneManager::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
	if (mouseEvent->button() & Qt::LeftButton) {

		// check if we have dropped onto a connectable socket
		if (m_currentlyConnecting) {
			if (!m_blockItems.isEmpty() && m_blockItems.back()->block()->m_mode == VICUS::BMBlockType::InvisibleBlock) {
				QPointF p = m_blockItems.back()->pos();
				bool connectionFound = false;
				for (SVBMBlockItem  * bi : qAsConst(m_blockItems)) {
					if (bi->block()->m_mode == VICUS::BMBlockType::InvisibleBlock)
						continue;

					// checks if connection was dropped on a connectorBlock, if yes, connect to it
					if(bi->acceptingConnection(p)){
						connectionFound = true;
						if(evaluateNewConnection(m_network->m_connectors.back().m_sourceSocket,  bi->block()->m_name + "." + bi->block()->m_sockets[0].m_name)){
							for(SVBMSocketItem *socketItem : bi->m_socketItems){
								socketItem->m_hovered = false;
							}
							emit newConnectionAdded();
						}
						break;
					}

					// now search for sockets that may be hovered
					SVBMSocketItem * si = bi->inletSocketAcceptingConnection(p);
					if (si != nullptr) {
						connectionFound = true;
						si->m_hovered = false;
						if(evaluateNewConnection(m_network->m_connectors.back().m_sourceSocket,  bi->block()->m_name + "." + si->socket()->m_name)){
							emit newConnectionAdded();
						}
						break;
					}
				}
				if(!connectionFound){
					if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock)
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


bool SVBMSceneManager::evaluateNewConnection(QString startSocketName, QString targetSocketName)
{

	VICUS::BMBlock *startBlock = nullptr;
	VICUS::BMBlock *targetBlock = nullptr;
	VICUS::BMSocket *startSocket = nullptr;
	VICUS::BMSocket *targetSocket = nullptr;
	m_network->lookupBlockAndSocket(startSocketName, const_cast<const VICUS::BMBlock *&>(startBlock), const_cast<const VICUS::BMSocket*&>(startSocket));
	m_network->lookupBlockAndSocket(targetSocketName,const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket*&>(targetSocket));

	if (!m_network->m_blocks.empty() && m_network->m_blocks.back().m_mode == VICUS::BMBlockType::InvisibleBlock)
		removeBlock(m_network->m_blocks.size() - 1);

	/* ConnectorBlocks cannot be directly connected,
	 * Entrance and Exits cannot be connected to already existing ConnectorBlocks because of ID mismatch */
	if((startBlock->m_mode == VICUS::BMBlockType::ConnectorBlock && targetBlock->m_mode == VICUS::BMBlockType::ConnectorBlock) ||
		(startBlock->m_mode == VICUS::BMBlockType::GlobalInlet && targetBlock->m_mode == VICUS::BMBlockType::ConnectorBlock) ||
		(startBlock->m_mode == VICUS::BMBlockType::ConnectorBlock && targetBlock->m_mode == VICUS::BMBlockType::GlobalOutlet) ||
		startBlock == targetBlock) {
		return false;
	}
	/* if sourceBlock not connected and targetBlock is connected, expects that targetBlock is connected */
	if(startSocket->m_id == VICUS::INVALID_ID && targetSocket->m_id != VICUS::INVALID_ID){
		// if connection directly connects the inlet and outletsockets of the startBlock, return
		if(startBlock->m_sockets[0].m_id == targetSocket->m_id) return false;

		startSocket->m_id = targetSocket->m_id;
		// if targetBlock is a ConnectorBlock
		if(targetBlock->m_mode == VICUS::BMBlockType::ConnectorBlock){
			createConnection(startBlock, targetBlock, startSocket, targetSocket);

		// if targetBlock is not a ConnectorBlock, find the appropriate connectorBlock and connect sourceBlock with the connectorBlock
		} else {
			if(targetBlock->m_mode == VICUS::BMBlockType::GlobalOutlet && m_blockConnectorMap[targetBlock].size() == 0){
				createConnection(startBlock, targetBlock, startSocket, targetSocket);
			} else {
				VICUS::BMConnector *con = firstConnectorOfBlock(const_cast<const VICUS::BMBlock *&>(targetBlock), const_cast<const VICUS::BMSocket *&>(targetSocket));
				if(isConnectedToConnectorBlock(targetSocket, con)){
					SVBMBlockItem *conBlock = nullptr;
					for(SVBMBlockItem *bi : m_blockItems){
						if(bi->block()->m_name == VICUS::CONNECTORBLOCK_NAME + QString::number(targetSocket->m_id)){
							conBlock = bi;
						}
					}
					createConnection(startBlock, const_cast<VICUS::BMBlock*>(conBlock->block()), startSocket, const_cast<VICUS::BMSocket*>(&(conBlock->block()->m_sockets[0])));
				} else {
					convertConnectionToConnectorBlock(targetBlock, targetSocket, startBlock, startSocket, con);
				}
			}
		}
	}

	// if sourceBlock is connected and targetBlock is not connected
	else if(startSocket->m_id != VICUS::INVALID_ID && targetSocket->m_id == VICUS::INVALID_ID){
		// if connection directly connects the inlet and outletsockets of the targetSocket, return
		if(targetBlock->m_sockets[1].m_id == startSocket->m_id) return false;
		targetSocket->m_id = startSocket->m_id;
		if(startBlock->m_mode == VICUS::BMBlockType::ConnectorBlock){
			createConnection(startBlock, targetBlock, startSocket, targetSocket);
		} else {
			if(startBlock->m_mode == VICUS::BMBlockType::GlobalInlet && m_blockConnectorMap[startBlock].size() == 0){
				createConnection(startBlock, targetBlock, startSocket, targetSocket);
			} else {
				VICUS::BMConnector *con = firstConnectorOfBlock(const_cast<const VICUS::BMBlock *&>(startBlock), const_cast<const VICUS::BMSocket *&>(startSocket));
				if(isConnectedToConnectorBlock(startSocket, con)){
					SVBMBlockItem *conBlock = nullptr;
					for(SVBMBlockItem *bi : m_blockItems){
						if(bi->block()->m_name == VICUS::CONNECTORBLOCK_NAME + QString::number(startSocket->m_id)){
							conBlock = bi;
						}
					}
					createConnection(const_cast<VICUS::BMBlock*>(conBlock->block()), targetBlock, const_cast<VICUS::BMSocket*>(&(conBlock->block()->m_sockets[1])), targetSocket);
				} else {
					convertConnectionToConnectorBlock(startBlock, startSocket, targetBlock, targetSocket, con);
				}
			}
		}
	}

	// if both Blocks are already connected and have IDs
	else if (startSocket->m_id != VICUS::INVALID_ID && targetSocket->m_id != VICUS::INVALID_ID){

		// if the globalInlet wants to be connected to an existing socket with ID, check first
		// if the globalInlet is already connected to something. If yes, that means there is an attempt to connect
		// two areas of the subnetworks with different IDs. Refuse that attempt
		// if the globalInlet is not connected, that is equivalent to a block that has not an ID assigned to it
		// in this case, change the ID of the targetSocket and all sockets and connectorBlocks that are connected to
		// it to the EntranceID and then connect globalInlet to it
		if(startSocket->m_id == VICUS::ENTRANCE_ID){
			// if globalInlet already connected, return
			if(m_blockConnectorMap[startBlock].size() != 0) return false;
			//check if targetBlock is connected to connectorBlock, if yes, change all sockets connected to connectorBlock to ID of globalInlet
			VICUS::BMConnector* connectorOfTargetBlock = firstConnectorOfBlock(targetBlock, &targetBlock->m_sockets[0]);
			const VICUS::BMSocket *connectorSourceSocket;
			const VICUS::BMBlock *connectorSourceBlock;
			const VICUS::BMSocket *connectorTargetSocket;
			const VICUS::BMBlock *connectorTargetBlock;
			m_network->lookupBlockAndSocket(connectorOfTargetBlock->m_sourceSocket, connectorSourceBlock, connectorSourceSocket);
			m_network->lookupBlockAndSocket(connectorOfTargetBlock->m_targetSocket, connectorTargetBlock, connectorTargetSocket);

			// if the targetBlock is not connected to a ConnectorBlock:
			if(!isConnectedToConnectorBlock(&targetBlock->m_sockets[0], connectorOfTargetBlock)){
				const_cast<VICUS::BMSocket*>(connectorSourceSocket)->m_id = VICUS::ENTRANCE_ID;
				const_cast<VICUS::BMSocket*>(connectorTargetSocket)->m_id = VICUS::ENTRANCE_ID;
				convertConnectionToConnectorBlock(targetBlock, targetSocket, startBlock, startSocket, connectorOfTargetBlock);
				return true;
			}
			// if targetBlock is connected to ConnectorBlock
			else {
				VICUS::BMBlock *connectorBlockOfTargetBlock;
				if(connectorSourceBlock->m_name.contains(VICUS::CONNECTORBLOCK_NAME)){
					connectorBlockOfTargetBlock = const_cast<VICUS::BMBlock*>(connectorSourceBlock);
				} else if(connectorTargetBlock->m_name.contains(VICUS::CONNECTORBLOCK_NAME)){
					connectorBlockOfTargetBlock = const_cast<VICUS::BMBlock*>(connectorTargetBlock);
				} else {
					return false;
				}

				QSet<VICUS::BMConnector*> allConnectorsAttachedToConnectorBlock = m_blockConnectorMap[connectorBlockOfTargetBlock];
				for(VICUS::BMConnector* con : allConnectorsAttachedToConnectorBlock){
					QString *nameOfSocketNotAttachedToConnectorBlock;
					QString *nameOfSocketAttachedToConnectorBlock;

					if(con->m_sourceSocket.contains(VICUS::CONNECTORBLOCK_NAME)){
						nameOfSocketAttachedToConnectorBlock = &con->m_sourceSocket;
						nameOfSocketNotAttachedToConnectorBlock = &con->m_targetSocket;
					} else {
						nameOfSocketAttachedToConnectorBlock = &con->m_targetSocket;
						nameOfSocketNotAttachedToConnectorBlock = &con->m_sourceSocket;
					}

					const VICUS::BMBlock *blockNotAttachedToConnectorBlock;
					const VICUS::BMSocket *socketNotAttachedToConnectorBlock;

					m_network->lookupBlockAndSocket(*nameOfSocketNotAttachedToConnectorBlock, blockNotAttachedToConnectorBlock, socketNotAttachedToConnectorBlock);
					const_cast<VICUS::BMSocket *>(socketNotAttachedToConnectorBlock)->m_id = VICUS::ENTRANCE_ID;
					QString newNameOfSocket;
					if(socketNotAttachedToConnectorBlock->m_isInlet){
						newNameOfSocket = QString("%1%2.%3").arg(VICUS::CONNECTORBLOCK_NAME).arg(QString::number(VICUS::ENTRANCE_ID)).arg(VICUS::OUTLET_NAME);
					} else {
						newNameOfSocket = QString("%1%2.%3").arg(VICUS::CONNECTORBLOCK_NAME).arg(QString::number(VICUS::ENTRANCE_ID)).arg(VICUS::INLET_NAME);
					}
					*nameOfSocketAttachedToConnectorBlock = newNameOfSocket;
				}

				connectorBlockOfTargetBlock->m_sockets[0].m_id = VICUS::ENTRANCE_ID;
				connectorBlockOfTargetBlock->m_sockets[1].m_id = VICUS::ENTRANCE_ID;
				connectorBlockOfTargetBlock->m_name = VICUS::CONNECTORBLOCK_NAME + QString::number(VICUS::ENTRANCE_ID);
				createConnection(startBlock, connectorBlockOfTargetBlock, startSocket, &connectorBlockOfTargetBlock->m_sockets[0]);
				return true;
			}
		}

		// if the globalOutlet wants to be connected to an existing socket with ID, check first
		// if the globalOutlet is already connected to something. If yes, that means there is an attempt to connect
		// two areas of the subnetworks with different IDs. Refuse that attempt
		// if the globalOutlet is not connected, that is equivalent to a block that has not an ID assigned to it
		// in this case, change the ID of the sourceSocket and all sockets and connectorBlocks that are connected to
		// it to the ExitID and then connect globalOutlet to it
		else if (targetSocket->m_id == VICUS::EXIT_ID){
			// if globalInlet already connected, return
			if(m_blockConnectorMap[targetBlock].size() != 0) return false;
			//check if targetBlock is connected to connectorBlock, if yes, change all sockets connected to connectorBlock to ID of globalInlet
			VICUS::BMConnector* connectorOfSourceBlock = firstConnectorOfBlock(startBlock, &startBlock->m_sockets[1]);
			const VICUS::BMSocket *connectorSourceSocket;
			const VICUS::BMBlock *connectorSourceBlock;
			const VICUS::BMSocket *connectorTargetSocket;
			const VICUS::BMBlock *connectorTargetBlock;
			m_network->lookupBlockAndSocket(connectorOfSourceBlock->m_sourceSocket, connectorSourceBlock, connectorSourceSocket);
			m_network->lookupBlockAndSocket(connectorOfSourceBlock->m_targetSocket, connectorTargetBlock, connectorTargetSocket);

			// if the startBlock is not connected to a ConnectorBlock:
			if(!isConnectedToConnectorBlock(&startBlock->m_sockets[1], connectorOfSourceBlock)){
				const_cast<VICUS::BMSocket*>(connectorSourceSocket)->m_id = VICUS::EXIT_ID;
				const_cast<VICUS::BMSocket*>(connectorTargetSocket)->m_id = VICUS::EXIT_ID;
				convertConnectionToConnectorBlock(startBlock, startSocket, targetBlock, targetSocket, connectorOfSourceBlock);
				return true;
			}

			// if startBlock is connected to a ConnectorBlock
			else {
				VICUS::BMBlock *connectorBlockOfSourceBlock;
				if(connectorSourceBlock->m_name.contains(VICUS::CONNECTORBLOCK_NAME)){
					connectorBlockOfSourceBlock = const_cast<VICUS::BMBlock*>(connectorSourceBlock);
				} else if(connectorTargetBlock->m_name.contains(VICUS::CONNECTORBLOCK_NAME)){
					connectorBlockOfSourceBlock = const_cast<VICUS::BMBlock*>(connectorTargetBlock);
				} else {
					return false;
				}

				QSet<VICUS::BMConnector*> allConnectorsAttachedToConnectorBlock = m_blockConnectorMap[connectorBlockOfSourceBlock];
				for(VICUS::BMConnector* con : allConnectorsAttachedToConnectorBlock){
					QString *nameOfSocketNotAttachedToConnectorBlock;
					QString *nameOfSocketAttachedToConnectorBlock;

					if(con->m_sourceSocket.contains(VICUS::CONNECTORBLOCK_NAME)){
						nameOfSocketAttachedToConnectorBlock = &con->m_sourceSocket;
						nameOfSocketNotAttachedToConnectorBlock = &con->m_targetSocket;
					} else {
						nameOfSocketAttachedToConnectorBlock = &con->m_targetSocket;
						nameOfSocketNotAttachedToConnectorBlock = &con->m_sourceSocket;
					}

					const VICUS::BMBlock *blockNotAttachedToConnectorBlock;
					const VICUS::BMSocket *socketNotAttachedToConnectorBlock;

					m_network->lookupBlockAndSocket(*nameOfSocketNotAttachedToConnectorBlock, blockNotAttachedToConnectorBlock, socketNotAttachedToConnectorBlock);
					const_cast<VICUS::BMSocket *>(socketNotAttachedToConnectorBlock)->m_id = VICUS::EXIT_ID;
					QString newNameOfSocket;
					if(socketNotAttachedToConnectorBlock->m_isInlet){
						newNameOfSocket = QString("%1%2.%3").arg(VICUS::CONNECTORBLOCK_NAME).arg(QString::number(VICUS::EXIT_ID)).arg(VICUS::OUTLET_NAME);
					} else {
						newNameOfSocket = QString("%1%2.%3").arg(VICUS::CONNECTORBLOCK_NAME).arg(QString::number(VICUS::EXIT_ID)).arg(VICUS::INLET_NAME);
					}
					*nameOfSocketAttachedToConnectorBlock = newNameOfSocket;
				}

				connectorBlockOfSourceBlock->m_sockets[0].m_id = VICUS::EXIT_ID;
				connectorBlockOfSourceBlock->m_sockets[1].m_id = VICUS::EXIT_ID;
				connectorBlockOfSourceBlock->m_name = VICUS::CONNECTORBLOCK_NAME + QString::number(VICUS::EXIT_ID);
				createConnection(connectorBlockOfSourceBlock, targetBlock, &connectorBlockOfSourceBlock->m_sockets[1], targetSocket);
				return true;
			}
		} else return false;
	}

	// if no previous connection
	else {
		startSocket->m_id = newSocketId();
		targetSocket->m_id = startSocket->m_id;
		createConnection(startBlock, targetBlock, startSocket, targetSocket);
	}

	return true;
}

void SVBMSceneManager::triggerItemChange()
{
	// trigger the itemChange() function to update adjust the connector positions
	for (auto blockItem : m_blockItems) {
		blockItem->setPos(blockItem->pos() + QPointF(8,8));
		blockItem->setPos(blockItem->pos() - QPointF(8,8));
	}
}

void SVBMSceneManager::centerOnScene()
{
	qreal minXPosition = std::numeric_limits<qreal>::max();
	qreal maxXPosition = std::numeric_limits<qreal>::lowest();
	qreal minYPosition = std::numeric_limits<qreal>::max();
	qreal maxYPosition = std::numeric_limits<qreal>::lowest();

	for(const auto &block : m_network->m_blocks){
		if(minXPosition > block.m_pos.x()){
			minXPosition = block.m_pos.x();
		}
		if(maxXPosition < block.m_pos.x()){
			maxXPosition = block.m_pos.x();
		}
		if(minYPosition > block.m_pos.y()){
			minYPosition = block.m_pos.y();
		}
		if(maxYPosition < block.m_pos.y()){
			maxYPosition = block.m_pos.y();
		}
	}

	int offsetLeftTop = 30;
	int offsetRight = offsetLeftTop + VICUS::ENTRANCEEXITBLOCK_WIDTH;
	int offsetBottom = offsetLeftTop + VICUS::ENTRANCEEXITBLOCK_HEIGHT;
	minXPosition -= offsetLeftTop;
	maxXPosition += offsetRight;
	minYPosition -= offsetLeftTop;
	maxYPosition += offsetBottom;

	SVBMZoomMeshGraphicsView *view = qobject_cast<SVBMZoomMeshGraphicsView *>(parent());
	view->fitInView(QRectF(minXPosition, minYPosition, maxXPosition - minXPosition, maxYPosition - minYPosition), Qt::KeepAspectRatio);

}


bool SVBMSceneManager::checkOneConnectionPerSocket(const VICUS::BMBlock *block)
{
	int outletConnectionCounter = 0;
	int inletConnectionCounter = 0;
	// iterates over all Connectors and counts the number of connections
	for(VICUS::BMConnector *con : m_blockConnectorMap[block]){
		if(con->m_sourceSocket == QString(block->m_name) + "." + VICUS::OUTLET_NAME || con->m_targetSocket == QString(block->m_name) + "." + VICUS::OUTLET_NAME){
			outletConnectionCounter++;
		} else if(con->m_targetSocket == QString(block->m_name) + "." + VICUS::INLET_NAME || con->m_sourceSocket == QString(block->m_name) + "." + VICUS::INLET_NAME){
			inletConnectionCounter++;

		} // TODO Edge case connectorblock mit globaloutlet verbunden!
	}
	// if both sockets have exactly one connection, return true, else false
	if(outletConnectionCounter != 1 || inletConnectionCounter != 1){
		return false;
	}
	return true;
}


SVBMBlockItem * SVBMSceneManager::createBlockItem(VICUS::BMBlock  & b, VICUS::NetworkComponent::ModelType modelType) {
	SVBMBlockItem * item = new SVBMBlockItem(&b, modelType);
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
		clearSelection();
		// now select all items that belong to the connector
		for (SVBMConnectorSegmentItem * item : m_connectorSegmentItems) {
			if (item->m_connector == selectedCons.back())
				item->setSelected(true);
		}
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


unsigned int SVBMSceneManager::newSocketId() const
{
	unsigned int nodeID = 0;
	for(const auto &block : m_network->m_blocks) {
		if(block.m_sockets.size() == 2){
			if ((block.m_sockets[0].m_id > nodeID && block.m_sockets[0].m_id != VICUS::ENTRANCE_ID && block.m_sockets[0].m_id != VICUS::EXIT_ID && block.m_sockets[0].m_id != VICUS::INVALID_ID)) {
				nodeID = block.m_sockets[0].m_id;
			}
			if((block.m_sockets[1].m_id > nodeID && block.m_sockets[1].m_id != VICUS::ENTRANCE_ID && block.m_sockets[1].m_id != VICUS::EXIT_ID && block.m_sockets[1].m_id != VICUS::INVALID_ID)) {
				nodeID = block.m_sockets[1].m_id;
			}
		}
	}
	return nodeID + 1;
}


unsigned int SVBMSceneManager::newBlockId() const
{
	unsigned int blockID = 0;
	for(const auto &block : m_network->m_blocks) {
		bool isInt = false;
		unsigned int id = block.m_name.toUInt(&isInt); // returns "0" for strings that are convertable
		if(isInt && id > blockID) {
			blockID = id;
		}
	}
	return blockID + 1;
}


bool SVBMSceneManager::isConnectedToConnectorBlock(const VICUS::BMSocket *evaluatedSocket, const VICUS::BMConnector *con)
{
	if(evaluatedSocket->m_isInlet){
		if(con->m_sourceSocket.contains(VICUS::CONNECTORBLOCK_NAME)){
			return true;
		}
		else{
			return false;
		}
	} else {
		if(con->m_targetSocket.contains(VICUS::CONNECTORBLOCK_NAME)){
			return true;
		}
		else{
			return false;
		}
	}
}


VICUS::BMConnector *SVBMSceneManager::firstConnectorOfBlock(const VICUS::BMBlock *block, const VICUS::BMSocket *socket)
{
	if(block->m_mode == VICUS::BMBlockType::NetworkComponentBlock || block->m_mode == VICUS::BMBlockType::GlobalInlet || block->m_mode == VICUS::BMBlockType::GlobalOutlet){
		if(socket->m_isInlet){
			for(auto &connector : m_blockConnectorMap[block]){
				if(connector->m_targetSocket == block->m_name + QString(".") + VICUS::INLET_NAME)
					return connector;
			}
		} else {
			for(auto &connector : m_blockConnectorMap[block]){
				if(connector->m_sourceSocket == block->m_name + QString(".") + VICUS::OUTLET_NAME)
					return connector;
			}
		}
	}
	return nullptr;
}


void SVBMSceneManager::addConnectorBlockAndSocket(const VICUS::BMBlock *sourceBlock, const VICUS::BMBlock *targetBlock,
												  VICUS::BMSocket *startSocket, VICUS::BMSocket *targetSocket, unsigned int id){

	// Create connector block and socket
	// calculate position in the center between source and target block
	VICUS::BMBlock connectorBlock(VICUS::CONNECTORBLOCK_NAME + QString::number(id),
								  ((sourceBlock->m_pos.x() + startSocket->m_pos.x() + targetBlock->m_pos.x() + targetSocket->m_pos.x()) / 2) - 16,
								  ((sourceBlock->m_pos.y() + startSocket->m_pos.y() + targetBlock->m_pos.y() + targetSocket->m_pos.y()) / 2) - 20);
	connectorBlock.m_mode = VICUS::BMBlockType::ConnectorBlock;
	connectorBlock.m_size = QSizeF(VICUS::CONNECTORBLOCK_WIDTH, VICUS::CONNECTORBLOCK_HEIGHT);
	VICUS::BMSocket inlet(VICUS::INLET_NAME, QPointF(0, connectorBlock.m_size.height() / 2), Qt::Horizontal, true);
	inlet.m_id = id;
	inlet.m_isSocketOfConnector = true;
	VICUS::BMSocket outlet(VICUS::OUTLET_NAME, QPointF(connectorBlock.m_size.width() / 2, connectorBlock.m_size.height() / 2), Qt::Horizontal, false);
	outlet.m_id = id;
	outlet.m_isSocketOfConnector = true;
	connectorBlock.m_sockets.append(inlet);
	connectorBlock.m_sockets.append(outlet);
	addConnectorBlock(connectorBlock);

	//Create connectors and connect them
	VICUS::BMConnector consource;
	consource.m_name = VICUS::CONNECTOR_NAME;
	consource.m_sourceSocket = sourceBlock->m_name + "." + startSocket->m_name;
	consource.m_targetSocket = connectorBlock.m_name + "." + inlet.m_name;
	m_network->m_connectors.push_back(consource);
	m_network->adjustConnector(m_network->m_connectors.back());
	updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);

	VICUS::BMConnector contarget;
	contarget.m_name = VICUS::CONNECTOR_NAME;
	contarget.m_sourceSocket = connectorBlock.m_name + "." + outlet.m_name;
	contarget.m_targetSocket = targetBlock->m_name + "." + targetSocket->m_name;
	m_network->m_connectors.push_back(contarget);
	m_network->adjustConnector(m_network->m_connectors.back());
	updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
	startSocket->m_id = id;
	targetSocket->m_id = startSocket->m_id;
}


void SVBMSceneManager::convertConnectionToConnectorBlock(const VICUS::BMBlock *connectedBlock, const VICUS::BMSocket *connectedSocket,
														 const VICUS::BMBlock *newBlock, const VICUS::BMSocket *newSocket, const VICUS::BMConnector *oldCon)
{
	unsigned int connectionID = connectedSocket->m_id;
	//remove existing Connection
	const VICUS::BMBlock* startBlock;
	const VICUS::BMBlock* targetBlock;
	const VICUS::BMSocket* startSocket;
	const VICUS::BMSocket* targetSocket;
	if(connectedSocket->m_isInlet){
		targetBlock = connectedBlock;
		targetSocket = connectedSocket;
		m_network->lookupBlockAndSocket(oldCon->m_sourceSocket, startBlock, startSocket);
	} else {
		startBlock = connectedBlock;
		startSocket = connectedSocket;
		m_network->lookupBlockAndSocket(oldCon->m_targetSocket, targetBlock, targetSocket);
	}
	removeConnector(oldCon);

	addConnectorBlockAndSocket(const_cast<VICUS::BMBlock*>(startBlock), const_cast<VICUS::BMBlock*>(targetBlock),
							   const_cast<VICUS::BMSocket*>(startSocket), const_cast<VICUS::BMSocket*>(targetSocket), connectionID);

	VICUS::BMConnector con;
	con.m_name = VICUS::CONNECTOR_NAME;

	if(connectedSocket->m_isInlet){
		con.m_sourceSocket = newBlock->m_name + "." + newSocket->m_name;
		con.m_targetSocket = VICUS::CONNECTORBLOCK_NAME + QString("%1.%2").arg(connectionID).arg(VICUS::INLET_NAME);
	} else {
		con.m_sourceSocket = VICUS::CONNECTORBLOCK_NAME + QString("%1.%2").arg(connectionID).arg(VICUS::OUTLET_NAME);
		con.m_targetSocket = newBlock->m_name + "." + newSocket->m_name;
	}
	m_network->m_connectors.push_back(con);
	m_network->adjustConnector(m_network->m_connectors.back());
	updateConnectorSegmentItems(m_network->m_connectors.back(), nullptr);
}

