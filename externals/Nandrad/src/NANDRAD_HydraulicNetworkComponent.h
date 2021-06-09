/*	The NANDRAD data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

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

#ifndef NANDRAD_HydraulicNetworkComponentH
#define NANDRAD_HydraulicNetworkComponentH

#include <IBK_Parameter.h>

#include "NANDRAD_CodeGenMacros.h"
#include "NANDRAD_Constants.h"
#include "NANDRAD_LinearSplineParameter.h"


namespace NANDRAD {

/*! Parameters for a hydraulic component for the network. */
class HydraulicNetworkComponent {
public:

	/*! The various types (equations) of the hydraulic component. */
	enum ModelType {
		MT_SimplePipe,						// Keyword: SimplePipe						'Pipe with a single fluid volume and with heat exchange'
		MT_DynamicPipe,						// Keyword: DynamicPipe						'Pipe with a discretized fluid volume and heat exchange'
		MT_ConstantPressurePump,			// Keyword: ConstantPressurePump			'Pump with constant/externally defined pressure'
		MT_ControlledPump,					// Keyword: ControlledPump					'Pump with pressure head controlled based on flow controller'
		MT_HeatExchanger,					// Keyword: HeatExchanger					'Simple heat exchanger with given heat flux'
		MT_HeatPumpIdealCarnotSourceSide,	// Keyword: HeatPumpIdealCarnotSourceSide	'Heat pump with variable heating power based on carnot efficiency, installed at source side (collector cycle)'
		MT_HeatPumpIdealCarnotSupplySide,	// Keyword: HeatPumpIdealCarnotSupplySide	'Heat pump with variable heating power based on carnot efficiency, installed at supply side'
//		MT_HeatPumpReal,					// xKeyword: HeatPumpReal					'On-off-type heat pump with based on manufacturer data sheet'
		MT_ControlledValve,					// Keyword: ControlledValve					'Valve with associated control model'
		NUM_MT
	};

	/*! Parameters for the component. */
	enum para_t {
		P_HydraulicDiameter,					// Keyword: HydraulicDiameter					[mm]	'Only used for pressure loss calculation with PressureLossCoefficient (NOT for pipes)'
		P_PressureLossCoefficient,				// Keyword: PressureLossCoefficient				[---]	'Pressure loss coefficient for the component (zeta-value)'
		P_PressureHead,							// Keyword: PressureHead						[Pa]	'Pressure head for a pump'
		P_PumpEfficiency,						// Keyword: PumpEfficiency						[---]	'Pump efficiency'
		P_FractionOfMotorInefficienciesToFluidStream,	// Keyword: FractionOfMotorInefficienciesToFluidStream	[---]	'Fraction of pump heat loss due to inefficiency that heats up the fluid'
		P_Volume,								// Keyword: Volume								[m3]	'Water or air volume of the component'
		P_PipeMaxDiscretizationWidth,			// Keyword: PipeMaxDiscretizationWidth			[m]		'Maximum width of discretized volumes in pipe'
		P_CarnotEfficiency,						// Keyword: CarnotEfficiency					[---]	'Carnot efficiency eta'
		P_MaximumHeatingPower,					// Keyword: MaximumHeatingPower					[W]		'Maximum heating power'
		NUM_P
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	NANDRAD_READWRITE
	NANDRAD_COMPARE_WITH_ID
	NANDRAD_COMP(HydraulicNetworkComponent)

	/*! Compares two component definitions by parameters only, without comparing ID. */
	bool sameParametersAs(const HydraulicNetworkComponent & other) const;

	/*! Checks for valid and required parameters (value ranges).
		\param networkModelType Type of network calculation model (HydraulicNetwork::ModelType).
	*/
	void checkParameters(int networkModelType);

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Unique ID for this component. */
	unsigned int					m_id			= NANDRAD::INVALID_ID;				// XML:A:required

	/*! Display name. */
	std::string						m_displayName;										// XML:A

	/*! Model type. */
	ModelType						m_modelType		= NUM_MT;							// XML:A:required

	/*! Parameters of the flow component. */
	IBK::Parameter					m_para[NUM_P];										// XML:E

	// *** STATIC FUNCTIONS ***

	/*! Needed both in user interface and for valid parameter checking in solver.
		\param networkModelType Identifies network model (HydraulicNetwork::ModelType).
	*/
	static std::vector<unsigned int> requiredParameter(const ModelType modelType, int networkModelType);

	/*! Helper function that implements specific rules for testing a single parameter.
		This is useful if the same parameter is used by several models and we want to avoid implementing
		the same checking rule multiple times.
		Is used in Nandrad as well as in the graphical user interface.
	*/
	static void checkModelParameter(const IBK::Parameter &para, const unsigned int numPara);

};

} // namespace NANDRAD

#endif // NANDRAD_HydraulicNetworkComponentH
