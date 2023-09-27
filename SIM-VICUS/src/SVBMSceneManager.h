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

#ifndef BM_SceneManagerH
#define BM_SceneManagerH

#include <QGraphicsScene>
#include <QMap>
#include "VICUS_NetworkComponent.h"

class QGraphicsItem;

namespace VICUS{
class BMNetwork;
class BMBlock;
class BMConnector;
class BMSocket;
}

class SVBMBlockItem;
class SVBMSocketItem;
class SVBMConnectorSegmentItem;
class SVBMSocketItem;

/*! The graphics scene that visualizes the network. */
class SVBMSceneManager : public QGraphicsScene {
	Q_OBJECT
public:
	explicit SVBMSceneManager(QObject *parent = nullptr);

	/*! D-tor. */
	virtual ~SVBMSceneManager() override;

	/*! Set a new network (a local copy is made of the network object).
		This will recreate the entire scene.
	*/
	void updateNetwork(VICUS::BMNetwork & network);

	/*! Provide read-only access to the network data structure.
		\note This data structure is internally used and modified by user actions.
		So, whenever a change signal is emitted, this network contains
		already the changes. If you need to create UNDO actions based on the previous
		state of the network, you must keep a separate copy of the network.
	*/
	const VICUS::BMNetwork & network() const;

	/*! Generates a pixmap from the current scene rect.
		Aspect ratio is kept, and the image is fitted into the selected target size.
	*/
	QPixmap generatePixmap(QSize targetSize);

	// query functions

	// Functions called from blocks/items to adjust the network due to user interaction

	/*! Called from BlockItem when a block was moved to signal the scene manager
		to adjust the connected connectors.
	*/
	void blockMoved(const VICUS::BMBlock * block, const QPointF oldPos);

	/*! Calls from BlockItem when a block was moved.
		Results in blockSelected(blockName) to be emitted.
	*/
	void blockSelected(const VICUS::BMBlock * block);

	/*! Called from ConnectorSegmentItem when a segment was moved to signal the scene manager
		to adjust the connected connectors.
		\param currentItem Pointer to the item currently being moved. It's socket index is
			expected to be already correctly set including possible inserted new segments.

		This function creates new segment items as needed and removes no longer needed segments
		(after a segment merge, for example).
	*/
	void connectorSegmentMoved(SVBMConnectorSegmentItem * currentItem);

	/*! Toggles high-lighting of connector segments. */
	void highlightConnectorSegments(const  VICUS::BMConnector& con, bool highlighted);

	/*! This will select all not yet selected segments of this connector.
		\note Item change flag will be turned off for all touched items, so that
		this function is not called several times.
	*/
	void selectConnectorSegments(const  VICUS::BMConnector& con);

	/*! Connected to selectionChanged() signal. */
	void onSelectionChanged();

	/*! Called from a block item when a block has been double-clicked, emits signal blockActionTriggered()  */
	void blockDoubleClicked(const SVBMBlockItem * blockItem);

	/*! This function removes line segments with 0 offset and merges the neighboring segments into one.
		Must not be called from within a move operation (only, for example, from mouse-release event handlers).
	*/
	void mergeConnectorSegments( VICUS::BMConnector & con);

	/*! Quick test if a socket is connected anywhere by a connector. */
	bool isConnectedSocket(const VICUS::BMBlock * b, const VICUS::BMSocket * s) const;

	/*! Returns true, if the user currently drags a connection.
		In this case, the hover effects for moving connectors/blocks are disabled.
	*/
	bool isCurrentlyConnecting() const { return m_currentlyConnecting; }

	/*! Called from a socket item, so that the scene is put into "actively connecting" mode.
		This means:
		- a virtual (invisible) block is created with a single inlet connector, the start line
			of this invisible block has zero length.
		- a connector between the virtual block and the current socket is created
		- all unconnected inlet sockets are marked as highlightable
		- all outlet sockets are marked as not highlightable
	*/
	void startSocketConnection(const SVBMSocketItem & outletSocketItem, const QPointF & mousePos);

