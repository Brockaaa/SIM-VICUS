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

#ifndef VICUS_NetworkComponentH
#define VICUS_NetworkComponentH

#include <map>

#include <QCoreApplication> // for tr functions

#include <IBK_MultiLanguageString.h>
#include <IBK_Parameter.h>
#include <IBK_IntPara.h>

#include <QColor>

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"
#include "VICUS_AbstractDBElement.h"
#include "VICUS_Database.h"
#include "VICUS_Schedule.h"
#include "VICUS_NetworkController.h"
#include "VICUS_NetworkHeatExchange.h"

#include <NANDRAD_HydraulicNetworkComponent.h>

namespace VICUS {

/*! Data model object for network components, basically the same as NANDRAD::HydraulicNetworkComponent with
	data members needed in the user interface.

	We cannot use inheritence here, but since both objects are very similar it should be easy to copy/paste back
	and forth between objects.
*/
class NetworkComponent : public AbstractDBElement {
	Q_DECLARE_TR_FUNCTIONS(NetworkComponent)
public:

	NetworkComponent() = default;

	/*! The various types (equations) of the hydraulic component. */
	enum ModelType {
		MT_SimplePipe,						// Keyword: SimplePipe						'Simple pipe with single fluid volume'
		MT_DynamicPipe,						// Keyword: DynamicPipe						'Detailled pipe with discretized fluid volume'
		MT_ConstantPressurePump,			// Keyword: ConstantPressurePump			'Pump with constant pressure head'
		MT_ConstantMassFluxPump,			// Keyword: ConstantMassFluxPump			'Pump with defined mass flux'
		MT_ControlledPump,					// Keyword: ControlledPump					'Pump with controlled pressure head'
		MT_VariablePressurePump,			// Keyword: VariablePressurePump			'Pump with linear pressure head'
		MT_HeatExchanger,					// Keyword: HeatExchanger					'Simple heat exchanger'
		MT_HeatPumpVariableIdealCarnotSourceSide,	// Keyword: HeatPumpVariableIdealCarnotSourceSide	'Simple heat pump installed at evaporator (source) side, based on carnot efficiency'
		MT_HeatPumpVariableIdealCarnotSupplySide,	// Keyword: HeatPumpVariableIdealCarnotSupplySide	'Simple heat pump installed at condenser (supply) side, based on carnot efficiency'
		MT_HeatPumpVariableSourceSide,		// Keyword: HeatPumpVariableSourceSide		'Detailled heat pump installed at evaporator (source) side, based on polynom for COP'
		MT_HeatPumpOnOffSourceSide,			// Keyword: HeatPumpOnOffSourceSide			'Detailled heat pump (on-off) at evaporator (source) source side, based on polynoms for heating power and el. power'
//		xMT_HeatPumpOnOffSourceSideWithBuffer,	// xKeyword: HeatPumpOnOffSourceSideWithBuffer			'On-off-type heat pump based on polynoms for heating power and el. power, installed at source side'
		MT_ControlledValve,					// Keyword: ControlledValve					'Controlled valve'
		MT_ConstantPressureLossValve,		// Keyword: ConstantPressureLossValve		'Valve with constant pressure loss'
		MT_IdealHeaterCooler,				// Keyword: IdealHeaterCooler				'Ideal heater with predefined supply temperature'
		MT_PressureLossElement,				// Keyword: PressureLossElement				'Adiabatic element with pressure loss defined by zeta-value'
		NUM_MT
	};

