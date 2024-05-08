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

#include "VICUS_NetworkHeatExchange.h"

#include "VICUS_KeywordList.h"

namespace VICUS {

AbstractDBElement::ComparisonResult NetworkHeatExchange::equal(const AbstractDBElement * other) const
{
	const NetworkHeatExchange * otherHeatExc = dynamic_cast<const NetworkHeatExchange*>(other);
	if (otherHeatExc == nullptr)
		return Different;

	if (otherHeatExc->m_modelType != m_modelType)
		return Different;

	//check parameters
	for (unsigned int i = 0; i < NetworkHeatExchange::NUM_T; ++i){
		// TODO
		//if (m_para[i] != otherHeatExc->m_para[i])
		//	return Different;
	}

	return Equal;
}

void NetworkHeatExchange::setDefaultValues(NetworkHeatExchange::ModelType modelType)
{
	m_modelType = modelType;
	switch(modelType){
		case T_HeatLossSpline:
		case T_HeatLossSplineCondenser: {
			if(m_buildingType == NUM_BT){
				m_buildingType = BT_ResidentialBuildingSingleFamily;
			}
			if(m_buildingType == BT_ResidentialBuildingSingleFamily) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 10);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 7500);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemandAreaSpecific, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 5);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 1200);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemandAreaSpecific, 8);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 150);
			} else if (m_buildingType == BT_ResidentialBuildingMultiFamily) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemandAreaSpecific, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemandAreaSpecific, 8);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			} else if (m_buildingType == BT_ResidentialBuildingLarge) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemandAreaSpecific, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemandAreaSpecific, 8);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			} else if (m_buildingType == BT_OfficeBuilding) {
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumHeatingLoad, 100);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemand, 50000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatingEnergyDemandAreaSpecific, 50);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_DomesticHotWaterDemand, 0);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_MaximumCoolingLoad, 25);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemand, 25000);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_CoolingEnergyDemandAreaSpecific, 8);
				KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_FloorArea, 1000);
			}
			break;
		}
		case T_HeatLossConstant: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_HeatLoss, 5);
			break;
		}
		case T_TemperatureSpline:
		{
			m_ambientTemperatureType = VICUS::NetworkHeatExchange::AT_UndisturbedSoilTemperature;
			break;
		}
		case T_TemperatureConstant: {
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_ExternalHeatTransferCoefficient, 5);
			KeywordList::setParameter(m_para, "NetworkHeatExchange::para_t", P_Temperature, 20);
			break;
		}
	}
}

} //namespace VICUS
