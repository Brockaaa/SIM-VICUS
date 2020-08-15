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

#include "NANDRAD_ConstructionType.h"

#include <IBK_Exception.h>

namespace NANDRAD {

bool ConstructionType::operator!=(const ConstructionType & other) const {
	if (m_id != other.m_id) return true;
	if (m_displayName != other.m_displayName) return true;
	if (m_materialLayers != other.m_materialLayers) return true;
	return  false;
}


void ConstructionType::checkParameters(const std::vector<Material> & materials) {
	FUNCID(ConstructionType::checkParameters);

	// process all material layers
	for (MaterialLayer & ml : m_materialLayers) {
		// valid layer thickness
		if (ml.m_thickness <= 0)
			throw IBK::Exception
	}

}

} // namespace NANDRAD