	/*! Parameters for the component. */
	enum para_t {
		// from NANDRAD::HydraulicNetworkComponent
		P_HydraulicDiameter,					// Keyword: HydraulicDiameter					[mm]	'Hydraulic diameter'
		P_PressureLossCoefficient,				// Keyword: PressureLossCoefficient				[---]	'Pressure loss coefficient (zeta)'
		P_PressureHead,							// Keyword: PressureHead						[Bar]	'Predefined pressure head'
		P_MassFlux,								// Keyword: MassFlux							[kg/s]	'Predefined mass flux'
		P_PumpMaximumEfficiency,				// Keyword: PumpMaximumEfficiency				[---]	'Efficiency in optimal operation'
		P_FractionOfMotorInefficienciesToFluidStream,	// Keyword: FractionOfMotorInefficienciesToFluidStream	[---]	'Fraction of losses that heats up fluid'
		P_MaximumPressureHead,					// Keyword: MaximumPressureHead					[Bar]	'Maximum pressure head at minimal mass flow'
		P_PumpMaximumElectricalPower,			// Keyword: PumpMaximumElectricalPower			[kW]	'Maximum electrical power at optimal operation'
		P_DesignPressureHead,					// Keyword: DesignPressureHead					[Bar]	'Design pressure head'
		P_DesignMassFlux,						// Keyword: DesignMassFlux						[kg/s]	'Design mass flux'
		P_PressureHeadReductionFactor,			// Keyword: PressureHeadReductionFactor			[---]	'Pressure head reduction at zero mass flux'
		P_Volume,								// Keyword: Volume								[m3]	'Volume'
		P_PipeMaxDiscretizationWidth,			// Keyword: PipeMaxDiscretizationWidth			[m]		'Discretization length'
		P_CarnotEfficiency,						// Keyword: CarnotEfficiency					[---]	'Carnot effectiveness'
		P_MaximumHeatingPower,					// Keyword: MaximumHeatingPower					[kW]	'Maximum heating power'
		P_MaximumCoolingPower,					// Keyword: MaximumCoolingPower					[kW]	'Maximum cooling power'
		P_PressureLoss,							// Keyword: PressureLoss						[Bar]	'Pressure loss'
		P_MinimumOutletTemperature,				// Keyword: MinimumOutletTemperature			[C]		'Minimum outlet temperature'
		P_HeatingPowerB0W35,					// Keyword: HeatingPowerB0W35					[kW]	'Heat pump heating power at B0/W35
		P_HeatingBufferSupplyTemperature,		// Keyword: HeatingBufferSupplyTemperature		[C]		'Heat pump supply temperature for heating buffer storage'
		P_HeatingBufferReturnTemperature,		// Keyword: HeatingBufferReturnTemperature		[C]		'Heat pump return temperature for heating buffer storage'
		P_DHWBufferSupplyTemperature,			// Keyword: DHWBufferSupplyTemperature			[C]		'Heat pump supply temperature for DHW buffer storage'
		P_DHWBufferReturnTemperature,			// Keyword: DHWBufferReturnTemperature			[C]		'Heat pump return temperature for DHW buffer storage'
		P_HeatingBufferVolume,					// Keyword: HeatingBufferVolume					[l]		'Heat pump heating buffer storage volume'
		P_DHWBufferVolume,						// Keyword: DHWBufferVolume						[l]		'Heat pump DHW buffer storage volume'
		// additional parameters
		P_PipeLength,							// Keyword: PipeLength							[m]		'Length of pipe'
		NUM_P
	};

	/*! Whole number parameters. */
	enum intPara_t {
		IP_NumberParallelPipes,					// Keyword: NumberParallelPipes				[---]	'Number of parallel pipes'
		IP_NumberParallelElements,				// Keyword: NumberParallelElements			[---]	'Number of parallel elements'
		NUM_IP
	};

	/*! Categories in SubnetworkEditDialog */
	enum ComponentCategory{
		CC_Pipes,                                      // Keyword: Pipes
		CC_Pumps,                                      // Keyword: Pumps
		CC_Heatpumps,                                  // Keyword: Heatpumps
		CC_Other,                                      // Keyword: Other
		NUM_CC
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE_OVERRIDE
	VICUS_COMP(NetworkComponent)
	VICUS_COMPARE_WITH_ID

	/*! Checks if all parameters are valid. */
	bool isValid(const Database<Schedule> &scheduleDB) const;

	/*! Comparison operator */
	ComparisonResult equal(const AbstractDBElement *other) const override;

