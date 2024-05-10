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

	/*! Defines the type of heat exchange */
	enum ModelType {
		T_TemperatureConstant,				// Keyword: TemperatureConstant			'Constant temperature'
		T_TemperatureSpline,				// Keyword: TemperatureSpline			'Time-dependent temperature'
		T_TemperatureSplineEvaporator,		// Keyword: TemperatureSplineEvaporator	'Heat pump evaporator mean temperature'
		T_TemperatureZone,					// Keyword: TemperatureZone				'Zone air temperature'
		T_TemperatureConstructionLayer,		// Keyword: TemperatureConstructionLayer 'Active construction layer (floor heating)'
		T_HeatLossConstant,					// Keyword: HeatLossConstant			'Constant heat loss'
		T_HeatLossSpline,					// Keyword: HeatLossSpline				'Time-dependent heat loss'
		/*! Heat loss from condenser is not the heat loss of the fluid, hence different parameter than T_HeatLossSpline. */
		T_HeatLossSplineCondenser,			// Keyword: HeatLossSplineCondenser		'Time-dependent heat pump heating demand'
		/*! Heating demand for space heating  */
		T_HeatingDemandSpaceHeating,		// Keyword: HeatingDemandSpaceHeating	'Heating demand for space heating'
		NUM_T
	};

	/*! Parameters for the element . */
	enum para_t {
		P_Temperature,							// Keyword: Temperature							[C]		'Temperature for heat exchange'
		P_HeatLoss,								// Keyword: HeatLoss							[W]		'Constant heat flux out of the element (heat loss)'
		P_ExternalHeatTransferCoefficient,		// Keyword: ExternalHeatTransferCoefficient		[W/m2K]	'External heat transfer coeffient for the outside boundary'
		P_HeatFlux,								// Keyword: HeatFlux							[W]			'TODO'
		P_FloorArea,							// Keyword: FloorArea							[m2]		'FloorArea'
		P_MaximumHeatingLoad,					// Keyword: MaximumHeatingLoad					[kW]		'MaximumHeatingLoad'
		P_HeatingEnergyDemand,					// Keyword: HeatingEnergyDemand					[kWh]		'HeatingEnergyDemand'
		P_HeatingEnergyDemandAreaSpecific,		// Keyword: HeatingEnergyDemandAreaSpecific		[kWh/m2]	'HeatingEnergyDemandAreaSpecific'
		P_MaximumCoolingLoad,					// Keyword: MaximumCoolingLoad					[kW]		'MaximumCoolingLoad'
		P_CoolingEnergyDemand,					// Keyword: CoolingEnergyDemand					[kWh]		'CoolingEnergyDemand'
		P_CoolingEnergyDemandAreaSpecific,		// Keyword: CoolingEnergyDemandAreaSpecific		[kWh/m2]	'CoolingEnergyDemandAreaSpecific'
		P_DomesticHotWaterDemand,				// Keyword: DomesticHotWaterDemand				[kWh]		'DomesticHotWaterDemand'
		P_DomesticHotWaterDemandAreaSpecific,	// Keyword: DomesticHotWaterDemandAreaRelated	[kWh/m2]	'DomesticHotWaterDemandAreaRelated'
		NUM_P
	};


	/*! Spline parameter as functions of time. Defined similarly as time series for location object (i.e. with start time shift). */
	enum splinePara_t {
		SPL_Temperature,						// Keyword: Temperature							[C]		'Temperature spline'
		/*! Heat loss spline is used for models T_HeatLossSpline and T_HeatLossSplineCondenser. */
		SPL_HeatLoss,							// Keyword: HeatLoss							[W]		'Heat flux spline'
		NUM_SPL
	};

	enum BuildingType {
		BT_ResidentialBuildingSingleFamily,		// Keyword: ResidentialBuildingSingleFamily		'Single Family House'
		BT_ResidentialBuildingMultiFamily,		// Keyword: ResidentialBuildingMultiFamily		'Multi Family House'
		BT_ResidentialBuildingLarge,			// Keyword: ResidentialBuildingLarge			'Large Residential Building'
		BT_OfficeBuilding,						// Keyword: OfficeBuilding						'Office Building'
		BT_UserDefineBuilding,					// Keyword: UserDefineBuilding					'User Defined Building'
		NUM_BT
	};

	enum AmbientTemperatureType {
		AT_UndisturbedSoilTemperature,			// Keyword: UndisturbedSoilTemperature			'Undisturbed Soil Temperature'
		AT_BoreholeHeatExchangerTemperature,	// Keyword: BoreholeHeatExchanger				'Borehole Heat Exchanger'
		AT_UserDefined,							// Keyword: UserDefined							'User Defined'
		NUM_AT
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE_OVERRIDE
	VICUS_COMP(NetworkHeatExchange)
	VICUS_COMPARE_WITH_ID

	ComparisonResult equal(const AbstractDBElement * other) const;

	void setDefaultValues(ModelType modelType);

	// *** Public Member variables ***

	/*! Model Type */
	ModelType							m_modelType		= NUM_T;					// XML:E

	bool								m_individualHeatFlux = false;				// XML:A

	bool								m_areaRelatedValues = false;				// XML:A

	bool								m_withCoolingDemand = true;					// XML:A

	bool								m_withDomesticHotWaterDemand = true;		// XML:A

	BuildingType						m_buildingType = NUM_BT;					// XML:A

	AmbientTemperatureType				m_ambientTemperatureType = NUM_AT;			// XML:A

	NANDRAD::LinearSplineParameter		m_userDefinedHeatFlux;						// XML:E

	/*! Parameters for the element . */
	IBK::Parameter						m_para[NUM_P];								// XML:E

	/*! Time-series of heat flux or temperature (can be spline or tsv-file). */
	NANDRAD::LinearSplineParameter		m_splPara[NUM_SPL];							// XML:E

	/*! IBK::Path to user defined tsv-file to be displayed in the plot */
	IBK::Path							m_userDefinedTsvFile;						// XML:E

};

} // namespace VICUS

#endif // VICUS_NETWORKHEATEXCHANGE_H
