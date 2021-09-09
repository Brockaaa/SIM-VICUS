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

#ifndef VICUS_NetworkH
#define VICUS_NetworkH

#include <vector>
#include <set>
#include <string>
#include <limits>
#include <string>

#include <IBK_rectangle.h>

#include <NANDRAD_HydraulicNetwork.h>
#include <NANDRAD_HydraulicNetworkComponent.h>

#include "VICUS_NetworkEdge.h"
#include "VICUS_NetworkNode.h"
#include "VICUS_CodeGenMacros.h"
#include "VICUS_NetworkPipe.h"
#include "VICUS_Database.h"
#include "VICUS_Object.h"
#include "VICUS_NetworkBuriedPipeProperties.h"

namespace IBK {
	class Path;
}

namespace VICUS {

class NetworkFluid;

class Network : public Object {
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE
	VICUS_COMPARE_WITH_ID

	/*! The various types (equations) of the hydraulic component. */
	enum ModelType {
		MT_HydraulicNetwork,				// Keyword: HydraulicNetwork				'Only Hydraulic calculation with constant temperature'
		MT_ThermalHydraulicNetwork,			// Keyword: ThermalHydraulicNetwork			'Thermo-hydraulic calculation'
		NUM_MT
	};

	/*! Defines wether this network represents a Single or DoublePipe Network (where each edges represents 2 pipes) */
	enum NetworkType {
		NET_SinglePipe,						// Keyword: SinglePipe
		NET_DoublePipe,						// Keyword: DoublePipe
		NUM_NET
	};

	/*! The parameters */
	enum para_t {
		P_TemperatureSetpoint,				// Keyword: TemperatureSetpoint					[C]		'Temperature for pipe dimensioning algorithm'
		P_TemperatureDifference,			// Keyword: TemperatureDifference				[K]		'Temperature difference for pipe dimensioning algorithm'
		P_MaxPressureLoss,					// Keyword: MaxPressureLoss						[Pa/m]	'Maximum pressure loss for pipe dimensioning algorithm'
		P_ReferencePressure,				// Keyword: ReferencePressure					[Pa]	'Reference pressure applied to reference element'
		P_DefaultFluidTemperature,			// Keyword: DefaultFluidTemperature				[C]		'Fluid temperature for hydraulic calculation, else initial temperature'
		P_InitialFluidTemperature,			// Keyword: InitialFluidTemperature				[C]		'Initial Fluid temperature for thermo-hydraulic calculation'
		P_MaxPipeDiscretization,			// Keyword: MaxPipeDiscretization				[m]		'Maximum discretization step for dynamic pipe model'
		NUM_P
	};


	Network();

	/*! creates a copy with new unique id */
	Network clone() const{
		Network n(*this); // create new network with same unique ID
		for (unsigned int i=0; i<m_edges.size(); ++i)
			n.m_edges[i] = m_edges[i].clone();
		for (unsigned int i=0; i<m_nodes.size(); ++i)
			n.m_nodes[i] = m_nodes[i].clone();
		Object & o = n;
		(Object&)n = o.clone(); // assign new ID only
		return n;
	}

	/*! copies basic information except nodes and edges */
	Network copyWithBaseParameters();

	/*! call private addNode and set position relative to orign.
	 * ALWAYS use this funtion If you add nodes in original coordinates to a network where m_origin may has been already set */
	unsigned addNodeExt(const IBKMK::Vector3D &v, const NetworkNode::NodeType type, const bool considerCoordinates=true){
		return addNode(v - m_origin, type, considerCoordinates);
	}

	/*! add Edge based on node ids */
	void addEdge(const unsigned nodeId1, const unsigned nodeId2, const bool supply);

	/*! add Edge using edge constructor */
	void addEdge(const NetworkEdge &edge);

	/*! reads csv-files from QGIS with multiple rows, containing "MULTILINESTRING"s and adds according nodes/edges to the network.
		Lines that share a common node (identical coordinates) are automatically connected.
	*/
	void readGridFromCSV(const IBK::Path & filePath);

	/*! reads csv-files from QGIS with multiple rows, containing "POINT"s and adds according nodes of type NT_BUILDING to the network.
	*/
	void readBuildingsFromCSV(const IBK::Path & filePath, const double & heatDemand);