	/*! returns the NANDRAD::HydraulicNetworkComponent parameters which may deviates from the VICUS one as we use the VICUS model
	 * for GUI and preprocessing */
	void nandradNetworkComponentParameter(IBK::Parameter *para) const;


	// *** Static Functions

	static std::vector<std::string> requiredScheduleNames(const ModelType modelType);

	/*! returns the NANDRAD::HydraulicNetworkComponent ModelType which may deviates from the VICUS one as we use the VICUS model
	 * for GUI and preprocessing */
	static NANDRAD::HydraulicNetworkComponent::ModelType nandradNetworkComponentModelType(ModelType modelType);

	/*! returns additional required parameters, not included in NANDRAD::HydraulicNetworkComponent */
	static std::vector<unsigned int> additionalRequiredParameter(const ModelType modelType);

	/*! returns optional parameters for the given model type */
	static std::vector<unsigned int> optionalParameter(const ModelType modelType);

	/*! returns additional required parameters */
	static std::vector<unsigned int> requiredIntParameter(const ModelType modelType);

	/*! Function that provides a list of possible controlled properties depending on the given model type. */
	static std::vector<VICUS::NetworkController::ControlledProperty> availableControlledProperties(const ModelType modelType);

	/*! checks additional required parameters, not included in NANDRAD::HydraulicNetworkComponent */
	static void checkAdditionalParameter(const IBK::Parameter &para, const unsigned int numPara);

	/*! checks required integer parameters */
	static void checkIntParameter(const IBK::IntPara &para, const unsigned int numPara);

	static bool hasPipeProperties(const ModelType modelType);


	// Helper function to get iconFile from ModelType
	static QString iconFileFromModelType(VICUS::NetworkComponent::ModelType modelType);

	// Helper function to get NetComCategory from ModelType
	static ComponentCategory componentCategoryFromModelType(VICUS::NetworkComponent::ModelType modelType);

	// Returns which heat exchanger types you can use with a given NetworkComponent type
	static std::vector<VICUS::NetworkHeatExchange::ModelType> availableHeatExchangeTypes(const VICUS::NetworkComponent::ModelType modelType);

	static QString detailledModelName(ModelType modelType);

	// *** PUBLIC MEMBER VARIABLES added for VICUS ***Simple

	//:inherited	unsigned int					m_id = INVALID_ID;					// XML:A:required
	//:inherited	IBK::MultiLanguageString		m_displayName;						// XML:A
	//:inherited	QColor							m_color;							// XML:A

	/*! Notes. */
	IBK::MultiLanguageString			m_notes;										// XML:E

	/*! Manufacturer. */
	IBK::MultiLanguageString			m_manufacturer;									// XML:E

	/*! Data source. */
	IBK::MultiLanguageString			m_dataSource;									// XML:E

	/*! Schedules for this component */
	std::vector<unsigned int>			m_scheduleIds;									// XML:E

	/*! Integer parameters. */
	IBK::IntPara						m_intPara[NUM_IP];								// XML:E

	/*! Reference id fo pipe properties for e.g. the GroundHeatExchanger model */
	IDType								m_pipePropertiesId = INVALID_ID;				// XML:E


	// *** PUBLIC MEMBER VARIABLES from NANDRAD::HydraulicNetworkComponent (without m_displayName) ***


	/*! Model type. */
	ModelType							m_modelType		= NUM_MT;						// XML:A:required

	/*! Parameters of the flow component. */
	IBK::Parameter						m_para[NUM_P];									// XML:E

	/*! Array parameters of the flow component */
	NANDRAD::DataTable					m_polynomCoefficients;							// XML:E

	/*! Network Controller of NetworkComponent */
	VICUS::NetworkController			m_networkController;							// XML:E

	/*! Heat Exchange Component of NetworkComponent */
	VICUS::NetworkHeatExchange			m_heatExchange;									// XML:E

};

} // namespace VICUS


#endif // VICUS_NetworkComponentH
