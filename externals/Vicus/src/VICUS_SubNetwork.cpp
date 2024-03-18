#include "VICUS_SubNetwork.h"

#include "VICUS_Project.h"
#include "VICUS_utilities.h"
#include "VICUS_BMBlock.h"
#include "VICUS_BMConnector.h"
#include "VICUS_BMSocket.h"
#include "VICUS_BMGlobals.h"

#include <QPixmap>

#include <NANDRAD_HydraulicNetworkElement.h>

namespace VICUS {

//TODO:: deprecated, needs rework
bool SubNetwork::isValid(const Database<NetworkComponent> &compDB,
						 const Database<NetworkController> &ctrlDB,
						 const Database<Schedule> &scheduleDB) const
{
	if (m_elements.empty())
		return false;

	for (const NetworkElement &e: m_elements) {
		// check if we have valid ids
		if (e.m_id == INVALID_ID ||
			e.m_componentId == INVALID_ID ||
			e.m_inletNodeId == INVALID_ID ||
			e.m_outletNodeId == INVALID_ID)
			return false;

		// check if the component exists in DB
		if (compDB[e.m_componentId] == nullptr)
			return false;
		if (!compDB[e.m_componentId]->isValid(scheduleDB))
			return false;
	}

	return true;
}

void SubNetwork::readXML(const TiXmlElement *element){
	readXMLPrivate(element);
	init();
}

TiXmlElement* SubNetwork::writeXML(TiXmlElement *parent) const {
	return writeXMLPrivate(parent);
}

void SubNetwork::init()
{
	for(auto &block : m_graphicalNetwork.m_blocks){
		bool ok;
		unsigned int number = block.m_name.toInt(&ok);
		// If we can convert the name to integer we have a "normal" component model block
		if(ok){
			NetworkElement element;
			for(auto elementTmp : m_elements){
				if(elementTmp.m_id == number){
					element = elementTmp;
					break;
				}
			}
			block.m_mode = BMBlockType::NetworkComponentBlock;
			block.m_displayName = element.m_displayName;
			block.m_componentId = element.m_componentId;
			block.m_size = QSizeF(BLOCK_WIDTH, BLOCK_HEIGHT);

			BMSocket inlet, outlet;

			inlet.m_name = INLET_NAME;
			inlet.m_isInlet = true;
			inlet.m_id = element.m_inletNodeId;
			inlet.m_orientation = Qt::Horizontal;
			inlet.m_pos = QPointF(0, BLOCK_HEIGHT / 2);
			block.m_sockets.append(inlet);

			outlet.m_name = OUTLET_NAME;
			outlet.m_isInlet = false;
			outlet.m_id = element.m_outletNodeId;
			outlet.m_orientation = Qt::Horizontal;
			outlet.m_pos = QPointF(BLOCK_WIDTH, BLOCK_HEIGHT / 2);
			block.m_sockets.append(outlet);
		}
		// Do we have a connector block?
		else if (block.m_name.contains(CONNECTORBLOCK_NAME)) {
			block.m_displayName = "";
			block.m_mode = BMBlockType::ConnectorBlock;
			block.m_size = QSizeF(CONNECTORBLOCK_WIDTH, CONNECTORBLOCK_HEIGHT);
			BMSocket inlet, outlet;

			inlet.m_name = INLET_NAME;
			inlet.m_isInlet = true;
			inlet.m_id = block.m_name.split(CONNECTORBLOCK_NAME)[1].toInt();
			inlet.m_orientation = Qt::Horizontal;
			inlet.m_pos = QPointF(0, CONNECTORBLOCK_HEIGHT / 2);
			block.m_sockets.append(inlet);

			outlet.m_name = OUTLET_NAME;
			outlet.m_isInlet = false;
			outlet.m_id = inlet.m_id;
			outlet.m_orientation = Qt::Horizontal;
			outlet.m_pos = QPointF(CONNECTORBLOCK_WIDTH, CONNECTORBLOCK_HEIGHT / 2);
			block.m_sockets.append(outlet);
		}
		// Do we have a global inlet?
		else if(block.m_name.contains(SUBNETWORK_INLET_NAME)){
			block.m_size = QSizeF(ENTRANCEEXITBLOCK_WIDTH, ENTRANCEEXITBLOCK_HEIGHT);
			block.m_mode = BMBlockType::GlobalInlet;
			block.m_displayName.clear();
			BMSocket outlet;
			outlet.m_name = OUTLET_NAME;
			outlet.m_isInlet = false;
			outlet.m_id = ENTRANCE_ID;
			outlet.m_orientation = Qt::Horizontal;
			outlet.m_pos = QPointF(ENTRANCEEXITBLOCK_WIDTH, ENTRANCEEXITBLOCK_HEIGHT / 2);
			block.m_sockets.append(outlet);
		}
		// Do we have a global outlet?
		else if(block.m_name.contains(SUBNETWORK_OUTLET_NAME)){
			block.m_size = QSizeF(ENTRANCEEXITBLOCK_WIDTH, ENTRANCEEXITBLOCK_HEIGHT);
			block.m_mode = BMBlockType::GlobalOutlet;
			block.m_displayName.clear();
			BMSocket inlet;
			inlet.m_name = INLET_NAME;
			inlet.m_isInlet = true;
			inlet.m_id = EXIT_ID;
			inlet.m_orientation = Qt::Horizontal;
			inlet.m_pos = QPointF(0, ENTRANCEEXITBLOCK_HEIGHT / 2);
			block.m_sockets.append(inlet);
		}
	}
}


AbstractDBElement::ComparisonResult SubNetwork::equal(const AbstractDBElement *other) const {
	const SubNetwork * otherSub = dynamic_cast<const SubNetwork*>(other);
	if (otherSub == nullptr)
		return Different;

	if (m_elements.size() != otherSub->m_elements.size())
		return Different;

	for (unsigned int i=0; i<m_elements.size(); ++i){
		if (m_elements[i] != otherSub->m_elements[i])
			return Different;
	}

	if (m_displayName != other->m_displayName)
		return Different;

	//check meta data
	if (m_color != otherSub->m_color)
		return OnlyMetaDataDiffers;

	return Equal;
}

SubNetwork::heatExchangeComponentStruct SubNetwork::heatExchangeComponent() const
{
	int counter = 0;
	NetworkHeatExchange::ModelType modelTypeToReturn;
	heatExchangeComponentStruct heatExchangeComponentToReturn;
	for(const NetworkComponent& component : m_components){
		if(component.m_heatExchange.m_modelType != NetworkHeatExchange::NUM_T){
			counter++;
			if(counter != 1) break;
			heatExchangeComponentToReturn.component = component;
		}
	}

	if(counter == 0){
		heatExchangeComponentToReturn.status = heatExchangeReturnStatus::RS_None;
	} else if (counter == 1){
		heatExchangeComponentToReturn.status = heatExchangeReturnStatus::RS_Unique;
	} else {
		heatExchangeComponentToReturn.status = heatExchangeReturnStatus::RS_TooMany;
	}

	return heatExchangeComponentToReturn;
}

} // namespace VICUS
