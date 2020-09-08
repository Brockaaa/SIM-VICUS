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

#ifndef NANDRAD_ZoneH
#define NANDRAD_ZoneH

#include <string>

#include <IBK_Parameter.h>
#include <IBK_IntPara.h>
#include <IBK_Path.h>

#include "NANDRAD_CodeGenMacros.h"
#include "NANDRAD_Constants.h"

namespace NANDRAD {

/*!	A zone defines a thermal zone/room with a single air temperature.

	The class Zone stores all properties needed to compute zone temperature from energy density (the conserved quantity).

	Zones can be either Constant or Active. For constant zones, the temperature is assumed to
	be fixed/predefined (given via parameter P_Temperature) whereas in Active zones the temperature
	is computed (i.e. included in the model's unknowns).
*/
class Zone {
public:

	/*! Type of zone. Defines whether zone is balanced and included in equation system. */
	enum type_t {
		ZT_Constant,				// Keyword: Constant		'Zone with constant/predefined temperatures. (schedule) '
		ZT_Active,					// Keyword: Active			'Zone described by a temperature node in space.'
		/// \todo research different models for ground temperature calculation
		ZT_Ground,					// Keyword: Ground			'Ground zone (calculates temperature based on standard).'
		NUM_ZT
	};

	/*! Parameters of a zone. */
	enum para_t {
		P_Temperature,				// Keyword: Temperature				[C]		'Temperature of the zone if set constant [C].'
		P_RelativeHumidity,			// Keyword: RelativeHumidity		[%]		'Relative humidity of the zone if set constant [%].'
		P_CO2Concentration,			// Keyword: CO2Concentration		[g/m3]	'CO2 concentration of the zone if set constant [g/m3].'
		P_Area,						// Keyword: Area					[m2]	'Net usage area of the ground floor [m2] (for area-related outputs and loads).'
		P_Volume,					// Keyword: Volume					[m3]	'Zone air volume [m3].'
		P_HeatCapacity,				// Keyword: HeatCapacity			[J/K]	'Extra heat capacity [J/K].'
		NUM_P
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	NANDRAD_READWRITE
	NANDRAD_COMPARE_WITH_ID

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Unique ID of the zone. */
	unsigned int				m_id = INVALID_ID;					// XML:A:required

	/*! Descriptive name of zone. */
	std::string					m_displayName;						// XML:A

	/*! Zone type (Constant, Active).
		\sa zoneType_t
	*/
	type_t						m_type = NUM_ZT;					// XML:A:required

	/*! Physical parameters describing the zone. */
	IBK::Parameter				m_para[NUM_P];						// XML:E

	/*! Optional schedule reference name for constant zones. */
	std::string					m_scheduleName;						// XML:E


	typedef std::pair<unsigned int, unsigned int>  viewFactorPair;
	/*! Optional: view factors for all inside interfaces of the current zone. */
	/// \todo viewfactor class read, write, etc... ToDo Katja
	std::vector<std::pair<viewFactorPair, double> >	m_viewFactors;

}; // Zone


} // namespace NANDRAD

#endif // NANDRAD_ZoneH
