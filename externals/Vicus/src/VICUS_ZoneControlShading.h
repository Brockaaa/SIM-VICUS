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

#ifndef VICUS_ZoneControlShadingH
#define VICUS_ZoneControlShadingH

#include <QColor>

#include <IBK_Parameter.h>

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"
#include "VICUS_AbstractDBElement.h"

namespace VICUS {

/*! Zone control parameters for dynamic shading. */
class ZoneControlShading : public AbstractDBElement {
public:

	/*! Basic parameters. */
	enum para_t {
		/*! Global horizontal (upper) sensor value. */
		P_GlobalHorizontal,				// Keyword: GlobalHorizontal		[W/m2]		'Global horizontal (upper) sensor setpoint value.'
		/*! Global north (upper) sensor value. */
		P_GlobalNorth,					// Keyword: GlobalNorth				[W/m2]		'Global north (upper) sensor setpoint value.'
		/*! Global east (upper) sensor value. */
		P_GlobalEast,					// Keyword: GlobalEast				[W/m2]		'Global east (upper) sensor setpoint value.'
		/*! Global south (upper) sensor value. */
		P_GlobalSouth,					// Keyword: GlobalSouth				[W/m2]		'Global south (upper) sensor setpoint value.'
		/*! Global west (upper) sensor value. */
		P_GlobalWest,					// Keyword: GlobalWest				[W/m2]		'Global west (upper) sensor setpoint value.'
		/*! Dead band value. */
		P_DeadBand,						// Keyword: DeadBand				[W/m2]		'Dead band value for all sensors.'

		NUM_P
	};

	/*! Categories.*/
	enum Category {
		C_GlobalHorizontalSensor,				// Keyword: GlobalHorizontalSensor					[-]		'One global horizontal sensor.'
		C_GlobalHorizontalAndVerticalSensors,	// Keyword: GlobalHorizontalAndVerticalSensors		[-]		'One global horizontal and for each direction (N, E, S, W) a vertical sensor.'

		NUM_C
	};

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE_OVERRIDE
	VICUS_COMPARE_WITH_ID

	/*! Checks if all parameters are valid. */
	bool isValid() const;

	/*! Comparison operator */
	ComparisonResult equal(const AbstractDBElement *other) const override;

	// *** PUBLIC MEMBER VARIABLES ***

	//:inherited	unsigned int					m_id = INVALID_ID;		// XML:A:required
	//:inherited	IBK::MultiLanguageString		m_displayName;			// XML:A
	//:inherited	QColor							m_color;				// XML:A

	/*! Notes. */
	IBK::MultiLanguageString		m_notes;								// XML:E

	/*! Data source. */
	IBK::MultiLanguageString		m_dataSource;							// XML:E

	/*! Category. */
	Category						m_category = NUM_C;						// XML:E:required

	/*! List of parameters. */
	IBK::Parameter					m_para[NUM_P];							// XML:E
};

}
#endif // VICUS_ZoneControlShadingH
