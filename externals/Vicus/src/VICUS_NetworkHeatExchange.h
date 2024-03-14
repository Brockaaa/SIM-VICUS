/*	The SIM-VICUS data model library.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This library is part of SIM-VICUS (https:/gfx/modeltypeicons//github.com/ghorwin/SIM-VICUS)

	This library is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef VICUS_NETWORKHEATEXCHANGE_H
#define VICUS_NETWORKHEATEXCHANGE_H

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"
#include "VICUS_AbstractDBElement.h"

#include "NANDRAD_LinearSplineParameter.h"

#include <IBK_Parameter.h>

namespace VICUS {

/*! Encapsulates all data defining heat exchange between flow elements and
	the environment or other models/elements.

	Definition of heat exchange is done in each flow element definition. If missing, the flow
	element is treated as adiabat.
*/
class NetworkHeatExchange : AbstractDBElement
{
public:
	NetworkHeatExchange() = default;

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE_OVERRIDE
	VICUS_COMP(NetworkHeatExchange)
	VICUS_COMPARE_WITH_ID

	ComparisonResult equal(const AbstractDBElement * other) const;

	struct HeatFluxSplineAttributesNotUserDefinedBuilding {
		IBK::Parameter		floorArea;
		IBK::Parameter		maximumHeatingLoad;
		IBK::Parameter		heatingEnergyDemand;
		IBK::Parameter		heatingAreaDemandAreaSpecific;
		IBK::Parameter		maximumCoolingLoad;
		IBK::Parameter		coolingEnergyDemand;
		IBK::Parameter		coolingEnergyDemandAreaSpecific;
		IBK::Parameter		domesticHotWaterDemand;
	};

	/*! Defines the type of heat exchange */
	enum ModelType {
		T_TemperatureConstant,				// Keyword: TemperatureConstant			'Constant temperature'
		T_TemperatureSpline,				// Keyword: TemperatureSpline			'Time-dependent temperature from spline'
		T_TemperatureSplineEvaporator,		// Keyword: TemperatureSplineEvaporator	'Evaporator medium temperature for heat pump'
		T_TemperatureZone,					// Keyword: TemperatureZone				'Zone air temperature'
		T_TemperatureConstructionLayer,		// Keyword: TemperatureConstructionLayer 'Active construction layer (floor heating)'
		T_HeatLossConstant,					// Keyword: HeatLossConstant			'Constant heat loss'
		T_HeatLossSpline,					// Keyword: HeatLossSpline				'Heat loss from spline'
		/*! Heat loss from condenser is not the heat loss of the fluid, hence different parameter than T_HeatLossSpline. */
		T_HeatLossSplineCondenser,			// Keyword: HeatLossSplineCondenser		'Heat loss of condenser in heat pump model'
		/*! Heating demand for space heating  */
		T_HeatingDemandSpaceHeating,		// Keyword: HeatingDemandSpaceHeating	'Heating demand for space heating'
		NUM_T
	};

	/*! Parameters for the element . */
	enum para{
		PT_Temperature,							// Keyword: Temperature							[C]			'Temperature for heat exchange'
		PT_HeatLoss,							// Keyword: HeatLoss							[W]			'Constant heat flux out of the element (heat loss)'
		PT_ExternalHeatTransferCoefficient,		// Keyword: ExternalHeatTransferCoefficient		[W/m2K]		'External heat transfer coeffient for the outside boundary'
		SPL_Temperature,						// Keyword: Temperature							[C]			'Temperature for heat exchange'
		SPL_HeatLoss,							// Keyword: HeatLoss							[W]			'Constant heat flux out of the element (heat loss)'
		HFC_HeatFlux,							// Keyword: HeatFlux							[W]			'TODO'
		HFS_FloorArea,							// Keyword: FloorArea							[m2]		'FloorArea'
		HFS_MaximumHeatingLoad,					// Keyword: MaximumHeatingLoad					[kW]		'MaximumHeatingLoad'
		HFS_HeatingEnergyDemand,				// Keyword: HeatingEnergyDemand					[kWh]		'HeatingEnergyDemand'
		HFS_HeatingEnergyDemandAreaSpecific,	// Keyword: HeatingEnergyDemandAreaSpecific		[kWh/m2]	'HeatingEnergyDemandAreaSpecific'
		HFS_MaximumCoolingLoad,					// Keyword: MaximumCoolingLoad					[kW]		'MaximumCoolingLoad'
		HFS_CoolingEnergyDemand,				// Keyword: CoolingEnergyDemand					[kWh]		'CoolingEnergyDemand'
		HFS_CoolingEnergyDemandAreaSpecific,	// Keyword: CoolingEnergyDemandAreaSpecific		[kWh/m2]	'CoolingEnergyDemandAreaSpecific'
		HFS_DomesticHotWaterDemand,				// Keyword: DomesticHotWaterDemand				[kWh]		'DomesticHotWaterDemand'
		HFS_DomesticHotWaterDemandAreaSpecific,	// Keyword: DomesticHotWaterDemandAreaRelated	[kWh]		'DomesticHotWaterDemandAreaRelated'
		NUM_P
	};

	enum BuildingType {
		BT_SingleFamilyHouse,
		BT_MultiHouseFamily,
		BT_OfficeBuilding,
		BT_UserDefineBuilding,
		NUM_BT
	};

	// *** Public Member variables ***

	/*! Model Type */
	ModelType							m_modelType		= NUM_T;					// XML:E

	bool								m_individualHeatFlux = false;				// XML:A

	BuildingType						m_buildingType = NUM_BT;					// XML:A

	NANDRAD::LinearSplineParameter		m_userDefinedHeatFlux;

	/*! Parameters for the element . */
	IBK::Parameter						m_para[NUM_P];								// XML:E
};

} // namespace VICUS

#endif // VICUS_NETWORKHEATEXCHANGE_H
