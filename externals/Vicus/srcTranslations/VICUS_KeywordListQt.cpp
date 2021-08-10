/*	The NANDRAD data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#include "VICUS_KeywordListQt.h"

namespace VICUS {
KeywordListQt::KeywordListQt() {

	tr("Outside wall construction");
	tr("Outside wall construction in contact with ground");
	tr("Interior construction");
	tr("Floor to basement");
	tr("Floor in contact with air");
	tr("Floor in contact with ground");
	tr("Ceiling construction");
	tr("Sloped roof construction");
	tr("Flat roof construction");
	tr("Flat roof construction (to heated/insulated space)");
	tr("Flat roof construction (to cold/ventilated space)");
	tr("Some other component type");
	tr("Outside wall construction");
	tr("Outside wall construction in contact with ground");
	tr("Interior construction");
	tr("Floor to basement");
	tr("Floor in contact with ground");
	tr("Ceiling construction");
	tr("Sloped roof construction");
	tr("Flat roof construction");
	tr("Miscellaneous");
	tr("Not insulated");
	tr("Inside insulated");
	tr("Core insulation");
	tr("Outside insulated");
	tr("Not selected");
	tr("Brick masonry");
	tr("Natural stones");
	tr("Concrete");
	tr("Wood");
	tr("Frame construction");
	tr("Loam");
	tr("Not selected");
	tr("Dry density of the material.");
	tr("Global Warming Potential.");
	tr("Depletion potential of the stratospheric ozone layer.");
	tr("Photochemical Ozone Creation Potential.");
	tr("Acidification potential.");
	tr("Eutrophication potential.");
	tr("Total use of non-renewable primary energy resources.");
	tr("Total use of renewable primary energy resources .");
	tr("Air change rate");
	tr("Shielding coefficient for n50 value");
	tr("normal");
	tr("n50");
	tr("Constant heat exchange coefficient");
	tr("No convective heat exchange");
	tr("Standard");
	tr("Constant");
	tr("Scheduled");
	tr("Convective heat transfer coefficient");
	tr("Constant temperature of other zone/ground");
	tr("Person count");
	tr("Person per area");
	tr("Area per person");
	tr("Power");
	tr("Power per area");
	tr("Convective heat factor");
	tr("Latent heat factor");
	tr("Loss heat factor");
	tr("Person");
	tr("ElectricEquiment");
	tr("Lighting");
	tr("Other");
	tr("Person per m2");
	tr("m2 per Person");
	tr("Person count");
	tr("Power per area");
	tr("Power");
	tr("Some temperatures");
	tr("Some mass");
	tr("Dry density of the material.");
	tr("Specific heat capacity of the material.");
	tr("Thermal conductivity of the dry material.");
	tr("Vapor diffusion resistance factor.");
	tr("Water content in relation to 80% humidity.");
	tr("Water content at saturation.");
	tr("Coating");
	tr("Plaster");
	tr("Bricks");
	tr("NaturalStones");
	tr("Cementitious");
	tr("Insulations");
	tr("BuildingBoards");
	tr("Woodbased");
	tr("NaturalMaterials");
	tr("Soils");
	tr("CladdingSystems");
	tr("Foils");
	tr("Miscellaneous");
	tr("Only Hydraulic calculation with constant temperature");
	tr("Thermo-hydraulic calculation");
	tr("SinglePipe");
	tr("DoublePipe");
	tr("Temperature for pipe dimensioning algorithm");
	tr("Temperature difference for pipe dimensioning algorithm");
	tr("Maximum pressure loss for pipe dimensioning algorithm");
	tr("Reference pressure applied to reference element");
	tr("Fluid temperature for hydraulic calculation, else initial temperature");
	tr("Initial Fluid temperature for thermo-hydraulic calculation");
	tr("Maximum discretization step for dynamic pipe model");
	tr("Pipe with a single fluid volume and with heat exchange");
	tr("Pipe with a discretized fluid volume and heat exchange");
	tr("Pump with constant/externally defined pressure");
	tr("Pump with constant/externally defined mass flux");
	tr("Pump with pressure head controlled based on flow controller");
	tr("Simple heat exchanger with given heat flux");
	tr("Heat pump with variable heating power based on carnot efficiency, installed at source side (collector cycle)");
	tr("Heat pump with variable heating power based on carnot efficiency, installed at supply side");
	tr("On-off-type heat pump based on polynoms, installed at source side");
	tr("Valve with associated control model");
	tr("Ideal heat exchange model that provides a defined supply temperature to the network and calculates the heat loss/gain");
	tr("Valve with constant pressure loss");
	tr("Only used for pressure loss calculation with PressureLossCoefficient (NOT for pipes)");
	tr("Pressure loss coefficient for the component (zeta-value)");
	tr("Pressure head for a pump");
	tr("Pump predefined mass flux");
	tr("Pump efficiency");
	tr("Fraction of pump heat loss due to inefficiency that heats up the fluid");
	tr("Water or air volume of the component");
	tr("Maximum width/length of discretized volumes in pipe");
	tr("Carnot efficiency eta");
	tr("Maximum heating power");
	tr("Pressure loss for Valve");
	tr("Maximum pressure head at point of minimal mass flow of pump");
	tr("Maximum electrical power at point of optimal operation of pump");
	tr("Set points are given as constant parameters");
	tr("Scheduled set point values");
	tr("Control temperature difference of this element");
	tr("Control temperature difference of the following element");
	tr("Control zone thermostat values");
	tr("Control mass flux");
	tr("PController");
	tr("PIController");
	tr("Kp-parameter");
	tr("Ki-parameter");
	tr("Kd-parameter");
	tr("Target temperature difference");
	tr("Target mass flux");
	tr("ID of zone containing thermostat");
	tr("ID of schedule");
	tr("Pipe with a single fluid volume and with heat exchange");
	tr("Pipe with a discretized fluid volume and heat exchange");
	tr("Distance between supply pipe and return pipe");
	tr("Distance between pipes and soil surface");
	tr("Dry density of the material.");
	tr("Specific heat capacity of the material.");
	tr("Thermal conductivity of the dry material.");
	tr("Building");
	tr("Mixer");
	tr("Source");
	tr("Outer diameter (not including optional insulation)");
	tr("Pipe wall thickness");
	tr("Pipe wall surface roughness");
	tr("Thermal conductivity of pipe wall");
	tr("Thickness of insulation around pipe");
	tr("Thermal conductivity of insulation");
	tr("If true, output files are written in binary format (the default, if flag is missing).");
	tr("If true, default output definitions for zones are created.");
	tr("If true, default output definitions for networks are created.");
	tr("Floor area of the zone");
	tr("Volume of the zone");
	tr("A window");
	tr("A door");
	tr("Some other component type");
	tr("Heating limit");
	tr("Cooling limit");
	tr("Pipe spacing");
	tr("Maximum fluid velocity");
	tr("Temperature difference between supply and return fluid temperature");
	tr("Ideal surface conditioning");
	tr("Water-based surface conditioning");
	tr("Air change rate");
	tr("Grid is visible");
	tr("None");
	tr("Fraction of area");
	tr("Constant width");
	tr("Frame width of the window");
	tr("Frame area fraction of the window");
	tr("Divider width of the window");
	tr("Divider area fraction of the window");
	tr("Divider material thickness.");
	tr("Frame material thickness.");
	tr("Standard globbed-layers model");
	tr("Thermal transmittance");
	tr("Incidence-angle dependent short wave transmittance across glazing system");
	tr("Upper limit for room air temperature.");
	tr("Lower limit for room air temperature.");
	tr("Upper limit for outside air temperature.");
	tr("Lower limit for outside air temperature.");
	tr("Temperature difference limit (inside - outside).");
	tr("Limit for wind speed .");
	tr("Global horizontal (upper) sensor setpoint value.");
	tr("Global north (upper) sensor setpoint value.");
	tr("Global east (upper) sensor setpoint value.");
	tr("Global south (upper) sensor setpoint value.");
	tr("Global west (upper) sensor setpoint value.");
	tr("Dead band value for all sensors.");
	tr("One global horizontal sensor.");
	tr("One global horizontal and for each direction (N, E, S, W) a vertical sensor.");
	tr("Thermostat tolerance heating and cooling mode");
	tr("Thermostat dead band (for digital controllers)");
	tr("Air temperature");
	tr("Operative temperature");
	tr("Analog");
	tr("Digital");
	tr("Heating limit");
	tr("Cooling limit (positive)");
	tr("Person loads");
	tr("Equipment loads");
	tr("Lighting loads");
	tr("Other internal loads");
	tr("Thermostat control");
	tr("Natural ventilation control");
	tr("Infiltration loads");
	tr("NaturalVentilation");
	tr("Heating/cooling loads");
}


QString KeywordListQt::Description( const std::string & category, int keywordId) { 

	std::string description = KeywordList::Description(category.c_str(), keywordId);
	return tr(description.c_str());

}

} // namespace
