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

#include "NANDRAD_InterfaceLongWaveEmission.h"

namespace NANDRAD {

bool InterfaceLongWaveEmission::operator!=(const InterfaceLongWaveEmission & other) const {
	// model comparison
	if (m_modelType != other.m_modelType) return true;
	for (int i=0; i<NUM_P; ++i)
		if (m_para[i] != other.m_para[i]) return true;
	return false; // not different
}


void InterfaceLongWaveEmission::checkParameters() const{
	// only check parameters if model is enable
	if (m_modelType == NUM_MT)
		return;

	m_para[P_Emissivity].checkedValue("---", "---",
									   0, true,
									   1, true,
									   "Long wave emissivity must between 0 and 1.");

}

} // namespace NANDRAD

