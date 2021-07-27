/*	The SIM-VICUS data model library.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "VICUS_NetworkEdge.h"
#include "VICUS_NetworkLine.h"
#include "VICUS_Project.h"

#include <IBK_assert.h>


namespace VICUS {


void NetworkEdge::collectConnectedNodes(std::set<const NetworkNode *> & connectedNodes,
								 std::set<const NetworkEdge *> & connectedEdge) const {
	// first store ourselves as connected
	connectedEdge.insert(this);
	// now ask our nodes to collect their connected elements
	m_node1->collectConnectedEdges(connectedNodes, connectedEdge);
	m_node2->collectConnectedEdges(connectedNodes, connectedEdge);
}


void NetworkEdge::setInletOutletNode(std::set<const NetworkNode *> &visitedNodes, std::vector<const NetworkEdge *> &orderedEdges) {
	// first store ourselves as connected
	orderedEdges.push_back(this);
	// now ask our nodes to collect their connected elements
	if (visitedNodes.find(m_node1) != visitedNodes.end())
		m_node2->setInletOutletNode(visitedNodes, orderedEdges);
	else{
		m_node1->setInletOutletNode(visitedNodes, orderedEdges);
	}
}


unsigned NetworkEdge::neighbourNode(unsigned nodeId) const{
	IBK_ASSERT(nodeId == m_nodeId1 || nodeId == m_nodeId2);
	if (nodeId == m_nodeId1)
		return m_nodeId2;
	else
		return m_nodeId1;
}


NetworkNode * NetworkEdge::neighbourNode(const NetworkNode *node) const {
	IBK_ASSERT(node->m_id == m_nodeId1 || node->m_id == m_nodeId2);
	if (node->m_id == m_nodeId1)
		return m_node2;
	else
		return m_node1;
}


void NetworkEdge::setLengthFromCoordinates() {
	m_length = NetworkLine(*this).length();
}


void NetworkEdge::setNodeId1(unsigned int nodeId1, NetworkNode *node1) {
	m_nodeId1 = nodeId1;
	m_node1 = node1;  // set pointer, so that setLengthFromCoordinates works
	setLengthFromCoordinates();
}


NetworkComponent::ModelType NetworkEdge::networkComponentModelType() const {
	switch (m_pipeModel) {
		case PM_SimplePipe:
			return NetworkComponent::MT_SimplePipe;
		case PM_DynamicPipe:
			return NetworkComponent::MT_DynamicPipe;
		case NUM_PM: ;
	}
	return NetworkComponent::NUM_MT;
}


} // namspace VICUS