	/*! generate all intersections in the network (runs in a loop as long as findAndAddIntersection() is true.) */
	void generateIntersections();

	/*! Process all edges vs. all other edges. If an intersection was found, set the according
	 * edges and the intersection point are set and return true. If there are no intersection points, return false.
	*/
	bool findAndAddIntersection();

	/*! Should be called whenever m_nodes or m_edges has been modified. */
	void updateNodeEdgeConnectionPointers();

	/*! Checks that all edges and nodes are connected with each other (i.e. single graph network). */
	bool checkConnectedGraph() const;

	/*! iterates through all building nodes, finds closest supply edge and connects the building node to the network */
	void connectBuildings(const bool extendSupplyPipes);

	/*! returns the first id in m_nodes, which is an unconnected building */
	int nextUnconnectedBuilding() const;

	/*! stores a copy of the current network without "dead end" nodes (and their connecting edges)
	 * "dead end" nodes have only one connecting edge and are not buildings nor sources  */
	void cleanDeadEnds(Network & cleanNetwork, const unsigned maxSteps=50);

	/*! stores a copy of the network without any redundant edges */
	void cleanRedundantEdges(Network & cleanNetwork) const;

	/*! iteratively removes edges which have a length below thresholdLength in [m] */
	void removeShortEdges(const double &thresholdLength);

	/*! For each building node: Find shortest path to the closest source node and store the pointers to the edges
	 * along that path. The result is a map with keys being the ids of the building nodes */
	void findShortestPathForBuildings(std::map<unsigned int, std::vector<NetworkEdge *> > &minPathMap);

	/*! calculate pipe dimensions using a maximum pressure loss per length and fixed temperature difference
	 * the mass flow rate of each pipe will be calculated based on the heatDemand of connected consumer loads (e.g. buildings)
	 */
	void sizePipeDimensions(const NetworkFluid *fluid, std::vector<const NetworkPipe *> & availablePipes);

	/*! Calculate the temperature change indicator for each edge. Therefore the massflow under nominal conditions for
	 * each edge is calculated using the shortest Path algorithm. Valid pipeIds must be specified in advance for
	 * each edge.
	 */
	void calcTemperatureChangeIndicator(const NetworkFluid *fluid, const Database<NetworkPipe> &pipeDB);

	void findSourceNodes(std::vector<NetworkNode> &sources) const;

	void writeNetworkCSV(const IBK::Path &file) const;

	void writePathCSV(const IBK::Path &file, const NetworkNode & nodeById, const std::vector<NetworkEdge *> &path) const;

	void writeBuildingsCSV(const IBK::Path &file) const;

	/*! find shortest Path from given startNode (e.g. a building) to Node with type source
	 * using dijkstra-algorithm, implemented according to Wikipedia and return path as vector of edges
	 */
	void dijkstraShortestPathToSource(NetworkNode &startNode, const NetworkNode &endNode, std::vector<NetworkEdge*> &pathEndToStart);

	/*! Recomputes the min/max coordinates of the network and updates m_extends. */
	void updateExtends();

	IBKMK::Vector3D origin() const;

	/*! set m_origin and normalize all position to this origin */
	void setOrigin(const IBKMK::Vector3D &origin);

	/*! return sum of length of all edges */
	double totalLength() const;

	/*! clear nodes, edges */
	void clear(){
		m_edges.clear();
		m_nodes.clear();
	}

	/*! returns pointer to edge, which is identified by its two nodeIds */
	NetworkEdge *edge(unsigned nodeId1, unsigned nodeId2);

	/*! returns the index of the according edge in the m_edges vector */
	unsigned int indexOfEdge(unsigned nodeId1, unsigned nodeId2);

	/*! returns the number of nodes with type NT_Building */
	size_t numberOfBuildings() const;

	/*! sets the visualization radius for edges and nodes based on the respective pipe diameters (edges)
	 * and heat demands (nodes)
	*/
	void updateVisualizationRadius(const VICUS::Database<VICUS::NetworkPipe> & pipeDB) const;

	/*! sets default colors */
	void setDefaultColors() const;

	/*! sets the network object as well as all edges and nodes visible */
	void setVisible(bool visible);