	/*! Finishes "actively connecting" mode and puts the scene back into regular modification mode.
		This function is called when a connection was made, or the mouse button was released without reaching an
		outlet connector. Removes our artificial connection block.
	*/
	void finishConnection();

	// functions to query current selection

	/*! There can be several currently selected blocks.
		\return Returns a list of selected blocks or an empty list, if none is selected.
	*/
	QList<const VICUS::BMBlock*> selectedBlocks() const;

	/*! There can be only one selected connector.
		\return Returns a pointer to the selected connector or a nullptr, if none is selected.
	*/
	const  VICUS::BMConnector * selectedConnector() const;


	// functions to modify managed network

	/*! Adds a new block to the network.
		The block is copied into the network and shown at the given coordinates.
	*/
	void addBlock(const VICUS::BMBlock & block);
	/*! creates a new Block based on the given type and adds it to the network.
		The block is shown at the given coordinates. Used for drag and dropping Blocks from the Toolbox
	*/
	void addBlock(VICUS::NetworkComponent::ModelType type, QPoint point, unsigned int componentID = VICUS::INVALID_ID);

	/*! Adds a new ConnectorBlock to the network.
		The ConnectorBlock is copied into the network and shown at the given coordinates.
	*/
	void addConnectorBlock(VICUS::BMBlock & block);

	/*! Adds ConnectorBlock to a given source and target block, connects source block, connectorBlock, target block */
	void addConnectorBlockAndSocket(const VICUS::BMBlock * sourceBlock, const VICUS::BMBlock * targetBlock, VICUS::BMSocket *startSocket, VICUS::BMSocket *targetSocket, unsigned int id);

	/*! Removes previous connection and creates ConnectorBlock between three Blocks */
	void convertConnectionToConnectorBlock(const VICUS::BMBlock * connectedBlock, const VICUS::BMSocket * connectedSocket, const VICUS::BMBlock * newBlock, const VICUS::BMSocket * newSocket, const VICUS::BMConnector * oldCon);

	// sets controllerID of Block and it's BlockItem
	void setControllerID(const VICUS::BMBlock * block, unsigned int id, QString controllerName);


	/*! Creates new Connector between two Blocks and Sockets */
	void createConnection(const VICUS::BMBlock &startBlock, const VICUS::BMBlock &targetBlock, const VICUS::BMSocket &startSocket, const VICUS::BMSocket &targetSocket);

	/*! Removes the block by giving a pointer to the block.
		Block must be stored in the network's block list.
		Also removes any connections made to this block.
	*/
	void removeBlock(const VICUS::BMBlock * block);

	/*! Removes the block at the given index in the network's block list.
		Index must be a valid, otherwise an exception is thrown.
		Also removes any connections made to this block.
	*/
	void removeBlock(unsigned int blockIndex);

	/*! remove all selected Blocks */
	void removeSelectedBlocks();

	/*! Removes connector by giving a pointer to a connector in the managed network.
		Connector must be stored in the network's connector list.
	*/
	void removeConnector(const  VICUS::BMConnector * con);

	/*! Removes connector with given index.
		Index must be a valid, otherwise an exception is thrown.
	*/
	void removeConnector(unsigned int connectorIndex);

	void removeSelectedConnector();

	/*! Removes the ConnectorBlock at the given index in the network's block list.
		Index must be a valid, otherwise an exception is thrown.
		Also removes any connections made to this block.
	*/
	void removeConnectorBlock(const VICUS::BMBlock * block);

	/* Function to highlight all Connectors of ConnectorBlock
	*/
	void setHighlightallConnectorsOfBlock(const VICUS::BMBlock * block, bool highlighted);

signals:
	/*! Emitted when a new connection was made and a connector was added.
		The new connector is added to the end of the connectors in the network.
	*/
	void newConnectionAdded();

	/*! Emitted whenever a block action was triggered (usually by double-clicking on the block). */
	void blockActionTriggered(const SVBMBlockItem * blockItem);

