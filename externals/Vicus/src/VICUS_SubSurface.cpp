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

#include "VICUS_SubSurface.h"

namespace VICUS {

SubSurface SubSurface::clone() const {
	SubSurface r(*this); // create new SubSurface with same unique ID
	Object & o = r;
	(Object&)r = o.clone(); // assign new ID only
	return r;
}


void SubSurface::updateColor() {
	if (m_subSurfaceComponentInstance == nullptr) {
		// no subsurface assigned -> dark gray
		m_color = QColor(64,64,64,255);
	}
	else {
		// TODO : depending on assigned subsurface type, select suitable color
		// for now always transparent blue
		m_color = QColor(96,96,255,128);
	}
}

} // namespace VICUS
