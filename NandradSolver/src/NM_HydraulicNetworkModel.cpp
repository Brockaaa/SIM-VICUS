/*	NANDRAD Solver Framework and Model Implementation.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "NM_HydraulicNetworkModel.h"

#include <NANDRAD_HydraulicNetwork.h>
#include <NANDRAD_HydraulicNetworkComponent.h>
#include <NANDRAD_KeywordList.h>
#include <NANDRAD_Thermostat.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>

#include <IBKMK_SparseMatrixPattern.h>

#include "NM_HydraulicNetworkFlowElements.h"
#include "NM_HydraulicNetworkModelPrivate.h"

namespace NANDRAD_MODEL {

// *** HydraulicNetworkModel members ***

HydraulicNetworkModel::HydraulicNetworkModel(const NANDRAD::HydraulicNetwork & nw,
											 const std::vector<NANDRAD::Thermostat> &thermostats,
											 unsigned int id, const std::string &displayName) :
	m_id(id), m_displayName(displayName),m_hydraulicNetwork(&nw), m_thermostats(thermostats)
{
	// first register all nodes
	std::set<unsigned int> nodeIds;
	// for this purpose process all hydraulic network elements
	for (const NANDRAD::HydraulicNetworkElement & e : nw.m_elements) {
		nodeIds.insert(e.m_inletNodeId);
		nodeIds.insert(e.m_outletNodeId);
	}

	// now populate the m_flowElements vector of the network solver
	std::vector<Element> elems;
	// process all hydraulic network elements and copy index
	for (const NANDRAD::HydraulicNetworkElement & e : nw.m_elements) {
		unsigned int idxInlet = std::distance(nodeIds.begin(), nodeIds.find(e.m_inletNodeId));
		unsigned int idxOutlet = std::distance(nodeIds.begin(), nodeIds.find(e.m_outletNodeId));
		elems.push_back(Element(idxInlet, idxOutlet) );
	}

	// set reference pressure node
	std::vector<NANDRAD::HydraulicNetworkElement>::const_iterator refFeIt = std::find(
				nw.m_elements.begin(), nw.m_elements.end(), nw.m_referenceElementId);
	unsigned int refElemeIdx = std::distance(nw.m_elements.begin(), refFeIt);
	// create implementation instance
	m_p = new HydraulicNetworkModelImpl(elems, refElemeIdx); // we take ownership
}


HydraulicNetworkModel::~HydraulicNetworkModel() {
	delete m_p; // delete pimpl object
}


const Network * HydraulicNetworkModel::network() const {
	return &m_p->m_network;
}

void HydraulicNetworkModel::setup() {
	FUNCID(HydraulicNetworkModel::setup);

	// now populate the m_flowElements vector of the network solver

	// process all hydraulic network elements and instatiate respective flow equation classes
	for (const NANDRAD::HydraulicNetworkElement & e : m_hydraulicNetwork->m_elements) {
		// each of the flow equation elements requires for calculation:
		// - instance-specific parameters from HydraulicNetworkElement e
		// - fluid property object from m_hydraulicNetwork->m_fluid
		// - component definition (via reference from e.m_componentId) and component DB stored
		//   in network
		IBK_ASSERT(e.m_component != nullptr);

		switch (e.m_component->m_modelType) {
			case NANDRAD::HydraulicNetworkComponent::MT_SimplePipe :
			case NANDRAD::HydraulicNetworkComponent::MT_DynamicPipe :
			{
				IBK_ASSERT(e.m_pipeProperties != nullptr);
				// create hydraulic pipe model
				HNPipeElement * pipeElement = new HNPipeElement(e, *e.m_pipeProperties,
																m_hydraulicNetwork->m_fluid,
																e.m_controlElement,
																m_thermostats);
				// add to flow elements
				m_p->m_flowElements.push_back(pipeElement); // transfer ownership
			} break;

			case NANDRAD::HydraulicNetworkComponent::MT_ConstantPressurePump :
			{
				// create pump model
				HNConstantPressurePump * pumpElement = new HNConstantPressurePump(e.m_id, *e.m_component);
				// add to flow elements
				m_p->m_flowElements.push_back(pumpElement); // transfer ownership
				m_pumpElements.push_back(pumpElement);
			} break;

			case NANDRAD::HydraulicNetworkComponent::MT_HeatExchanger :
			case NANDRAD::HydraulicNetworkComponent::MT_HeatPumpIdealCarnotSourceSide :
			case NANDRAD::HydraulicNetworkComponent::MT_HeatPumpIdealCarnotSupplySide :
			case NANDRAD::HydraulicNetworkComponent::MT_ControlledValve:
			{

				// Note: we have already checked that no controller is configured for HeatPumpIdealCarnot

				// create pressure loss flow element - controller is set up later
				HNPressureLossCoeffElement * pressLossCoeffelement = new HNPressureLossCoeffElement(e.m_id, *e.m_component, m_hydraulicNetwork->m_fluid, e.m_controlElement);


				// TODO Andreas / Anne: geht das woanders effizienter ?

				// find the following flow element and make sure the node in between is only connected to this and the following element
				if (e.m_controlElement != nullptr){
					if (e.m_controlElement->m_controlledProperty == NANDRAD::HydraulicNetworkControlElement::CP_TemperatureDifferenceOfFollowingElement){
						// make sure there is not another element with the same outlet id
						//(then our outlet temperature would not be equal to the next elements inlet temperature)
						for (const NANDRAD::HydraulicNetworkElement & otherElems : m_hydraulicNetwork->m_elements) {
							if (e.m_outletNodeId == otherElems.m_outletNodeId && e.m_id != otherElems.m_id )
								throw IBK::Exception(IBK::FormatString("The element with id #%1 has a controller that has controlledProperty '%2'."
																	   "This element can not be connected in parallel to any other element (share the same outletNodeId)")
													 .arg(e.m_id)
													 .arg(NANDRAD::KeywordList::Keyword("HydraulicNetworkControlElement::ControlledProperty", e.m_controlElement->m_controlledProperty)),
													 FUNC_ID);
						}
						// make sure there is only one following element (not another one in parallel)
						unsigned int followingElementId = 0;
						for (const NANDRAD::HydraulicNetworkElement & otherElems : m_hydraulicNetwork->m_elements) {
							if (e.m_outletNodeId == otherElems.m_inletNodeId){
								if (followingElementId != 0)
									// there can not be two following flow elements in parallel (with same inletNodeId)
									throw IBK::Exception(IBK::FormatString("The element with id #%1 has a controller that has controlledProperty '%2'."
																		   "The follwoing element can not be connected in parallel to any other element (share the same inletNodeId)")
														 .arg(e.m_id)
														 .arg(NANDRAD::KeywordList::Keyword("HydraulicNetworkControlElement::ControlledProperty", e.m_controlElement->m_controlledProperty)),
														 FUNC_ID);
								else
									followingElementId = otherElems.m_id;
							}
						}
						pressLossCoeffelement->m_followingflowElementId = followingElementId;
					}
				}

				m_p->m_flowElements.push_back(pressLossCoeffelement); // transfer ownership

			} break;

			case NANDRAD::HydraulicNetworkComponent::NUM_MT: {
				throw IBK::Exception(IBK::FormatString("Unsupported model type for "
									"HydraulicNetworkComponent with id %1!")
									.arg(e.m_componentId),FUNC_ID);
			}
		}
		// fill ids
		m_elementIds.push_back(e.m_id);
		m_elementDisplayNames.push_back(e.m_displayName);

		// retrieve model quantities
		m_modelQuantityOffset.push_back(m_modelQuantities.size());
		// retrieve current flow element (m_flowElements vector has same size as
		const HydraulicNetworkAbstractFlowElement *fe = m_p->m_flowElements.back();
		fe->modelQuantities(m_modelQuantities);
		fe->modelQuantityValueRefs(m_modelQuantityRefs);
		// correct type and id of quantity description
		for(unsigned int k = m_modelQuantityOffset.back(); k < m_modelQuantities.size(); ++k) {
			m_modelQuantities[k].m_id = m_elementIds.back();
			m_modelQuantities[k].m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
		}
		// implementation check
		IBK_ASSERT(m_modelQuantities.size() == m_modelQuantityRefs.size());
	} // for m_hydraulicNetwork->m_elements
	// mark end of vector
	m_modelQuantityOffset.push_back(m_modelQuantities.size());

	// set initial temperature in case of HydraulicNetwork
	if (m_hydraulicNetwork->m_modelType == NANDRAD::HydraulicNetwork::MT_HydraulicNetwork) {
		for (HydraulicNetworkAbstractFlowElement * e : m_p->m_flowElements)
			e->m_fluidTemperatureRef = &m_hydraulicNetwork->m_para[NANDRAD::HydraulicNetwork::P_DefaultFluidTemperature].value;
	}

	// set reference pressure
	m_p->m_referencePressure = m_hydraulicNetwork->m_para[NANDRAD::HydraulicNetwork::P_ReferencePressure].value;

	// setup the equation system
	try {
		m_p->setup();
	} catch (IBK::Exception & ex) {
		throw IBK::Exception(ex, "Error setting up equation system/Jacobian for flow network.", FUNC_ID);
	}
}


void HydraulicNetworkModel::resultDescriptions(std::vector<QuantityDescription> & resDesc) const {
	// mass flux vector is a result
	QuantityDescription desc("FluidMassFluxes", "kg/s", "Fluid mass flux trough all flow elements", false);
	// this has been checked already in NANDRAD::HydraulicNetwork::checkParameters()
	IBK_ASSERT(!m_p->m_flowElements.empty());
	desc.resize(m_elementIds, NANDRAD_MODEL::VectorValuedQuantityIndex::IK_ModelID);
	resDesc.push_back(desc);

	// we cannot use IndexKeyType Index for vector value quantities below,
	// because we want to request flow element properties by providing flow element IDs!
	desc = QuantityDescription("FluidMassFlux", "kg/s", "Fluid mass flux through a flow element", false);

	// Important: change reftype to MRT_NETWORKELEMENT, because it otherwise defaults to the reftype of this object.
	desc.m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
	// loop through all flow elements
	for(unsigned int i = 0; i < m_elementIds.size(); ++i) {
		desc.m_id = m_elementIds[i];
		resDesc.push_back(desc);
	}

	// inlet node pressure vector is a result
	desc = QuantityDescription("InletNodePressure", "Pa", "Fluid pressure at inlet node of a flow element", false);
	// Important: change reftype to MRT_NETWORKELEMENT, because it otherwise defaults to the reftype of this object.
	desc.m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
	// loop through all flow elements
	for(unsigned int i = 0; i < m_elementIds.size(); ++i) {
		desc.m_id = m_elementIds[i];
		resDesc.push_back(desc);
	}

	// outlet node pressure vector is a result
	desc = QuantityDescription("OutletNodePressure", "Pa", "Fluid pressure at outlet node of a flow element", false);
	// Important: change reftype to MRT_NETWORKELEMENT, because it otherwise defaults to the reftype of this object.
	desc.m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
	// loop through all flow elements
	for(unsigned int i = 0; i < m_elementIds.size(); ++i) {
		desc.m_id = m_elementIds[i];
		resDesc.push_back(desc);
	}

	// pressure difference between inlet and outlet is a vector result
	desc = QuantityDescription("PressureDifference", "Pa", "Fluid pressure difference over a flow element", false);
	// Important: change reftype to MRT_NETWORKELEMENT, because it otherwise defaults to the reftype of this object.
	desc.m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
	// loop through all flow elements
	for(unsigned int i = 0; i < m_elementIds.size(); ++i) {
		desc.m_id = m_elementIds[i];
		resDesc.push_back(desc);
	}

	// add individual model results
	if (!m_modelQuantities.empty())
		resDesc.insert(resDesc.end(), m_modelQuantities.begin(), m_modelQuantities.end());
}


const double * HydraulicNetworkModel::resultValueRef(const InputReference & quantity) const {
	FUNCID(HydraulicNetworkModel::resultValueRef);

	const QuantityName & quantityName = quantity.m_name;
	// return vector of mass fluxes
	if (quantityName.m_name == std::string("FluidMassFluxes")) {
		// id must be ID of network, and reftype must be NETWORK
		if (quantity.m_id == id() && quantity.m_referenceType == NANDRAD::ModelInputReference::MRT_NETWORK) {

			// no element id? maybe the entire vector is requested
			if (quantity.m_name.m_index == -1)
				return &m_p->m_fluidMassFluxes[0];
			else {
				// we have published values via ID, so search through m_elementIds
				for (unsigned int i=0; i<m_elementIds.size(); ++i) {
					if (m_elementIds[i] == (unsigned int)quantity.m_name.m_index) {
						return &m_p->m_fluidMassFluxes[i]; // return memory location of requested element
					}
				}
				throw IBK::Exception(IBK::FormatString("Unknown flow element ID '%1' out of range in requested output quantity '%2'")
									 .arg(quantity.m_name.m_index).arg(quantity.m_name.encodedString()), FUNC_ID);
			}
		}
		return nullptr; // invalid ID or reftype...
	}

	// everything below will be reftype NETWORKELEMENT, so ignore everything else
	if (quantity.m_referenceType != NANDRAD::ModelInputReference::MRT_NETWORKELEMENT)
		return nullptr;

	// lookup element index based on given ID
	std::vector<unsigned int>::const_iterator fIt =
			std::find(m_elementIds.begin(), m_elementIds.end(), (unsigned int) quantity.m_id);
	// invalid ID?
	if (fIt == m_elementIds.end())
		return nullptr;
	unsigned int pos = (unsigned int) std::distance(m_elementIds.begin(), fIt);

	if (quantityName == std::string("FluidMassFlux"))
		return &m_p->m_fluidMassFluxes[pos];
	else if (quantityName == std::string("InletNodePressure"))
		return &m_p->m_inletNodePressures[pos];
	else if (quantityName == std::string("OutletNodePressure"))
		return &m_p->m_outletNodePressures[pos];
	else if (quantityName == std::string("PressureDifference"))
		return &m_p->m_pressureDifferences[pos];

	// search for quantity inside individual element results
	IBK_ASSERT(pos < m_modelQuantityOffset.size() - 1);
	unsigned int startIdx = m_modelQuantityOffset[pos];
	unsigned int endIdx = m_modelQuantityOffset[pos + 1];

	// check if element contains requested quantity
	for (unsigned int resIdx = startIdx; resIdx < endIdx; ++resIdx) {
		const QuantityDescription &modelDesc = m_modelQuantities[resIdx];
		if (modelDesc.m_name == quantityName.m_name) {
			// index is not allowed for network element output
			if (quantityName.m_index != -1)
				return nullptr;
			return m_modelQuantityRefs[resIdx];
		}
	}
	// unknown quantity name
	return nullptr;
}


void HydraulicNetworkModel::variableReferenceSubstitutionMap(std::map<std::string, std::string> & varSubstMap) {
	// add substitutions for all outputs generated from this class
	if (!m_displayName.empty())
		varSubstMap[ IBK::FormatString("Network(id=%1)").arg(m_id).str() ] = m_displayName;

	for (unsigned int i = 0; i<m_elementIds.size(); ++i) {
		if (m_elementDisplayNames[i].empty()) continue;
		varSubstMap[ IBK::FormatString("NetworkElement(id=%1)").arg(m_elementIds[i]).str() ] = m_elementDisplayNames[i];
	}
}


void HydraulicNetworkModel::initInputReferences(const std::vector<AbstractModel *> & /*models*/) {
	// no inputs for now
}


