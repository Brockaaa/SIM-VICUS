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

namespace VICUS {

std::vector<VICUS::NetworkHeatExchange::ModelType> VICUS::NetworkHeatExchange::availableHeatExchangeTypes(const NetworkComponent::ModelType modelType)
{
	// some models may be adiabatic, hence we also return NUM_T as available heat exchange type
	switch (modelType) {
		case NetworkComponent::MT_SimplePipe:
			return {NUM_T, T_TemperatureConstant, T_TemperatureSpline, T_HeatLossConstant, T_HeatLossSpline, T_TemperatureZone, T_TemperatureConstructionLayer};
		case NetworkComponent::MT_DynamicPipe:
			return {NUM_T, T_TemperatureConstant, T_TemperatureSpline, T_TemperatureZone, T_TemperatureConstructionLayer};
		case NetworkComponent::MT_HeatPumpVariableIdealCarnotSourceSide:
		case NetworkComponent::MT_HeatPumpVariableSourceSide:
			return {T_HeatLossSplineCondenser};  // must not be adiabatic
			//		case NetworkComponent::MT_HeatPumpOnOffSourceSideWithBuffer:
			//			return {T_HeatingDemandSpaceHeating};  // must not be adiabatic
		case NetworkComponent::MT_HeatExchanger:
			return {T_HeatLossConstant, T_HeatLossSpline}; // must not be adiabatic
		case NetworkComponent::MT_HeatPumpVariableIdealCarnotSupplySide:
		case NetworkComponent::MT_ConstantPressurePump:
		case NetworkComponent::MT_ConstantMassFluxPump:
		case NetworkComponent::MT_VariablePressurePump:
		case NetworkComponent::MT_ControlledPump:
		case NetworkComponent::MT_ControlledValve:
		case NetworkComponent::MT_HeatPumpOnOffSourceSide:
		case NetworkComponent::MT_IdealHeaterCooler:
		case NetworkComponent::MT_ConstantPressureLossValve:
		case NetworkComponent::MT_PressureLossElement:
			return {NUM_T};
		case NetworkComponent::NUM_MT: ; // just to make compiler happy
	}
	return {};
}

} //namespace VICUS