	/*! identifies node by its id (in m_nodes vector) and returns according pointer
	 * Note: make sure the id exists beforehand, there is no plausible case where we want to return a nullptr here !
	 */
	NetworkNode *nodeById(unsigned int id);

	/*! identifies node by its id (in m_nodes vector) and returns according const pointer
	 * Note: make sure the id exists beforehand, there is no plausible case where we want to return a nullptr here !
	 */
	const NetworkNode *nodeById(unsigned int id) const;

	/*! identifies node by its id and returns according index in m_nodes vector
	 * Note: make sure the id exists beforehand, there is no plausible case where we want to return an index >= m_nodes.size() !
	 */
	unsigned int indexOfNode(unsigned int id) const;

	// *** PUBLIC MEMBER VARIABLES ***

	/*! unique ID of network */
	unsigned int					m_id = INVALID_ID;							// XML:A:required

	/*! fluid id */
	unsigned int					m_idFluid = INVALID_ID;						// XML:A

	/*! Network name */
	//:inherited	QString			m_displayName;								// XML:A

	/*! Nodes id must not match index in vector. To obtain a node by id use nodeById() function
	*/
	std::vector<NetworkNode>				m_nodes;									// XML:E

	/*! Vector with edges */
	std::vector<NetworkEdge>				m_edges;									// XML:E

	/*! List of pipes (ids) that may be used in this network. */
	std::vector<unsigned int>				m_availablePipes;							// XML:E

	/*! Origin of the network. */
	IBKMK::Vector3D							m_origin = IBKMK::Vector3D(0.0, 0.0, 0.0);	// XML:E

	/*! Hydraulic sub networks in the network. */
	std::vector<NANDRAD::HydraulicNetwork>	m_hydraulicSubNetworks;						// XML:E

	NetworkType								m_type = NET_DoublePipe;					// XML:E

	/*! Network parameters (e.g. for pipe sizing algorithm) */
	IBK::Parameter							m_para[NUM_P];								// XML:E

	double									m_scaleNodes = 30;							// XML:E

	double									m_scaleEdges = 30;							// XML:E

	ModelType								m_modelType = MT_ThermalHydraulicNetwork;	// XML:A

	/*! Determines if this network is currently selected for simulation */
	unsigned int							m_selectedForSimulation = false;			// XML:E

	/*! Determines wether the entire network has heat exchange with the ground */
	bool									m_hasHeatExchangeWithGround = false;		// XML:E

	/*! Describes all properties for a buried pipe in the ground */
	NetworkBuriedPipeProperties				m_buriedPipeProperties;						// XML:E


	/*! Stores visibility information for this network.
		Note: keep the next line - this will cause the code generator to create serialization code
			  for the inherited m_visible variable.
	*/
	//:inherited	bool					m_visible = true;							// XML:A

	// *** RUNTIME VARIABLES ***

	/*! Stores the extends of the network.
		Use the function updateExtends() to compute these.
		\code
		m_extends.set(minX, minY, maxX, maxY);
		\endcode
	*/
	IBK::rectangle<double>					m_extends;



	// *** STATIC FUNCTIONS

	/*! returns a specific color for each heat exchange type */
	static QColor colorHeatExchangeType(NANDRAD::HydraulicNetworkHeatExchange::ModelType heatExchangeType);


	/*! Checks if an object is contained in the set */
	template <typename T>
	static bool contains(const std::set<T> & set, unsigned int element) {
		return set.find(element) != set.end();
	}

	/*! Checks if an object is contained in the map */
	template <typename T, typename d>
	static bool contains(const std::map<T, d> & map, unsigned int element) {
		return map.find(element) != map.end();
	}

private:

	/*! add node to network based on coordinates and type and return the node id.
	 * When considerCoordinates==true and the given coordinates exist already in the network: return the id of this existing node
		ALWAYS use this function if you add nodes with coordinates that where calculated based on already existing coordinates */
	unsigned int addNode(const IBKMK::Vector3D &v, const NetworkNode::NodeType type, const bool considerCoordinates=true);

	/*! addNode using Node constructor for convenience,
	 * does only copy position, type and maxHeatingDemand */
	unsigned int addNode(const NetworkNode & nodeById, const bool considerCoordinates=true);

};


} // namespace VICUS


#endif // VICUS_NetworkH