void HydraulicNetworkModel::inputReferences(std::vector<InputReference> & inputRefs) const {
	// only require input references (to temperatures) if we compute ThermalHydraulicNetworks
	if (m_hydraulicNetwork->m_modelType == NANDRAD::HydraulicNetwork::MT_ThermalHydraulicNetwork) {
		// use hydraulic network model to generate temperature references
		InputReference inputRef;
		inputRef.m_referenceType = NANDRAD::ModelInputReference::MRT_NETWORKELEMENT;
		inputRef.m_name = std::string("FluidTemperature");
		inputRef.m_required = true;
		for(unsigned int i = 0; i < m_elementIds.size(); ++i) {
			inputRef.m_id = m_elementIds[i];
			// register reference
			inputRefs.push_back(inputRef);
		}
	}
	// loop over all elements and ask them to request individual inputs, for example scheduled quantities
	for (unsigned int i = 0; i < m_p->m_flowElements.size(); ++i)
		m_p->m_flowElements[i]->inputReferences(inputRefs);
}


void HydraulicNetworkModel::setInputValueRefs(const std::vector<QuantityDescription> & /*resultDescriptions*/,
											  const std::vector<const double *> & resultValueRefs)
{
	unsigned int currentIndex = 0;
	if (m_hydraulicNetwork->m_modelType == NANDRAD::HydraulicNetwork::MT_ThermalHydraulicNetwork) {
		// set all fluid temperature references
		for (unsigned int i = 0; i < m_elementIds.size(); ++i) {
			HydraulicNetworkAbstractFlowElement *fe = m_p->m_flowElements[i];
			fe->m_fluidTemperatureRef = resultValueRefs[i];
		}
		currentIndex = m_elementIds.size();
	}

	// now provide elements with their specific input quantities
	std::vector<const double *>::const_iterator valRefIt = resultValueRefs.begin() + currentIndex; // Mind the index increase here

	for (unsigned int i = 0; i < m_p->m_flowElements.size(); ++i)
		m_p->m_flowElements[i]->setInputValueRefs(valRefIt);

	IBK_ASSERT(valRefIt == resultValueRefs.end());
}