	/*! Emitted, when a block was selected. */
	void newBlockSelected(const QString & blockName);

	/*! Emitted, when a connector was selected. */
	void newConnectorSelected(const QString & sourceSocketName, const QString & targetSocketName);

	/*! Emitted when a block or connector has been moved. */
	void networkGeometryChanged();

	/*! Emitted when the selection was cleared (by click on empty space in view). */
	void selectionCleared();

	/* Emitted when new block is added. Used to check for component validity in SVSubNetwordEditDialog */
	void newBlockAdded(VICUS::BMBlock *block, unsigned int componentID);

protected:
	/*! Listens for right-mouse-button clicks that turn off connection mode. */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	/*! When mouse is released, check if we are hovering over an inlet socket. If yet, make a new connection, otherwise
		just leave connection mode.
	*/
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	/*! Listens for right-mouse-button clicks that turn off connection mode. */
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

	/*! Create a graphics item based on the data in the given block.
		You can override this method and create your own graphics items, derived from
		base class BlockItem (which contains all the move/selection logic).
	*/
	virtual SVBMBlockItem * createBlockItem(VICUS::BMBlock & b);

	/*! Create the graphics item for a single connector line segment.
		You can override this method and create your own graphics items, derived from
		base class ConnectorSegmentItem (which contains all the move/selection logic).
	*/
	virtual SVBMConnectorSegmentItem * createConnectorItem( VICUS::BMConnector & con);

	/*! A single connect yields actually several line segments, which are created here.
		You can override this method and create your own graphics items, derived from
		base class ConnectorSegmentItem (which contains all the move/selection logic).
		\note This function calls createConnectorItem() internally, so it may be sufficient to
		replace the logic there.
	*/
	virtual QList<SVBMConnectorSegmentItem *> createConnectorItems( VICUS::BMConnector & con);


private:
	/*! Looks up all segment items belonging to this connector and updates
		their coordinates.
		Adds/removes segment items as necessary and updates m_connectorSegmentItems accordingly.

		\param con Connector to sync with connector items
		\param currentItem Pointer to currently moved item. May be a nullptr, in which case the
			first segment is treated as current item.
	*/
	void updateConnectorSegmentItems(const  VICUS::BMConnector & con, SVBMConnectorSegmentItem * currentItem);

	/*! Create new unique socket id */
	unsigned int newSocketId() const;

	/*! Helper Function to get new valid Block ID */
	unsigned int newBlockId() const;

	/*! Helper Function to check if a Block and Connection is connected to a ConnectorBlock */
	bool isConnectedToConnectorBlock(const VICUS::BMSocket * evaluatedSocket, const VICUS::BMConnector * con);

	/*! Retrieve first connector of a block */
	VICUS::BMConnector* firstConnectorOfBlock(const VICUS::BMBlock *block, const VICUS::BMSocket *socket);

	/*! Helper Function to evaluate attempted new Connection */
	bool evaluateNewConnection(QString startSocketName, QString targetSocketName);

	/*! Checks if each socket has exactly one connection */
	bool checkOneConnectionPerSocket(const VICUS::BMBlock *block);

	/*! The network that we own and manage. */
	VICUS::BMNetwork                            *m_network = nullptr;

	/*! The block-graphics items that we show on the scene. */
	QList<SVBMBlockItem*>                       m_blockItems;

	/*! The connector-graphics items that we show on the scene. */
	QList<SVBMConnectorSegmentItem*>            m_connectorSegmentItems;

	/*! Map to speed up lookup of connectors connected to a block.
		This map is initialized in createConnectorItems() and updated, whenever a connection is
		made/removed.
	*/
	QMap<const VICUS::BMBlock*, QSet< VICUS::BMConnector*>>	m_blockConnectorMap;

	/*! If true, then we are currently dragging a connection line. */
	bool                                        m_currentlyConnecting;

	/*! used to store the Socket that is currently in the process of being connected */
	VICUS::BMSocket								*m_connectingSocket = nullptr;
};


#endif // BM_SceneManagerH
