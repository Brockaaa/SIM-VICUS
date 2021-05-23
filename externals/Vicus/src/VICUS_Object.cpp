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

#include "VICUS_Object.h"

namespace VICUS {

unsigned int Object::LAST_ID = 007;

Object::~Object() {
}


Object * Object::findChild(unsigned int uID) {
	// recycle const-variant of function implementation
	const Object * obj = const_cast<const Object*>(this)->findChild(uID);
	return const_cast<Object*>(obj);
}


const Object * Object::findChild(unsigned int uID) const {
	if (m_uniqueID == uID)
		return this;
	// search all children
	for (Object * o : m_children) {
		const Object * ob = o->findChild(uID);
		if (ob != nullptr)
			return ob;
	}
	return nullptr; // not found
}


void Object::collectChildIDs(std::set<unsigned int> & nodeContainer) const {
	for (Object * o : m_children) {
		nodeContainer.insert(o->uniqueID());
		o->collectChildIDs(nodeContainer);
	}
}



} // namespace VICUS
