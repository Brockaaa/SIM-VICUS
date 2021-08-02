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

#ifndef VICUS_MaterialLayerH
#define VICUS_MaterialLayerH

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"

#include <QString>

#include <vector>

#include <IBK_Flag.h>
#include <IBK_Parameter.h>

namespace VICUS {

/*! Stores data for a single material layer in a construction. */
class MaterialLayer {
public:

	// *** PUBLIC MEMBER FUNCTIONS ***

	/*! Default c'tor. */
	MaterialLayer() {}

	/*! Simple Constructor with thickness in [m] and material id. */
	MaterialLayer(double thickness, unsigned int id):
		m_matId(id),
		m_thickness(IBK::Parameter("Thickness", thickness, "m"))
	{}

	/*! Simple Constructor with thickness and material id. */
	MaterialLayer(IBK::Parameter thickness, unsigned int id):
		m_matId(id),
		m_thickness(thickness)
	{}


	VICUS_READWRITE

	/*! Inequality operator. */
	bool operator!=(const MaterialLayer & other) const { return (m_thickness != other.m_thickness || m_matId != other.m_matId);	}
	/*! Equality operator. */
	bool operator==(const MaterialLayer & other) const { return !operator!=(other); }

	// *** PUBLIC MEMBER VARIABLES ***

	/*! Unique ID of material. */
	unsigned int					m_matId = INVALID_ID;	// XML:A:required

	/*! Thickness of the material layer. */
	IBK::Parameter					m_thickness;			// XML:E:required
};

} // namespace VICUS


#endif // VICUS_MaterialLayerH