void HydraulicNetworkModel::stateDependencies(std::vector<std::pair<const double *, const double *> > & /*resultInputValueReferences*/) const {
	// we ignore dependencies
}


int HydraulicNetworkModel::update() {
	FUNCID(HydraulicNetworkModel::update);

	// re-compute hydraulic network

	IBK_ASSERT(m_p != nullptr);
	try {
		// TODO : check input ref values vs. old input ref values - no change, no recomputation needed
		int res = m_p->solve();
		// signal an error
		if (res != 0) {
			IBK_FastMessage(IBK::VL_DETAILED)("Network solver returned recoverable error.", IBK::MSG_ERROR, FUNC_ID, IBK::VL_DETAILED);
			return res;
		}
		// update all model results
		for (unsigned int i = 0; i < m_elementIds.size(); ++i) {
			HydraulicNetworkAbstractFlowElement *fe = m_p->m_flowElements[i];
			fe->updateResults(m_p->m_fluidMassFluxes[i], m_p->m_inletNodePressures[i], m_p->m_outletNodePressures[i]);
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception(ex,
							 IBK::FormatString("Error solving hydraulic network equations for network '%1' (#%2).")
							 .arg(m_displayName).arg(m_id), FUNC_ID);

	}

	return 0; // signal success
}


void HydraulicNetworkModel::stepCompleted(double /*t*/) {
	m_p->storeSolution();
}


// *** HydraulicNetworkModelImpl members ***

// constants that control Jacobian matrix generation
const double JACOBIAN_EPS_RELTOL = 1e-6;
const double JACOBIAN_EPS_ABSTOL = 1e-8; // in Pa and scaled kg/s

// convergence threshold for WRMS norm
const double THRESHOLD = 0.1;
const double MASS_FLUX_SCALE = 1000;


HydraulicNetworkModelImpl::HydraulicNetworkModelImpl(const std::vector<Element> &elems, unsigned int referenceElemIdx) {
	FUNCID(HydraulicNetworkModelImpl::HydraulicNetworkModelImpl);
	// copy elements vector
	m_network.m_elements = elems;
	// count number of nodes
	unsigned int nodeCount = 0;
	for (const Element &fe :elems) {
		nodeCount = std::max(nodeCount, fe.m_nodeIndexInlet);
		nodeCount = std::max(nodeCount, fe.m_nodeIndexOutlet);
	}

	// create fast access connections between nodes and flow elements
	m_network.m_nodes.resize(nodeCount+1);
	for (unsigned int i=0; i<elems.size(); ++i) {
		const Element &fe = elems[i];
		m_network.m_nodes[fe.m_nodeIndexInlet].m_elementIndexesOutlet.push_back(i);
		m_network.m_nodes[fe.m_nodeIndexOutlet].m_elementIndexesInlet.push_back(i);
		m_network.m_nodes[fe.m_nodeIndexInlet].m_elementIndexes.push_back(i);
		m_network.m_nodes[fe.m_nodeIndexOutlet].m_elementIndexes.push_back(i);
	}

	// set reference nodeindex: inlet node of reference element
	m_pressureRefNodeIdx = elems[referenceElemIdx].m_nodeIndexInlet;

	m_nodeCount = m_network.m_nodes.size();
	m_elementCount = m_network.m_elements.size();
	IBK::IBK_Message(IBK::FormatString("Nodes:         %1\n").arg(m_nodeCount), IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
	IBK::IBK_Message(IBK::FormatString("Flow elements: %1\n").arg(m_elementCount), IBK::MSG_PROGRESS, FUNC_ID, IBK::VL_STANDARD);
}


HydraulicNetworkModelImpl::~HydraulicNetworkModelImpl() {
	// delete KLU specific pointer
	if (m_sparseSolver.m_KLUSymbolic !=  nullptr) {
		klu_free_symbolic(&(m_sparseSolver.m_KLUSymbolic), &(m_sparseSolver.m_KLUParas));
		delete m_sparseSolver.m_KLUSymbolic;
	}
	if (m_sparseSolver.m_KLUNumeric !=  nullptr) {
		klu_free_numeric(&(m_sparseSolver.m_KLUNumeric), &(m_sparseSolver.m_KLUParas));
		delete m_sparseSolver.m_KLUNumeric;
	}
}


void HydraulicNetworkModelImpl::setup() {
	FUNCID(HydraulicNetworkModelImpl::setup);


	// error checks:
	// 1.) no open ends
	// -> all m_nodes[i] must have at least 2 m_flowElementIndexes
	// 2.) no single cycles:
	// -> inlet must be different from outlet
	for (unsigned int i=0; i<m_network.m_nodes.size(); ++i) {
		const Node &node = m_network.m_nodes[i];
		// error check 1
		if(node.m_elementIndexes.size() == 1){
			throw IBK::Exception(IBK::FormatString(
					"FlowElement with id %1 is an open end of hydraulic network!")
					 .arg(node.m_elementIndexes[0]).str(),
					FUNC_ID);
		}
		// error check 2
		std::set<unsigned int> indexes;
		for(unsigned int j = 0; j < node.m_elementIndexes.size(); ++j) {
			unsigned int elementIdx = node.m_elementIndexes[j];
			if(indexes.find(elementIdx) != indexes.end()){
				throw IBK::Exception(IBK::FormatString(
						"FlowElement with id %1 is an invalid cyclic connection!")
						 .arg(elementIdx).str(),
						FUNC_ID);
			}
		}
	}


	// 3.) no distinct networks
	// -> each node must connect to any other

	// create adjancency information between connected nodes
	std::vector<std::vector<unsigned int> > nodeConnections(m_network.m_nodes.size());

	for (unsigned int k=0; k<m_network.m_elements.size(); ++k) {
		const Element &fe = m_network.m_elements[k];

		unsigned int i = fe.m_nodeIndexInlet;
		unsigned int j = fe.m_nodeIndexOutlet;
		// node connection may not be registered already
		if(!nodeConnections[i].empty() &&
		   std::find(nodeConnections[i].begin(), nodeConnections[i].end(), j) !=
		   nodeConnections[i].end())
			continue;
		// set connect inlet and outlet node
		nodeConnections[i].push_back(j);
		// as well as for the transposed
		nodeConnections[j].push_back(i);
	}

	// use Cuthill McKee algorithm in order to check connectivity
	// create path vector
	std::vector<unsigned int>	path(m_nodeCount, (unsigned int)(-1));
	std::vector<unsigned int>   nodeList(m_nodeCount, (unsigned int)(-1));
	unsigned int subPathLen = 1; // remaining length of path is 1
	// set path index (index of node
	unsigned int subPathStartIdx = 0;

	// we start numbering using CMK algorithm
	path[0] = 0;

	// number all nodes, n is the new node number
	for (unsigned int n = 0; n < m_nodeCount; ++n) {

		// if path is empty and we still have nodes (k<n) registert, than
		// the graph is not fully connected
		if (subPathLen == 0) {
			std::set<unsigned int> disjunctElements;
			// find out disjunct network elements
			for (unsigned int j = 0; j < m_nodeCount; ++j) {
				disjunctElements.insert(j);
			}
			for (unsigned int j = 0; j < m_nodeCount; ++j) {
				if (nodeList[j] != (unsigned int)(-1)) {
					disjunctElements.erase(nodeList[j]);
				}
			}
			// create a string for all missing elements
			IBK_ASSERT(!disjunctElements.empty());
			std::string networkStr(IBK::val2string<unsigned int>(*disjunctElements.begin()));

			for(std::set<unsigned int>::const_iterator elemIt = disjunctElements.begin();
				elemIt != disjunctElements.end(); ++elemIt)
				networkStr += std::string(",") + IBK::val2string<unsigned int>(*elemIt);

			throw IBK::Exception(IBK::FormatString(
					"Network is not completely connected! Distinct network formed by flow elements (%1)!")
					.arg(networkStr).str(),
					FUNC_ID);
		}

		// get next node number from registered path
		unsigned int nodeIdx = path[subPathStartIdx++]; // increase path index
		--subPathLen; // decrease length of remaining path

		// relabel node and store node mapping
		nodeList[nodeIdx] = n;

		// create convenience pointer to node numbers connected to this node
		const std::vector<unsigned int> &nodeConnect = nodeConnections[nodeIdx];

		// get degree of this node
		unsigned int nNeighbors = nodeConnect.size();

		// loop through all neighbors and connect to corresponding nodes
		for (unsigned int j=0; j < nNeighbors; ++j) {
			// get node number of neighboring node (nnn == old numbering)
			unsigned int nextNodeIdx = nodeConnect[j];

			// check if this node has already been renumbered
			if (nodeList[nextNodeIdx] != (unsigned int)(-1) )
				continue; // skip this node

			// check if this node is already in the list
			unsigned int k = subPathStartIdx;
			for (; k < subPathStartIdx + subPathLen; ++k) {
				if (path[k] == nextNodeIdx)
					break;
			}
			if (k != subPathStartIdx + subPathLen)
				continue;
			// register node in path
			path[k] = nextNodeIdx;
			// correct sub path lenght from current node
			++subPathLen;
		}
	}

	// count number of nodes
	unsigned int n = m_nodeCount + m_elementCount;

	// set initial conditions (pressures and mass fluxes)
	m_y.resize(n, 10);
	m_yLast.resize(n, 10);

	m_G.resize(n);
	m_fluidMassFluxes.resize(m_elementCount);
	m_inletNodePressures.resize(m_elementCount);
	m_outletNodePressures.resize(m_elementCount);
	m_nodalPressures.resize(m_nodeCount);
	m_pressureDifferences.resize(m_elementCount);

	// create jacobian
	jacobianInit();
}


double WRMSNorm(const std::vector<double> & vec) {
	double resNorm = 0;
	for (unsigned int i=0; i<vec.size(); ++i)
		resNorm += vec[i]*vec[i];
	resNorm /= vec.size();
	resNorm = std::sqrt(resNorm);
	return resNorm;
}


void HydraulicNetworkModelImpl::printVars() const {
	std::cout << "Mass fluxes [kg/s]" << std::endl;
	for (unsigned int i=0; i<m_elementCount; ++i)
		std::cout << "  " << i << "   " << m_y[i]/MASS_FLUX_SCALE  << std::endl;

	std::cout << "Nodal pressures [Pa]" << std::endl;
	for (unsigned int i=0; i<m_nodeCount; ++i)
		std::cout << "  " << i << "   " << m_y[i + m_elementCount] << std::endl;
}


void HydraulicNetworkModelImpl::writeNetworkGraph() const {
#if 0
	// generate dot graph file for plotting
	std::stringstream strm;
	strm << "digraph {\n";
	for (HydraulicNetworkAbstractFlowElement * fe : m_flowElements) {
		strm << "  " << fe->m_nInlet+1 << " -> " << fe->m_nOutlet+1;
		if (dynamic_cast<Pump*>(fe) != nullptr) {
			strm << "[fontsize=7, label=\"pump\", weight=200, color=red]";
		}
		strm << ";\n";
	}

	strm << "}\n";

	std::ofstream out("graph.gv");
	out << strm.rdbuf();
#endif
}


int HydraulicNetworkModelImpl::solve() {
	FUNCID(HydraulicNetworkModelImpl::solve);

	unsigned int n = m_nodeCount + m_elementCount;

	// reset initial guess
	std::vector<double> rhs(n, 0);
	std::memcpy(m_y.data(), m_yLast.data(), sizeof(double)*n);

	// now start the Newton iteration
	int iterations = 100;
	while (--iterations > 0) {
		// evaluate system function for current guess
		updateG();

		// store RHS
		for (unsigned int i=0; i<m_G.size(); ++i)
			rhs[i] = -m_G[i];

		// compose right hand side (mind the minus sign)
		// and evaluate residuals
		double resNorm = WRMSNorm(m_G);
//		std::cout << "res = " << resNorm << std::endl;
		if (resNorm < THRESHOLD)
			break;

		// now compose Jacobian with FD quotients

		// perform jacobian update
		int res = jacobianSetup();
		// error signaled:
		// may be result of a diverging Newton iteration
		// -> regsiter a recoverable error and allow a retry
		if (res != 0) {
			IBK_FastMessage(IBK::VL_DETAILED)("Error during Jacobian setup.", IBK::MSG_ERROR, FUNC_ID, IBK::VL_DETAILED);
			return 1;
		}

//		std::cout << "\n\n*** Iter " << 100-iterations  << std::endl;

//		printVars();
//		jacobianWrite(rhs);

#ifdef RESIDUAL_TEST
		std::vector<double> originalRHS(rhs);
#endif // RESIDUAL_TEST

		// now solve the equation system
		res = jacobianBacksolve(rhs);
		// backsolving problems imply coarse structural errors
		if (res != 0) {
			IBK_FastMessage(IBK::VL_DETAILED)("Error solving equation system.", IBK::MSG_ERROR, FUNC_ID, IBK::VL_DETAILED);
			return 2;
		}

//		std::cout << "deltaY" << std::endl;
//		for (unsigned int i=0; i<n; ++i)
//			std::cout << "  " << i << "   " << rhs[i]  << std::endl;

#ifdef RESIDUAL_TEST
		// check if equation system was solved correctly.
		std::vector<double> originalRHS2(rhs);
		jacobianMultiply(rhs, originalRHS);
		std::cout << "residuals" << std::endl;
		for (unsigned int i=0; i<n; ++i)
			std::cout << "  " << i << "   " << originalRHS[i]-originalRHS2[i]  << std::endl;
#endif // RESIDUAL_TEST

		// and add corrections to m_y
		double max_scale = 1;
#ifdef SCALE_DELTAY
		for (unsigned int i=0; i<n; ++i) {
			double y_next = m_y[i] + rhs[i];
			if (y_next < 0)
				max_scale = std::min(max_scale, (0.01-m_y[i])/(rhs[i]-1e-6) );
		}
#endif
		for (unsigned int i=0; i<n; ++i) {
			m_y[i] += max_scale*rhs[i];
		}
//		std::cout << "deltaY (improved)" << std::endl;
//		for (unsigned int i=0; i<n; ++i)
//			std::cout << "  " << i << "   " << rhs[i]  << std::endl;

		// TODO : add alternative convergence criterion based on rhs norm
	}

#ifdef NANDRAD_NETWORK_DEBUG_OUTPUTS
	printVars();
#endif // NANDRAD_NETWORK_DEBUG_OUTPUTS

	// update nodal values
	for(unsigned int i = 0; i < m_network.m_elements.size(); ++i) {
		const Element &e = m_network.m_elements[i];
		double inletNodePressure = m_nodalPressures[e.m_nodeIndexInlet];
		double outletNodePressure = m_nodalPressures[e.m_nodeIndexOutlet];
		m_inletNodePressures[i] = inletNodePressure;
		m_outletNodePressures[i] = outletNodePressure;
		m_pressureDifferences[i] = inletNodePressure - outletNodePressure;
	}


	if (iterations > 0)
		return 0;
	// we register a recoverable error if the system did not converge
	// (and allow a retry with a new guess)
	else {
		IBK_FastMessage(IBK::VL_DETAILED)("Not converged within given number of iterations.", IBK::MSG_ERROR, FUNC_ID, IBK::VL_DETAILED);
		return 1;
	}

}


void HydraulicNetworkModelImpl::storeSolution() {
	std::memcpy(m_yLast.data(), m_y.data(), sizeof(double)*m_y.size());
}


void HydraulicNetworkModelImpl::jacobianInit() {

	unsigned int n = m_nodeCount + m_elementCount;
	// if sparse solver is not available use dense matrix
	if (m_solverOptions == LESDense) {
		m_denseSolver.m_jacobian.resize(n);
		m_denseSolver.m_jacobianFactorized.resize(n);
	}
	else {

		IBKMK::SparseMatrixPattern pattern(n);
#ifdef PRESSURES_FIRST
		// nodal equations
		for (unsigned int i=0; i<m_nodeCount; ++i) {
			// now sum up all the mass fluxes in the nodes
			for (unsigned int j=0; j<m_network->m_nodes[i].m_elementIndexes.size(); ++j) {
				unsigned int feIndex = m_network->m_nodes[i].m_elementIndexes[j];
				// node is connected to all inflow and outflow elements
				if (!pattern.test(i, m_nodeCount + feIndex))
					pattern.set(i, m_nodeCount + feIndex);
			}
		}

		// nodal constraint to first node
		if (!pattern.test(m_pressureRefNodeIdx, m_pressureRefNodeIdx))
			pattern.set(m_pressureRefNodeIdx, m_pressureRefNodeIdx);

		// flow element equations
		for (unsigned int i=0; i<m_elementCount; ++i) {
			const HydraulicNetworkElement &fe = m_network->m_elements[i];
			// we need mass flux for pressure loss calculatiopn
			if (!pattern.test(m_nodeCount + i, m_nodeCount + i))
				pattern.set(m_nodeCount + i, m_nodeCount + i);
			// element is connected to inlet and outlet node
			if (!pattern.test(m_nodeCount + i, fe.m_nInlet))
				pattern.set(m_nodeCount + i, fe.m_nInlet);
			if (!pattern.test(m_nodeCount + i, fe.m_nOutlet))
				pattern.set(m_nodeCount + i, fe.m_nOutlet);
		}

#else
		// nodal equations
		for (unsigned int i=0; i<m_nodeCount; ++i) {
			// now sum up all the mass fluxes in the nodes
			for (unsigned int j=0; j<m_network.m_nodes[i].m_elementIndexes.size(); ++j) {
				unsigned int feIndex = m_network.m_nodes[i].m_elementIndexes[j];
				// node is connected to all inflow and outflow elements
				if (!pattern.test(i + m_elementCount, feIndex))
					pattern.set(i + m_elementCount, feIndex);
			}
		}

		// set entry for reference pressure
		if (!pattern.test(m_pressureRefNodeIdx + m_elementCount, m_pressureRefNodeIdx + m_elementCount))
			pattern.set(m_pressureRefNodeIdx + m_elementCount, m_pressureRefNodeIdx + m_elementCount);

		// flow element equations
		for (unsigned int i=0; i<m_elementCount; ++i) {
			const Element &fe = m_network.m_elements[i];
			// we need mass flux for pressure loss calculatiopn
			if (!pattern.test(i, i))
				pattern.set(i, i);
			// element is connected to inlet and outlet node
			if (!pattern.test(i, fe.m_nodeIndexInlet + m_elementCount))
				pattern.set(i, fe.m_nodeIndexInlet + m_elementCount);
			if (!pattern.test(i, fe.m_nodeIndexOutlet + m_elementCount))
				pattern.set(i, fe.m_nodeIndexOutlet + m_elementCount);
		}

#endif

		// construct CSR pattern information
		std::vector<unsigned int> ia(n+1);
		std::vector<unsigned int> ja;

		for(unsigned int i = 0; i < n; ++i) {
			// get colors from pattern
			std::vector<unsigned int> cols;
			pattern.indexesPerRow(i, cols);
			IBK_ASSERT(!cols.empty());
			// store indexes
			ja.insert(ja.end(), cols.begin(), cols.end());
			// store offset
			ia[i + 1] = (unsigned int) ja.size();
		}

		// generate transpose indes
		std::vector<unsigned int> iaT;
		std::vector<unsigned int> jaT;
		IBKMK::SparseMatrixCSR::generateTransposedIndex(ia, ja, iaT, jaT);
		// resize jacobian
		m_sparseSolver.m_jacobian.resize(n, ja.size(), &ia[0], &ja[0], &iaT[0], &jaT[0]);

		// vector to hold colors associated with individual columns
		std::vector<unsigned int> colarray(n, 0);
		// array to flag used colors
		std::vector<unsigned int> scols(n+1); // must have size = m_n+1 since valid color numbers start with 1

		// loop over all columns
		for (unsigned int i=0; i<n; ++i) {

			// clear vector with neighboring colors
			std::fill(scols.begin(), scols.end(), 0);

			// loop over all rows, that have have entries in this column
			// Note: this currently only works for symmetric matricies
			unsigned int j;
			for (unsigned int jind = iaT[i]; jind < iaT[i + 1]; ++jind) {
				// j always holds a valid row number
				j = jaT[jind];

				// search all columns in this row < column i and add their colors to our "used color set" scol
				unsigned int k;
				for (unsigned int kind = ia[j]; kind < ia[j + 1]; ++kind) {
					k = ja[kind];

					// k now holds column number in row j
					if (k >= i && kind != 0) break; // stop if this column is > our current column i
					// retrieve color of column and mark color as used
					scols[ colarray[k] ] = 1;
				}
			}
			// search lowest unused color
			unsigned int colIdx = 1;
			for (; colIdx < n; ++colIdx)
				if (scols[colIdx] == 0)
					break;
			//IBK_ASSERT(colIdx != m_n); /// \todo check this, might fail when dense matrix is being used!!!
			// set this color number in our colarray
			colarray[i] = colIdx;
			// store color index in colors array
			if (m_sparseSolver.m_jacobianColors.size() < colIdx)
				m_sparseSolver.m_jacobianColors.resize(colIdx);
			m_sparseSolver.m_jacobianColors[colIdx-1].push_back(i); // associate column number with color
		}

		// initialize KLU
		klu_defaults(&m_sparseSolver.m_KLUParas);
		// use COLAMD method for reduced fill-ordering
		m_sparseSolver.m_KLUParas.ordering = 1;
		// setup synmbolic matrix factorization
		m_sparseSolver.m_KLUSymbolic = klu_analyze(n, (int*) (&ia[0]),
						   (int*) (&ja[0]), &(m_sparseSolver.m_KLUParas));
		// error may only occur if a wrong network topology was tolerated
		IBK_ASSERT(m_sparseSolver.m_KLUSymbolic != nullptr);
	}
}


int HydraulicNetworkModelImpl::jacobianSetup() {

	unsigned int n = m_nodeCount + m_elementCount;
	std::vector<double> Gy(n);

	// store G(y)
	std::copy(m_G.begin(), m_G.end(), Gy.begin());

	if (m_denseSolver.m_jacobian.n() > 0) {

		IBKMK::DenseMatrix &jacobian = m_denseSolver.m_jacobian;
		IBKMK::DenseMatrix &jacobianFac = m_denseSolver.m_jacobianFactorized;
		// loop over all variables
		for (unsigned int j=0; j<n; ++j) {
			// modify y_j by a small EPS
			double eps = std::fabs(m_y[j])*JACOBIAN_EPS_RELTOL + JACOBIAN_EPS_ABSTOL;
			// for mass fluxes, if y > eps, rather subtract the eps
			if (j > m_nodeCount && m_y[j] > eps)
				eps = -eps;
			m_y[j] += eps;
			// evaluate G(y_mod)
			updateG();
			// loop over all equations
			for (unsigned int i=0; i<n; ++i) {
				// now approximate dG_i/dy_j = [G_i(y_j+eps) - G_i(y_j)] / eps
				jacobian(i,j) = (m_G[i] - Gy[i])/eps;
			}
			// restore y
			m_y[j] -= eps;
		}
		// copy jacobian
		std::copy(jacobian.data().begin(), jacobian.data().end(),
				  jacobianFac.data().begin());
		// factorize matrix
		int res = jacobianFac.lu(); // Note: might be singular!!!
		// singular
		if( res != 0)
			return 1;
	}
	// we use a sparse jacobian representation
	else if(m_sparseSolver.m_jacobian.nnz() > 0) {
		IBKMK::SparseMatrixCSR &jacobian = m_sparseSolver.m_jacobian;
		const std::vector<std::vector<unsigned int> > &colors = m_sparseSolver.m_jacobianColors;

		IBK_ASSERT(!colors.empty());

		const unsigned int * iaIdxT = jacobian.iaT();
		const unsigned int * jaIdxT = jacobian.jaT();

		// process all colors individually and modify y in groups
		for (unsigned int i=0; i<colors.size(); ++i) {  // i == color index

			// modify m_yMod[] in all columns marked by color i
			for (unsigned int jind=0; jind<colors[i].size(); ++jind) {
				unsigned int j = colors[i][jind];
				// modify y_j by a small EPS
				double eps = std::fabs(m_y[j])*JACOBIAN_EPS_RELTOL + JACOBIAN_EPS_ABSTOL;
				// for mass fluxes, if y > eps, rather subtract the eps
				if (j > m_nodeCount && m_y[j] > eps)
					eps = -eps;
				m_y[j] += eps;
			}
			// evaluate G(y_mod)
			updateG();
			// compute Jacobian elements in groups
			for (unsigned int jind=0; jind<colors[i].size(); ++jind) {
				unsigned int j = colors[i][jind];
				// compute finite-differences column j in row i
				double eps = std::fabs(m_y[j])*JACOBIAN_EPS_RELTOL + JACOBIAN_EPS_ABSTOL;
				// for mass fluxes, if y > eps, rather subtract the eps
				if (j > m_nodeCount && m_y[j] > eps)
					eps = -eps;
				// we compute now all Jacobian elements in the column j
				for (unsigned int k = iaIdxT[j]; k < iaIdxT[j + 1]; ++k) {
					unsigned int rowIdx = jaIdxT[k];
					// now approximate dG_i/dy_j = [G_i(y_j+eps) - G_i(y_j)] / eps
					jacobian(rowIdx,j) = (m_G[rowIdx] - Gy[rowIdx])/eps;
				} // for k

			} // for jind

			// modify m_yMod[] in all columns marked by color i
			for (unsigned int jind=0; jind<colors[i].size(); ++jind) {
				unsigned int j = colors[i][jind];
				// modify y_j by a small EPS
				double eps = std::fabs(m_y[j])*JACOBIAN_EPS_RELTOL + JACOBIAN_EPS_ABSTOL;
				// for mass fluxes, if y > eps, rather subtract the eps
				if (j > m_nodeCount && m_y[j] > eps)
					eps = -eps;
				m_y[j] -= eps;
			}
		} // for i
		// calculate lu composition for klu object (creating a new pivit ordering)
		m_sparseSolver.m_KLUNumeric = klu_factor((int*) jacobian.ia(),
					(int*) jacobian.ja(),
					 jacobian.data(),
					 m_sparseSolver.m_KLUSymbolic,
					 &(m_sparseSolver.m_KLUParas));
		// error treatment: singular matrix
		if (m_sparseSolver.m_KLUNumeric == nullptr)
			return 1;
	}
	return 0;
}

void HydraulicNetworkModelImpl::jacobianMultiply(const std::vector<double> &b, std::vector<double> &res) {

	if(m_denseSolver.m_jacobian.n() > 0)
		m_denseSolver.m_jacobian.multiply(&b[0], &res[0]);
	else if(m_sparseSolver.m_jacobian.nnz() > 0)
		m_sparseSolver.m_jacobian.multiply(&b[0], &res[0]);
}


int HydraulicNetworkModelImpl::jacobianBacksolve(std::vector<double> & rhs) {

	// decide which matrix to use
	if(m_denseSolver.m_jacobian.n() > 0) {
		m_denseSolver.m_jacobianFactorized.backsolve(&rhs[0]);
	}
	else if(m_sparseSolver.m_jacobian.nnz() > 0) {
		IBK_ASSERT(m_sparseSolver.m_KLUNumeric != nullptr);
		IBK_ASSERT(m_sparseSolver.m_KLUSymbolic != nullptr);
		unsigned int n = m_nodeCount + m_elementCount;
		/* Call KLU to solve the linear system */
		int res = klu_tsolve(m_sparseSolver.m_KLUSymbolic,
				  m_sparseSolver.m_KLUNumeric,
				  (int) n, 1,
				  &rhs[0],
				  &(m_sparseSolver.m_KLUParas));
		// an error occured
		if(res == 0)
			return 1;
	}
	return 0;
}


void HydraulicNetworkModelImpl::jacobianWrite(std::vector<double> & rhs) {

	std::cout << "Jacobian:" << std::endl;

	if(m_denseSolver.m_jacobian.n() > 0)
		m_denseSolver.m_jacobian.write(std::cout, &rhs[0], false, 10);
	else if(m_sparseSolver.m_jacobian.nnz() > 0)
		m_sparseSolver.m_jacobian.write(std::cout, &rhs[0], false, 10);
}

#ifdef PRESSURES_FIRST

void HydraulicNetworkModelImpl::updateG() {

	// extract mass flows
	for (unsigned int i=0; i<m_elementCount; ++i) {
		m_massFluxes[i] = m_y[i+m_nodeCount]/MASS_FLUX_SCALE;
	}
	// first nodal equations
	for (unsigned int i=0; i<m_nodeCount; ++i) {
		m_nodePressures[i] = m_y[i];
		// set pressure of all inlets and outlets
		for(unsigned int idx : m_network.m_nodes[i].m_elementIndexesInlet) {
			if(m_massFluxes[idx] < 0) {
				m_outletPressures[idx] = m_nodalPressures[i];
			}
		}
		for(unsigned int idx : m_network.m_nodes[i].m_elementIndexesOutlet) {
			if(m_massFluxes[idx] >= 0) {
				m_outletPressures[idx] = m_nodalPressures[i];
			}
		}

		// now sum up all the mass fluxes in the nodes
		double massSum = 0;
		for (unsigned int j=0; j<m_network.m_nodes[i].m_elementIndexes.size(); ++j) {
			unsigned int feIndex = m_network.m_nodes[i].m_elementIndexes[j];
			const Element &fe = m_network.m_elements[ feIndex ];
			// if the flow element is connected to the node via inlet, the mass goes from node to flow element
			// and hence has a negative sign
			if (fe.m_nInlet == i)
				massSum -= m_massFluxes[feIndex];
			else
				massSum += m_massFluxes[feIndex]; // otherwise flux goes into the node -> positive sign
		}
		// store in system function vector
		m_G[i] = massSum*MASS_FLUX_SCALE; // we'll apply scaling here

	}

	// nodal constraint to reference node
	m_G[m_pressureRefNodeIdx] += m_nodePressures[m_pressureRefNodeIdx] - m_referencePressure; // 0 Pa on first node

	// now evaluate the flow system equations
	for (unsigned int i=0; i<m_elementCount; ++i) {
		const Element &fe = m_network.m_elements[i];
		m_G[m_nodeCount + i] = m_flowElements[i]->systemFunction( m_massFluxes[i], m_nodePressures[fe->m_nInlet], m_nodePressures[fe->m_nOutlet]);
	}

}

#else

void HydraulicNetworkModelImpl::updateG() {

	// extract mass flows
	for (unsigned int i=0; i<m_elementCount; ++i) {
		m_fluidMassFluxes[i] = m_y[i]/MASS_FLUX_SCALE;
	}
	// first nodal equations
	for (unsigned int i=0; i<m_nodeCount; ++i) {
		m_nodalPressures[i] = m_y[i + m_elementCount];

		// now sum up all the mass fluxes in the nodes
		double massSum = 0;
		for (unsigned int j=0; j<m_network.m_nodes[i].m_elementIndexes.size(); ++j) {
			unsigned int feIndex = m_network.m_nodes[i].m_elementIndexes[j];
			const Element &fe = m_network.m_elements[ feIndex ];
			// if the flow element is connected to the node via inlet, the mass goes from node to flow element
			// and hence has a negative sign
			if (fe.m_nodeIndexInlet == i)
				massSum -= m_fluidMassFluxes[feIndex];
			else
				massSum += m_fluidMassFluxes[feIndex]; // otherwise flux goes into the node -> positive sign
		}
		// store in system function vector
		m_G[i + m_elementCount] = massSum*MASS_FLUX_SCALE; // we'll apply scaling here

	}

	// nodal constraint to reference node
	m_G[m_pressureRefNodeIdx + m_elementCount] += m_nodalPressures[m_pressureRefNodeIdx] - m_referencePressure;

	// now evaluate the flow system equations
	for (unsigned int i=0; i<m_elementCount; ++i) {
		const Element &fe = m_network.m_elements[i];
		m_G[i] = m_flowElements[i]->systemFunction( m_fluidMassFluxes[i], m_nodalPressures[fe.m_nodeIndexInlet], m_nodalPressures[fe.m_nodeIndexOutlet]);
	}

}

#endif

} // namespace NANDRAD
